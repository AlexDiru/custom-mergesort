/*
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define DEBUG

#include "vectormergesort.h"

int main()
{
	srand(time(NULL));

	#ifdef _WIN32
	system("Color F5");
	#endif
	
	cout << "# elements\tfunctions" << endl;
	for (int n=50000; n<=1000000; n+=50000)
	{
		int numberOfElements = n;
		vector<float> arr;

		for (int i=0; i<numberOfElements; i++)
			arr.push_back(rand()%1000000-500000);

		cout << n << endl;

		vector<float> output(mergesortNaN(arr));
	}

	cout << "\nPress any key to continue . . .";
	cin.get();

	return 0;
}
*/