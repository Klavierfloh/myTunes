#include "../../include/albumMenu/albumMenu.h"
#include <raylib.h>
#include "../../include/scene/scene.h"
#include "../../include/LibraryManager/libraryManager.h"
#include "../../include/TrackButtons/trackButton.h"
#include "../../include/utils.h"

AlbumMenu::AlbumMenu() {}

AlbumMenu::AlbumMenu(Scene *scene, int pox, int poy, int wit, int heit, LibraryManager *libman)
    : GameObject(scene), posx(pox), posy(poy), width(wit), height(heit), headHeight(40), albumPath(""), libmanager(libman)
{

    scene->getEventBus().registerListener("openAlbum", this);
}

void AlbumMenu::render()
{
    DrawRectangle(posx, posy, width, headHeight, PURPLE);
    DrawRectangle(posx, posy + headHeight, width, height, DARKPURPLE);

    DrawText(get<2>(parseMusicPath(albumPath)).c_str(), posx, posy, 20, BLACK);

    for (auto track : trackButtons)
    {
        track->render();
    }
}

void AlbumMenu::process()
{
    for (auto track : trackButtons)
    {
        track->process();
    }
}

void AlbumMenu::setAlbum(std::string albumName)
{
    albumPath = ".\\Library\\" + albumName;
    cout << "setting album " << albumName << "\n";

    trackButtons.clear();
    std::vector<std::filesystem::__cxx11::path> tracks = libmanager->getInDirectory(albumPath);
    for (int i = 0; i < (int)(tracks.size()); i++)
    {
        TrackButton *b = new TrackButton(scene, posx + 20, posy + headHeight + (45 * i), width - 40, 40, tracks[i].string());
        trackButtons.push_back(b);
    }
}

void AlbumMenu::event(std::string eventString, std::string eventObject)
{
    if (eventString == "openAlbum")
    {
        setAlbum(eventObject);
    }
}

std::string AlbumMenu::getAlbumPath()
{
    return albumPath;
}

AlbumMenu::~AlbumMenu()
{
    trackButtons.clear();
}
