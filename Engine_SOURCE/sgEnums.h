#pragma once


namespace sg::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		MeshRenderer,
		Collider2D,
		Animator,
		Mesh,
		Particle,
		Script,
		Light,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Grid,
		BGImg,
		Tile,
		InteractableObject,
		Monster_BulletBehindMonster,
		Monster,
		Monster_Bullet,
		Monster_Bullet2,
		Player,
		Effect,
		Player_Bullet,
		Player_Beam,
		Monster_Effect,
		Player_Effect,
		Light,
		Item,
		UI,
		UI_Box,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Mesh,
		Shader,
		Material,
		Tile_Image,
		Animation,
		ComputeShader,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eBulletType
	{
		Cheese,
		Lucy,
		Robo,
		End,
	};
	
	enum class eMProjType
	{
		PoisonOrb,
		EntRock,
		Basic,
		Basic_RandDir,
		Basic_NearCardinalDir,
		Basic_Dir,
		BloodSpit,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}