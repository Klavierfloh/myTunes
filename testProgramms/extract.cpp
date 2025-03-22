#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>
#include <filesystem>
#include <iostream>
#include <fstream>

// To compile: g++ -std=c++17 extract.cpp -o extract.exe -I C:/msys64/mingw64/include -L C:/msys64/mingw64/lib -ltag

void extractAlbumArt(const std::string &filename)
{
    std::cout << "Extracting from: " << filename << std::endl;

    if (!std::filesystem::exists(filename))
    {
        std::cerr << "File not found: " << filename << std::endl;
        return;
    }

    std::cout << "File exists." << std::endl;

    TagLib::MPEG::File file(filename.c_str());
    if (!file.isValid())
    {
        std::cerr << "Invalid MP3 file: " << filename << std::endl;
        return;
    }

    std::cout << "MP3 file is valid." << std::endl;

    TagLib::ID3v2::Tag *tag = file.ID3v2Tag();
    if (!tag)
    {
        std::cerr << "No ID3v2 tag found in: " << filename << std::endl;
        return;
    }

    std::cout << "ID3v2 tag found." << std::endl;

    // Look for attached pictures (APIC frames)
    auto frameList = tag->frameListMap()["APIC"];
    std::cout << "APIC frame count: " << frameList.size() << std::endl;

    for (auto frame : frameList)
    {
        auto *apic = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame *>(frame);
        if (apic)
        {
            std::ofstream img("cover.jpg", std::ios::binary);
            img.write(apic->picture().data(), apic->picture().size());
            img.close();
            std::cout << "Album art saved as cover.jpg" << std::endl;
            return;
        }
    }

    std::cerr << "No album art found in: " << filename << std::endl;
}


int main()
{
    std::cout << "Start Test" << std::endl;
    extractAlbumArt("D:\\VS Code Programms\\raylibtest\\Florence + The Machine - Bedroom Hymns.mp3");
    std::cout << "Stop Test" << std::endl;
    return 0;
}
