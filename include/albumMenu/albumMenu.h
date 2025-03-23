#ifndef ALBUMMENU_H
#define ALBUMMENU_H

#include "../../include/gameObject/gameObject.h"
#include <vector>

class LibraryManager;
class TrackButton;
class AlbumMenu : public GameObject
{
private:
    int posx;
    int posy;
    int width;
    int height;
    int headHeight;
    std::string albumPath;
    LibraryManager* libmanager;
    vector<TrackButton*> trackButtons;


public:
    AlbumMenu();
    AlbumMenu(Scene* scene,int pox, int poy, int wit, int heit, LibraryManager* libman);

    void render() override;
    void process() override;
    void event(std::string eventString, std::string eventObject) override;
    void setAlbum(std::string albumName);

    std::string getAlbumPath();
    ~AlbumMenu();
};

#endif