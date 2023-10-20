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
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		Grid,
		BG,
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
		AudioClip,
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
		Szila,
		End,
	};
	
	enum class eMProjType
	{
		PoisonOrb,
		LightningOrb,
		WhirlWind,
		EntRock,
		MummyBomb,
		Spear,
		BigOrb,
		Basic,
		Basic_RandDir,
		Basic_NearCardinalDir,
		Basic_Dir,
		Fire,
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