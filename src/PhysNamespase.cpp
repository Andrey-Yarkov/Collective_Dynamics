#include "PhysNamespase.h"

namespace phys
{
	// Mass units
	double kg()
	{
		return 1.0;
	}
	double g()
	{
		return 1e-3 * kg();
	}
	double mg()
	{
		return 1e-6 * kg();
	}
	double Da()
	{
		return 1.66e-27 * kg();
	}

	// Amount of substance units
	double mole()
	{
		return 1.0;
	}
	double kmole()
	{
		return 1e3 * mole();
	}
	double mmole()
	{
		return 1e-3 * mole();
	}

	// Length units
	double m()
	{
		return 1.0;
	}
	double cm()
	{
		return 1e-2 * m();
	}
	double mm()
	{
		return 1e-3 * m();
	}
	double um()
	{
		return 1e-6 * m();
	}
	double nm()
	{
		return 1e-9 * m();
	}
	double angstrem()
	{
		return 1e-10 * m();
	}

	// Time units
	double s()
	{
		return 1.0;
	}
	double ms()
	{
		return 1e-3 * s();
	}
	double us()
	{
		return 1e-6 * s();
	}
	double ns()
	{
		return 1e-9 * s();
	}

	// Temperature units
	double K()
	{
		return 1.0;
	}

	// Amount of substance
	double mol()
	{
		return 1.0;
	}
	double kmol()
	{
		return 1e3 * mol();
	}
	double mmol()
	{
		return 1e-3 * mol();
	}

	// Force units
	double N()
	{
		return kg() * m() / pow(s(), 2.0);
	}

	// Pressure units
	double Pa()
	{
		return N() / pow(m(), 2.0);
	}
	double atm()
	{
		return 101325.0 * Pa();
	}

	// Energy units
	double J()
	{
		return N() * m();
	}
	double kJ()
	{
		return 1e3 * J();
	}
	double MJ()
	{
		return 1e6 * J();
	}
	double cal()
	{
		return 4.184 * J();
	}
	double kcal()
	{
		return 1e3 * cal();
	}
	double eV()
	{
		return 1.6e-19 * J();
	}
	double keV()
	{
		return 1e3 * eV();
	}
	double MeV()
	{
		return 1e6 * eV();
	}

	// Gas constant
	double R()
	{
		return 8.314 * J() / mol() / K();
	}
}