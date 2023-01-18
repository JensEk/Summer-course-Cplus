/*
Uppgift 5 Klasser del B
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
  double histogramRel[ANTAL_BOKSTAVER];
  int antal;

public:
  Text();
  void setText(const string &nytext);
  bool beraknaHistogramAbs();
  void skrivHistogramAbs();
  void absTillRel();
  void plottaHistogramRel();
  void beraknaHistogram();
  string tolka();
};

// Här kommer Funktionsdeklarationer:
// Funktionen namn_pa_fil
string namn_pa_fil(string inputNamn);

// Funktionen inlasning
string inlasning(string filnamn);

// -------------------------------------------------------

// Huvudprogram:

int main()
{
  // Deklarera variabler
  string text;
  string inputNamn;
  string filnamn;
  string closestLang;
  Text minText; // Ett objekt av typen Text skapas

  cout << "Ange filnamn: " << endl;
  getline(cin, inputNamn);
  filnamn = namn_pa_fil(inputNamn);
  text = inlasning(filnamn);

  minText.setText(text);

  // Ber�kna och skriv ut det relativa histogrammet och gissa språket
  minText.beraknaHistogram();
  closestLang = minText.tolka();
  cout << "Det är mest troligt att språket är " << closestLang << endl;
  minText.plottaHistogramRel();

  return 0;
}

// -------------------------------------------------------
// H�r skriver du klassimplementationen

// Default konstruktor
Text::Text()
{
  texten = "";
  antal = 0;
  std::fill(histogram, histogram + ANTAL_BOKSTAVER, 0);
}

// Setter
void Text::setText(const string &nytext)
{
  texten = nytext;
}

// Metoden kollar om inlästa texten har en längd > 0 och isåfall läser in varje enskild bokstav där 'a' motsvarar int 97 därav omvandlingen för hålla koll på alfabetet.
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

// Metoden är samma som i uppgift 4 där varje bokstav skrivs ut och dess frekvens. +97 används för att börja från 'a'.
void Text::skrivHistogramAbs()
{
  cout << "Totala antalet bokstaver:" << antal << endl;
  cout << "Bokstavsfordelning:" << endl;
  for (int i = 0; i < sizeof(histogram) / sizeof(histogram[0]); i++)
  {
    cout << (char)(toupper(i + 97)) << ": " << histogram[i] << endl;
  }
}

// Samma tillvägagångsätt som i uppg4 för att omvandla abs till rel frekvens.
void Text::absTillRel()
{
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    double f = (histogram[i] / (double)antal) * 100;
    int s = (int)(f * 100 + 0.5);
    histogramRel[i] = s / (double)100;
  }
}

// Samma tillvägagångsätt som i uppg4 för att skriva ut den relativa frekevensen där +97 motsvarar char 'a'.
void Text::plottaHistogramRel()
{

  cout << "Bokstavsfördelning: " << endl;
  for (int i = 0; i < ANTAL_BOKSTAVER; i++)
  {
    string ch;
    for (int j = 0; j < (int)(histogramRel[i] / 0.5); j++)
    {
      ch.append("*");
    }

    cout << (char)(toupper(i + 97)) << " " << ch << endl;
  }
}

// metoden beraknaHistogramAbs returnerar true/false beroende om det finns några bokstäver i texten.
void Text::beraknaHistogram()
{
  if (beraknaHistogramAbs())
  {
    absTillRel();
  }
  else
  {
    cout << "Filen innerhåller inga bokstäver, programmet avslutas" << endl;
    exit(EXIT_FAILURE);
  }
}

// Beräknar vilket språk som texten sannolikt är skriven av med samma tillvägagångsätt som i uppg4 med skillnaden att språket returneras.
string Text::tolka()
{
  double closestSum = MAXFLOAT;
  string closestLang;
  string lang[4] = {"engelska", "franska", "svenska", "tyska"};
  double langSum[4] = {0.0};

  cout << "Totala antalet bokstäver: " << antal << endl;

  for (int i = 0; i < sizeof(TOLK_HJALP) / sizeof(TOLK_HJALP[0]); i++)
  {

    for (int j = 0; j < sizeof(TOLK_HJALP[i]) / sizeof(TOLK_HJALP[0][0]); j++)
    {
      langSum[i] += (TOLK_HJALP[i][j] - histogramRel[j]) * (TOLK_HJALP[i][j] - histogramRel[j]);
    }

    cout << lang[i] << " har kvadratsumma "
         << " = " << langSum[i] << endl;
    if (langSum[i] < closestSum)
    {
      closestSum = langSum[i];
      closestLang = lang[i];
    }
  }

  return closestLang;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

// Kopierad från uppg4.
// Tar in ett angivet filnamn och kontrollerar om det slutar på .txt annars läggs det tills i slutet och returneras.
string namn_pa_fil(string inputNamn)
{

  string filnamn;
  if (inputNamn.rfind(".txt") != (inputNamn.length() - 4))
  {
    filnamn = inputNamn.append(".txt");
  }
  else
  {
    filnamn = inputNamn;
  }

  return filnamn;
}

// Kopierad från uppg4.
// Läser in filen från angivet filnamn och kontrollerar filen existerar, sedan läser in tecken varje tecken och returnerar kompletta stringen
string inlasning(string filnamn)
{

  string text;
  ifstream fin(filnamn.c_str());

  if (!fin)
  {
    cout << "Det finns ingen fil med namnet " << filnamn << endl;
    exit(EXIT_FAILURE);
  }

  char in;
  fin.get(in);
  while (!fin.eof())
  {
    text.push_back(in);
    fin.get(in);
  }
  return text;
}

// -------------------------------------------------------
// Rapport om uppgiften
