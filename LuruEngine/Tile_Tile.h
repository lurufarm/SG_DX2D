#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgMaterial.h"
#define TILE_SIZE_X 18
#define TILE_SIZE_Y 18
#define TILE_SIZE_Z 0

namespace sg
{


	class Tile : public GameObject
	{
	public:
		Tile();
		Tile(Vector3 pos);
		~Tile();

		void InitializeTile(std::shared_ptr<Material> atlas, int index);
		void SetIndex(int index);

		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		UINT X() { return mX; }
		UINT Y() { return mY; }
		UINT Z() { return mZ; }

		UINT Index() { return mIndex; }

	private:

		std::shared_ptr<Material> mAtlas;
		UINT mIndex;
		UINT mX;
		UINT mY;
		UINT mZ;

	};
}
