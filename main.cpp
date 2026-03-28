#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

const int MAX_BINS = 1000;
int histogram[MAX_BINS] = {0};
int binSize;

void traverseFolder(string dirPath) {
    DIR* directory = opendir(dirPath.c_str());
    if (!directory) return;

    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        string entryName = entry->d_name;
        if (entryName == "." || entryName == "..") continue;

        string fullPath = dirPath + "/" + entryName;

        struct stat fileInfo;
        if (stat(fullPath.c_str(), &fileInfo) == -1) continue;

        if (S_ISDIR(fileInfo.st_mode)) {
            traverseFolder(fullPath); // recursive call
        } else if (S_ISREG(fileInfo.st_mode)) {
            long fSize = fileInfo.st_size;
            int binIdx = fSize / binSize;
            if (binIdx < MAX_BINS) histogram[binIdx]++;
        }
    }

    closedir(directory);
}

int main() {
    string folderInput;
    cout << "Enter directory path: ";
    cin >> folderInput;

    cout << "Enter bin size: ";
    cin >> binSize;

    traverseFolder(folderInput);
    return 0;
}