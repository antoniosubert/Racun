#include "Bankar.h"
#include "pch.h"
#include <iostream>
#include <string>
using namespace std;


Bankar::Bankar(string i, string p, string oi, int s) : Covjek(i, p, oi)
{
	sifra = s;
}

Bankar::~Bankar()
{
}