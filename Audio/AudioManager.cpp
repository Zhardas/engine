#include <iostream>
#include "AudioManager.h"

AudioManager::AudioManager() {
    pXAudio2 = NULL;
    pMasteringVoice = NULL;

    flags = 0;

#ifdef DEBUG
        flags |= XAUDIO2_DEBUG_ENGINE;
    #endif

    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    //LogInfo("<li>Audio created OK");
}

AudioManager::~AudioManager() {

    if (pMasteringVoice != NULL)
        pMasteringVoice->DestroyVoice();

    SafeRelease(pXAudio2);

    CoUninitialize();

    //LogInfo("<li>Audio destroyed OK");
}

bool AudioManager::InitializeAudio() {
    HRESULT hr;
    return FAILED(hr = XAudio2Create(&pXAudio2, flags)) ? false : !FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice));

}

//Alter the volume up and down
void AudioManager::AlterVolume(float fltVolume) {
    if (pMasteringVoice == NULL)
        return;

    pMasteringVoice->SetVolume(fltVolume);    //Playback device volume
}

//Return the current volume
void AudioManager::GetVolume(float &fltVolume) {
    if (pMasteringVoice == NULL)
        return;

    pMasteringVoice->GetVolume(&fltVolume);
}

void AudioManager::Update() {
    for (Audio *a : lAudio) {
        a->Update();
    }
}

Audio *AudioManager::Generate() {
    Audio *audio = new Audio(pXAudio2);
    lAudio.push_back(audio);
    return audio;
}
