#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace raylib {
#include "raylib.h"
}
//compile with g++ m4aPlaer.cpp -o play_m4a.exe  -lraylib -lopengl32 -lgdi32 -lwinmm

// Global structure to store decoded PCM data
struct AudioData {
    std::vector<float> pcmData;
    unsigned int sampleRate = 44100;
    unsigned int channels = 2;
    size_t pcmIndex = 0; // Track playback position
} audio; // Global instance of AudioData

// Function to decode .m4a to raw PCM using FFmpeg
bool LoadM4AWithFFmpeg(const char* filename) {
    std::string command = "ffmpeg -hide_banner -loglevel error -i \"" + std::string(filename) + "\" -f f32le -ac 2 -ar 44100 -";

    FILE* pipe = popen(command.c_str(), "rb"); // Open FFmpeg process in binary mode
    if (!pipe) {
        std::cerr << "Failed to run FFmpeg!" << std::endl;
        return false;
    }

    float sample;
    while (fread(&sample, sizeof(float), 1, pipe) == 1) {
        audio.pcmData.push_back(sample);
    }

    pclose(pipe);

    if (audio.pcmData.empty()) {
        std::cerr << "Decoded audio is empty!" << std::endl;
        return false;
    }

    return true;
}

// Audio callback to stream PCM data into Raylib's Music buffer
void AudioStreamCallback(void* buffer, unsigned int frames) {
    float* outBuffer = static_cast<float*>(buffer);
    size_t samplesToCopy = frames * audio.channels; // Total samples (frames * channels)

    // Copy PCM data into the buffer
    for (size_t i = 0; i < samplesToCopy; i++) {
        if (audio.pcmIndex < audio.pcmData.size()) {
            outBuffer[i] = audio.pcmData[audio.pcmIndex++];
        } else {
            outBuffer[i] = 0.0f; // Fill remaining buffer with silence
        }
    }
}

int main() {
    // Initialize window and audio
    raylib::InitWindow(800, 600, "Raylib Music Stream with FFmpeg");
    raylib::InitAudioDevice();

    const char* filename = "10_Interstellar.m4a"; // Ensure this file exists!

    if (!LoadM4AWithFFmpeg(filename)) {
        std::cerr << "Failed to decode audio.\n";
        raylib::CloseAudioDevice();
        raylib::CloseWindow();
        return -1;
    }

    std::cout << "Decoded PCM samples: " << audio.pcmData.size() << std::endl;

    // Create an empty Music object
    raylib::Music music;
    music.stream = raylib::LoadAudioStream(audio.sampleRate, 32, audio.channels);
    music.frameCount = audio.pcmData.size() / audio.channels;
    music.looping = false;

    // Set our custom callback for streaming audio (no userData needed)
    raylib::SetAudioStreamCallback(music.stream, AudioStreamCallback);
    raylib::SetMusicVolume(music, 0.5);

    // Start playing the music stream
    raylib::PlayMusicStream(music);
    raylib::SetTargetFPS(60);

    while (!raylib::WindowShouldClose()) {
        raylib::UpdateMusicStream(music); // Keep feeding audio data

        raylib::BeginDrawing();
        raylib::ClearBackground(raylib::RAYWHITE);
        raylib::DrawText("Playing M4A Music Stream with FFmpeg!", 150, 250, 20, raylib::DARKGRAY);
        raylib::EndDrawing();
    }

    // Cleanup
    raylib::UnloadMusicStream(music);
    raylib::CloseAudioDevice();
    raylib::CloseWindow();

    return 0;
}
