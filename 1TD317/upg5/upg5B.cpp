// SVAR PÅ FRÅGOR LÄNGST NER
// Programskal till Inlupp5A
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Anv�nd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// ist�llet f�r v�rdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26; // A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP inneh�ller bokstavsfrekvensen i %
// f�r fyra spr�k. TOLK_HJALP[0][0] �r frekvensen av
// bokstaven a f�r engelska. TOLK_HJALP[0][25] �r frekvensen av
// bokstaven z f�r engelska.
// Arrayen �r en GLOBAL KONSTANT och skall allts� ej skickas
// som parameter till den funktion som beh�ver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER] =
    {{8.27, 1.48, 2.94, 4.03, 11.78, 2.22, 1.72, 6.77, // engelska
      7.39, 0.12, 0.81, 3.76, 2.85, 6.71, 7.79, 1.54,
      0.05, 5.95, 6.69, 9.07, 2.66, 1.13, 2.14, 0.19,
      1.89, 0.03},
     {7.97, 1.40, 3.55, 3.79, 16.89, 1.02, 1.00, 0.75, // franska
      7.08, 0.38, 0.04, 5.51, 2.82, 8.11, 5.19, 2.78,
      1.01, 6.69, 8.35, 7.22, 6.09, 1.35, 0.02, 0.54,
      0.30, 0.15},
     {9.50, 1.11, 1.53, 5.30, 8.94, 1.74, 3.57, 3.94, // svenska
      3.98, 0.89, 3.26, 4.93, 3.41, 8.46, 5.01, 1.77,
      0.00, 6.73, 5.56, 9.20, 1.94, 2.42, 0.00, 0.05,
      0.45, 0.00},
     {5.12, 1.95, 3.57, 5.07, 16.87, 1.35, 3.00, 5.79, // tyska
      8.63, 0.19, 1.14, 3.68, 3.12, 10.64, 1.74, 0.42,
      0.01, 6.30, 6.99, 5.19, 3.92, 0.77, 1.79, 0.01,
      0.69, 1.24}};

// Globala variabler �r ej till�tna

//--------------------------------------------------------
// H�r kommer klassdeklarationen
class Text
{
private:
    string text_data;
    int histogram_abs[ANTAL_BOKSTAVER]{}; // Fyller arrayen med 0:or, tillåtet?
    int letter_count;
    double rel[ANTAL_BOKSTAVER]{};

public:
    Text();

    void setText(const string &nyText);
    bool beraknaHistogramAbs();
    void skrivHistogramAbs();
    void absTillRel();
    string tolka();
    void plottaHistogramRel();
    void beraknaHistogram();
};
// -------------------------------------------------------
// Funktionsdeklarationer:
// Funktionen namn_pa_fil
string namn_pa_fil();
// Funktionen inlasning
bool inlasning(const string &filename, string &file_content);

// Huvudprogram:
int main()
{
    // Deklarera variabler
    string text, filename, most_likely_language;
    Text minText; // Ett objekt av typen Text skapas

    filename = namn_pa_fil();

    if (inlasning(filename, text))
    {

        minText.setText(text);
        minText.beraknaHistogram();
        cout << "\nResultat för bokstäverna A-Z" << endl;

        most_likely_language = minText.tolka();
        cout << "Det är mest troligt att språket är " << most_likely_language << ".\n"
             << endl;

        minText.plottaHistogramRel();
    }

    return 0;
}

// -------------------------------------------------------
// H�r skriver du klassimplementationen
Text::Text()
{
    text_data = "";
    letter_count = 0;
}
void Text::setText(const string &nyText)
{
    text_data = nyText;
}

bool Text::beraknaHistogramAbs()
{
    char current;
    bool has_letters = false;

    for (int i = 0; i < text_data.length(); i++)
    {
        current = text_data[i];

        if (isalpha(current))
        {
            current = toupper(current);
            histogram_abs[current - 'A']++;
            letter_count++;
            has_letters = true;
        } // if isalpha slut
    }     // for loop genom inmatad sträng slut
    return has_letters;
}

void Text::skrivHistogramAbs()
{
    cout << "\nResultat för bokstäverna A-Z" << endl;
    cout << "\nTotala antalet bokstäver: " << letter_count << endl;
    cout << "Bokstavsfördelning:\n"
         << endl;
    char letter;
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
    {

        cout << char('A' + i) << ": " << histogram_abs[i] << endl;
    }
}

void Text::absTillRel()
{
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
    {
        rel[i] = static_cast<double>(histogram_abs[i]) / letter_count * 100.0;
    }
}
string Text::tolka()
{
    double min_square_sum = 100;
    int most_likely_language = -1;
    string lang_arr[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};

    cout << "\nTotala antalet bokstäver: " << letter_count << endl;

    for (int language = 0; language < ANTAL_SPRAK; language++)
    {
        double square_sum = 0.0;

        for (int letter = 0; letter < ANTAL_BOKSTAVER; letter++)
        {
            double difference = rel[letter] - TOLK_HJALP[language][letter];
            square_sum += difference * difference;
        }

        if (square_sum < min_square_sum)
        {
            min_square_sum = square_sum;
            most_likely_language = language;
        }

        cout << lang_arr[language] << " har kvadratsumma= " << square_sum << endl;
    }

    return lang_arr[most_likely_language];
}
void Text::plottaHistogramRel()
{
    char letter = 'A';

    cout << "Bokstavsfördelning:\n"
         << endl;

    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
    {
        cout << letter << " ";

        // Varje 2% motsvarar en symbol
        for (int j = 0; j < rel[i] * 2; j++)
        {
            cout << "*";
        }

        cout << endl;
        letter++;
    } // for loop genom alla bokstäver slut
}

void Text::beraknaHistogram()
{
    if (beraknaHistogramAbs())
        absTillRel();
}
//--------------------------------------------------------
// Funktionsdefinitioner:
string namn_pa_fil()
{
    string filename;
    string filetype_txt = ".txt";

    cout << "Namn på fil: " << endl;
    cin >> filename;

    if (filename.length() < 4 || filename.rfind(filetype_txt) != filename.length() - 4)
        filename.append(filetype_txt);

    return filename;
}

bool inlasning(const string &filename, string &file_content)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Det finns ingen fil med namnet " << filename << endl;
        return false;
    }

    char character;
    while (file.get(character))
    {
        file_content.push_back(character);
    }

    file.close();
    return true;
}
// -------------------------------------------------------
// Rapport om uppgiften
/*
1. Finns det någon anledning varför vi beräknar både det absoluta
och det relativa histogrammet i samma funktionsanrop?

SVAR: För att huvudprogrammet blir simplare och vi vill inte
beräkna rel i onödan om det inte finns några bokstäver och
huvudprogrammet blir kortare om vi lämnar detta åt en metod i klassen.

2. Tänk dig att vi lägger till en rad sist i huvudprogrammet
som anropar funktionen setText med en ny text, då får vi
resultatet att attributet text ändras, men histogrammen
fortfarande är desamma och alltså inte hör ihop med den aktuella texten.
Finns det något sätt att lösa det problemet?
Du behöver bara svara med ord, inte programmera något nytt.

SVAR: setText() skulle kunna anropa beraknaHistogram()

3. Skulle man kunna inkludera funktionerna namn_pa_fil
och inlasning i klassen? Skulle det göra någon skillnad på resultatet?
Finns det några fördelar med att använda samma funktioner som tidigare?

SVAR: Ja det skulle vara möjligt och kunna ge exakt samma resultat men
det vore onödigt att ha detta i klassen. Detta eftersom klassen kan
användas på flera sätt som i t.ex 5A där vi andvänder cin för att
setta texten. Om vi vill expandera programmet är det också troligt
att vi vill läsa in fler filer på samma sätt och det är då opraktiskt
att ha inläsningen bunden till klassen Text.
*/