// Computing Structures - Fall 2019
// Project 4
// Author: Shehnaz Shaik
// SampleMainP4.cpp
/*In this project I am implementing the following sorting algorithms: Shell sort and Adaptive sort. At the end the commented section
is the part where i had calculated the time taken for each of the techniques. Below are the portions of this project.
1. Generated an array of randomly generated numbers based on input number of elements(num elements), seed, lower bound 
and upper bound of the elements
2. Used the display method to display the results at every section.
//Shell Sort
3. Accessing the Elements array, sorted the elements using shell sorting technique, i.e.,	involving comparisons between two
numbers between a gap. A gap is number of elements/2.
4. The process of iterating and comparison between elements occurs in for each gap in gaps and starting from first element as long as
the gap is > 0
5. Then comparing withing the elements if the former number is greater than the latter they will be swapped.
//Adaptive Sort
6. For adaptive sort I have taken reference from Sridhar et al.
7. First i have split the and allocated number of elements into even and odd arrays of integers.(Detailed in the code below)
8. By using the isSorted method and merge methods, The final sorted array of elements isreturned(Detailed in the code below)
The detail explanation is available under each method.



*/
#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for ceil and floor functions in adaptive sort
#include<ctime> // used for measuring time

using namespace std;

class sortElements {
protected:
	int numElements; //Number of elements of the array
	int short* elements; //dynamic array with the elements of type int short or int long(for experiment)

public:
	sortElements() {
		numElements = 0; //Intializing the number of elements
		elements = NULL;//Initializing the dynamic array

	};	// default constructor
	sortElements(int n) {
		numElements = n;
		elements = new int short[n];
	}; // non-default constructor
	~sortElements(){
		
	}; // Defining the destructor

	void generateRandom(int seed, int lower, int upper); // will generate numElement set of elements randomly with the seed and range from lower to upper
	void displayElements(int short* arr); // display the given set 
	int short* getElementsArray(); // return the entire array of elements
	int getnumElements(); // return the number of elements

	int short* shellSort();	// method used for shell sort

	bool isSorted(int short* array, int len); // helper method for adaptive sort
	int short* mergeArrays(int short* arr1, int short* arr2, int n1, int n2); // merge method for adaptive sort
	int short* adaptiveSort(int short* a, int length); // method for adaptive sort
};
// This method generates a set of random integers based on given, number of elements, seed, lower bound and upper bound
void sortElements::generateRandom(int seed, int lower, int upper) {
	srand(seed);

	int range = upper - lower + 1;
	for (int i = 0; i < numElements; i++)
	{
		elements[i] = rand() % range + lower; //The random integers are generated using the rand method and allocated to elements[i]

	}

}
//This method is used to display the given input array
void sortElements::displayElements(int short* arr) {
	for (int i = 0; i < numElements; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
};

//This method is used to fetch the elements of the given array
int short* sortElements::getElementsArray() {
	return elements;
};
//This method is used to sort the elements using shell sort technique
int short* sortElements::shellSort() {
	int gap; //defining the number of gaps between two numbers under comparision
	int short* shellSort = new int short[numElements];//defining a pointer array to allocate the elements generated for shellSorting
	for (int i = 0; i < numElements; i++)
		shellSort[i] = elements[i];//Allocation occurs here
	for (gap = numElements / 2; gap > 0; gap = gap / 2) {//iterated for each gap in gaps(we know that gap = numElements/2)
		for (int j = gap; j < numElements; j++) {//This is to start with the first gap and loops as long as gap is < numElements
			for (int k = j - gap; k >= 0; k = k - gap) {//This is to make sure we are starting with 0th index of elements and comparing each element with k+gap'th element
				if (elements[k] > elements[k + gap]) {//Compare
					swap(elements[k], elements[k + gap]);//swap occurs here using the swap method
				}
				else {
					break;
				}
			}
		}
		//return elements;
	}
	return shellSort; // returns the sorted array
};
//This method performs adaptive sorted on a given array
int short* sortElements::adaptiveSort(int short* a, int length) {
	int short* eleAdaptive = new int short[length];//Defining the pointer array to allocate the elements generated for adaptive sorting
	for (int i = 0; i < length; i++)//Allocation occurs via this loop
		eleAdaptive[i] = a[i];
	if (length < 2)//This makes sure that the length of array is > = 2 for sorting
		return eleAdaptive;
	int eSize = ceil(length / 2.0);//Defining the even array size using the ceil method
	int oSize = floor(length / 2.0);//Defining the odd array size using the floor method

	int short* even = new int short[eSize]; //Defining the pointer array for even array for short integer types
	int short* odd = new int short[oSize];//Defining the pointer array for odd array for short integer types

	int max = length / 2;
	for (int j = 0, j2 = 0; j < max; j++, j2++)//defining 2 variables to iterate and allocate values to even and odd arrays
	{
		even[j] = eleAdaptive[j2];//allocating the even array
		j2++;
		odd[j] = eleAdaptive[j2];//allocating the odd array
	}
	//to handle the extra element when the length of elements is odd
	if (length % 2 > 0)
		even[eSize - 1] = eleAdaptive[length - 1];
	if (!isSorted(even, eSize))//passing the values of array and size to is sorted method
		even = adaptiveSort(even, eSize);

	if (!isSorted(odd, oSize))//passing the values of array and size to is sorted method
		odd = adaptiveSort(odd, oSize);
	//Merging the individual arrays into a single array
	eleAdaptive = mergeArrays(even, odd, eSize, oSize);//passing the even, odd arrays and their sizes to mergeArrays method to get the final adaptive sorted array

	delete odd;//deleting the variable for odd array
	delete even;//deleting the variable for even array
	return eleAdaptive;
};
//This method return the elements
int sortElements::getnumElements() {
	return numElements;
};
//This method retruns either true or false
bool sortElements::isSorted(int short* array, int len) {
	int firstE = array[0];//defining and allocating the first element 
	for (int i = 1; i < len; i++) {//iterating through all the elements
		if (firstE > array[i]) {//comparing the previous value allocated to the current
			return false;
		}
		else {
			firstE = array[i];//if the above fails allocating the firstE to next value

		}
	}
	return true;
};
//This method performs merge sort
int short* sortElements::mergeArrays(int short* arr1, int short* arr2, int n1, int n2) {

	int index = 0;//Defining and intializing variables
	int a1 = 0; 
	int a2 = 0;
	int short* eleMerge = new int short[n1 + n2];//defining a pointer array to concatenate the even odd arrays in input
	while (a1 < n1 && a2 < n2) {//making sure a1, a2 are < n1 n2
		if (arr1[a1] < arr2[a2]) {//comparing elements of two arrays
			eleMerge[index] = arr1[a1];//allocating the arr1 values
			a1++;//incrementing for next value
		}
		else {
			eleMerge[index] = arr2[a2];//allocating the arr2 values
			a2++;//incrementing for next value
		}
		index++;//incrementing the index so that eleMerge can accomodate the elements
	}
	while (a1 < n1) {//condition to assign values to merge array eleMerge
		eleMerge[index] = arr1[a1];//assigning 
		a1++;
		index++;
	}
	while (a2 < n2) {//condition to assign values to merge array eleMerge
		eleMerge[index] = arr2[a2];//assigning 
		a2++;
		index++;
	}
	return eleMerge;// returns the merged array
};

//The execution starts here
int main()
{
	// TODO:
	// get the number of elements and create a pointer object of class with the non default constructor
	int s; //defining the seed
	int l; // defining the lower bound
	int u; // defining the upper bound
	int n; // defining the number of elements to be generated
   //getting the seed, lower and upper bounds for random number generation
	cin >> n >> s >> l >> u;
	//creating an object sortClass for the sortElements class
	sortElements* sortClass = new sortElements(n);
	cout << "Number of elements: " << n << endl;

	// calling generateRandom method with s, l and u.
	cout << "Randomly generated elements: " << endl;
	sortClass->generateRandom(s, l, u);

	// calling the displayElements method to display the randomly generated 'elements'
	sortClass->displayElements(sortClass->getElementsArray());
	//cout << endl;

	// calling the shellSort method that would return the sortedElements. 
	// this above call can be timed
	cout << "Shell sort sorted elements: " << endl;
	// calling the shell sort method and displayElements method to display the returned sortedElements from shellSort
	sortClass->shellSort();
	sortClass->displayElements(sortClass->getElementsArray());
	//cout << endl;

	// calling the adaptiveSort method that would return the sortedElements. 
	// this above call can be timed
	cout << "Adaptive sort sorted elements: " << endl;

	// calling the adaptiveSort and displayElements methods to display the returned sortedElements from adaptiveSort
	sortClass->displayElements(sortClass->adaptiveSort(sortClass->getElementsArray(), sortClass->getnumElements()));
	/*
	clock_t start, stop; // clock variables to get the time 
	double totalTime;


	start = clock(); //clock to check the start time
	sortClass->shellSort();
	stop = clock();//clock to check the End time

	totalTime = (stop - start) / (double)CLOCKS_PER_SEC; //calculating the total time

	cout << totalTime << endl; //displaying the total time taken

	start = clock();
	sortClass->adaptiveSort(sortClass->getElementsArray(), sortClass->getnumElements());
	stop = clock();

	totalTime = (stop - start) / (double)CLOCKS_PER_SEC;
	cout << totalTime;
	*/

	
	delete sortClass;
	return 0;
}