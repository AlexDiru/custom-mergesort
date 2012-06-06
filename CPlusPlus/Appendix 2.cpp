/*
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

#include "vectormergesort.h"

int main()
{
	srand(time(NULL));
	
	float ftwoElementList[] = { 123.43, 123.429 };
	float flongList[] = { MINUS_ZERO, 1, 3, 91.3, 234.2, INFINITY, NAN, 234, MINUS_ZERO, 0, MINUS_INFINITY, NAN, -213.2, NAN, -1293890.234 };
	float fzeroList[] = { 0, MINUS_ZERO, 0, 0, 0, MINUS_ZERO, 0, 0, MINUS_ZERO, 0, MINUS_ZERO, MINUS_ZERO, MINUS_ZERO, 0, MINUS_ZERO };

	vector<float> emptyList;
	vector<float> oneElementList; oneElementList.push_back(2.7);
	vector<float> twoElementList(ftwoElementList, ftwoElementList + sizeof(ftwoElementList)/sizeof(float) );
	vector<float> longList(flongList, flongList + sizeof(flongList)/sizeof(float) );
	vector<float> zeroList(fzeroList, fzeroList + sizeof(fzeroList)/sizeof(float) );

	#ifdef _WIN32
	system("Color F5"); //colour the console, to save on black ink being used when screenshots are required
	#endif

	vector<float> output;
	
	//sort empty list
	cout << "~~~~~~~~~~~~~~~~~~~~~~\nSorting empty list: ";
	printVector(emptyList);
	output = mergesortNaN(emptyList);
	cout << "\nSorted: ";
	printVector(output);
	cout << "\n";

	//sort one element list
	cout << "~~~~~~~~~~~~~~~~~~~~~~\nSorting one element list: ";
	printVector(oneElementList);
	output = mergesortNaN(oneElementList);
	cout << "\nSorted: ";
	printVector(output);
	cout << "\n";

	//sort two element list
	cout << "~~~~~~~~~~~~~~~~~~~~~~\nSorting two element list: ";
	printVector(twoElementList);
	output = mergesortNaN(twoElementList);
	cout << "\nSorted: ";
	printVector(output);
	cout << "\n";

	//sort big list
	cout << "~~~~~~~~~~~~~~~~~~~~~~\nSorting big list: ";
	printVector(longList);
	output = mergesortNaN(longList);
	cout << "\nSorted: ";
	printVector(output);
	cout << "\n";

	//sort zero list
	cout << "~~~~~~~~~~~~~~~~~~~~~~\nSorting zero list: ";
	printVector(zeroList);
	output = mergesortNaN(zeroList);
	cout << "\nSorted: ";
	printVector(output);
	cout << "\n";

	//sort random data
	vector<float> randomData;
	for (int i=0; i<100; i++)
		randomData.push_back(pow((double)-1,(double)((rand()%2)+1)) * (rand()%1000000)/5327);
	cout << "~~~~~~~~~~~~~~~~~~~~~~\nSorting random list: ";
	printVector(randomData);
	output = mergesort(randomData);
	cout << "\nSorted: ";
	printVector(output);

	cout << "\nPress any key to continue . . .";
	cin.get();

	return 0;
}
*/