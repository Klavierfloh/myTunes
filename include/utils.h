#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <filesystem>
#include <tuple>
#include <string>

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


inline std::tuple<std::string, std::string, std::string> parseMusicPath(const std::string& path) {
    std::filesystem::path fsPath(path);

    // Extract components
    std::string trackTitle = fsPath.stem().string();  // Remove extension
    std::string album = fsPath.parent_path().filename().string();
    std::string artist = fsPath.parent_path().parent_path().filename().string();

    return {artist, album, trackTitle};
}

#endif