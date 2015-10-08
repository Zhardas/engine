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

class AudioManager {
 private:
  IXAudio2 *device_;
  IXAudio2MasteringVoice *mastering_voice_;
  std::list<Audio *> audio_list;
  UINT32 flags_;

 public:
  AudioManager();

  ~AudioManager();

  bool InitializeAudio();

  void Update();

  void AlterVolume(float fltVolume);

  void GetVolume(float &fltVolume);

  Audio *Generate();
};


#endif //HEADACHE_AUDIOMANAGER_H
