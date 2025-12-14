#include <iostream>
#include <fstream>
#include <string>
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
int main(int argc, char* argv[]){
    if(argc != 5){
        cerr << "Correct syntax: " << argv[0] << " -s <source_path> -d <destination_path>" << endl;
        return 1;
    }

    string sourcePath;
    string destPath;
    for(int i = 0; i < argc; i++){
        string arg = argv[i];
        if(arg == "-s" && i + 1 < argc) sourcePath = argv[i+1];
        else if(arg == "-d" && i+1 < argc) destPath = argv[i+1];
    }
    if(sourcePath.empty() || destPath.empty()){
        cerr << "Error: Missing source or destination arguments." << endl;
        return 1;
    }
    string filename = getFileName(sourcePath);
    string fullDestPath = joinPath(destPath,filename);

    ifstream fin(sourcePath, ios::binary);
    if(!fin){
        cerr << "Error: Could not open source file" << endl;
        return 1;
    }
    ofstream fout(fullDestPath, ios::binary);
    if(!fout){
        cerr << "Error: Could not open destination file" << endl;
        return 1;
    }
    const size_t BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];

    while(fin){
        fin.read(buffer,BUFFER_SIZE);
        streamsize bytesread = fin.gcount();
        if(bytesread > 0){
            fout.write(buffer, bytesread);
        }
    }
    if(!fout){
        cerr << "Error: Could not write file" << endl;
        return 1;
    }
    cout << "File copied succesfully!" << endl;
    return 0;
}