#include "Gobj_Sound.h"

namespace sg
{
	Gobj_Sound::Gobj_Sound()
	{
		mAc = AddComp<AudioSource>();
		Gobj_Sound::Initialize();
	}
	Gobj_Sound::~Gobj_Sound()
	{
	}
	void Gobj_Sound::Initialize()
	{
		mPlay = false;
		mLoop = false;
		mClip = nullptr;
	}
	void Gobj_Sound::Update()
	{
		//mAc->SetClip(mClip);
		//if (mPlay)
		//	mAc->Play();
		//else
		//	mAc->Stop();
		//mAc->SetLoop(mLoop);

		GameObject::Update();
	}
	void Gobj_Sound::SetSound(std::wstring source)
	{
		mClip = Resources::Find<AudioClip>(source);
		mAc->SetClip(mClip);
	}
}