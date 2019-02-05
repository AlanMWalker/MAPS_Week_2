/****************************************************************
Approximate Pi by throwing 'darts' at a 2x2 square with an inscribed circle.
Circle radius = 1, so area of circle = Pi. Ratio of dart hits in the circle to the number of throws
(hits/darts) approaches pi/4:
hitCircle      areaCircle      Pi
---------   =  ----------  =   --
dartsThrown    areaSquare      4
Results:
How many dart throws requested (in multiples of 1000's)? 1,000,000
Pi approx =  3.14153 using 1,000,000,000 darts
Pi actually= 3.14159  Error = 0.00192%
Elapsed time = 29.6 secs (on a SHU PC)
*****************************************************************/

#include <fstream>	
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <conio.h>
#include "hr_time.h"		//for stopwatches
#include <iomanip>
using namespace std;
CStopWatch s1;

unsigned long long hitCircle = 0;
unsigned long long dartsThrown = 9000000;
double x, y;
double PiApprox;
const double Pi(3.14159);

int main(void)
{
	//cout << "How many dart throws requested (in multiples of 1000's)? ";
	//cin >> dartsThrown;
	//dartsThrown *= 1000;

	dartsThrown = 99999999;  // to match Go solution

	if (dartsThrown != 0)
	{
		srand(999);		// seed random generator (constant used for repeatability)

		//***** START TIMING *********************************************************
		s1.startTimer();
		for (int i = 0; i < dartsThrown; ++i)
		{
			// 'Throw a dart' by generating two random coords x and y, scaled to 0.0 -> 1.0
			x = rand() / (double)RAND_MAX;
			y = rand() / (double)RAND_MAX;

			if ((x*x + y*y) < 1.0) ++hitCircle;		// did the dart hit the circle?
		}
		PiApprox = 4.0 * hitCircle / dartsThrown;
	}

	//***** STOP TIMING *********************************************************
	s1.stopTimer();
	cout << setprecision(6);
	cout << "\n\nPi approx =  " << PiApprox << " using " << dartsThrown << " darts";
	cout << "\nPi actually= " << Pi << "  Error = " << setprecision(3) << fabs(Pi - PiApprox)*(100.0 / Pi) << '%';
	cout << "\n\nElapsed time = " << s1.getElapsedTime() << " secs\n\nPress a key to finish...";

	ofstream PiResults;
	PiResults.open("PiResults.txt", ios::app);
	PiResults << "\n\nPi approx =  " << PiApprox << " using " << dartsThrown << " darts";
	PiResults << "\nPi actually= " << Pi << "  Error = " << setprecision(3) << fabs(Pi - PiApprox)*(100.0 / Pi) << '%';
	PiResults << "\n\nElapsed time = " << s1.getElapsedTime() << " secs";
	PiResults << "\n_______________________________________________";
	PiResults.close();

	while (!_kbhit());  //to hold console
	return (0);
}
