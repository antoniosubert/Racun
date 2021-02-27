#include "Klijent.h"
#include <iostream>
#include <string>
#include "pch.h"
using namespace std;


Klijent::Klijent(string i, string p, string oi, string ad, int sf) : Covjek(i, p ,oi)
{
	adresa = ad;
	sifra = sf;
}

Klijent::~Klijent()
{
}