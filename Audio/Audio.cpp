//
// Created by Owner on 7.05.2015.
//

#include "Audio.h"

Audio::Audio() {

}

Audio::~Audio() {
    if (pSourceVoice != NULL) {
        pSourceVoice->Stop(0);
        pSourceVoice->DestroyVoice();
    }
}
