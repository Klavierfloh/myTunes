#ifndef BODY_H
#define BODY_H
#include "../../include/gameObject/gameObject.h"

#include <string>
#include <filesystem>
#include <vector>

class LibraryManager;
class Scene;
class Body : public GameObject
{
private:
    int posx;
    int posy;
    int width;
    int height;
    vector<std::string>* index;
public:
    Body(Scene* scene,int pox, int poy, int wit, int heit, LibraryManager* libman);
    ~Body();

    void render() override;
    void process() override;
};

#endif