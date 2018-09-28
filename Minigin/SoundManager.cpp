#include "MiniginPCH.h"
#include "SoundManager.h"
//
//
//#include "MiniginPCH.h"
//#include "SoundManager.h"
//#include <sstream>
//
//SoundManager::SoundManager()
//	: m_pFMODSystem(nullptr),
//	m_FMODResult(FMOD_OK)
//{
//}
//
//void SoundManager::Destroy()
//{
//	if (m_pFMODSystem)
//		m_pFMODSystem->release();
//}
//
//void SoundManager::CreateSound(int soundId, const std::string& filePath, const FMOD_MODE& mode, bool isStream)
//{
//	auto it = m_pSounds.insert({ soundId, nullptr }).first;
//
//	if (it != m_pSounds.end()) {
//		if (isStream)
//			m_FMODResult = m_pFMODSystem->createStream(filePath.c_str(), mode, nullptr, &it->second);
//		else
//			m_FMODResult = m_pFMODSystem->createSound(filePath.c_str(), mode, nullptr, &it->second);
//		ErrorCheck(m_FMODResult);
//	}
//}
//
//void SoundManager::SetSoundMode(int soundId, const FMOD_MODE& mode)
//{
//	auto it = m_pSounds.find(soundId);
//
//	if (it != m_pSounds.end()) {
//		m_FMODResult = it->second->setMode(mode);
//		ErrorCheck(m_FMODResult);
//	}
//}
//
//void SoundManager::PlaySoundOnChannel(int soundId, int channelId, bool isPaused)
//{
//	auto soundIt = m_pSounds.find(soundId);
//	auto channelIt = m_pChannels.insert({ channelId, nullptr }).first;
//
//	if (soundIt != m_pSounds.end()) {
//		m_FMODResult = m_pFMODSystem->playSound(soundIt->second, nullptr, isPaused, &channelIt->second);
//		ErrorCheck(m_FMODResult);
//	}
//}
//
//void SoundManager::TogglePauseOnChannel(int channelId)
//{
//	auto it = m_pChannels.find(channelId);
//
//	if (it != m_pChannels.end()) {
//		bool isPaused;
//		m_FMODResult = it->second->getPaused(&isPaused);
//		ErrorCheck(m_FMODResult);
//
//		m_FMODResult = it->second->setPaused(!isPaused);
//		ErrorCheck(m_FMODResult);
//	}
//}
//
//void SoundManager::StopChannel(int channelId)
//{
//	auto it = m_pChannels.find(channelId);
//
//	if (it != m_pChannels.end()) {
//		m_FMODResult = it->second->stop();
//		ErrorCheck(m_FMODResult);
//	}
//}
//
//void SoundManager::ChangeVolumeOnChannel(int channelId, float amount, bool increase)
//{
//	auto it = m_pChannels.find(channelId);
//
//	if (it != m_pChannels.end()) {
//		float volume;
//		m_FMODResult = it->second->getVolume(&volume);
//		ErrorCheck(m_FMODResult);
//
//		increase ? volume += amount : volume -= amount;
//		//Clamp(volume, 1.0f, 0.0f);
//
//		m_FMODResult = it->second->setVolume(volume);
//		ErrorCheck(m_FMODResult);
//	}
//}
//
//void SoundManager::Initialize()
//{
//	unsigned int version;
//	int numdrivers;
//
//	FMOD_RESULT result = System_Create(&m_pFMODSystem);
//	ErrorCheck(result);
//	result = m_pFMODSystem->getVersion(&version);
//	ErrorCheck(result);
//
//	if (version < FMOD_VERSION) {
//		
//		return;
//	}
//
//	result = m_pFMODSystem->getNumDrivers(&numdrivers);
//	ErrorCheck(result);
//	if (numdrivers == 0) {
//		result = m_pFMODSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
//		ErrorCheck(result);
//	}
//	else {
//		result = m_pFMODSystem->init(32, FMOD_INIT_NORMAL, nullptr);
//		ErrorCheck(result);
//	}
//}
//
//bool SoundManager::ErrorCheck(const FMOD_RESULT& res)
//{
//	if (res != FMOD_OK) {
//		std::stringstream ss;
//		ss << "FMOD error! [" << res << "] " << FMOD_ErrorString(res) << std::endl;
//		
//		return false;
//	}
//	return true;
//}