#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream out("teste.txt");
    out << "oi.";
    std::cout << "Hello, World!" << std::endl;
    out.close();
    return 0;
}