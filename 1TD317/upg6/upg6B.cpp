#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

// Klassdeklarationer

class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string *kompisar;

public:
    Transaktion();
    ~Transaktion()
    {
        delete[] kompisar;
        kompisar = 0;
    }
    Transaktion &operator=(const Transaktion &t);
    string hamtaNamn();
    double hamtaBelopp();
    int hamtaAntalKompisar();
    bool finnsKompis(const string &namnet);
    bool lasIn(istream &is);
    void skrivUt(ostream &os);
    void skrivTitel(ostream &os);
};

class Person
{
private:
    string namn;
    double betalat_andras; // ligger ute med totalt
    double skyldig;        // skyldig totalt

public:
    Person() : betalat_andras(0), skyldig(0){};
    Person(const string &namn, double betalat_andras, double skyldig) : namn(namn), betalat_andras(betalat_andras), skyldig(skyldig){};
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    void skrivUt(ostream &os);
};

class PersonLista
{
private:
    int antal_personer;
    Person *personer;

public:
    PersonLista() : antal_personer(0), personer(0){};
    ~PersonLista()
    {
        delete[] personer;
        personer = 0;
    };
    void laggTill(Person ny_person);
    void skrivUtOchFixa(ostream &os);
    double summaSkyldig();
    double summaBetalat();
    bool finnsPerson(const string &namn);
};

class TransaktionsLista
{
private:
    int antal_transaktioner;
    Transaktion *transaktioner;

public:
    TransaktionsLista() : antal_transaktioner(0), transaktioner(0){};
    ~TransaktionsLista()
    {
        delete[] transaktioner;
        transaktioner = 0;
    };
    TransaktionsLista &operator=(const TransaktionsLista &tl);
    void lasIn(istream &is);
    void skrivUt(ostream &os);
    void laggTill(Transaktion &t);
    double totalKostnad();
    double liggerUteMed(const string &namnet);
    double arSkyldig(const string &namnet);
    PersonLista FixaPersoner();
};

// Huvudprogram
int main()
{
    cout << "Startar med att läsa från en fil." << endl;

    TransaktionsLista transaktioner;
    std::ifstream is("resa.txt");
    transaktioner.lasIn(is);

    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Välj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;

        cin >> operation;
        cout << endl;

        switch (operation)
        {
        case 1:
        {
            transaktioner.skrivUt(cout);
            break;
        }
        case 2:
        {
            Transaktion transaktion;
            cout << "Ange transaktion i följande format" << endl;
            transaktion.skrivTitel(cout);
            transaktion.lasIn(cin);
            transaktioner.laggTill(transaktion);
            break;
        }
        case 3:
        {
            cout << "Den totala kostnanden för resan var "
                 << transaktioner.totalKostnad() << endl;
            break;
        }
        case 4:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ar_skyldig = transaktioner.arSkyldig(namn);
            if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " är skyldig " << ar_skyldig << endl;
            break;
        }
        case 5:
        {
            cout << "Ange personen: ";
            string namn;
            cin >> namn;
            double ligger_ute_med = transaktioner.liggerUteMed(namn);
            if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
            else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
            break;
        }
        case 6:
        {
            cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
            PersonLista lista = transaktioner.FixaPersoner();
            lista.skrivUtOchFixa(cout);
            break;
        }
        }
    }

    std::ofstream os("transaktioner.txt");
    transaktioner.skrivUt(os);

    return 0;
}

// Klassdefinitioner

// Transaktion
// Konstruktor
Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0.0;
    antal_kompisar = 0;
    kompisar = 0;
}

// Selektorer
string Transaktion::hamtaNamn()
{
    return namn;
}

double Transaktion::hamtaBelopp()
{
    return belopp;
}

int Transaktion::hamtaAntalKompisar()
{
    return antal_kompisar;
}

// Övriga metoder
bool Transaktion::finnsKompis(const string &namnet)
{
    for (int i = 0; i < antal_kompisar; i++)
        if (kompisar[i] == namnet)
            return true;
    return false;
}

bool Transaktion::lasIn(istream &is)
{
    delete[] kompisar;
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;

    kompisar = new string[antal_kompisar];

    for (int i = 0; i < antal_kompisar; i++)
        is >> kompisar[i];

    return !is.eof();
}

void Transaktion::skrivUt(ostream &os)
{
    os << setw(8) << left << datum;
    os << setw(8) << left << typ;
    os << setw(8) << left << namn;
    os << setw(8) << left << belopp;
    os << setw(8) << left << antal_kompisar;

    for (int i = 0; i < antal_kompisar; i++)
        os << setw(8) << left << kompisar[i];
    os << endl;
}
void Transaktion::skrivTitel(ostream &os)
{
    os << "Datum   Typ     Namn    Belopp  Antal och lista av kompisar" << endl;
}

// Tilldelningsoperator
Transaktion &Transaktion::operator=(const Transaktion &t)
{
    if (this != &t)
    {
        delete[] kompisar;
        datum = t.datum;
        typ = t.typ;
        namn = t.namn;
        belopp = t.belopp;
        antal_kompisar = t.antal_kompisar;
        kompisar = new string[antal_kompisar];
        for (int i = 0; i < antal_kompisar; i++)
            kompisar[i] = t.kompisar[i];
    }
    return *this;
}

// TransaktionsLista
void TransaktionsLista::laggTill(Transaktion &t)
{
    Transaktion *temp_trans = 0;
    temp_trans = new Transaktion[antal_transaktioner + 1];

    for (int i = 0; i < antal_transaktioner; i++)
    {
        temp_trans[i] = transaktioner[i];
    }

    delete[] transaktioner;

    transaktioner = temp_trans;
    antal_transaktioner++;
    transaktioner[antal_transaktioner - 1] = t;
}

void TransaktionsLista::skrivUt(ostream &os)
{
    os << "Antal trans = " << antal_transaktioner << endl;
    transaktioner->skrivTitel(os);
    for (int i = 0; i < antal_transaktioner; i++)
        transaktioner[i].skrivUt(os);
}

void TransaktionsLista::lasIn(istream &is)
{
    // En inläsningsmetod i klassen TransaktionsLista.
    Transaktion t;

    // Så länge det går bra att läsa (filen ej slut)
    while (t.lasIn(is))
        laggTill(t);
}

double TransaktionsLista::totalKostnad()
{
    double summa = 0;
    for (int i = 0; i < antal_transaktioner; i++)
        summa += transaktioner[i].hamtaBelopp();
    return summa;
}

double TransaktionsLista::liggerUteMed(const string &namn)
{
    double summa = 0.;
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namn)
            summa += transaktioner[i].hamtaBelopp() *
                     (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
    return summa;
}

double TransaktionsLista::arSkyldig(const string &namnet)
{
    double tot = 0;
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].finnsKompis(namnet))
            tot += transaktioner[i].hamtaBelopp() * (1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));

    return tot;
}

PersonLista TransaktionsLista::FixaPersoner()
{
    PersonLista pl;
    string namn;
    for (int i = 0; i < antal_transaktioner; i++)
    {
        if (!(pl.finnsPerson(transaktioner[i].hamtaNamn())))
        {
            namn = transaktioner[i].hamtaNamn();
            Person p(namn, liggerUteMed(namn), arSkyldig(namn));
            pl.laggTill(p);
        }
    }

    return pl;
}

// Person
// Selektorer
string Person::hamtaNamn()
{
    return namn;
}

double Person::hamtaBetalat()
{
    return betalat_andras;
}

double Person::hamtaSkyldig()
{
    return skyldig;
}

// Övriga metoder
void Person::skrivUt(ostream &os)
{
    os << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ". ";
    if (betalat_andras - skyldig > 0)
        os << "Ska ha " << betalat_andras - skyldig << " från potten!";
    else
        os << "Ska ge " << abs(betalat_andras - skyldig) << " till potten!";
    os << endl;
}

// PersonLista
void PersonLista::skrivUtOchFixa(ostream &os)
{
    for (int i = 0; i < antal_personer; i++)
        personer[i].skrivUt(os);
}
void PersonLista::laggTill(Person ny_person)
{
    Person *temp_pers = 0;
    temp_pers = new Person[antal_personer + 1];

    for (int i = 0; i < antal_personer; i++)
        temp_pers[i] = personer[i];

    delete[] personer;
    personer = temp_pers;
    antal_personer++;
    personer[antal_personer - 1] = ny_person;
}

double PersonLista::summaSkyldig()
{
    double summa = 0;
    for (int i = 0; i < antal_personer; i++)
        summa += personer[i].hamtaSkyldig();
    return summa;
}

double PersonLista::summaBetalat()
{
    double summa = 0;
    for (int i = 0; i < antal_personer; i++)
        summa += personer[i].hamtaBetalat();
    return summa;
}

bool PersonLista::finnsPerson(const string &namn)
{
    for (int i = 0; i < antal_personer; i++)
        if (personer[i].hamtaNamn() == namn)
            return true;
    return false;
}