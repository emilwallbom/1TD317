// SVAR PÅ FRÅGOR LÄNGST NER
// Programskal till inl�mningsuppgift 4 - deluppgift B
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
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Anv�nd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
// denna skrevs i A-uppgiften och kan klippas in h�r
int berakna_histogram_abs(string text_data, int histogram[]);

// Funktionen abs_till_rel
void abs_till_rel(double rel[], int abs[], int letter_count);

// Funktionen plotta_histogram_rel
void plotta_histogram_rel(double histogram_rel[]);

// Funktionen tolkning
void tolkning(double beraknat_histogram[]);

// Funktionen namn_pa_fil
string namn_pa_fil();

// Funktionen inlasning
bool inlasning(const string &filename, string &file_content);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  string text_data, filename, file_content;
  int letter_count;
  int histogram[ANTAL_BOKSTAVER] = {0};
  double rel[ANTAL_BOKSTAVER];

  filename = namn_pa_fil();

  if (inlasning(filename, file_content))
  {
    cout << "\nResultat för bokstäverna A-Z" << endl;

    letter_count = berakna_histogram_abs(file_content, histogram);

    cout << "\nTotala antalet bokstäver: " << letter_count << endl;

    abs_till_rel(rel, histogram, letter_count);
    tolkning(rel);
    plotta_histogram_rel(rel);
  }

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(string text_data, int histogram[])
{
  char current;
  int letter_count = 0;

  for (int i = 0; i < text_data.length(); i++)
  {
    current = text_data[i];

    if (isalpha(current))
    {
      current = toupper(current);
      histogram[current - 'A']++;
      letter_count++;
    } // if isalpha slut
  }   // for loop genom inmatad sträng slut

  return letter_count;
}

void abs_till_rel(double rel[], int abs[], int letter_count)
{

  double sum = 0;
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    rel[i] = static_cast<double>(abs[i]) / letter_count * 100.0;
  }
}

void plotta_histogram_rel(double histogram_rel[])
{

  char letter = 'A';

  cout << "Bokstavsfördelning:\n"
       << endl;

  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    cout << letter << " ";

    // Varje 2% motsvarar en symbol
    for (int j = 0; j < histogram_rel[i] * 2; j++)
    {
      cout << "*";
    }

    cout << endl;
    letter++;
  } // for loop genom alla bokstäver slut
}

void tolkning(double rel[])
{
  double min_square_sum = 100;
  int most_likely_language = -1;
  string lang_arr[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};

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

    cout << "Kvadratsumma för språk " << lang_arr[language] << ": " << square_sum << endl;
  }

  cout << "Det är mest troligt att språket är " << lang_arr[most_likely_language] << ".\n"
       << endl;
}

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
1. I lösningsförslagen tipsar vi om att du ska skapa/ladda
hem en fil med bara lite innehåll medan man testar sitt program.
Varför, tror du?

SVAR: För att det är lättare att felsöka och se vart i programmet fel uppstår.

2. Texten i filen lagerlof.txt innehåller de svenska bokstäverna å, ä och ö.
Som programmet fungerar nu räknas inte dessa bokstäver med alls.
Hur skulle man gå tillväga för att också inkludera å, ä och ö i histogrammet.
Du behöver inte ge en program-lösning, men resonera kring hur man skulle kunna göra.

SVAR: Man skulle kunna använda ascii-koderna för å,ä,ö för att inkludera dem som ett
special fall med t.ex en switch eller flera if satser.
*/
