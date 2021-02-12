#include <iostream>

#include "AudioSystem.h"

using namespace freebird;

float gameTime;

void InitSound()
{
	AudioEngine& engine = AudioEngine::Instance();
	engine.Init();
	engine.LoadBank("Master");
	engine.LoadBus("MusicBus", "{a5b53ded-d7b3-4e6b-a920-0b241ef6f268}");

	AudioEvent& music = engine.CreateSoundEvent("music", "{b56cb9d2-1d47-4099-b80e-7d257b99a823}"); //Mii song
}

void Update(float dt)
{
	//Increment game time
	gameTime += dt;

	AudioEngine& engine = AudioEngine::Instance();

	//Get ref to music
	AudioEvent& music = engine.GetEvent("music");

	//Get ref to bus
	AudioBus& musicBus = engine.GetBus("MusicBus");

	engine.Update();
}

void Shutdown()
{
	AudioEngine::Instance().Shutdown();
}