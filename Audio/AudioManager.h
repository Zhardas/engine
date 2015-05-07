class AudioManager;

#ifndef HEADACHE_AUDIOMANAGER_H
#define HEADACHE_AUDIOMANAGER_H

#include <xaudio2.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <list>
#include "Audio.h"

//Safely release and delete objects
#define SafeRelease(pInterface) if(pInterface != NULL) {pInterface->Release(); pInterface=NULL;}
#define SafeDelete(pObject) if(pObject != NULL) {delete pObject; pObject=NULL;}

#define STREAMING_BUFFER_SIZE 65536*10
#define MAX_BUFFER_COUNT 3

class AudioManager {
private:
    IXAudio2 *pXAudio2;
    IXAudio2MasteringVoice *pMasteringVoice;
    std::list<Audio*> lAudio;

    UINT32 flags;
    char buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];
    //bool bFileOpened;
    OggVorbis_File vf;
    bool isRunning;
    bool boolIsPaused;
    bool bAlmostDone;
    bool bDone;
    bool bLoop;
    DWORD currentDiskReadBuffer;

    void resetParams();

public:
    AudioManager();

    ~AudioManager();

    bool InitializeAudio();

    bool LoadSound(const char *szSoundFilePath);

    bool Play(bool loop = false);

    bool IsPlaying();

    void Update();

    void Stop();

    void AlterVolume(float fltVolume);

    void GetVolume(float &fltVolume);

    void Pause();
};


#endif //HEADACHE_AUDIOMANAGER_H
