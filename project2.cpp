//************************************ DSA 5005 Computing Structures****************************************************//
//******************************************* Fall 2019 ***************************************************************//
//******************************************* Project 2 **************************************************************//
//Submitted By: Shehnaz Shaik
//Due Date: 10/19/2019
// Sample Main V2
/*1.1 ABOUT CSR:
A matrix is said to be a Sparse matrix when the number of non zero values are significantly less than the empty cells 
represented as '0'. Sparse matrices are a key data structure for implementing graph algorithms. One of ways to store such 
matrix of dimensions n x m (No. of rows and No. of columns) can be represented in a Compressed Row Format using 3 one dimensional arrays i.e., 
IA(cumulative number of non-common values in a row), JA(column number of the non zero values), VA(Non zero value array). 
The following sections are a brief explanation of what this algorithm returns.

*1.2 Project 2 Part A:
In This project I am providing the no. of rows, columns and all the values of matrix as an input and the below algorithm
can return the One dimension arrays i.e., IA, JA, VA(Like described in section 1.1).
IA is returned from the method "display_IA()".
JA is returned from the method "display_JA()".
VA is returned from the method "display_valueArray()".

*1.3 Project 2 Part B:
Using n , m values and IA, JA, VA arrays we can perform some computations and display the actual matrix of n x m form.
And also the edge existence between between two vertices, Neighbours of a particular node, Breadth for Search(BFS) starting 
from a particular node and Depth for search(DFS) from a particular node.
The matrix is displayed using an ostream operator.
Edge existance is returned by the method "edgeExistent()".
Neighbours of a node is returned by the method "findNeighbours()".
BFS of a node is returned by the method "display_Array(sequenceBFS)".
DFS of a node is returned by the method "display_Array(sequenceDFS)".

*/
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

#define commonValue 0

class CSR
{
	// overload the ostream operator
	//Using friend operator ostream operator can access all the objects and variables from CSR
	friend ostream& operator << (ostream& output, CSR& obj);
protected:
	int numRows; //Number of rows of the original matrix
	int numCols; //Number of columns of the original matrix
	int noNonSparseValues; //Number of non sparse values of the original matrix
	int* valueArray; //to store the non cv values
	int* IA; //to store the IA values
	int* JA; //to store the JA values
	int k, l;
	int m = 1;

public:
	CSR();
	CSR(int n, int m, int numNZV) {
		numRows = n;
		numCols = m;
		noNonSparseValues = numNZV;
		valueArray = new int[numNZV];
		JA = new int[numNZV];
		IA = new int[numNZV];
	};


	int getRows() {
		return numRows;
	};

	int getCols() {
		return numCols;
	};
	int getnumNZV() {
		return noNonSparseValues;
	};

	int getIA(int i);
	int getJA(int i);
	int getvalueArray(int i);
	void setnumNZV(int numNZVlocal);
	void set_valueArray(int val);
	void set_JA(int col);
	void set_IA(int dex);
	void display_matrix();
	//This method returns the value array, by using for loop we can display the Value array in desired format as in sample output.
	void display_valueArray() {
		for (int i = 0; i < noNonSparseValues; i++) {
			cout << valueArray[i] << " ";
		};
		cout << endl;
	};
	//This method returns the JA array(returned from set_JA() ), by using for loop we can display the array in desired format as in sample output.
	void display_JA() {
		for (int i = 0; i < noNonSparseValues; i++) {
			cout << JA[i] << " ";
		};
		cout << endl;
	};
	//This method returns the IA array(returned from set_IA() ), by using for loop we can display the array in desired format as in sample output.
	void display_IA() {

		for (int i = 0; i < numRows; i++){
			cout << IA[i] << " ";
		}
		cout << endl;
	};
	//This method returns "," separated values of arr[] array passed from BFS, DFS methods.
	void display_array(int* arr) {
		char const* str = "";

		for (int i = 0; i < numRows; i++) {
			cout << str << arr[i];
			str = ",";
		}
	};
	//This method returns True if there is an edge between given nodes and false when there isnt any.
	int edgeExistent(int u, int v) {
		int count1 = IA[u]; //Assigning the given node value to count1
		int edgeOut = 0; 


		int i;
		//The loop iterates between the cumulative row index value, for example if node is 3, it iterates the JA[] array from IA[3] to IA[4] .
		for (i = IA[u]; i < IA[u + 1]; i++) {
			if (JA[count1] == v) {//Verifying if there exists an edge value
				edgeOut = valueArray[count1];
				
			}
			count1++;
		}
			
		if (edgeOut != 0) {
			cout << "True, " << edgeOut;
		}
		else {
			cout << "False";
		}

	
		return edgeOut;
	};
	//Similar to edge existence by iterating JA[] array from IA[] array and assiging teh values of the particular columns and returning in the form of a tuple.
	int* findNeighbours(int node) {
		int i;
		char const* str = "";
		for (i = IA[node]; i < IA[node + 1]; i++) {

			cout <<str<< "(" << JA[i] << "," << valueArray[i] << ")"; //Tuple format
			str = ", ";
		};
		cout << endl;
		return 0;
	};
	//This methos returns the sequence of Breadth for search starting from a given node.
	int* BFS(int start) {
		queue<int> Q;//Defining the Queue
		int* nvisit = new int[numRows]; //Array to mark if a node is visited
		int* BFSout = new int[numRows]; //Array to store each visited value
		int count = 0;
		for (int i = 0; i < numRows; i++) {//Iterating to mark all nodes as not visited initially
			nvisit[i] = 0; //Declaring the node visit array as false
		}
		Q.push(start); //Assigning the starting node to the queue
		nvisit[start] = 1;//Marking the first node as visited before starting the loop
		while(!Q.empty()){
			int tempVar = Q.front(); //Pushiing the first values in Q to a temp variable
			BFSout[count] = tempVar; //Assigning the nodes in while loop iteration to BFSout[] array
			count++;
			//cout << tempVar << " ";
			Q.pop();
			for (int j = IA[tempVar]; j < IA[tempVar + 1]; j++) {//Iterating the JA[] array using IA[] 
				if (nvisit[JA[j]] != 1) {//Checking if the node has not been visited
					nvisit[JA[j]] = 1; //THen marking it visited
					Q.push(JA[j]); //Pushing the value out of the Queue
				}
			}
		}
		return BFSout; //Returns the BFS sequence
	};
	//This methos returns the sequence of Breadth for search starting from a given node.
	int* DFS(int start) {
		stack<int> S; //Defining Stack
		int* nvisit = new int[numRows];//Array to mark if a node is visited
		int* DFSout = new int[numRows];//Array to store each visited value
		int count = 0;

		for (int i = 0; i < numRows; i++) {
			nvisit[i] = 0; //Declaring the node visit array as false
		}

		S.push(start); //Pushing the starting node to the stack
		

		while(!S.empty()){

			int tempVar = S.top(); //Assigning the top values in S to a temp variable
			S.pop();//The upper value gets popped out.

			if (nvisit[tempVar] != 1) {//If it is not visited, We are marking the value as visited.
				DFSout[count] = tempVar;
				nvisit[tempVar] = 1;
				count++;
			}
			for (int j = IA[tempVar +1]-1; j >=IA[tempVar]; j--) {//Iterating from top to bottom approach in the stack

				if (nvisit[JA[j]] != 1) {
					S.push(JA[j]);//If the node is not visited we are pushing it to the stack
				}
			    
			}    
			
		}
		return DFSout;//REturns the DFS sequence
	};
	//other methods as you deem fit	
};
//This methods sets the values of value array taking input from main()
void CSR::set_valueArray(int val) {

	valueArray[k++] = val;//Increment after every iteration
};
//This methods sets the values of value index of columns taking input from main()
void CSR::set_JA(int col) {
	JA[l++] = col;//Increment after every iteration
};
//This methods sets the cumilative values of value index of rows taking input from main()
void CSR::set_IA(int dex) {
	IA[0] = 0;//first value of IA array is initialized to 0
	IA[m++] = dex;//Increment after every iteration
};
//Writing the ostream operator to display the Matrix
ostream& operator << (ostream& output, CSR& obj) {
	int i, j;
	int count = 0;
	for (i = 0; i < obj.numRows; i++) {//Iterating through rows
		for (j = 0; j < obj.numCols; j++)//Iterating through columns
		{
			if (obj.JA[count] == j) { //Comparing the column index to the column number and assigning the non zero value 
				cout << obj.valueArray[count] << " ";
				count++;
			}
			else {
				cout << "0" << " ";
			}
		}
		cout << endl;
	}

	return output;
};
//Execution starts here
int main()
{
	int n, m, numNZV;
	int i, j, count1 = 0;
	int testValue, count = 0;

	//matrixA
	cin >> n >> m >> numNZV; //receive the n, m and numNZV for matrix A
	CSR* matrixA = new CSR(n, m, numNZV);

	cout << "MATRIX A ---- Rows, Cols and number of non common values: " << matrixA->getRows() <<
		", " << matrixA->getCols() << ", " << matrixA->getnumNZV() << endl;

	//TODO: read in the matrix A from the input file and store it in the given format
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> testValue; //The values of every ith row jth column, will be entered/read here
			//Now we need to verify if there are non zero values in all ith row jth column elemnts using testValue variable
			if (testValue != 0) {
				matrixA->set_valueArray(testValue);//passing on non zero values to the methos set_valueArray
				matrixA->set_JA(j);
				count++;
			}
		}
		matrixA->set_IA(count);
	}


	cout << "The valuesArray for matrix A are : ";
	matrixA->display_valueArray();

	cout << "The JA for matrix A are : ";
	matrixA->display_JA();
	cout << "The IA for matrix A are : ";
	matrixA->display_IA();
	cout << "The matrix A is : " << endl;
	cout << *matrixA; // overload the ostream operator

	// necessary declarations for the next incomming variables
	int u = 0, v = 0;
	int node = 0;
	int s = 0;
	int* sequenceBFS;
	int* sequenceDFS;

	cin >> u >> v; // get the vertices to check for edge existance
	
	cout << "Edge existance between " << u << " and " << v << ": ";
	matrixA->edgeExistent(u, v);
	cout << endl;

	
	cin >> node; // get the node for which you need to get all the neighbours
	cout << "Neighbours of " << node << " are:" << endl;
	matrixA->findNeighbours(node);

	cin >> s; // get the start node for BFS and DFS
	sequenceBFS = matrixA->BFS(s);
	
	sequenceDFS = matrixA->DFS(s);
	
	cout << "BFS with start node " << s << " is:" << endl;
	matrixA->display_array(sequenceBFS);
	cout << endl;
	
	cout << "DFS with start node " << s << " is:" << endl;
	matrixA->display_array(sequenceDFS);
	cout << endl;

	return 0;
}
