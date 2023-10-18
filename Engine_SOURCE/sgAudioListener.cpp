#include "sgAudioListener.h"
#include "sgTransform.h"
#include "sgGameObject.h"
#include "sgFmod.h"

namespace sg
{
	AudioListener::AudioListener()
		: Component(eComponentType::AudioListener)
	{

	}

	AudioListener::~AudioListener()
	{

	}

	void AudioListener::Initialize()
	{

	}

	void AudioListener::Update()
	{

	}

	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 forward = tr->Forward();
		Vector3 up = tr->Up();

		Vector3 vel = { 0.0f, 0.0f, 0.0f };
		//Fmod::Set3DListenerAttributes(&pos, &vel, &forward, &up);
	}

	void AudioListener::Render()
	{

	}
}