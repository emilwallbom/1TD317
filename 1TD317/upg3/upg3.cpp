#include <iostream>
using namespace std;

// Deklarationer av funktionerna

// Skriver en kort förklaring av programmet
void skrivInfo();
// Läser in ett heltal och returnerar det
int lasEttTal();
// Låter användaren välja operator och returnerar inmatad char
char lasOp();
// Sätter två tal i storleksordning
void ordna(int &tal1, int &tal2);
// Utför beräkningar på två tal beroende på vald operartor
int berakna(int nedre, int ovre, char op);
// Skriver ut inputat heltal med ledtext
void skrivResultat(int resultat);

int main()
{
    int tal1, tal2, svar;
    char op;

    skrivInfo();

    tal1 = lasEttTal();
    tal2 = lasEttTal();
    op = lasOp();

    ordna(tal1, tal2);

    svar = berakna(tal1, tal2, op);

    skrivResultat(svar);

    return 0;
}

// Definitioner av funktionerna

void skrivInfo()
{
    cout << "Detta program beräknar olika operationer på två heltal." << endl;
}

int lasEttTal()
{
    int tal;
    cout << "Skriv in ett heltal: ";
    cin >> tal;
    return tal;
}

char lasOp()
{
    char op;
    cout << "Välj en av följande beräkningstyper (a - Addera, m - Multiplicera, k - Kvadratsumma): ";
    cin >> op;
    return op;
}

void ordna(int &tal1, int &tal2)
{
    if (tal1 > tal2)
    {
        int temp = tal1;
        tal1 = tal2;
        tal2 = temp;
    }
}

int berakna(int nedre, int ovre, char op)
{
    int resultat = 0;
    int temp = 1;
    switch (op)
    {
    // Summerar alla tal mellan nedre-ovre
    case 'a':
        for (int i = nedre; i <= ovre; i++)
        {
            resultat += i;
        }
        break;

    // Multiplicerar alla tal mellan nedre-ovre
    case 'm':
        for (int i = nedre; i <= ovre; i++)
        {
            temp *= i;
        }
        resultat = temp;
        break;

    // Beräknar kvadratsumman mellan nedre-ovre
    case 'k':
        for (int i = nedre; i <= ovre; i++)
        {
            resultat += i * i;
        }
        break;

    default:
        cout << "Ogiltig beräkningstyp vald" << endl;
        break;
    }

    return resultat;
}

void skrivResultat(int resultat)
{
    cout << "Resultatet av beräkningen är: " << resultat << endl;
}
