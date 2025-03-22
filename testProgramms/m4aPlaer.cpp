#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace raylib
{
#include "raylib.h"
}

// Structure to store decoded audio
struct AudioData
{
    std::vector<float> pcmData;
    unsigned int sampleRate = 44100;
    unsigned int channels = 2;
};

// Function to decode .m4a to raw PCM using FFmpeg
bool LoadM4AWithFFmpeg(const char *filename, AudioData &audio)
{
    std::string fullFilePath = "D:\\VS Code Programms\\raylibtest\\testProgramms\\10_Interstellar.m4a";
    std::string command = "ffmpeg -hide_banner -loglevel error -i \"" + fullFilePath + "\" -f f32le -ac 2 -ar 44100 -";

    FILE *pipe = popen(command.c_str(), "rb"); // Open in binary mode to read raw data

    if (!pipe)
    {
        std::cerr << "Failed to run FFmpeg!" << std::endl;
        return false;
    }

    float sample;
    while (fread(&sample, sizeof(float), 1, pipe) == 1)
    {
        audio.pcmData.push_back(sample);
    }

    pclose(pipe);
    return !audio.pcmData.empty();
}

int main()
{
    raylib::SetAudioStreamBufferSizeDefault(95000);  // Adjust buffer size here
    raylib::InitWindow(800, 600, "raylib + FFmpeg: Play M4A");
    raylib::InitAudioDevice();

    AudioData audio;
    const char *filename = "10_Interstellar.m4a";

    if (!LoadM4AWithFFmpeg(filename, audio)) {
        std::cerr << "Failed to decode audio.\n";
        raylib::CloseAudioDevice();
        raylib::CloseWindow();
        return -1;
    }

    std::cout << "Decoded PCM samples: " << audio.pcmData.size() << std::endl;
    std::cout << "Expected samples (estimate): " << (audio.sampleRate * audio.channels * 3 * 60) << std::endl;

    // Create a raylib audio stream
    raylib::AudioStream stream = raylib::LoadAudioStream(audio.sampleRate, 32, audio.channels);
    raylib::PlayAudioStream(stream);

    size_t pcmIndex = 0;
    size_t bufferSize = 95000;  // Adjust buffer size here
    bool isAudioStreamPlaying = true;
    raylib::SetTargetFPS(60); 
    while (!raylib::WindowShouldClose()) {
        if (raylib::IsAudioStreamProcessed(stream)) {
            // Check if there are frames left to stream
            size_t framesToStream = std::min(bufferSize, audio.pcmData.size() - pcmIndex);
            if (framesToStream > 0) {
                // Update the audio stream with the frames
                raylib::UpdateAudioStream(stream, &audio.pcmData[pcmIndex], framesToStream);
                pcmIndex += framesToStream;
            } else {
                // Handle audio completion
                isAudioStreamPlaying = false;
                break;  // Exit the loop if the audio has finished playing
            }
        }

        raylib::BeginDrawing();
        raylib::ClearBackground(raylib::RAYWHITE);
        raylib::DrawText("Playing M4A using FFmpeg!", 200, 250, 20, raylib::DARKGRAY);
        raylib::EndDrawing();
    }

    // Cleanup
    raylib::UnloadAudioStream(stream);
    raylib::CloseAudioDevice();
    raylib::CloseWindow();

    return 0;
}
