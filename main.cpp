#include <iostream>
#include <dirent.h>
using namespace std;

void traverseFolder(string dirPath) {
    DIR* directory = opendir(dirPath.c_str());
    if (!directory) return;

    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        string entryName = entry->d_name;
        if (entryName == "." || entryName == "..") continue;

        string fullPath = dirPath + "/" + entryName;

        // For now, just print directory paths
        cout << "Found: " << fullPath << endl;
    }

    closedir(directory);
}

int main() {
    string folderInput;
    cout << "Enter directory path: ";
    cin >> folderInput;

    traverseFolder(folderInput);
    return 0;
}