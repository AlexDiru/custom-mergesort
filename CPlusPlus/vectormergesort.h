//algorithm tested to sort 2^23 elements in ~38 secs (can't do 2^24)

#include <iostream>
#include <vector>
#include <Windows.h> //_FPCLASS_NZ & _fpclass

using namespace std;

int zero = 0;
int one = 1;
float INFINITY			= one/ (one - 1.0);
float MINUS_INFINITY	= -INFINITY;
float NAN				= (one - 1.0) / (one - 1.0);
float NEG_ONE			= -1.0;
float MINUS_ZERO		= NEG_ONE*zero;

vector<float> appendVectors ( const vector<float>, const vector<float> );
vector<float> mergesortNaN ( const vector<float> );
vector<float> mergesort ( const vector<float> );
vector<float> merge ( const vector<float>,  const vector<float> );
void printVector( const vector<float> );

vector<float> bsort(vector<float> a);

//for debug
bool MERGESORT_DEBUG = false;
int mergesort_count=0;
int merge_count=0;

template <class T>
inline bool isGreaterThan(T a, T b) //sorts minus zeroes
{
	if (_fpclass(a)==_FPCLASS_NZ)
	{
		if (b >= 0)
			return false;
		else return true;
	}
	else if (_fpclass(b)==_FPCLASS_NZ)
	{
		if (a >= 0)
			return true;
		else return false;
	}
	else return a>b;
}

vector<float> appendVectors ( const vector<float> a, const vector<float> b ) //returns two arrays appended together
{
	vector<float> result;
	for (int va=0;va<a.size();va++)
		result.push_back(a[va]);
	for (int vb=0;vb<b.size();vb++)
		result.push_back(b[vb]);

	return result;
}

vector<float> mergesortNaN ( const vector<float> arr ) 
{
	// this function is designed as a pre-function to a mergesort
	// calling this function allows arrays with NaNs to be sorted
	// the basic premise of this function is that is takes an array
	//  say i.e. { 1, 3, NaN, 4, 0, -1, NaN, 9, 2 }
	// it will parse through the array swapping the NaNs with the left-most element that isn't a NaN
	// so the above array would become
	//           { NaN, NaN, 1, 4, 0, -1, 3, 9, 2 }
	// it will then split the array into two parts, one containing the NaNs, the other containing everything else
	//  { NaN, NaN } & { 1, 4, 0, -1, 3, 9, 2 }
	// it will then perform the mergesort algorithm on the right array, so you will end up with two arrays like:
	//  { NaN, NaN } & { -1, 0, 1, 2, 3, 4, 9 }
	// it will then return an array of these two arrays appended together
	//  { NaN, NaN, -1, 0, 1, 2, 3, 4, 9 }
	// processing the NaNs does require extra time, but it doesn't effect the time complexity of the algorithm


	if (MERGESORT_DEBUG)
	{
		mergesort_count=0;
		merge_count=0;
	}

	//since the array, arr, is passed to the function as a const
	//create a new array with the same data as arr that can be changed
	vector<float> newArr(arr);

	//swap the nans to the left of the array, and keep a count of how many have been swapped
	//so we know where to split
	int numNaNs = 0;
	for (int i=0;i<arr.size();i++)
		if (newArr[i] != newArr[i])
			swap(newArr[i],newArr[numNaNs++]);

	//we only need to mergesort the non NaNs
	//use a pointer to deduce the elements we need to sort
	vector<float> toSort;
	for (int i=0;i<arr.size()-numNaNs;i++)
		toSort.push_back(newArr[numNaNs+i]);

	//create an array with just the nans
	vector<float> NaNArray;
	for (int i=0;i<numNaNs;i++)
		NaNArray.push_back(newArr[i]);

	//return the appendedArrays
	vector<float> sorted = mergesort(toSort);
	newArr = appendVectors(NaNArray,sorted);

	if (MERGESORT_DEBUG)
	{
		cout << "\t~Mergesort() called " << mergesort_count << " times" << endl;
		cout << "\t~Merge() called " << merge_count << " times" << endl;
	}

	return newArr;
}

vector<float> mergesort ( const vector<float> arr)//splits up a list
{
	if (MERGESORT_DEBUG) mergesort_count++;

	int size = arr.size(); 

	//if the list is empty, return 'nothing'
	if (size == 0)
	{
		vector<float> empty;
		return empty;
	}

	if (size == 1) 
	{
		vector<float> retVal;
		retVal.push_back(arr[0]);
		return retVal;
	}

	//arrays for the right and left side
	vector<float> left,right;
	if (size > 1)
	{
		if (size/2 * 2 == size) //if size is even
		{
			for (int n=0; n<size/2; n++)
			{
				left.push_back(arr[n]);
				right.push_back(arr[size/2+n]);
			}
		}
		else //size is odd
		{
			int n;
			for (n=0; n<size/2; n++)
			{
				left.push_back(arr[n]);
				right.push_back(arr[size/2+n+1]);
			}
			left.push_back(arr[(size/2)]); //account for the middle element
		}
	}

	vector<float> retVal = merge(mergesort(left), mergesort(right));

	return retVal;
}

vector<float> merge ( vector<float> arr1, vector<float> arr2) //sorts two lists
{
	if (MERGESORT_DEBUG) merge_count++;

	vector<float> retVal; //empty

	int orig1size = arr1.size(); //a way to remove elements from the arrays
	int orig2size = arr2.size();
	int arr1size = orig1size;
	int arr2size = orig2size;

	while (arr1size > 0 && arr2size > 0) //both lists aren't empty
	{
		int o1=orig1size - arr1size;
		int o2=orig2size - arr2size;
		if (isGreaterThan(arr1[o1],arr2[o2]))
		{
			retVal.push_back(arr2[o2]); //append element to return list
			arr2size--; //a way to 'remove' the first element in arr2
		}
		else
		{
			retVal.push_back(arr1[o1]); //append element to return list
			arr1size--; //a way to 'remove' the first element in arr1
		}
	}

	while (arr1size > 0)
	{
		retVal.push_back(arr1[orig1size - arr1size]); //append element to return list
		arr1size--; //a way to 'remove' the first element in arr1
	}

	while (arr2size > 0)
	{
		retVal.push_back(arr2[orig2size - arr2size]); //append element to return list
		arr2size--; //a way to 'remove' the first element in arr2
	}

	return retVal;
}

void printVector( const vector<float> arr ) //function to print an array
{
	int size=arr.size();
	cout << "{";
	for (int i = 0; i < size; i++)
	{
		if (i != size-1)
			cout << " " << arr[i] << " " << ",";
		else
			cout << " " << arr[i];
	}
	cout << " }" << endl;
}

//store data for the tests
class test
{
private:
	int startTime, endTime;
public:
	int power; //2^power
	void startRecording() { startTime = clock(); }
	void stopRecording() { endTime = clock(); }

	int getElapsedTime() { return this->endTime - this->startTime; } //gets the time it took

	void printTabular() { cout << this->power << "\t" << this->getElapsedTime() << endl; } //prints the test data

	void printTabularNoNewLine() { cout << this->power << "\t" << this->getElapsedTime(); } //prints the test data
};