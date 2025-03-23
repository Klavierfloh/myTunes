#include "raylib.h"

#include "../../include/musicPlayer/musicPlayer.h"
#include <iostream>
#include "../../include/utils.h"
#include <vector>
using namespace std;

MusicPlayer::MusicPlayer() : isPlaying(false), isLoaded(false), m4a(false), m4aPrev(nullptr) {}

void MusicPlayer::play()
{
    PlayMusicStream(music);
    isPlaying = true;
}

struct AudioData
{
    std::vector<float> pcmData;
    unsigned int sampleRate = 44100;
    unsigned int channels = 2;
    size_t pcmIndex = 0;   // Track playback position
    bool isPaused = false; // NEW: Track if playback is paused
} audio;

bool LoadM4AWithFFmpeg(const char *filename)
{
    std::string command = "ffmpeg -hide_banner -loglevel error -i \"" + std::string(filename) + "\" -f f32le -ac 2 -ar 44100 -";

    FILE *pipe = popen(command.c_str(), "rb"); // Open FFmpeg process in binary mode
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

    if (audio.pcmData.empty())
    {
        std::cerr << "Decoded audio is empty!" << std::endl;
        return false;
    }

    return true;
}

void AudioStreamCallback(void *buffer, unsigned int frames)
{
    float *outBuffer = static_cast<float *>(buffer);
    size_t samplesToCopy = frames * audio.channels;

    if (audio.isPaused)
    {
        // Fill the buffer with silence when paused
        for (size_t i = 0; i < samplesToCopy; i++)
        {
            outBuffer[i] = 0.0f;
        }
        return;
    }

    // Normal playback
    for (size_t i = 0; i < samplesToCopy; i++)
    {
        if (audio.pcmIndex < audio.pcmData.size())
        {
            outBuffer[i] = audio.pcmData[audio.pcmIndex++];
        }
        else
        {
            outBuffer[i] = 0.0f; // Fill remaining buffer with silence
        }
    }
}

int MusicPlayer::changeMusic(const string &path)
{
    bool wasM4A = m4a; // Store previous format

    if (isPlaying)
    {
        StopMusicStream(music);
        isPlaying = false;
    }

    if (isLoaded)
    {
        if (wasM4A)
        {
            std::cout << "Unloading previous M4A audio stream..." << std::endl;

            // Ensure callback is removed before unloading the stream
            SetAudioStreamCallback(music.stream, NULL);

            if (music.stream.buffer != NULL)
            {
                UnloadAudioStream(music.stream);
            }
        }
        else
        {
            std::cout << "Unloading previous MP3/WAV/OGG music stream..." << std::endl;
            UnloadMusicStream(music);
        }
        isLoaded = false;
    }

    // Reset audio data safely
    audio.pcmData.clear();
    audio.pcmData.shrink_to_fit();
    audio.pcmIndex = 0;
    audio.isPaused = false;
    audio = AudioData(); // Reset struct

    m4a = false; // Default to non-M4A format

    if (ends_with(path, ".m4a"))
    {
        std::cout << "Loading M4A file: " << path << std::endl;

        if (!LoadM4AWithFFmpeg(path.c_str()))
        {
            std::cerr << "Failed to decode M4A audio.\n";
            return -1;
        }

        std::cout << "Decoded PCM samples: " << audio.pcmData.size() << std::endl;

        // Load custom PCM stream for M4A
        music.stream = LoadAudioStream(audio.sampleRate, 32, audio.channels);
        music.frameCount = audio.pcmData.size() / audio.channels;
        music.looping = false;

        // Ensure callback is set AFTER stream is loaded
        SetAudioStreamCallback(music.stream, AudioStreamCallback);
        m4a = true;
    }
    else
    {
        std::cout << "Loading non-M4A file: " << path << std::endl;
        music = LoadMusicStream(path.c_str());

        if (music.frameCount == 0)
        {
            std::cerr << "Music failed to load: " << path << std::endl;
            return -1;
        }
    }

    play();
    isLoaded = true;
    musicPath = path;

    return 1;
}


string MusicPlayer::getSongName()
{
    return musicPath;
}

void MusicPlayer::update()
{
    if (isLoaded)
    {
        UpdateMusicStream(music);
    }
}

void MusicPlayer::pause()
{
    if (isLoaded)
    {
        if (m4a)
        {
            audio.isPaused = true;
        }
        else
            PauseMusicStream(music);
        isPlaying = false;
    }
}

/*void MusicPlayer::pause()
{
    PauseMusicStream(music);
    isPlaying = false;
}*/

void MusicPlayer::stop()
{
    if (isLoaded)
    {
        pause();
        UnloadMusicStream(music);
        isLoaded = false;
    }
}
void MusicPlayer::resume()
{
    if (isLoaded)
    {
        if (m4a)
        {
            audio.isPaused = false;
        }
        else
            ResumeMusicStream(music);
        isPlaying = true;
    }
}
/*void MusicPlayer::resume()
{
    if (isLoaded)
    {
        ResumeMusicStream(music);
        isPlaying = true;
    }
}*/

bool MusicPlayer::getIsPlaying()
{
    return isPlaying;
}

tuple<float, float, float> MusicPlayer::getMusicInfo()
{
    float timePlayed = GetMusicTimePlayed(music);
    float musicTimeLength = GetMusicTimeLength(music);
    float ratio = (musicTimeLength > 0) ? (timePlayed / musicTimeLength) : 0.0f;
    return make_tuple(timePlayed, musicTimeLength, ratio);
}

MusicPlayer::~MusicPlayer()
{
    if (isLoaded)
    {
        PauseMusicStream(music);
        UnloadMusicStream(music);
    }

    audio.pcmData.clear();
    audio.pcmData.shrink_to_fit();
}
