#include "Transakcije.h"
#include "Bankar.h"
#include <iostream>
#include <string>
#include "pch.h"
using namespace std;

Transakcije::Transakcije(int str, int i, string brp, string br)
{
	sifraTrans = str;
	iznos = i;
	brojRacPrim = brp;
	brojRacPos = br;
}

Transakcije::~Transakcije()
{
}
