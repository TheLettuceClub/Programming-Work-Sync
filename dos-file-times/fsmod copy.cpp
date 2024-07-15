#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

int main(int argc, char *argv[])
{
  // bool print = true;
  // if (argc > 1)
  // {
  //   string arg = argv[1];
  //   if (arg == "-m")
  //   {
  //     print = false;
  //   }
  // }
  fs::path current_dir(".");
  // time_t most_recent = 0;
  // string fileName = "";
  for (auto &file : fs::recursive_directory_iterator(current_dir))
  {
    fs::file_time_type ftime = fs::last_write_time(file);
    string time = ftime;
    cout << time << endl;
  }
  // cout << "The most recently modified file is: " << fileName << " with modification time of: " << ctime(&most_recent) << endl;
  return 0;
}