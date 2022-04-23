#include <iostream>
#include <fstream>
#include <string>
#include "CSVManager/CSVfile.h"
using namespace std;

int main()
{
    fstream file;
    file.open("../src/data/plik.txt", ios::out);
    if (file.is_open())
    {
        file << "Jakis tekst" << endl;
        file << "to jest druga linijka" << endl;
        file.close();
    }
    CSVfile<RowType> myfile("../src/data/example.csv");
    //  cout << myfile.getRow(1).toStrings()[0];
    return 0;
}
// CSVfile<Player> playerFile(pathEx);