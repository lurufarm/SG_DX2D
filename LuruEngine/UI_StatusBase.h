#pragma once
#include "Gobj_UI.h"

namespace sg
{
	class UI_StatusBase : public Gobj_UI
	{
	public:

		struct StatusSet
		{
			int charNum;
			class Gobj_Character* character;
			class Img_CharIcon* charIcon;
			class Img_BulletIcon* bulletIcon;
			class UI_CharBox* charBox;
			class Gobj_Font* Status;
		};

		UI_StatusBase();
		~UI_StatusBase();
		
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
		
		void MakeStatusSheet(class Gobj_Character* character);
		void StateUpdate();
		void SceneUpdate();

		bool GetStatusSheetEmpty() 
		{ 
			if (mStatuses.empty())
				return true;
			else
				return false;
		}

	private:

		//static class Transform* mTr;
		//static class MeshRenderer* mMr;

		static std::vector<StatusSet*> mStatuses;
		static class UI_FocusBoxes* mFocus;
		Scene* mScene;

	};
}
