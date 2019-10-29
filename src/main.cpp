#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main( int argc, char *argv[] ) {
    ifstream productsFile;
    if (argc < 2) {
        cout << "The 1st parameter <data_path> must be set!";
        return 1;
    }

    productsFile.open(argv[1]);

    if (productsFile.fail()) {
        cout << "The products file was not found.";
        return 1;
    }

    string line;

    while(getline(productsFile, line)) {
        cout << line << endl;
    }

    productsFile.close();
    return 0;
}