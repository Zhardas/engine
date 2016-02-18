#include <iostream>
#include "audio_manager.h"

AudioManager::AudioManager() {
  device_ = NULL;
  mastering_voice_ = NULL;

  flags_ = 0;

#ifdef DEBUG
  flags |= XAUDIO2_DEBUG_ENGINE;
#endif

  CoInitializeEx(NULL, COINIT_MULTITHREADED);
}

AudioManager::~AudioManager() {

  if (mastering_voice_ != NULL)
    mastering_voice_->DestroyVoice();
  SafeRelease(device_);
  while (!audio_list.empty()) delete audio_list.front(), audio_list.pop_front();
  CoUninitialize();
}

bool AudioManager::InitializeAudio() {
  HRESULT hr;
  return FAILED(hr = XAudio2Create(&device_, flags_)) ? false : !FAILED(
      hr = device_->CreateMasteringVoice(&mastering_voice_));

}

//Alter the volume up and down
void AudioManager::AlterVolume(float fltVolume) {
  if (mastering_voice_ == NULL)
    return;

  mastering_voice_->SetVolume(fltVolume);    //Playback device volume
}

//Return the current volume
void AudioManager::GetVolume(float &fltVolume) {
  if (mastering_voice_ == NULL)
    return;

  mastering_voice_->GetVolume(&fltVolume);
}

void AudioManager::Update() {
  std::list<Audio *> remove_list;
  for (auto audio : audio_list) {
    audio->Update();
    if (audio->destroy_after_playback_ && !audio->IsPlaying()) {
      remove_list.push_back(audio);
    }
  }
  for (auto removable : remove_list) {
    audio_list.remove(removable);
    delete removable;
  }
}

Audio *AudioManager::Generate() {
  Audio *audio = new Audio(device_);
  audio_list.push_back(audio);
  return audio;
}

void AudioManager::Remove(Audio *obj) {
  audio_list.remove(obj);
  delete obj;
}
