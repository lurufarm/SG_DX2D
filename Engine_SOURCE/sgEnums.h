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
		Player,
		Player_Bullet,
		Effect,
		Light,
		UI,
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
		Basic,
		Curved,
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