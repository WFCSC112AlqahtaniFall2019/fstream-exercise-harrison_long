#include <iostream>
#include <fstream>
using namespace std;

void readEntry(ifstream& in, int& entry);

int main() {

    ifstream input;
    ofstream output;

    input.open("../inFile.txt");
    if(!input.is_open()){
        cout << "File is not open" << endl;
        return 1;
    }
    output.open("../outFile.txt");

    // read table dimensions and allocate 2D array
    int nRows, nCols;
    input >> nRows >> nCols;
    int** table = new int*[nRows];
    for(int i = 0; i < nRows; i++) {
        table[i] = new int[nCols];
    }

    // read table data
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            try {
              readEntry(input, table[i][j]);
            }
            catch (int x) {
                    output << "Entry " << i << "," << j << " not an integer, was set to " << x << ", now setting it to 0" << endl;
                    table[i][j] = 0;
                    input.clear();
                    string tmp;
                    input >> tmp;

            }
            input.clear();

        }
    }


    // write table data to the screen in transposed order
    output << nCols << " " << nRows << endl;
    for(int i = 0; i < nCols; i++) {
        for(int j = 0; j < nRows; j++) {
            output << table[j][i] << " ";
        }
        output << endl;
    }


    // free memory
    for(int i = 0; i < nRows; i++) {
        delete [] table[i];
    }
    delete [] table;

    input.close();
    output.close();

}

void readEntry( ifstream& in, int& entry) {

    in >> entry;
    if(in.fail()) {
        throw entry;
    }
}