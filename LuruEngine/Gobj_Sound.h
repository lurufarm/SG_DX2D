#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgAudioClip.h"
#include "..\Engine_SOURCE\sgAudioSource.h"

namespace sg
{
	class Gobj_Sound : public GameObject
	{
	public:
		Gobj_Sound();
		~Gobj_Sound();

		void Initialize();
		void Update();
		//void LateUpdate();

		void Play() { /*mPlay = true;  */mAc->Play(); }
		void Stop() { /*mPlay = false; */mAc->Stop(); }

		void SetSound(std::wstring source);
		void SetSoundLoop(bool value);

	private:
		AudioSource* mAc;
		std::shared_ptr<AudioClip> mClip;
		bool mPlay;
		bool mLoop;

	};
}
