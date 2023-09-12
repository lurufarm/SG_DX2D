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
		Monster_Bullet2,
		Player,
		Effect,
		Monster_Effect,
		Player_Bullet,
		Player_Beam,
		Player_Effect,
		Light,
		Item,
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
		Robo,
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