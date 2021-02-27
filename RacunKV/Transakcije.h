#pragma once
#include "Racuni.h"
#include "Bankar.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Transakcije
{
public:
	Transakcije(int str, int i, string brp, string br);
	~Transakcije();

	int sifraTrans;
	int iznos;
	string brojRacPrim;
	string brojRacPos;
};

