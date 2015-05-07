#ifndef HEADACHE_AUDIO_H
#define HEADACHE_AUDIO_H

#include <XAudio2.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#define STREAMING_BUFFER_SIZE 65536*10
#define MAX_BUFFER_COUNT 3

class Audio {
private:
    IXAudio2 *am_xaudio2;
    IXAudio2SourceVoice *pSourceVoice;
    bool bFileOpened;
    OggVorbis_File vf;
    char buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];
    DWORD currentDiskReadBuffer;

    bool isRunning;
    bool boolIsPaused;
    bool bAlmostDone;
    bool bDone;
    bool bLoop;

    void ResetParams();

public:
    Audio(IXAudio2 *parent);

    ~Audio();

    bool LoadSound(const char *szSoundFileName);

    void AlterVolume(float fltVolume);

    void GetVolume(float &fltVolume);

    bool Play(bool loop);

    void Stop();

    bool IsPlaying();

    void Pause();

    void Update();

    bool destroy_after_playback;
};


#endif //HEADACHE_AUDIO_H
