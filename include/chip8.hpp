#pragma once

#include "audio.hpp"

#include <string>

class Chip8 {
private:
    // unsig short: 2 bytes unsig char: 1 byte

    // 4096 bytes within 4KB
    // Note: In an emulator, font set begins at 0x000 because 
    // we don't actually require an interpreter within the memory array
    // because this is all run on a host computer

    // 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
    // 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
    // 0x200-0xFFF - Program ROM and work RAM
    unsigned char memory[4096];

    // Current opcode
    unsigned short opcode;

    // 16 CPU registers, 16th is a carry flag, V0-VF
    unsigned char V[16];

    unsigned short I;
    unsigned short pc;

    // Stores current key state. 0 meaning key is up,
    // and any other value meaning key is down.
    unsigned char key[16];
    unsigned char key_wait_buffer;

    // Timer registers that countdown
    unsigned char delay_timer;
    unsigned char sound_timer;

    // Audio device for beeping sound
    AudioDevice audio_device = AudioDevice();

    // Store return address of subroutines
    unsigned short stack[16];
    unsigned char sp;

    // Indicates when the screen needs to be updated
    bool draw_flag;
    bool key_wait_flag;

    void clearStack();
    void clearRegisters();
    void clearMemory();
    void clearKeyBuffer();
    void resetTimers();
    
    void loadFontSet();

    void fetchOpcode();
    void decodeOpcode();

    void executeSI(unsigned short opInstruction);
    void executeJMP(unsigned short opInstruction);
    void executeSRC(unsigned short opInstruction);
    void executeSE(unsigned short opInstruction);
    void executeSNE(unsigned short opInstruction);
    void executeSRE(unsigned short opInstruction);
    void executeLC(unsigned short opInstruction);
    void executeAC(unsigned short opInstruction);
    void executeAL(unsigned short opInstruction);
    void executeSRNE(unsigned short opInstruction);
    void executeLI(unsigned short opInstruction);
    void executeJMPOFF(unsigned short opInstruction);
    void executeRAN(unsigned short opInstruction);
    void executeDR(unsigned short opInstruction);
    void executeKII(unsigned short opInstruction);
    void executeMISC(unsigned short opInstruction);

public:
    Chip8();

    void reset();
    void loadROM(const std::string& message);
    void emulationCycle();
    bool getDrawFlag() const { return draw_flag; }
    void setDrawFlag(bool flag) { draw_flag = flag; }
    void setKeyState(const unsigned char& key_id, const unsigned char& state);
    void tickDelayTimer() { delay_timer = delay_timer > 0 ? delay_timer - 1 : delay_timer; }
    void tickSoundTimer() { sound_timer = sound_timer > 0 ? sound_timer - 1 : sound_timer; }
};
