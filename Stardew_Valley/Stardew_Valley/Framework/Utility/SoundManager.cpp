#include "framework.h"
#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;
SoundManager::SoundManager()
{
	FMOD::System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
}

SoundManager::~SoundManager()
{
	for (auto pair : _soundTable)
	{
		pair.second.sound->release();
	}
}

void SoundManager::Update()
{
	_soundSystem->update();
}

void SoundManager::Add(string key, string file, bool bgm)
{
	if (_soundTable.count(key) > 0)
		return;
	SoundInfo info;
	if (bgm)
		_soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, OUT & info.sound);
	else
		_soundSystem->createStream(file.c_str(), FMOD_DEFAULT, nullptr, OUT & info.sound);

	assert(info.sound != nullptr);

	_soundTable[key] = info;
}

void SoundManager::Play(string key, float volume)
{
	if (_soundTable.count(key) == 0)
		return;

	_soundSystem->playSound(_soundTable[key].sound, nullptr, false, OUT & _soundTable[key].channel);
	_soundTable[key].channel->setVolume(volume);

	if (_soundTable[key].channel == nullptr)
		return;
}

void SoundManager::Stop(string key)
{
	if (_soundTable.count(key) == 0)
		return;
	if (_soundTable[key].channel == nullptr)
		return;

	_soundTable[key].channel->stop();
}

void SoundManager::Pause(string key)
{
	if (_soundTable.count(key) == 0)
		return;
	if (_soundTable[key].channel == nullptr)
		return;
	_soundTable[key].channel->setPaused(true);
}

void SoundManager::Resume(string key)
{
	if (_soundTable.count(key) == 0)
		return;
	if (_soundTable[key].channel == nullptr)
		return;
	_soundTable[key].channel->setPaused(false);
}

void SoundManager::SetVolume(string key, float volume)
{
	if (_soundTable.count(key) == 0)
		return;
	if (_soundTable[key].channel == nullptr)
		return;
	if (volume < 0.0f)
		volume = 0.0f;
	if (volume > 2.0f)
		volume = 2.0f;

	_soundTable[key].channel->setVolume(volume);
}

bool SoundManager::IsPlayingSound(string key)
{
	if (_soundTable.count(key) == 0)
		return false;
	if (_soundTable[key].channel == nullptr)
		return false;

	bool isPlay = false;
	_soundTable[key].channel->isPlaying(OUT & isPlay);

	return isPlay;
}
