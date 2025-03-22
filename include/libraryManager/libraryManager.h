#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H
#include <string>
#include <filesystem>
#include <fstream>
#include "../../include/gameObject/gameObject.h"
#include <vector>

using namespace std;

class LibraryManager : public GameObject
{
    private:
        string libraryPathRoot;
        ofstream libraryFile;
        ofstream albumLibraryFile;
        vector<std::filesystem::path> index;
        vector<std::string> albumIndex;
        vector<std::filesystem::path> getInDirectory(string path);
    public:
        LibraryManager(Scene* scene);

        void setLibraryPathRoot(string path);

        void indexLibrary(string path, int level);

        vector<std::filesystem::path>* getLibraryIndex();
        vector<std::string>* getLibraryAlbumIndex();
};

#endif