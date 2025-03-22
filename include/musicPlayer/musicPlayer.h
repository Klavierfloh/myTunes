#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "raylib.h"
#include <string>
#include <tuple>

using namespace std;

class MusicPlayer
{
private:
    Music music; // Raylib Music structure
    bool isPlaying = false;
    string musicPath = "";
    bool isLoaded = false;

    void play();                              // Play the music
    bool loadMusicStream(const string &path); // Load music stream (handle .m4a separately)

public:
    MusicPlayer();
    void changeMusic(const string &path);
    tuple<float, float, float> getMusicInfo();
    string getSongName();
    bool getIsPlaying();
    void update();
    void stop();
    void resume();
    void pause();
    ~MusicPlayer();
};

#endif // MUSICPLAYER_H
