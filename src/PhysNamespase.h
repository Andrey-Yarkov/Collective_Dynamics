#pragma once
#include <math.h>

namespace phys
{
	// Mass units
	double kg();
	double g();
	double mg();
	double Da();

	// Amount of substance units
	double mole();
	double kmole();
	double mmole();

	// Length units
	double m();
	double cm();
	double mm();
	double um();
	double nm();
	double angstrem();

	// Time units
	double s();
	double ms();
	double us();
	double ns();

	// Temperature units
	double K();

	// Amount of substance
	double mol();
	double kmol();
	double mmol();

	// Force units
	double N();

	// Pressure units
	double Pa();
	double atm();

	// Energy units
	double J();
	double kJ();
	double MJ();
	double cal();
	double kcal();
	double eV();
	double keV();
	double MeV();

	// Gas constant
	double R();
}