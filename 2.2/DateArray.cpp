//25125080
//PHAM QUOC BAO
//25A02
#include <iostream>
#include <fstream>
using namespace std;

struct date
{
    int day,month,year;
};
void save(){
    cout << "Enter number of dates: ";
    int n; cin >> n;
    cout << "Enter date(s) (dd-mm-yyyy): ";
    date *a = new date[n];
    for(int i = 0; i < n; i++){
        cin >> a[i].day >> a[i].month >> a[i].year;
    }
    ofstream fout("data.bin", ios::out | ios::binary);
    if(fout.is_open()){
        fout.write((char*)&n, sizeof(int));
        fout.write(reinterpret_cast<char*>(a), n*sizeof(date));
        fout.close();
        cout << "Saved successfully!" << endl;
    }
    else cout << "Unable to open file!" << endl;
}
void load(){
    ifstream fin("data.bin", ios::out | ios::binary);
    if(fin.is_open()){
        int n;
        fin.read((char*)&n, sizeof(int));
        date *a = new date[n];
        fin.read(reinterpret_cast<char*>(a), n*sizeof(date));
        date max = a[0];
        for(int i = 1; i < n; i++){
            if(a[i].year > max.year) max = a[i];
            else if(a[i].year == max.year){
                if(a[i].month > max.month) max = a[i];
                else if(a[i].month == max.month){
                    if(a[i].day > max.day) max = a[i];
                }
            }
        }
        cout << "Newest day: " << max.day << "/" << max.month << "/" << max.year << endl;
    }
    else cout << "Unable to open file!" << endl;
}
void menu(){
    cout << "1. Save an array of dates\n";
    cout << "2. Load an array of dates and find the newest date\n";
    cout << "Enter your choice (0 to exit program):";
}
int main(){
    while(true){
        menu();
        int opt; cin >> opt;
        switch (opt)
        {
        case 1:
            save();
            break;
        case 2:
            load();
            break;
        case 0:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Pls enter a valid option 0,1,2";
            break;
        }
    }
}
