#include "../../include/albumMenu/albumMenu.h"
#include <raylib.h>

AlbumMenu::AlbumMenu() {}

AlbumMenu::AlbumMenu(Scene *scene, int pox, int poy, int wit, int heit, LibraryManager *libman)
    : GameObject(scene), posx(pox), posy(poy), width(wit), height(heit), albumPath("") {}

void AlbumMenu::render()
{
    DrawRectangle(posx, posy, width, height,DARKPURPLE  );
}

void AlbumMenu::process(){}

void AlbumMenu::event(std::string eventString, std::string eventObject) {}