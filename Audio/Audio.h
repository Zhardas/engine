#ifndef HEADACHE_AUDIO_H
#define HEADACHE_AUDIO_H
#include <XAudio2.h>

class Audio {
private:
    IXAudio2SourceVoice* pSourceVoice;
public:
    Audio();
    ~Audio();
};


#endif //HEADACHE_AUDIO_H
