#ifndef TRACKBUTTON_H
#define TRACKBUTTON_H
#include <string>
#include "../../include/albumMenu/albumMenu.h"
class Scene;
class TrackButton : public GameObject
{
    private:
    int posx;
    int posy;
    int width;
    int height;
    std::string trackPath;
    std::string trackName;

    public:
        TrackButton();
        TrackButton(Scene* scene,int pox, int poy, int wit, int heit, std::string trackPathL);

        void render() override;
        void process() override;

        void event(std::string eventString, std::string eventObject) override;
};

#endif