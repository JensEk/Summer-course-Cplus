/*
Uppgift: Strängar och arrayer, del A
Av: Jens Ekenblad
Datum: 07/07-2022
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// Använd gärna denna globala konstant i programmet
// i stället för värdet 26
const int ANTAL_BOKSTAVER = 26; // A-Z
// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string rad, string alpha, int freq[]);
// Funktionen skriv_histogram_abs
void skriv_histogram_abs(string alpha, int freq[], int len, int antal);
//--------------------------------------------------------
// Huvudprogram:

// Läser in en string och beräknar antalet bokstäver och skriver ut dess histogram över förekomst.
int main()
{
  // Deklarera variabler
  string rad;
  string alpha = "abcdefghijklmnopqrstuvwxyz";
  int freq[ANTAL_BOKSTAVER] = {0};

  // Läs in en rad med text från tangentbordet
  getline(cin, rad);

  // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
  // och antalet bokstäver.
  int antal = berakna_histogram_abs(rad, alpha, freq);
  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  skriv_histogram_abs(alpha, freq, ANTAL_BOKSTAVER, antal);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

// Tar in an angiven string med text, ett alfapet och en pekare till en array som uppdateras med varje bokstavs frekvens i stringen rad. Returnerar sedan totala antelt bokstäver.
int berakna_histogram_abs(string rad, string alpha, int freq[])
{
  int antal = 0;
  for (int i = 0; i < rad.length(); i++)
  {

    char c = rad.at(i);
    if (isalpha(c))
    {
      antal++;
      c = tolower(c);
      int index = alpha.find(c);
      if (index < 26)
        freq[index]++;
    }
  }
  return antal;
}

// Skriver ut varje bokstavs frekvens som blivit uppdateras i arrayen freq från den tidigare inlästa stringen.
void skriv_histogram_abs(string alpha, int freq[], int len, int antal)
{

  cout << "Totala antalet bokstaver:" << antal << endl;
  cout << "Bokstavsfordelning:" << endl;
  for (int i = 0; i < len; i++)
  {
    cout << (char)(toupper(alpha.at(i))) << ": " << freq[i] << endl;
  }
}
