//25125080
//PHAM QUOC BAO
//25A02
#include <iostream>
#include <fstream>
using namespace std;
string getFileName(const string &path){
    size_t lastSlash = path.find_last_of('\\');
    if(lastSlash == string::npos) return path;
    return path.substr(lastSlash+1);
}
string joinPath(string dir, const string &filename){
    if(!dir.empty()){
        char last = dir.back();
        if(last != '\\') dir += '\\';
    }
    return dir + filename;
}
long long fileSize(const string &filename){
    ifstream fin(filename, ios::ate | ios::binary);
    if(!fin.is_open()) return -1;
    streampos size = fin.tellg();
    return size;
}
int main(int argc, char* argv[]){
    if(argc != 7){
        cerr << "Correct syntax: MYSPLITFILE -s path_of_source_file -d path_of_destination -numpart x OR MYSPLITFILE -s path_of_source_file -d path_of_destination -sizeapart x" << endl;
        return 1;
    }
    string sourcePath;
    string destPath;
    string method;
    string numStr;

    for(int i = 0; i < argc; i++){
        string arg = argv[i];
        if(arg == "-s" && i + 1 < argc) sourcePath = argv[i+1];
        else if(arg == "-d" && i + 1 < argc) destPath = argv[i+1];
        else if(arg == "-numpart" || arg == "-sizeapart"){
            method = argv[i];
            numStr= argv[i+1];
        }
    }
    if(sourcePath.empty() || destPath.empty()){
        cerr << "Error: Missing source or destination arguments." << endl;
        return 1;
    }
    string filename = getFileName(sourcePath);
    long long sourceSize = fileSize(sourcePath);
    if(sourceSize == -1){
        cerr << "Could not open source file!" << endl;
        return 1;
    }
    long long chunkSize = 0;
    long long numVal =stoll(numStr);
    if(method == "-sizeapart") chunkSize = numVal;
    else if(method == "-numpart"){
        if(numVal <= 0){
            cerr << "Numbers of part must be greater than 0!" << endl;
            return 1;
        }
        chunkSize = (sourceSize/numVal) + (sourceSize % numVal != 0);
    }
    if(chunkSize <= 0){
        cerr << "Invalid chunk size calculation!" << endl;
        return 1;
    }
    ifstream fin(sourcePath, ios::binary);
    int fileIdx = 1;
    long long totalBytesRead = 0;
    const long long MAX_RAM = 10 * 1024 * 1024; 
    long long bufferSize = min(chunkSize, MAX_RAM);
    char *buffer = new char[bufferSize];
    while(totalBytesRead < sourceSize){
        string outName = filename + ".part" + to_string(fileIdx);
        string outPath = joinPath(destPath, outName);
        
        ofstream fout(outPath, ios::binary);

        long long bytesLeftInFile = sourceSize - totalBytesRead;
        long long toRead = min(bytesLeftInFile,bufferSize);

        fin.read((char*)buffer, toRead);
        fout.write((char*)buffer, toRead);
        totalBytesRead += toRead;
        fout.close();
        cout << "Created: " << outName << " (" << toRead << " bytes)" << endl;
        fileIdx++;
    }
    delete[] buffer;
    fin.close();
    cout << "Split succesfully!" << endl;
    return 0;
}
