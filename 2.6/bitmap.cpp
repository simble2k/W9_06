#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;

#pragma pack(push, 1) 

struct BitmapFileHeader {
    uint16_t Signature = 0x4D42;  
    uint32_t FileSize;   
    uint32_t Reserved = 0;   
    uint32_t DataOffset; 
};

struct BitmapInfoHeader {
    uint32_t HeaderSize = 40; 
    uint32_t Width;      
    uint32_t Height;
    uint16_t Planes = 1;
    uint16_t BitCount = 24;
    uint32_t Compression = 0;
    uint32_t ImageSize;
    uint32_t XPixelsPerM = 0;
    uint32_t YPixelsPerM = 0;
    uint32_t ColorsUsed = 0;
    uint32_t ColorsImportant = 0;
};

#pragma pack(pop)

int main(){
    int width, height;
    cout << "Enter width and height of the flag of England: ";
    cin >> width >> height;
    int centerX = width/2;
    int centerY = height/2;
    int thickness = height/5;
    int rowSize = width*3;
    int padding = (4-(rowSize % 4)) % 4;
    int pixelArraySize = (rowSize + padding)*height;
    int totalFileSize = 54 + pixelArraySize;
    unsigned char redPixel[3] = {0,0,255};
    unsigned char whitePixel[3] = {255,255,255};
    BitmapFileHeader fileHeader;
    fileHeader.FileSize = totalFileSize;
    fileHeader.DataOffset = 54;
    BitmapInfoHeader infoHeader;
    infoHeader.Width = width;
    infoHeader.Height = height;
    infoHeader.ImageSize = pixelArraySize;
    ofstream fout("England.bmp", ios::binary);
    fout.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    fout.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if((i >= centerY - thickness/2 && i <= centerY + thickness/2) || (j <= centerX+thickness/2 && j >= centerX - thickness/2)){
                fout.write(reinterpret_cast<char*> (redPixel),sizeof(redPixel));
            }
            else fout.write(reinterpret_cast<char*> (whitePixel),sizeof(whitePixel));
        }
        int x = 0;
        if(padding) fout.write(reinterpret_cast<char*>(&x), padding);
    }
    return 0;
}