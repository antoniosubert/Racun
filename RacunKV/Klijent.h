#pragma once
#include "Covjek.h"
#include <iostream>
#include <string>
using namespace std;


class Klijent : public Covjek
{
public:
	Klijent(string i, string p, string oi, string ad, int sf);
	~Klijent();

	string adresa;
	int sifra;
};

