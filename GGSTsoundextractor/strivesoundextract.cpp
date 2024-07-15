#include <Filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#define OFFSET 164

namespace fs = std::filesystem;
using namespace std;

/**
 * what this should do: convert GGST's UEXP sound files to the OGG files they really are
 * do this by removing all the bytes before the first "OggS", leaving the rest of the file alone. it is also seemingly always the first 164 bytes being removed
 * should create a new file with the same name and .ogg extension to not overwrite anything
 * will recursively go through all the subdirectories it sees, and should only act on files ending in .uexp
 */

int main(int argc, char *argv[])
{
  fs::path current_dir(".");
  for (auto &file : fs::recursive_directory_iterator(current_dir))
  {
    if (file.is_directory())
    {
      continue;
    }
    string path = file.path().parent_path().string();       // just the relative path from exe
    string extension = file.path().extension().string();    // just the extension
    string name = file.path().stem().string();              // just the file name
    string fullPath = file.path().relative_path().string(); // full path with filename and extenstion
    string newPath = path + "\\" + name + ".ogg";           // full new path with same name and new extension
    auto length = fs::file_size(file.path());               // file size for later
    if (extension == ".uexp" && name.find("_Cue") == string::npos && name.find("VoiceData") == string::npos && name.find("SEData") == string::npos && name.find("_lip") == string::npos)
    {
      ifstream inFile;
      ofstream outFile;
      try
      {
        inFile.open(fullPath, ifstream::binary);
        inFile.seekg(OFFSET); // ignore the first 164 bytes to remove the UE4 header
        outFile.open(newPath, ofstream::binary);
        vector<byte> buffer(length - OFFSET);
        inFile.read(reinterpret_cast<char *>(buffer.data()), length - OFFSET); // this is necessary because c++ is stupid and drops characters otherwise
        outFile.write(reinterpret_cast<char *>(buffer.data()), length - OFFSET);
        inFile.close();
        outFile.close();
        cout << "Wrote " << newPath << endl;
      }
      catch (exception e)
      {
        inFile.close(); // make sure files are closed in event of error
        outFile.close();
        cerr << "Something bad happened: " << e.what() << endl;
        return -1;
      }
    }
  }
  return 0;
}