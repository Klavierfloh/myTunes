#include "../../include/albumMenu/albumMenu.h"
#include <raylib.h>
#include "../../include/scene/scene.h"

AlbumMenu::AlbumMenu() {}

AlbumMenu::AlbumMenu(Scene *scene, int pox, int poy, int wit, int heit, LibraryManager *libman)
    : GameObject(scene), posx(pox), posy(poy), width(wit), height(heit), albumPath("")
     {
        
        scene->getEventBus().registerListener("openAlbum", this);
     }

void AlbumMenu::render()
{
    DrawRectangle(posx, posy, width, height,DARKPURPLE  );
}

void AlbumMenu::process(){}

void AlbumMenu::setAlbum(std::string albumName)
{
    cout << "setting album " << albumName << "\n";
}

void AlbumMenu::event(std::string eventString, std::string eventObject) 
{
    if (eventString == "openAlbum")
    {
        setAlbum(eventObject);
    }
}