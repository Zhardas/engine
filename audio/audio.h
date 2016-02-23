#ifndef AUDIO_AUDIO_H_
#define AUDIO_AUDIO_H_

#include <XAudio2.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265359f
#endif
#define STREAMING_BUFFER_SIZE 44100
//44100/5
//#define DATA_SIZE STREAMING_BUFFER_SIZE/2
//65536*10
#define MAX_BUFFER_COUNT 3

class Audio {
 private:
  IXAudio2 *device_ = nullptr;
  IXAudio2SourceVoice *source_voice_ = nullptr;
  OggVorbis_File vorbis_file_;
  char buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];

  bool is_file_opened_ = false;
  bool is_running_ = false;
  bool is_paused_ = false;
  bool is_almost_done_ = false;
  bool is_done_ = false;
  bool loop_ = false;

  void ResetParams();

 public:
  DWORD current_read_buffer_ = 0;
  bool destroy_after_playback_ = false;

  Audio(IXAudio2 *parent);
  ~Audio();

  bool LoadSound(const char *szSoundFileName);

  // Volume
  void AlterVolume(float fltVolume);
  void GetVolume(float &fltVolume);

  // Controls
  bool Play(bool loop);
  void Stop();
  bool IsPlaying();
  void Pause();

  // Update
  void Update();

  // Samples
  double **GetSamples(double rate, int size);
  uint64_t GetPlayedSamples() {
    XAUDIO2_VOICE_STATE state;
    source_voice_->GetState(&state);
    return state.SamplesPlayed%total;
  }
  uint64_t total;
  uint64_t sets;
};


#endif // AUDIO_AUDIO_H_
