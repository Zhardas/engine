#ifndef HEADACHE_AUDIO_H
#define HEADACHE_AUDIO_H

#include <XAudio2.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#define STREAMING_BUFFER_SIZE 65536*10
#define MAX_BUFFER_COUNT 3

class Audio {
private:
    IXAudio2 *device_;
    IXAudio2SourceVoice *source_voice_;
    OggVorbis_File vorbis_file_;
    char buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];
    DWORD current_read_buffer_;

    bool is_file_opened_;
    bool is_running_;
    bool is_paused_;
    bool is_almost_done_;
    bool is_done_;
    bool loop_;

    void ResetParams();

public:
    bool destroy_after_playback_;

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
};


#endif //HEADACHE_AUDIO_H
