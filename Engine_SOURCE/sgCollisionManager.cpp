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
				if (mMatrix[row] == true)
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
		// �� �浹ü�� ID bool ���� Ȯ��
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// �浹 ���� ��������
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// �浹 O
			if (iter->second == false) // ���� �浹�� ��
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
			}
			else // �浹 ���̾��� ��
			{
				left->OnCollisionStay(right);
				right->OnCollisionEnter(left);
			}
		}
		else
		{	
			// �浹 X
			if (iter->second == true)
			{
				// �浹�ϴٰ� ���� ��
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
		}

	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		struct verticePos
		{
			Vector2 verticePos[4];
		};

		Transform* leftTr = left->GetOwner()->GetComp<Transform>();
		Transform* rightTr = right->GetOwner()->GetComp<Transform>();

		Vector3 leftPos = leftTr->GetPosition();
		Vector3 rightPos = rightTr->GetPosition();
		Vector3 leftScale = leftTr->GetScale();
		Vector3 rightScale = rightTr->GetScale();
		float leftRot = leftTr->GetRotation().z;
		float rightRot = rightTr->GetRotation().z;


		verticePos leftvertices;
		verticePos rightvertices;

		leftvertices.verticePos[0]
			= Vector2((leftPos.x - leftScale.x / 2) * cos(leftRot) - (leftPos.y + leftScale.y / 2) * sin(leftRot)
				, (leftPos.x - leftScale.x / 2) * sin(leftRot) + (leftPos.y + leftScale.y / 2) * cos(leftRot));
		leftvertices.verticePos[1]
			= Vector2((leftPos.x + leftScale.x / 2) * cos(leftRot) - (leftPos.y + leftScale.y / 2) * sin(leftRot)
				, (leftPos.x + leftScale.x / 2) * sin(leftRot) + (leftPos.y + leftScale.y / 2) * cos(leftRot));
		leftvertices.verticePos[2]
			= Vector2((leftPos.x + leftScale.x / 2) * cos(leftRot) - (leftPos.y - leftScale.y / 2) * sin(leftRot)
				, (leftPos.x + leftScale.x / 2) * sin(leftRot) + (leftPos.y - leftScale.y / 2) * cos(leftRot));
		leftvertices.verticePos[3]
			= Vector2((leftPos.x - leftScale.x / 2) * cos(leftRot) - (leftPos.y - leftScale.y / 2) * sin(leftRot)
				, (leftPos.x - leftScale.x / 2) * sin(leftRot) + (leftPos.y - leftScale.y / 2) * cos(leftRot));


		rightvertices.verticePos[0]
			= Vector2((rightPos.x - rightScale.x / 2) * cos(rightRot) - (rightPos.y + rightScale.y / 2) * sin(rightRot)
				, (rightPos.x - rightScale.x / 2) * sin(rightRot) + (rightPos.y + rightScale.y / 2) * cos(rightRot));
		rightvertices.verticePos[1]
			= Vector2((rightPos.x + rightScale.x / 2) * cos(rightRot) - (rightPos.y + rightScale.y / 2) * sin(rightRot)
				, (rightPos.x + rightScale.x / 2) * sin(rightRot) + (rightPos.y + rightScale.y / 2) * cos(rightRot));
		rightvertices.verticePos[2]
			= Vector2((rightPos.x + rightScale.x / 2) * cos(rightRot) - (rightPos.y - rightScale.y / 2) * sin(rightRot)
				, (rightPos.x + rightScale.x / 2) * sin(rightRot) + (rightPos.y - rightScale.y / 2) * cos(rightRot));
		rightvertices.verticePos[3]
			= Vector2((rightPos.x - rightScale.x / 2) * cos(rightRot) - (rightPos.y - rightScale.y / 2) * sin(rightRot)
				, (rightPos.x - rightScale.x / 2) * sin(rightRot) + (rightPos.y - rightScale.y / 2) * cos(rightRot));


		Vector2 axis[4] = {};
		axis[0] = leftvertices.verticePos[3] - leftvertices.verticePos[2];
		axis[1] = leftvertices.verticePos[3] - leftvertices.verticePos[0];
		axis[2] = rightvertices.verticePos[3] - rightvertices.verticePos[2];
		axis[3] = rightvertices.verticePos[3] - rightvertices.verticePos[0];

		float leftmin = 0;
		float leftmax = 0;
		float rightmin = 0;
		float rightmax = 0;

		std::vector<float> leftv;
		std::vector<float> rightv;

		for (size_t i = 0; i < 4; i++)
		{

			leftv.clear();
			rightv.clear();
			for (size_t j = 0; j < 4; j++)
			{
				float a = axis[i].Dot(leftvertices.verticePos[j]);
				float b = axis[i].Dot(rightvertices.verticePos[j]);
				//leftv.push_back(axis[i].Dot(leftvertices.verticePos[j]));
				//rightv.push_back(axis[i].Dot(rightvertices.verticePos[j]));
				leftv.push_back(a);
				rightv.push_back(b);
			}

			leftmin = leftv[0];
			leftmax = leftv[0];
			rightmin = rightv[0];
			rightmax = rightv[0];

			for (size_t j = 0; j < 4; j++)
			{
				leftmin = min(leftmin, leftv[j]);
				rightmin = min(rightmin, rightv[j]);

				leftmax = max(leftmax, leftv[j]);
				rightmax = max(rightmax, rightv[j]);
			}

			if (leftmin < rightmin) // left�� ����, right�� �������� ���
			{
				if (leftmax - rightmin < 0)
					continue;
				else
					return false;
			}
			else if (leftmin > rightmin) // left�� ������, right�� ������ ���
			{
				if (leftmin - rightmax < 0)
					continue;
				else
					return false;
			}
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