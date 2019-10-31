#include <iostream>
#include <fstream>
using namespace std;

void readEntry( int& entry);

int main() {

    ifstream input;
    ofstream output;

    input.open("inFile");
    if(!input.is_open()){
        cout << "File is not open" << endl;
    }
    output.open("outFile");

    // read table dimensions and allocate 2D array
    int nRows, nCols;
    cout<<"Enter the number of rows and columns: ";
    cin >> nRows >> nCols;
    int** table = new int*[nRows];
    for(int i = 0; i < nRows; i++) {
        table[i] = new int[nCols];
    }

    // read table data
    cout<<"Enter your numbers: ";
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            try {
              readEntry(table[i][j]);
            }
            catch (int x) {
                    cout << "Entry " << i << "," << j << " not an integer, was set to " << x << ", now setting it to 0" << endl;
                    table[i][j] = 0;
                    cin.clear();
                    string tmp;
                    cin >> tmp;
            }
        }

        input.close();
        output.close();
    }



    // write table data to the screen in transposed order
    cout << nCols << " " << nRows << endl;
    for(int i = 0; i < nCols; i++) {
        for(int j = 0; j < nRows; j++) {
            cout << table[j][i] << " ";
        }
        cout << endl;
    }


    // free memory
    for(int i = 0; i < nRows; i++) {
        delete [] table[i];
    }
    delete [] table;

}

void readEntry( int& entry) {

    cin >> entry;
    if(cin.fail()) {
        throw entry;
    }
}