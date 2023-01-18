/*
Uppgift 5 Klasser del A
Av: Jens Ekenblad
Datum: 12/07-2022
*/

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
  string texten;
  int histogram[ANTAL_BOKSTAVER];
  int antal;

public:
  Text();
  void setText(const string &nytext);
  bool beraknaHistogramAbs();
  void skrivHistogramAbs();
};

// -------------------------------------------------------

// Huvudprogram:

int main()
{
  // Deklarera variabler
  string text;
  Text minText; // Ett objekt av typen Text skapas

  // L�s in en rad med text fr�n tangentbordet
  cout << "Ge en rad med text:" << endl;
  getline(cin, text);

  // Skicka str�ngen text till objektet minText
  minText.setText(text);

  // Ber�kna och skriv ut histogrammet
  minText.beraknaHistogramAbs();
  minText.skrivHistogramAbs();

  return 0;
}

// -------------------------------------------------------
// H�r skriver du klassimplementationen

Text::Text()
{
  texten = "";
  antal = 0;
  std::fill(histogram, histogram + ANTAL_BOKSTAVER, 0);
}

void Text::setText(const string &nytext)
{
  texten = nytext;
}

bool Text::beraknaHistogramAbs()
{

  bool exists;

  if (texten.length() > 0)
  {
    exists = true;
    for (int i = 0; i < texten.length(); i++)
    {
      char c = texten.at(i);
      if (isalpha(c))
      {
        antal++;
        c = tolower(c);
        int index = c - 97; // alpha.find(c);
        if (index < 26)
          histogram[index]++;
      }
    }
  }
  else
  {
    exists = false;
  }

  return exists;
}

void Text::skrivHistogramAbs()
{
  cout << "Totala antalet bokstaver:" << antal << endl;
  cout << "Bokstavsfordelning:" << endl;
  for (int i = 0; i < sizeof(histogram) / sizeof(histogram[0]); i++)
  {
    cout << (char)(toupper(i + 97)) << ": " << histogram[i] << endl;
  }
}

//--------------------------------------------------------
// Funktionsdefinitioner:

// -------------------------------------------------------
// Rapport om uppgiften
