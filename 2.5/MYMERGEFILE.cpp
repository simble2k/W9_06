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
string getBaseName(const string &path) {
    size_t pos = path.rfind(".part");
    
    if (pos != string::npos) {
        return path.substr(0, pos);
    }
    
    return path; 
}
string getPath(const string &sourcePath, const string &filename){
    size_t pos = sourcePath.rfind(filename);

    if(pos != string::npos){
        return sourcePath.substr(0,pos);
    }
    return sourcePath;
}
int main(int argc, char* argv[]){
    if(argc != 5){
        cerr << "Correct syntax: MYMERGEFILE -s path_of_part01 -d path_of_destination" << endl;
        return 1;

    }
    string sourcePath, destPath;
    for(int i = 0; i < argc; i++){
        string arg = argv[i];
        if(arg == "-s" && i + 1 < argc) sourcePath = argv[i+1];
        else if (arg == "-d" && i + 1 < argc) destPath = argv[i+1];
    }
    if(sourcePath.empty() || destPath.empty()){
        cerr << "Error: Missing source or destination arguments." << endl;
        return 1;
    }
    string part1 = getFileName(sourcePath);
    string finalFileName = getBaseName(part1);
    string finalDestPath = joinPath(destPath, finalFileName);
    ofstream fout(finalDestPath, ios::binary);
    int idx = 1;
    while(true){
        string fileName = finalFileName + ".part" + to_string(idx++);
        string filePath = joinPath(getPath(sourcePath,part1),fileName);
        ifstream fin(filePath, ios::binary);
        if(!fin) break; 
        long long toRead = fileSize(filePath);
        char *buffer = new char[toRead];
        fin.read(buffer,toRead);
        fout.write(buffer,toRead);
        fin.close();
        delete[] buffer;
    }
    fout.close();
    cout << "Merge successfully. New file created: " << finalFileName << " (" << fileSize(finalDestPath) << " bytes)" << endl;
    return 0;
}