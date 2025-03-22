#include "../../include/head/head.h"
#include "../../include/utils.h"

Header::Header(Scene *scene, int pox, int poy, int wit, int heit) : GameObject(scene)
{
    posx = pox;
    posy = poy;
    width = wit;
    height = heit;

    startButton = Button(scene, posx + 10, posy + 10, height - 20, height - 20, STARTBUTTON);
    stopButton = Button(scene, posx + 190, posy + 10, height - 20, height - 20, STOPBUTTON);
    pauseButton = Button(scene, posx + 300, posy + 10, height - 20, height - 20, PAUSEBUTTON);
    resumeButton = Button(scene, posx + 400, posy + 10, height - 20, height - 20, RESUMEBUTTON);
    scene->getEventBus().event("headSizeSet", to_string(height));
    cout << "fired Size \n";
}

void Header::process()
{
    startButton.process();
    stopButton.process();
    pauseButton.process();
    resumeButton.process();
}

void Header::render()
{
    DrawRectangle(posx, posy, width, height, GRAY);
    startButton.render();
    stopButton.render();
    pauseButton.render();
    resumeButton.render();

    // DrawRectangle(400, 30, 100, 20, GREEN);
    DrawRectangle(posx + (width - (playingWidth + 30)), 0 + 30, playingWidth, playingHeight, GREEN);
    if (scene->getMusicPlayer().getIsPlaying())
    {
        tuple<float, float, float> musicInfo = scene->getMusicPlayer().getMusicInfo();
        // cout << get<2>(musicInfo) << endl;
        DrawRectangle(posx + (width - (playingWidth + 30)), posy + 30, (int)(playingWidth * get<2>(musicInfo)), playingHeight, MAROON);
    }
    DrawText(get<0>(parseMusicPath(scene->getMusicPlayer().getSongName())).c_str(),posx + (width - (playingWidth + 30)),posy + 30 - 10,15,BLACK);
    DrawText(get<2>(parseMusicPath(scene->getMusicPlayer().getSongName())).c_str(),posx + (width - (playingWidth + 30)),posy + 30 + playingHeight + 10,15,BLACK);
}
