#include "sgCollisionManager.h"
#include "sgSceneManager.h"
#include "sgScene.h"
#include "sgLayer.h"
#include "sgGameObject.h"
#include "sgCollider2D.h"

namespace sg
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};


	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComp<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState()
				!= GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComp<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;
				if (rightObj->GetState()
					!= GameObject::eState::Active)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체의 ID bool 값을 확인
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// 충돌 정보 가져오기
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// 충돌 O
			if (iter->second == false) // 최초 충돌일 때
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else // 충돌 중이었을 때
			{
				left->OnCollisionStay(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
		}
		else
		{	
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하다가 나갈 때
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}

	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{

#pragma region my code
		//VertexPos leftvertexes = MakeVertexPos(left);
		//VertexPos rightvertexes = MakeVertexPos(right);

		//Vector2 axis[4];
		//												  
		//axis[0] = leftvertexes.vertexPos[3] - leftvertexes.vertexPos[0];
		//axis[1] = leftvertexes.vertexPos[3] - leftvertexes.vertexPos[2];
		//axis[2] = rightvertexes.vertexPos[3] - rightvertexes.vertexPos[0];
		//axis[3] = rightvertexes.vertexPos[3] - rightvertexes.vertexPos[2];

		//float leftmin = 0;
		//float leftmax = 0;
		//float rightmin = 0;
		//float rightmax = 0;

		//std::vector<float> leftv;
		//std::vector<float> rightv;

		//for (size_t i = 0; i < 4; i++)
		//{
		//	leftv.clear();
		//	rightv.clear();
		//	for (size_t j = 0; j < 4; j++)
		//	{
		//		leftv.push_back(axis[i].Dot(leftvertexes.vertexPos[j]));
		//		rightv.push_back(axis[i].Dot(rightvertexes.vertexPos[j]));
		//	}

		//	leftmin = leftv[0];
		//	leftmax = leftv[0];
		//	rightmin = rightv[0];
		//	rightmax = rightv[0];

		//	for (size_t j = 0; j < 4; j++)
		//	{
		//		leftmin = min(leftmin, leftv[j]);
		//		rightmin = min(rightmin, rightv[j]);

		//		leftmax = max(leftmax, leftv[j]);
		//		rightmax = max(rightmax, rightv[j]);
		//	}

		//	if (leftmin < rightmin) // left가 왼쪽, right가 오른쪽인 경우
		//	{
		//		if (leftmax - rightmin <= 0)
		//			continue;
		//		else
		//			return false;
		//	}
		//	else if (leftmin > rightmin) // left가 오른쪽, right가 왼쪽인 경우
		//	{
		//		if (leftmin - rightmax <= 0)
		//			continue;
		//		else
		//			return false;
		//	}
		//}
		//return true;

#pragma endregion
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2

		Vector3 arrLocalPos[4] =
		{
			Vector3{-0.5f, 0.5f, 0.0f},
			Vector3{0.5f, 0.5f, 0.0f},
			Vector3{0.5f, -0.5f, 0.0f},
			Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* leftTr = left->GetOwner()->GetComp<Transform>();
		Transform* rightTr = right->GetOwner()->GetComp<Transform>();

		Matrix leftMatrix = leftTr->GetMatrix();
		Matrix rightMatrix = rightTr->GetMatrix();

		Vector3 Axis[4] = {};

		Vector3 leftScale = Vector3(left->GetCSize().x, left->GetCSize().y, 1.0f);
		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMatrix;

		Vector3 rightScale = Vector3(right->GetCSize().x, right->GetCSize().y, 1.0f);
		Matrix finalRight = Matrix::CreateScale(rightScale);
		finalRight *= rightMatrix;

		Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
		Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
		Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
		Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

		Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

		for (size_t i = 0; i < 4; i++)
		{
			Axis[i].z = 0.0f;
		}

		Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];
			float projDistance = 0.0f;
			for (size_t j = 0; j < 4; j++)
			{
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}
			
			if (projDistance < fabsf(centerDir.Dot(vA)))
				return false;
		}
		return true;
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}
		
		mMatrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}

}