// Computing Structures CS/DSA 5005 Fall 2019
// Project 3
// Author: Shehnaz Shaik
//Submission Date: 11/12/2019
/*************************************************Description*****************************************************/
/*
As a part of this project a set of documents are provided as input and the main objective is to raed the contents of 
the document and further perform set of operations by storing the strings of the document in a hash table. 
I am using vector to dynamically assign values of non null values of the hash table. Below are the key operations performed and 
detailed explanation has been commented above each method and important lines of the code.
(i)Reading the documents using fstream operator and storing the words of document into a string array
(ii)Wrote a hash class and defined the bucket size and created a vector table
(iii)wrote wordExistent method that iterates throughout bucket size checks for wordexistence
(iv)With result from wordexistent method, that particular word id counted and inserted in hash tablke h[i] using insertItem
(v)The hash table is displayed using ostream operator(logic explained within method)
(Vi)Finding the frequency of a word using findKey method
(vii)Finding the word given key(frequency of occurance) as input using findValue
(viii)Finding the term frequency using a string in a particular document
(ix)Finally finding the inverse document frequency as per formula provided in project specification

*/
#include<iostream> 
#include<vector> // used in the class for storing the bash buckets only
#include<string> // used for all string manipulations
#include<fstream> // used for reading the documents only
#include<math.h> // used for finding the log in idf only

using namespace std;

// Class Hash
class Hash
{
	// ostream operator to display the hash table
	//defining as friend to access variables and methods of hash using obj
	friend ostream& operator << (ostream& output, Hash& obj);
protected:
	int buckets; // Number of buckets in 
	vector<string>* table; // hash table
public:
	Hash() // default constructor 
	{
		buckets = 0; //Initialing buckets for bucket size of hash table
		table = NULL; // Intitializing the table vector

	} 
	// non-default constructor
	Hash(int v) {
		buckets = v; // assigning bucket size here 
		table = new vector<string>[buckets]; //dynamically assigning the size to the table
	}; 
	//Deifining Destructor
	~Hash() {

	};
	void insertItem(int index, string w); // to insert item to the hash table
	void displayHash(); // to display the has table(same as the ostream)
	int wordExistent(string check); // rerurn 1 if the word is existent in the hash table
	int findKey(string check); // given a string, return the key
	void findValue(int keyToFind); // given a key, return the value/string
	int docFrequency(string nWord);
};

//insertItem method inserts the keys(count of word) and value(word itself) into the hash table
void Hash::insertItem(int index, string w) {
	table[index].push_back(w);// inserting values into the table using push back method passing index and value(w)

}
//wordExistent menthod checks if the table has a certain word and returns 1 if it exists
int Hash::wordExistent(string check) {//word(check) is passed to this method
	for (int i = 0; i < buckets; i++) //iterating through the hash table from 0 to bucket size 
	{
		for (auto j = table[i].begin(); j != table[i].end(); j++) //Since "table" is vector and  size changes dynamically, iterating from .begin to .end of that vector.
		{
			if (*j == check) { //word check happens here
				return 1;
			}
		}
	}
}
//This method returns the frequency of ocuurence of a word i.e., key, given a word string as input
int Hash::findKey(string check) {
	int count = 0;//Initializing the counter
	for (int i = 0; i < buckets; i++) //iterating through the hash table from 0 to bucket size 
	{
		for (auto j = table[i].begin(); j != table[i].end(); j++) //Since "table" is vector and  size changes dynamically, iterating from .begin to .end of that vector.
		{
			if (*j == check) { //word check happens here
				count = count +i;//to cum the total count of occurance
			}
		}
	}
	return count; 
}
//This method return the word strings that have occured given "key" times.
void Hash::findValue(int keyToFind) {
	for (int i = 0; i < buckets; i++) //iterating through the hash table from 0 to bucket size 
	{
		for (auto j = table[i].begin(); j != table[i].end(); j++) //Since "table" is vector and  size changes dynamically, iterating from .begin to .end of that vector.
		{
			if (i == keyToFind) { //accessing the and checking if the key value is equal to the table key then we print the value of the key
				cout << *j << " ";//*j is the easiest way to access the table content
			}
		}
	}
}
//This method returns number of times a given word has occured in the table vector
int Hash::docFrequency(string nWord) {
	int count2 = 0;//initializing the counter
	for (int i = 0; i < buckets; i++) //iterating through the hash table from 0 to bucket size 
	{
		for (auto j = table[i].begin(); j != table[i].end(); j++) //Since "table" is vector and  size changes dynamically, iterating from .begin to .end of that vector.
		{
			if ((*j)==nWord) { //comparing the nWord string with every value in table
				count2++;
				return count2;
			}
		}
	}
	return count2;
}
//ostream operator ised used to print the hash table since cout cannot print all types of data
ostream& operator << (ostream& output, Hash& obj) {
	for (int i = 0; i < obj.buckets; i++) {//iterating through bucket size
		if (obj.table[i].size() != 0) {//condition to enter for non null keys, so that we can handle collison by iterating
			//cout << *j;
			cout << i;
			for (auto j = obj.table[i].begin(); j != obj.table[i].end(); j++) //this for loop handles collision for extra "--> word"
			{
				cout << " --> " << *j;
			}
			cout << endl;//for formatting as per sample output
		}
		else {
			cout << i << endl;

		}
		
	}
	return output;
}
//****************************Execution starts here****************************//
int main()
{
	// TODO:
	// get the numberOfDocuments as redirected input from the input file
	int numberOfDocuments; 
	int wordCount; //total no. of words in a given document
	string docName; //name of the document
	
	// Creation of fstream class object to read and close files
	fstream fio;
	cin >> numberOfDocuments;
	cout << "The number of documents: " << numberOfDocuments << endl;
	// to insert the keys into the hash table desining the hash table h below
	Hash* h = new Hash[numberOfDocuments]; // 20 is count of buckets in 
    // hash table 

	// TODO:
	// declare an array of objects(h[]) of class hash of length numberOfDocuments

	int* numWords = new int[numberOfDocuments]; // used to store the words that are read from the document

	for (int i = 0; i < numberOfDocuments; i++) { //To perform following operations on all given documents
		h[i] = 20;
		cin >> docName >>  wordCount;

		string* wordB = new string[wordCount];//to store the words in wordB array
		fio.open(docName);

		for (int j = 0; j < wordCount; j++) {
			fio >> wordB[j];	
		}

		for (int k = 0; k < wordCount; k++) {//2nd loop to compare every word with every other word in document
			int count = 0;

			if (h[i].wordExistent(wordB[k])!=1) {//enter when wordExistent method returns 1

				for (int l = 0; l < wordCount; l++) {

					if (wordB[k] == wordB[l]) {//this condition is used to count when a match happens
						count++;
					}
				}

				h[i].insertItem(count, wordB[k]);//inserting the count of word and the word into h[i]

			}
			  
			//cout << wordB[k] << " = " << count << endl;
		}
		fio.close();
	}


	//int* numWords = new int[numberOfDocuments]; // used to store the words that are read from the document

	// TODO:
	// input the all the document names to be opened and the corresponding word count in each of them
	// count the number of occurances(key) of each word in the document and store it to the hash table of the corresponding hash object

	// display the Hash table 

	for (int i = 0; i < numberOfDocuments; i++)
	{
		cout << "Hash table for doc" << i + 1 << ".txt" << endl;
		cout << h[i]; // ostream overloaded
		cout << endl;
	}
	
	string newWord;//defining the word that will be given as input 
	cin >> newWord; 
	int sum = 0;// initializing sum variable
	int key = 0;// initializing key variable
	for (int i = 0; i < numberOfDocuments; i++) //Iterating through all documents to get total no. of key from all documents for that input newWord
	{
		key = h[i].findKey(newWord); //finding the key value for newWord using findKey method
		sum = sum + key; //Summation of total no. of keys from given number of documents
	}
	// TODO:
	// input the string for which we need to find the number of occurances across all documents
	// display the result
	
	if (sum > 0) //we need to print the key frequency only when there is word occurence hence sum > 0
		cout << "The key/frequency of the word '" << newWord << "': " << sum << endl;
	else
		cout << "The word was not found!" << endl;

	
	// TODO:
	// input the key for which the strings are to be displayed - format to be viewed in the sample output file
	int inputkey;
	cin >> inputkey;
	cout << "Key " << inputkey << ": ";
	for (int i = 0; i < numberOfDocuments; i++) {
		h[i].findValue(inputkey);//calls findValue and accesses the value of given key
	}
	cout << endl;

	// Term Frequency 
	// TODO:
	// input the string and the document for which we need to find the tf
	int tf;
	string str;
	string inputDocN;
	
	cin >> str >> inputDocN;
	int t = stoi(inputDocN.substr(3, 1));//accepts 1 char after occurance of "doc"(3) according to sample input format
	tf = h[t - 1].findKey(str);//to access the key of the particular string from hash table
	if (tf > 0) 
		cout << "Term Frequency(" << str << ", doc" << t << ".txt) = " << tf << endl;//printing TF as per format
	else
		cout << "The word was not found!" << endl;
	
	//Inverse Document Frequency
	// TODO:
	// input the string for which we need to find the idf

	string inputWord;
	cin >> inputWord;
	int var = 0;//initialing a variable
	double count1 = 0;//initializing counter
	for (int i = 0; i < numberOfDocuments; i++) {
		var = h[i].docFrequency(inputWord);//accessing the frequency of the word in a document given a word as input
		count1 = var + count1;
	}
	cout << "Inverse Document Frequency(" << inputWord << ") = " << log10(numberOfDocuments / count1) << endl;//formula and output as per description
	delete[]h;
	return 0;
}
