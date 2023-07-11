#pragma once


namespace sg::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		MeshRenderer,
		Collider2D,
		Mesh,
		Particle,
		Script,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Grid,
		BGImg,
		InteractableObject,
		Player,
		Monster,
		UI,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Mesh,
		Shader,
		Material,
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
}