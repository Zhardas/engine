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

    //LogInfo("<li>Audio created OK");
}

AudioManager::~AudioManager() {

    if (mastering_voice_ != NULL)
        mastering_voice_->DestroyVoice();

    SafeRelease(device_);

    while (!audio_list.empty()) delete audio_list.front(), audio_list.pop_front();

    CoUninitialize();

    //LogInfo("<li>Audio destroyed OK");
}

bool AudioManager::InitializeAudio() {
    HRESULT hr;
    return FAILED(hr = XAudio2Create(&device_, flags_)) ? false : !FAILED(hr = device_->CreateMasteringVoice(&mastering_voice_));

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
    //TODO: Make this cleaner
    bool bDel = false;
    Audio* del;
    for (Audio *a : audio_list) {
        a->Update();
        if(a->destroy_after_playback_ && !a->IsPlaying()){
            del = a;
            bDel = true;
        }
    }
    if(bDel){
        audio_list.remove(del);
        delete del;
    }
}

Audio *AudioManager::Generate() {
    Audio *audio = new Audio(device_);
    audio_list.push_back(audio);
    return audio;
}
