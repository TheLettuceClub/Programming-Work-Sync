#include <Filesystem>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

namespace fs = std::filesystem;
using namespace std;
typedef struct stat Stat;

int main(int argc, char *argv[])
{
  bool print = true;
  if (argc > 1)
  {
    string arg = argv[1];
    if (arg == "-m")
    {
      print = false;
    }
  }
  fs::path current_dir(".");
  Stat st;
  int ierr = 0;
  time_t most_recent = 0;
  string fileName = "";
  for (auto &file : fs::recursive_directory_iterator(current_dir))
  {
    string namePath = file.path().string(); // relative path from current directory to file, including filename
    char *path = new char[namePath.length() + 1];
    strcpy(path, namePath.c_str());
    ierr = stat(path, &st);
    if (print)
    {
      cout << namePath << " " << st.st_mtime << endl;
    }
    if (ierr != 0)
    {
      cout << "file error!" << endl;
      // return 1;
    }
    if (st.st_mtime > most_recent)
    {
      most_recent = st.st_mtime;
      fileName = namePath;
      cout << "The most recently modified file is: " << fileName << " with modification time of: " << ctime(&most_recent) << endl;
    }
    delete[] path;
  }
  cout << "Final: The most recently modified file is: " << fileName << " with modification time of: " << ctime(&most_recent) << endl;
  return 0;
}