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
		Effect,
		Monster,
		Monster_Bullet,
		Monster_Bullet2,
		Player,
		Monster_Effect,
		Player_Bullet,
		Player_Effect,
		Light,
		UI,
		UI_Box,
		End = 16,
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
		End,
	};
	
	enum class eMProjType
	{
		PoisonOrb,
		EntRock,
		Basic,
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