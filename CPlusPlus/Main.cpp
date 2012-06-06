#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

#include "vectormergesort.h"

int main()
{
	srand(time(NULL));

	#ifdef _WIN32
	system("Color F5"); //colour the console, to save on black ink being used when screenshots are required
	#endif

	// ******* //
	//Section 1// - Testing the algorithm can sort empty list, 1 element list, 2 element list,
	// ******* //   a general list, random data, NaNs, +/- Infinity, +/- 0

	float ftwoElementList[] = { 123.43, 123.429 };
	float flongList[] = { MINUS_ZERO, 1, 3, 91.3, 234.2, INFINITY, NAN, 234, MINUS_ZERO, 0, MINUS_INFINITY, NAN, -213.2, NAN, -1293890.234 };
	float fzeroList[] = { 0, MINUS_ZERO, 0, 0, 0, MINUS_ZERO, 0, 0, MINUS_ZERO, 0, MINUS_ZERO, MINUS_ZERO, MINUS_ZERO, 0, MINUS_ZERO };

	vector<float> emptyList;
	vector<float> oneElementList; oneElementList.push_back(2.7);
	vector<float> twoElementList(ftwoElementList, ftwoElementList + sizeof(ftwoElementList)/sizeof(float) );
	vector<float> longList(flongList, flongList + sizeof(flongList)/sizeof(float) );
	vector<float> zeroList(fzeroList, fzeroList + sizeof(fzeroList)/sizeof(float) );

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
		randomData.push_back(((float)rand()/RAND_MAX)*100000);
	cout << "~~~~~~~~~~~~~~~~~~~~~~\nSorting random list: ";
	printVector(randomData);
	output = mergesort(randomData);
	cout << "\nSorted: ";
	printVector(output);

	cout << "\nPress any key to continue to Section 2 - Testing 2^n elements\n";
	cin.get();

	// ******* //
	//Section 2// - Testing the algorithm speed for 2^n number of elements
	// ******* //   

	test testData;
	
	cout << "2^n\ttime" << endl;
	for (int n=0; n<=20; n++)
	{
		//setup test data
		testData.power = n;

		int numberOfElements = pow((double)2,(double)n);
		vector<float> arr;

		for (int i=0; i<numberOfElements; i++)
		{
			//set random data
			arr.push_back(((float)rand()/RAND_MAX)*100000);
		}

		testData.startRecording();
		vector<float> sorted = mergesort(arr);
		testData.stopRecording();

		testData.printTabular();
	}

	cout << "\nPress any key to continue to Section 3 - Testing from 50,000 to 1,000,000 elements\n";
	cin.get();

	// ******* //
	//Section 3// - Testing the algorithm speed for 50,000 to 1,000,000 elements
	// ******* //

	cout << "n\ttime" << endl;
	for (int n=50000; n<=1000000; n+=50000)
	{
		//setup test data
		testData.power = n;

		int numberOfElements = n;
		vector<float> arr;

		for (int i=0; i<numberOfElements; i++)
		{
			//set random data
			arr.push_back(((float)rand()/RAND_MAX)*100000);
		}

		testData.startRecording();
		vector<float> sorted(mergesort(arr));
		testData.stopRecording();

		testData.printTabular();
	}

	cout << "\nPress any key to continue to Section 4 - Testing from 50,000 to 1,000,000 elements with repeat readings\n";
	cin.get();

	// ******* //
	//Section 4// - Testing the algorithm speed for 50,000 to 1,000,000 elements with repeat readings
	// ******* //

	cout << "n\ttime\tn\ttime\tn\ttime\taverage" << endl;
	for (int n=50000; n<=1000000; n+=50000)
	{
		float av_sum = 0;

		for (int average=0;average<3;average++)
		{
			//setup test data
			testData.power = n;

			int numberOfElements = n;
			vector<float> arr;

			for (int i=0; i<numberOfElements; i++)
			{
				//set random data
				arr.push_back(((float)rand()/RAND_MAX)*100000);
			}

			testData.startRecording();
			vector<float> sorted(mergesort(arr));
			testData.stopRecording();

			testData.printTabularNoNewLine();cout << "\t";
			av_sum+=testData.getElapsedTime();
		}
		cout << av_sum/3 << endl;
	}

	cout << "\nPress any key to continue to Section 5 - Showing how many times the algorithm executes it's function\n";
	cin.get();

	// ******* //
	//Section 5// - Showing how many times the algorithm executes it's function
	// ******* //

	MERGESORT_DEBUG = true;

	cout << "# elements\tfunctions" << endl;
	for (int n=50000; n<=1000000; n+=50000)
	{
		int numberOfElements = n;
		vector<float> arr;

		for (int i=0; i<numberOfElements; i++)
			arr.push_back(((float)rand()/RAND_MAX)*100000);

		cout << n << endl;

		vector<float> output(mergesortNaN(arr));
	}

	cout << "\nPress any key to continue . . .";
	cin.get();

	return 0;
}