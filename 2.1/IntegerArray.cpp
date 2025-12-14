//25125080
//PHAM QUOC BAO
//25A02
#include <iostream>
#include <fstream>
using namespace std;
void saveArray(){
    int n;
    cout << "Enter the size of array: ";
    cin >> n;
    cout << "Enter all element(s): ";
    int *a = new int[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ofstream fout("input.bin", ios::out | ios::binary);
    if(fout.is_open()){
        fout.write((char*)&n, sizeof(int));
        fout.write(reinterpret_cast<const char*>(a), n*sizeof(int));
        fout.close();
        cout << "Succesfully saved!" << endl;
    }
    else cout << "Unable to open file!" << endl;
    delete[] a;
}
void loadArrayFindMedian(){
    ifstream fin("input.bin", ios::in | ios::binary);
    if(fin.is_open()){
        int n;
        fin.read((char*)&n, sizeof(int));
        int a[n];
        fin.read((char*)a, n*sizeof(int));
        fin.close();
        for(int i = 0; i < n-1; i++){
            for(int j = i + 1; j < n; j++){
                if(a[i] > a[j]) swap(a[i],a[j]);
            }
        }
        double median = n % 2 == 0 ? (a[n/2-1] + a[n/2])/2.0 : a[n/2];
        cout << median << endl;
    }
    else cout << "Unable to open file!" << endl;
}

int main(){
    while(true){
        cout << "1. Save an array to a binary file.\n";
        cout << "2. Load an array from a binary file and find the median\n";
        int opt; 
        cout << "Enter your choice: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
            saveArray();
            break;
        case 2:
            loadArrayFindMedian();
            break;
        case 0:
            cout << "Ending program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Enter valid option (0,1,2)" << endl;
            break;
        }
    }
}