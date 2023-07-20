#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgMaterial.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "Tile_Image.h"
#define TILE_SIZE_X 18
#define TILE_SIZE_Y 18
#define TILE_SIZE_Z 1

namespace sg
{


	class Tile : public GameObject
	{
	public:
		Tile();
		Tile(Vector3 pos);
		~Tile();

		void InitializeTile(std::shared_ptr<Texture> atlas, int index);
		void SetIndex(int index);

		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		UINT X() { return mX; }
		UINT Y() { return mY; }
		UINT Z() { return mZ; }

		UINT Index() { return mIndex; }

		renderer::MyCB mCB;


	private:

		class Transform* mTr;
		class MeshRenderer* mMr;
		class Collider2D* mCol;

		std::shared_ptr<Texture> mAtlas;
		UINT mIndex;
		UINT mX;
		UINT mY;
		UINT mZ;


	};
}
