#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::filesystem::directory_iterator;

int main() {
  string path = "./";

  for (const auto& file : directory_iterator(path)) cout << file.path() << endl;

  return EXIT_SUCCESS;
}