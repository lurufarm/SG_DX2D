#include "sgCamera.h"
#include "sgApplication.h"
#include "sgRenderer.h"
#include "sgSceneManager.h"
#include "sgGameObject.h"

#include "sgTransform.h"
#include "sgMeshRenderer.h"

extern sg::Application application;

namespace sg
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	bool CompareZSort(GameObject* a, GameObject* b)
	{
		float aZPos = a->GetComp<Transform>()->GetPosition().z;
		float bZPos = b->GetComp<Transform>()->GetPosition().z;
		
		if (aZPos <= bZPos)
			return false;

		return true;
	}

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::OrthoGraphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(260.0f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentGameObjects{}
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
	{
		EnableLayerMask();
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
	}
	void Camera::Update()
	{
	}
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);

		RegisterCameraInRenderer();
	}
	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		AlphaSortGameObjects();
		ZSortTransparencyGameObjects();

		RenderOpaque();
		
		DisableDepthStencilState();

		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}
	bool Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		// View Translate Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// View Rotate Matrix
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 forward = tr->Forward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = forward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = forward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = forward.z;
		mView *= viewRotate;

		return true;
	}
	bool Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		mAspectRatio = width / height;

		if (type == eProjectionType::OrthoGraphic)
		{
			float OrthoGraphicRatio = mSize / 1000.0f;
			width *= OrthoGraphicRatio;
			height *= OrthoGraphicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}

		return true;
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	void Camera::TurnLayerMask(eLayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}
	void Camera::AlphaSortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		// Alpha Sorting
		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i])
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				const std::vector<GameObject*> gameObjs
					= layer.GetGameObjects();
				// layer에 있는 게임 오브젝트들을 가져온다.
				DivideAlphaBlendGameObjects(gameObjs);
			}
		}
		
	}
	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(mCutOutGameObjects.begin()
			, mCutOutGameObjects.end()
			, CompareZSort);

		std::sort(mTransparentGameObjects.begin()
			, mTransparentGameObjects.end()
			, CompareZSort);
	}
	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs)
	{
		for (GameObject* obj : gameObjs)
		{
			// MeshRenderer가 없는 오브젝트는 걸러준다.
			MeshRenderer* mr = obj->GetComp<MeshRenderer>();
			
			if (mr == nullptr)
				continue;
			else
			{
				std::shared_ptr<Material> mt = mr->GetMaterial();
				eRenderingMode mode = mt->GetRenderingMode();

				switch (mode)
				{
				case sg::graphics::eRenderingMode::Opaque:
					mOpaqueGameObjects.push_back(obj);
					break;
				case sg::graphics::eRenderingMode::CutOut:
					mCutOutGameObjects.push_back(obj);
					break;
				case sg::graphics::eRenderingMode::Transparent:
					mTransparentGameObjects.push_back(obj);
					break;
				case sg::graphics::eRenderingMode::End:
					break;
				default:
					break;
				}
			}
		}
	}
	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : mOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}
	void Camera::RenderCutOut()
	{
		for (GameObject* gameObj : mCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}
	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : mTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->GetState()
				!= GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}
	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::Less];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
}