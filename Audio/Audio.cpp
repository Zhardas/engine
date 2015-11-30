#include <iostream>
#include "Audio.h"

Audio::Audio(IXAudio2 *parent) {
  device_ = parent;
  destroy_after_playback_ = false;
  double_samples_ = new double[samples_count_];
}

Audio::~Audio() {
  if (source_voice_ != NULL) {
    source_voice_->Stop(0);
    source_voice_->FlushSourceBuffers();
    source_voice_->DestroyVoice();
  }
  if (is_file_opened_)
    ov_clear(&vorbis_file_);
}

bool Audio::LoadSound(const char *szSoundFileName) {
  char strSoundPath[MAX_PATH];
  //Get the our applications "sounds" directory.
  GetCurrentDirectory(MAX_PATH, strSoundPath);
  strncat(strSoundPath, "\\resources\\sounds\\", MAX_PATH);
  strncat(strSoundPath, szSoundFileName, MAX_PATH);

  //Convert the path to unicode.
  //MultiByteToWideChar(CP_ACP, 0, strSoundPath, -1, wstrSoundPath, MAX_PATH);

  //If we already have a file open then kill the current voice setup
  if (is_file_opened_) {
    source_voice_->Stop(0);
    source_voice_->FlushSourceBuffers();
    source_voice_->DestroyVoice();

    ov_clear(&vorbis_file_);

    ResetParams();
  }

  FILE *f;
  //errno_t err;

  //if ((err  = fopen_s( &f, strSoundPath, "rb" )) != 0)
  if (!(f = fopen(strSoundPath, "rb"))) {
    std::cout << "\nERROR: failed to open audio file " << strSoundPath;
    //LogError("<li>Failed to open audio: %s", strSoundPath);

    /*
    char szBuffer[MAX_PATH];
     _strerror_s(szBuffer, MAX_PATH, NULL);
     */
    //LogError("<li>Reason: %s", szBuffer);
    return false;
  }

  //ov_open(f, &vf, NULL, 0); //Windows does not like this function so we use ov_open_callbacks() instead
  if (ov_open_callbacks(f, &vorbis_file_, NULL, 0, OV_CALLBACKS_DEFAULT) < 0) {
    fclose(f);
    return false;
  } else {
    is_file_opened_ = true;
  }

  //The vorbis_info struct keeps the most of the interesting format info
  vorbis_info *vi = ov_info(&vorbis_file_, -1);

  //Set the wave format
  WAVEFORMATEX wfm;
  memset(&wfm, 0, sizeof(wfm));

  wfm.cbSize = sizeof(wfm);
  wfm.nChannels = static_cast<WORD>(vi->channels);
  wfm.wBitsPerSample = 16;                    //Ogg vorbis is always 16 bit
  wfm.nSamplesPerSec = static_cast<DWORD>(vi->rate);
  wfm.nAvgBytesPerSec = wfm.nSamplesPerSec * wfm.nChannels * 2;
  wfm.nBlockAlign = static_cast<WORD>(2 * wfm.nChannels);
  wfm.wFormatTag = 1;

  DWORD pos = 0;
  int sec = 0;
  int ret = 1;

  memset(&buffers[current_read_buffer_], 0, sizeof(buffers[current_read_buffer_]));

  //Read in the bits
  while (ret && pos < STREAMING_BUFFER_SIZE) {
    ret = ov_read(&vorbis_file_,
                  buffers[current_read_buffer_] + pos,
                  static_cast<int>(STREAMING_BUFFER_SIZE - pos),
                  0,
                  2,
                  1,
                  &sec);
    pos += ret;
  }

  HRESULT hr;

  //Create the source voice
  if (FAILED(hr = device_->CreateSourceVoice(&source_voice_, &wfm))) {
    //LogError("<li>Error %#X creating source voice", hr);
    return false;
  }

  //Submit the wave sample data using an XAUDIO2_BUFFER structure
  XAUDIO2_BUFFER buffer = {0};
  buffer.pAudioData = (BYTE *) &buffers[current_read_buffer_];
  buffer.AudioBytes = STREAMING_BUFFER_SIZE;

  if (FAILED(hr = source_voice_->SubmitSourceBuffer(&buffer))) {
    //LogError("<li>Error %#X submitting source buffer", hr);
    return false;
  }

  current_read_buffer_++;

  return true;
}

void Audio::ResetParams() {
  is_file_opened_ = false;
  is_running_ = false;
  is_paused_ = false;
  loop_ = false;
  is_done_ = false;
  is_almost_done_ = false;
  current_read_buffer_ = 0;
}

bool Audio::Play(bool loop) {
  if (source_voice_ == NULL) {
    //LogError("<li>Error: pSourceVoice NOT created");
    return false;
  }

  HRESULT hr;

  if (FAILED(hr = source_voice_->Start(0))) {
    //LogError("<li>Error %#X submitting source buffer", hr);
  }

  XAUDIO2_VOICE_STATE state;
  source_voice_->GetState(&state);
  is_running_ = (state.BuffersQueued > 0) != 0;

  loop_ = loop;
  is_done_ = false;
  is_almost_done_ = false;
  is_paused_ = false;

  return is_running_;
}

void Audio::Stop() {
  if (source_voice_ == NULL)
    return;

  // TODO (Zhardas): Check if anything needs to be done here.
  //XAUDIO2_FLUSH_BUFFERS according to MSDN is meant to flush the buffers after the voice is stopped
  //unfortunately the March 2008 release of the SDK does not include this parameter in the xaudio files
  //and I have been unable to ascertain what its value is
  //pSourceVoice->Stop(XAUDIO2_FLUSH_BUFFERS);
  //pSourceVoice->Stop(0);
  //pSourceVoice->FlushSourceBuffers();

  is_paused_ = false;
  is_running_ = false;
}

bool Audio::IsPlaying() {
  /*XAUDIO2_VOICE_STATE state;
  pSourceVoice->GetState(&state);
  return (state.BuffersQueued > 0) != 0;*/

  return is_running_;
}

//Alter the volume up and down
void Audio::AlterVolume(float fltVolume) {
  if (source_voice_ == NULL)
    return;

  source_voice_->SetVolume(fltVolume);         //Current voice volume
  //pMasteringVoice->SetVolume(fltVolume);    //Playback device volume
}

//Return the current volume
void Audio::GetVolume(float &fltVolume) {
  if (source_voice_ == NULL)
    return;

  source_voice_->GetVolume(&fltVolume);
  //pMasteringVoice->GetVolume(&fltVolume);
}

void Audio::Pause() {
  if (source_voice_ == NULL)
    return;

  if (is_paused_) {
    source_voice_->Start(0); // Unless we tell it otherwise the voice resumes playback from its last position
    is_paused_ = false;
  } else {
    source_voice_->Stop(0);
    is_paused_ = true;
  }
}

void Audio::Update() {
  if (source_voice_ == nullptr)
    return;

  if (!is_running_)
    return;

  if (is_done_ && !loop_) {
    Stop();
  }

  // Do we have any free buffers?
  XAUDIO2_VOICE_STATE state;
  source_voice_->GetState(&state);

  if(state.SamplesPlayed > 0){
    //if(left_samples_ == nullptr)left_samples_ = new float[samples];
    //if(right_samples_ == nullptr)right_samples_ = new float[samples];
    int sec = 0;
    float **pcm = new float*[2];
    pcm[0] = new float[samples_count_];
    pcm[1] = new float[samples_count_];
    auto sp = ov_pcm_tell(&vorbis_file_);
    ov_pcm_seek(&vorbis_file_, state.SamplesPlayed);
    //ov_pcm_seek(&vorbis_file_, sp-44100);
    //std::cout << "\n" << sp << " - " << state.SamplesPlayed;
    int test = 0;
    while (test < samples_count_){
      float **b;
      int a = ov_read_float(&vorbis_file_, &b, samples_count_, &sec);
      for (int i = 0; i < a; ++i) {
        if(test+i>= samples_count_)break;
        pcm[0][test+i] = b[0][i];
        pcm[1][test+i] = b[1][i];
      }
      test+= a;
    }
    ov_pcm_seek(&vorbis_file_, sp);
    //float *left, *right;
    //left = pcm[0];
    //right = pcm[1];
    for (int i = 0; i < samples_count_; ++i) {
      //left_samples_[i] = left[i] *0.5f*(1.0f-(float)cos(2.0f*M_PI*(float)(i)/(samples-1.0f)));
      //right_samples_[i] = right[i] *0.5f*(1.0f-(float)cos(2.0f*M_PI*(float)(i)/(samples-1.0f)));
      double_samples_[i] = pcm[0][i] *0.5f*(1.0f-(float)cos(2.0f*M_PI*(float)(i)/(samples_count_-1.0f)));
      //double_samples_[i*2] = pcm[0][i] *0.5f*(1.0f-(float)cos(2.0f*M_PI*(float)(i)/(samples_count_-1.0f)));
      //double_samples_[i*2+1] = pcm[1][i] *0.5f*(1.0f-(float)cos(2.0f*M_PI*(float)(i)/(samples_count_-1.0f)));
    }
  }

  if (state.BuffersQueued < MAX_BUFFER_COUNT - 1) {

    //Got to use this trick because otherwise all the bits wont play
    if (is_almost_done_ && !loop_) {
      is_done_ = true;
    }

    memset(&buffers[current_read_buffer_], 0, sizeof(buffers[current_read_buffer_]));

    DWORD pos = 0;
    int sec = 0;
    int ret = 1;

    while (ret && pos < STREAMING_BUFFER_SIZE) {
      ret =
          ov_read(&vorbis_file_, buffers[current_read_buffer_] + pos, static_cast<int>(STREAMING_BUFFER_SIZE - pos), 0,
                  2, 1, &sec);
      pos += ret;
    }
    //Reached the end?
    if (!ret && loop_) {
      //We are looping so restart from the beginning
      //NOTE: sound with sizes smaller than BUFSIZE may be cut off

      ret = 1;
      ov_pcm_seek(&vorbis_file_, 0);
      while (ret && pos < STREAMING_BUFFER_SIZE) {
        ret = ov_read(&vorbis_file_, buffers[current_read_buffer_] + pos, static_cast<int>(STREAMING_BUFFER_SIZE - pos),
                      0, 2, 1, &sec);
        pos += ret;
      }
    }
    else if (!ret && !(loop_)) {
      //Not looping so fill the rest with 0
      //while(pos<size)
      //    *(buffers[currentDiskReadBuffer]+pos)=0; pos ++;

      //And say that after the current section no other section follows
      is_almost_done_ = true;
    }

    XAUDIO2_BUFFER buffer = {0};
    buffer.pAudioData = (BYTE *) &buffers[current_read_buffer_];
    if (is_almost_done_) {
      buffer.Flags = 0;   //Tell the source voice not to expect any data after this buffer
    }
    buffer.AudioBytes = STREAMING_BUFFER_SIZE;

    HRESULT hr;
    if (FAILED(hr = source_voice_->SubmitSourceBuffer(&buffer))) {
      //LogError("<li>Error %#X submitting source buffer\n", hr );
      return;
    }

    current_read_buffer_++;
    current_read_buffer_ %= MAX_BUFFER_COUNT;
  }
}
