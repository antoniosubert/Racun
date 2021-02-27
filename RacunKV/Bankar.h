#pragma once
#include "Covjek.h"
#include <iostream>
#include <string>
using namespace std;

class Bankar : public Covjek
{
public:
	Bankar(string i, string p, string oi, int s);
	~Bankar();

	int sifra;
};

