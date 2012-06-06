/*
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#include "vectormergesort.h" //due to the nature of vectors, the sorting algorithm will be around 20 times quicker if the project is built in release mode not debug

//store data for the tests
class test
{
private:
	int startTime, endTime;
public:
	int power;
	void startRecording() { startTime = clock(); }
	void stopRecording() { endTime = clock(); }

	int getElapsedTime() { return this->endTime - this->startTime; } //gets the time it took

	void printTabular() { cout << this->power << "\t" << this->getElapsedTime(); } //prints the test data
};

int main()
{
	srand(time(NULL));

	#ifdef _WIN32
	system("Color F5"); //colour the console, to save on black ink being used when screenshots are required
	#endif

	test testData;
	
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
				arr.push_back(pow((double)-1,(double)((rand()%2)+1)) * (rand()%1000000)/5327);
			}

			testData.startRecording();
			vector<float> sorted(mergesort(arr));
			testData.stopRecording();

			testData.printTabular();cout << "\t";
			av_sum+=testData.getElapsedTime();
		}
		cout << av_sum/3 << endl;
	}

	cout << "\nPress any key to continue . . .";
	cin.get();

	return 0;
}
*/