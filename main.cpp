#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

const int MAX_BINS = 1000;
int fileHistogram[MAX_BINS] = {0};
int binSizeBytes;
#Function to recursively scan a directory and its subdirectories
void scanDirectory(string pathInput) {
    DIR* dirPtr = opendir(pathInput.c_str());
    if (!dirPtr) return;

    struct dirent* item;
    while ((item = readdir(dirPtr)) != NULL) {
        string itemName = item->d_name;
        #skip current and parent directory entries 
        if (itemName == "." || itemName == "..") continue;

        string fullPath = pathInput + "/" + itemName;

        struct stat info;
        if (stat(fullPath.c_str(), &info) == -1) continue;

        if (S_ISDIR(info.st_mode)) {
            scanDirectory(fullPath);
        } else if (S_ISREG(info.st_mode)) {
            long fSize = info.st_size;
            int binIdx = fSize / binSizeBytes;
            if (binIdx < MAX_BINS) fileHistogram[binIdx]++;
        }
    }

    closedir(dirPtr);
}

int main() {
    string folderPath;
    cout << "Enter directory path: ";
    cin >> folderPath;

    cout << "Enter bin size in bytes: ";
    cin >> binSizeBytes;
    #Start scanning the directory 
    scanDirectory(folderPath);
    #print the histogram 
    cout << "\nFile size histogram:\n";
    for (int i = 0; i < MAX_BINS; i++) {
        if (fileHistogram[i] > 0) {
            int start = i * binSizeBytes;
            int end = start + binSizeBytes - 1;
            cout << start << " - " << end << " : " << fileHistogram[i] << endl;
        }
    }

    return 0;
}