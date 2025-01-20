#pragma once

#include "constants.hpp"

#include <SDL2/SDL.h>

class AudioDevice {
private:
    SDL_AudioDeviceID device_id;
    SDL_AudioSpec spec;
    float frequency = AUDIO_FREQ;
    float phase = 0.f;
    bool isPlaying = false;

    static void audioCallback(void* user_data, Uint8* stream, int len);
    bool initSDLAudio();
public:
    AudioDevice();
    ~AudioDevice();

    void startBeep();
    void stopBeep();
};
