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
		Monster,
		Monster_Bullet,
		Player,
		Player_Bullet,
		Effect,
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