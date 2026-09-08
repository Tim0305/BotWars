#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("bitacora.txt");

    if (!file.is_open()) {
        cerr << "Error: Could not open the file" << endl;
        return 1;
    }
    
    string startDate;
    string endDate;

    cout << "Enter the start date in DD-MM format" << endl;
    cin >> startDate;
    
    cout << "Enter the end date in DD-MM format" << endl;
    cin >> endDate;

    

    return 0;
}