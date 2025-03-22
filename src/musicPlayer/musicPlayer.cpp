#include "raylib.h"

#include "../../include/musicPlayer/musicPlayer.h"
#include <iostream>
#include "../../include/utils.h"
using namespace std;

MusicPlayer::MusicPlayer() : isPlaying(false), isLoaded(false) {}

void MusicPlayer::play()
{
    PlayMusicStream(music);
    isPlaying = true;
}

void MusicPlayer::changeMusic(const string &path)
{
    if (isPlaying)
    {
        StopMusicStream(music);
        isPlaying = false;
    }
    if (isLoaded)
    {
        UnloadMusicStream(music);
        isLoaded = false;
    }

    music = LoadMusicStream(path.c_str());
    if (music.frameCount > 0)
    {
        /*if (ends_with(path, ".m4a"))
        {
            ma_decoder decoder;
            if (ma_decoder_init_file(path.c_str(), NULL, &decoder) != MA_SUCCESS)
            {
                cout << "Failed to initialize decoder for " << path << endl;
                return;
            }

            ma_uint32 sampleRate = decoder.outputSampleRate;
            ma_uint32 channels = decoder.outputChannels;

            music.stream = LoadAudioStream(sampleRate, 16, channels);

            ma_uint64 frameCount = 0;
            ma_decoder_get_length_in_pcm_frames(&decoder, &frameCount);
            music.frameCount = frameCount;

            PlayAudioStream(music.stream);

            ma_decoder_uninit(&decoder); // Free decoder after use
        }
        else
        {
            music = LoadMusicStream(path.c_str());
            play();
        }*/
        // music = LoadMusicStream(path.c_str());
        play();
        isLoaded = true;
        musicPath = path;
    }
    else
    {
        /**/
        cout << "Music failed to load: " << path << endl;
        isPlaying = false;
    }
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
    PauseMusicStream(music);
    isPlaying = false;
}

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
        ResumeMusicStream(music);
        isPlaying = true;
    }
}

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
}
