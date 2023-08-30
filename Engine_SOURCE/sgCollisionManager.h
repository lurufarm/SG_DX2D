#pragma once
#include "LuruEngine.h"

namespace sg
{
#define LAYER_MAX (UINT)eLayerType::End
	using namespace enums;

	class Collider2D;
	class CollisionManager
	{
	public:
		union ColliderID
		{
			struct
			{
				UINT left;
				UINT right;
			};
			UINT64 id;
		};

		static void Initialize();
		static void Update();
		static void LayerCollision(eLayerType left, eLayerType right);
		static void ColliderCollision(Collider2D* left, Collider2D* right);
		static bool Intersect(Collider2D* left, Collider2D* right);

		static void SetLayer(eLayerType left, eLayerType right, bool enable);
		static void Clear();

		// ¼º°æ
		//struct VertexPos
		//{
		//	Vector2 vertexPos[4];
		//};
		//static VertexPos MakeVertexPos(Collider2D* col)
		//{
		//	Vector3 colPos = col->GetOwner()->GetComp<Transform>()->GetPosition()/*GetCPosition()*/;
		//	Vector3 colScale = col->GetCScale();
		//	float colRotation = col->GetOwner()->GetComp<Transform>()->GetRotation().z;

		//	VertexPos vertexpos = {};

		//	vertexpos.vertexPos[0]
		//		= Vector2((colPos.x - colScale.x / 2) * cos(colRotation) - (colPos.y + colScale.y / 2) * sin(colRotation)
		//			, (colPos.x - colScale.x / 2) * sin(colRotation) + (colPos.y + colScale.y / 2) * cos(colRotation));
		//	vertexpos.vertexPos[1]
		//		= Vector2((colPos.x + colScale.x / 2) * cos(colRotation) - (colPos.y + colScale.y / 2) * sin(colRotation)
		//			, (colPos.x + colScale.x / 2) * sin(colRotation) + (colPos.y + colScale.y / 2) * cos(colRotation));
		//	vertexpos.vertexPos[2]
		//		= Vector2((colPos.x + colScale.x / 2) * cos(colRotation) - (colPos.y - colScale.y / 2) * sin(colRotation)
		//			, (colPos.x + colScale.x / 2) * sin(colRotation) + (colPos.y - colScale.y / 2) * cos(colRotation));
		//	vertexpos.vertexPos[3]
		//		= Vector2((colPos.x - colScale.x / 2) * cos(colRotation) - (colPos.y - colScale.y / 2) * sin(colRotation)
		//			, (colPos.x - colScale.x / 2) * sin(colRotation) + (colPos.y - colScale.y / 2) * cos(colRotation));
		//	
		//	return vertexpos;
		//}

		//static std::vector<Vector2> MakeAxis(VertexPos vPos)
		//{
		//	std::vector<Vector2> axis;

		//	axis.push_back(vPos.vertexPos[3] - vPos.vertexPos[2]);
		//	axis.push_back(vPos.vertexPos[3] - vPos.vertexPos[0]);

		//	return axis;
		//}

	private:
		static std::bitset<LAYER_MAX> mMatrix[LAYER_MAX];
		static std::map<UINT64, bool> mCollisionMap;
	};
}
