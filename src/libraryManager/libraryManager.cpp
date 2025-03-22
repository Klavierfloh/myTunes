#include "../../include/libraryManager/libraryManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "../../include/utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::filesystem::directory_iterator;

LibraryManager::LibraryManager(Scene *scene) : GameObject(scene) {}

void LibraryManager::setLibraryPathRoot(string path)
{
    libraryPathRoot = path;
}

vector<std::filesystem::path> LibraryManager::getInDirectory(string path)
{
    vector<std::filesystem::path> files;

    for (const auto &file : std::filesystem::directory_iterator(path))
    {
        files.push_back(file.path()); // Store paths in a vector
    }

    return files;
}

void LibraryManager::indexLibrary(string path, int level)
{
    if (level == 0)
    {
        libraryFile.open("./Assets/index.txt");
        albumLibraryFile.open("./Assets/albumIndex.txt");
        if (!libraryFile.is_open() || !albumLibraryFile.is_open())
        {
            cout << "Unable to open file" << endl;
            return;
        }
    }
    // libraryFile.open("..\\..\\Assets\\index.txt");
    vector<std::filesystem::path> files = LibraryManager::getInDirectory(path);
    for (size_t i = 0; i < files.size(); i++) // Iterate using index
    {
        if (!std::filesystem::is_directory(files[i]))
        {
            libraryFile << files[i].string().c_str() << "\n";
            index.push_back(files[i]);
        }
    }
    for (size_t i = 0; i < files.size(); i++) // Iterate using index
    {
        if (std::filesystem::is_directory(files[i]))
        {
            indexLibrary(files[i].string(), level + 1);
        }
        if (std::filesystem::is_directory(files[i]) && level == 1)
        {
            albumLibraryFile << get<2>(parseMusicPath(files[i].string())) << "\n";
            cout << get<2>(parseMusicPath(files[i].string())) << "\n";
        }
    }

    if (level == 0)
    {
        libraryFile.close();
        albumLibraryFile.close();
        cout << "Library Indexing finished" << endl;
        for (size_t i = 0; i < index.size(); i++) // Iterate using index
        {
            cout << index[i].string().c_str() << endl;
        }

    }
}

vector<std::filesystem::path>* LibraryManager::getLibraryIndex()
{
    return &index;
}
