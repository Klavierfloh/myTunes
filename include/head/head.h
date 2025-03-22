#ifndef HEAD_H
#define HEAD_H
#include <raylib.h>
#include "../../include/gameObject/gameObject.h"
#include "../../include/constDefinitions.h"
#include "../../include/button/button.h"
#include <tuple>

class Header : public GameObject
{
private:
    int posx;
    int posy;
    int width;
    int height;

    int playingWidth = 200;
    int playingHeight = playingWidth/10;

    Button startButton;
    Button stopButton;
    Button pauseButton;
    Button resumeButton;

public:
    Header(Scene *scene, int pox, int poy, int wit, int heit);

    void process() override;

    void render() override;
};

#endif