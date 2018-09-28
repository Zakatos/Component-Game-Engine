#pragma once
//
//#include <map>
//#include "Singleton.h"
//
//class SoundManager final : public Singleton<SoundManager>
//{
//public:
//	SoundManager();
//	~SoundManager() = default;
//
//	void Initialize();
//	void Destroy();
//	
//	static bool ErrorCheck(const FMOD_RESULT& res);
//	FMOD::System* GetSystem() const { return m_pFMODSystem; }
//
//	void CreateSound(int soundId, const std::string& filePath, const FMOD_MODE& mode = FMOD_DEFAULT, bool isStream = false);
//	void SetSoundMode(int soundId, const FMOD_MODE& mode);
//
//	void PlaySoundOnChannel(int soundId, int channelId, bool isPaused = false);
//	void TogglePauseOnChannel(int channelId);
//	void StopChannel(int channelId);
//	void ChangeVolumeOnChannel(int channelId, float amount, bool increase = true);
//	
//private:
//	FMOD::System* m_pFMODSystem;
//	FMOD_RESULT m_FMODResult;
//
//	std::map<int, FMOD::Sound*> m_pSounds;
//	std::map<int, FMOD::Channel*> m_pChannels;
//};
