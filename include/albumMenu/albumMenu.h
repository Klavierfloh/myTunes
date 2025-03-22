#ifndef ALBUMMENU_H
#define ALBUMMENU_H

#include "../../include/gameObject/gameObject.h"

class LibraryManager;
class AlbumMenu : public GameObject
{
private:
    int posx;
    int posy;
    int width;
    int height;
    std::string albumPath;

public:
    AlbumMenu();
    AlbumMenu(Scene* scene,int pox, int poy, int wit, int heit, LibraryManager* libman);

    void render() override;
    void process() override;
    void event(std::string eventString, std::string eventObject) override;
    void setAlbum(std::string albumName);
};

#endif