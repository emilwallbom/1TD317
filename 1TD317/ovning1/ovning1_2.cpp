#include <iostream>
using namespace std;

int main()
{
    int x; // sats 1: en variabel deklareras

    cout << "Mata in ett tal: "; // sats 2: En text skall stå inom " "
    cin >> x;                    // sats 3: programmet stannar: mata in
                                 //  ett tal, tryck <return>

    cout << "Du skrev talet "; // sats 4
    cout << x << endl;         // sats 5: här skrivs ditt tal ut
                               //  på skärman. INGA " " RUNT x!

    cout << "Mata in ett nytt tal: "; // sats 6
    cin >> x;                         // sats 7: x får ett nytt värde

    cout << "Nu skrev du talet: "; // sats 8
    cout << x << endl;             // sats 9: det nya värdet skrivs ut

    return 0;
}