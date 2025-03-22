#include "../../include/body/body.h"
#include "../../include/libraryManager/libraryManager.h"
#include "raylib.h"
#include "../../include/albumBox/albumBox.h"

Body::Body(Scene *scene, int pox, int poy, int wit, int heit, LibraryManager *libman)
    : GameObject(scene), posx(pox), posy(poy), width(wit - 120), height(heit)
{
    index = libman->getLibraryAlbumIndex();
    using namespace std;
    int widthBut = 100;
    int maxWidthInButtons = (width) / widthBut;
    for (int i = 0; i < (int)(index->size()); i++)
    {
        int level = i / (maxWidthInButtons);
        int posxB = 20 + posx + (i * widthBut) + 20 * i - ((level) * (width + widthBut));
        int posyB = posy + 20 + ((level)*widthBut) + 20 * (level - 1);
        Box *b = new Box(scene, posxB, posyB, widthBut, widthBut, (*index)[i]);
        scene->addObject(b);
    }
}
Body::~Body() {}

void Body::render() {}
void Body::process()
{

    using namespace std;
    /*for (int i = 0; i < (int)(index->size()); i++)
    {
        DrawRectangle(posx + (110 * i), posy + 20, 100, 100,RED);
        DrawText((*index)[i].string().c_str(),posx + (110 * i), posy + 20,10,BLACK );
    }*/
}