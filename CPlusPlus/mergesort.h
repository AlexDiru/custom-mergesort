//algorithm tested to sort 2^23 elements in ~38 secs (can't do 2^24)

float *appendArrays ( const float *a, int asize, const float *b, int bsize );
float *mergesortNaN ( const float *arr, int size );
float *mergesort ( const float *arr, int size );
float *merge ( float *arr1, int arr1size, float *arr2, int arr2size);
void printArray( float arr[], int size );

float *appendArrays ( const float *a, int asize, const float *b, int bsize ) //returns two arrays appended together
{
	float *result = new float[asize+bsize];
	for (int va=0;va<asize;va++)
		result[va] = a[va];
	for (int vb=0;vb<bsize;vb++)
		result[asize+vb] = b[vb];

	return result;
}

float  *mergesortNaN ( const float *arr, int size ) 
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
	 

	//since the array, arr, is passed to the function as a const
	//create a new array with the same data as arr that can be changed
	float *newArr = new float[size];
	memcpy(newArr,arr,sizeof(float)*size);

	//swap the nans to the left of the array, and keep a count of how many have been swapped
	//so we know where to split
	int numNaNs = 0;
	for (int i=0;i<size;i++)
		if (newArr[i] != newArr[i])
			swap(newArr[i],newArr[numNaNs++]);

	//we only need to mergesort the non NaNs
	//use a pointer to deduce the elements we need to sort
	const float *ptr = (&newArr[0]) + numNaNs;

	//create a new array with what we need to sort
	float *toSort = new float[size-numNaNs];
	for (int i=0;i<size-numNaNs;i++)
		toSort[i] = *(ptr++);

	//create an array with just the nans
	float *NaNArray = new float[numNaNs];
	for (int i=0;i<numNaNs;i++)
		NaNArray[i] = newArr[i];

	//return the appendedArrays
	float *ptr2 = mergesort(toSort,size-numNaNs);
	delete[] newArr;
	newArr = appendArrays(NaNArray,numNaNs,ptr2,size-numNaNs);
	delete[] NaNArray,toSort,ptr,ptr2;
	return newArr;

}

float *mergesort ( const float *arr, int size )//splits up a list
{
	//if the list is empty, return 'nothing'
	if (size == 0) return NULL;

	if (size == 1) 
	{
		float retVal[1];
		retVal[0] = arr[0];
		return retVal;
	}

	//arrays for the right and left side
	float *left = NULL,*right = NULL;
	int sizeLeft, sizeRight;
	if (size > 1)
	{
		if (size/2 * 2 == size) //if size is even
		{
			 //allocate memory
			 left = new float[size/2];
			 sizeLeft = size/2;
			 right = new float[size/2];
			 sizeRight = size/2;

			 for (int n=0; n<size/2; n++)
			 {
				left[n] = arr[n];
				right[n] = arr[size/2+n];
			 }
		}
		else //size is odd
		{
			 //allocate memory
			 left = new float[(size/2)+1];
			 sizeLeft= (size/2)+1;
			 right = new float[size/2];
			 sizeRight = size/2;

			 int n;
			 for (n=0; n<size/2; n++)
			 {
				left[n] = arr[n];
				right[n] = arr[size/2+1+n];
			 }
			 left[n] = arr[(size/2)]; //account for the middle element
		}
	}

	float *retVal = merge(mergesort(left,sizeLeft), sizeLeft,mergesort(right,sizeRight),sizeRight);

	
	//clear up memory
	if (left!=NULL)delete[] left;
	if(right!=NULL)delete[] right;

	return retVal;
}


float *merge ( float *arr1, int arr1size, float *arr2, int arr2size) //sorts two lists
{
	float *retVal = new float[arr1size+arr2size]; //empty
	int currElement = 0;
	
	int orig1size = arr1size; //a way to remove elements from the arrays
	int orig2size = arr2size;

	while (arr1size > 0 && arr2size > 0) //both lists aren't empty
	{
		if (arr1[orig1size - arr1size] > arr2[orig2size - arr2size])
		{
			retVal[currElement++] = arr2[orig2size - arr2size]; //append element to return list
			arr2size--; //a way to 'remove' the first element in arr2
		}
		else
		{
			retVal[currElement++] = arr1[orig1size - arr1size]; //append element to return list
			arr1size--; //a way to 'remove' the first element in arr1
		}
	}

	while (arr1size > 0)
	{
		retVal[currElement++] = arr1[orig1size - arr1size]; //append element to return list
		arr1size--; //a way to 'remove' the first element in arr1
	}

	while (arr2size > 0)
	{
		retVal[currElement++] = arr2[orig2size - arr2size]; //append element to return list
		arr2size--; //a way to 'remove' the first element in arr2
	}

	return retVal;
}

void printArray( float arr[], int size ) //function to print an array
{
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