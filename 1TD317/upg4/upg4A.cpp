// SVAR PÅ FRÅGOR LÄNGST NER
// Programskal till inl�mningsuppgift 4 - deluppgift A
//
// Hanterar fallet med 26 bokst�ver A-Z

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// Anv�nd g�rna denna globala konstant i programmet
// i st�llet f�r v�rdet 26
const int ANTAL_BOKSTAVER = 26; // A-Z
// Globala variabler �r ej till�tna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Anv�nd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string text_data, int histogram[]);

// Funktionen skriv_histogram_abs
void skriv_histogram_abs(int histogram[], int letter_count);
//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
  string text_data;
  int letter_count;
  int histogram[ANTAL_BOKSTAVER] = {0};

  // L�s in en rad med text fr�n tangentbordet
  cout << "Ge en rad med text: " << endl;
  getline(cin, text_data);

  // Anropa funktionen berakna_histogram_abs som ber�knar histogrammet
  // och antalet bokst�ver.
  letter_count = berakna_histogram_abs(text_data, histogram);

  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  skriv_histogram_abs(histogram, letter_count);

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

void skriv_histogram_abs(int histogram[], int letter_count)
{
  cout << "\nResultat för bokstäverna A-Z" << endl;
  cout << "\nTotala antalet bokstäver: " << letter_count << endl;
  cout << "Bokstavsfördelning:\n"
       << endl;
  char letter;
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {

    cout << char('A' + i) << ": " << histogram[i] << endl;
  }
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