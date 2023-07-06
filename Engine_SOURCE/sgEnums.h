#pragma once


namespace sg::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Particle,
		MeshRenderer,
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
}