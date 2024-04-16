#include <iostream>
using namespace std;

struct Hidrocarboneto
{
    int C;
    int H;
};


int main () {
    Hidrocarboneto* elemento = new Hidrocarboneto;
    cin >> elemento->C >> elemento->H;

    cout << elemento->C * 12 + elemento->H;

    delete[] elemento;

    return 0;
}