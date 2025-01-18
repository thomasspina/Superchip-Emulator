#include "audio.hpp"

void AudioDevice::audioCallback(void* user_data, Uint8* stream, int len) {
    AudioDevice* audio = (AudioDevice*) user_data;
    float* float_stream = (float*) stream;
    const int samples = len / sizeof(float);
    const float PI2 = 2.f * M_PI;

    if (audio->isPlaying) {
        // fill output stream with sin wave freq
        for (int i = 0; i < samples; i++) {
            float_stream[i] = sinf(audio->phase) * AUDIO_VOLUME;
            audio->phase += PI2 * audio->frequency / audio->spec.freq;

            if (audio->phase > PI2) {
                audio->phase -= PI2;
            }
        }
    } else {
        // fill output stream with 0 (silence)
        SDL_memset(stream, 0, len);
    }
}

bool AudioDevice::initSDLAudio() {
    if (!SDL_WasInit(SDL_INIT_AUDIO)) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
            SDL_Log("Failed to initialize SDL audio: %s", SDL_GetError());
            return false;
        }
    }

    return true;
}

AudioDevice::AudioDevice() {
    if (!initSDLAudio()) {
        SDL_Log("Cannot initialize audio device - SDL audio initialization failed");
        return;
    }

    SDL_AudioSpec desired_sepcs;
    SDL_zero(desired_sepcs);
    desired_sepcs.freq = AUDIO_DESIRED_FREQ;
    desired_sepcs.format = AUDIO_F32;
    desired_sepcs.channels = 1; // mono sound
    desired_sepcs.samples = AUDIO_SAMPLES;
    desired_sepcs.callback = audioCallback;
    desired_sepcs.userdata = this;

    device_id = SDL_OpenAudioDevice(nullptr, 0, &desired_sepcs, &spec, 0);
    if (device_id == 0) {
        SDL_Log("Failed to open audio device: %s", SDL_GetError());
        return;
    }

    SDL_PauseAudioDevice(device_id, 0);
}

AudioDevice::~AudioDevice() {
    if (device_id > 0) {
        SDL_CloseAudioDevice(device_id);
    }
}

void AudioDevice::startBeep() { 
    isPlaying = true; 
}

void AudioDevice::stopBeep() {
    isPlaying = false;
}
