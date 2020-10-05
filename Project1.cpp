/* DSA 5005
   Submitted By: Shehnaz Shaik
   Project 1
   Date: 09-22-2019
   */
/*This Project generates a data frame from given input file by accessing the rows and columns each. 
First it sets the values of all the rows and columns using the rows and column values table will be set.
Finally we iterate the datafile with rows and column values using the row column idexes and setTable will store content of a table.
display method will finally return the contents of the table.

*/
#include <iostream>
using namespace std;
class DataFrame {
protected:
	int** table;
	int noRows, noCols;
	char** colNames;
	char** rowNames;
public:
	//Constructors
	DataFrame();
	DataFrame(int rows, int cols);

	//Output Method
	void display();

	//Setters
	void setRowName(int row, char* name);
	void setColName(int col, char* name);

	//setting rows and columns using col and name variables
	void setColName2(int col, char* name);
	void setRowName2(int col, char* name);

	//Using the the row col index we access the val variable and set the table
	int** setTable(int row, int col, int val);
	int* operator[] (int i); //get row i;

	//Getters
	char** getRowNames(char a);
	char** getColNames(char a);
	int getNumberRows();
	int getNumberCols();
	DataFrame* getColumns(int* columns, int cLen);
	DataFrame* getRows(int* rows, int rLen);
	DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen);


	//Destructor
	~DataFrame();
};

//Another Constructor method to initialize the no of rows and no of columns and table

DataFrame::DataFrame() {
	noRows = 0;
	noCols = 0;
	colNames = NULL;
	rowNames = NULL;
	table = NULL;
};

// Constructor Method to access the no. of rows no. of columns and then set the table 
DataFrame::DataFrame(int rows, int cols) {
	noRows = rows;
	noCols = cols;

	colNames = new char* [noCols];
	for (int i = 0; i < noCols; i++)
		colNames[i] = new char[20];

	rowNames = new char* [noRows];
	for (int i = 0; i < noRows; i++)
		rowNames[i] = new char[20];

	table = new int* [noRows];
	for (int i = 0; i < noRows; i++)
		table[i] = new int[noCols];
};

// Void method to generate the data frame by reading each of column name
void DataFrame::setColName(int col, char* name) {
	//intializing all the variables
	int k = 0;
	int kint = 0;  //setting the initial as kint
	int v;
	int kfinal = 0;

	//Here we are checking if the i th column such that it is not equal to comma and not a null value
	for (int i = 0; i < col; i++)
	{
		kint = k;
		while (name[k] != ',' && name[k] != '\0')
		{
			k++;
			kfinal = k;
		}
		k++;

		for (v = 0; v < (kfinal - kint); v++)
		{
			colNames[i][v] = name[kint + v];
		}
		colNames[i][v] = '\0';
	}

};

// Using similar method to generate the data frame by reading each of row name
void DataFrame::setRowName(int row, char* name) {
	int k = 0;
	int kint = 0;
	int kfinal = 0;
	int v;

	for (int i = 0; i < row; i++)
	{
		kint = k;
		while (name[k] != ',' && name[k] != '\0')
		{
			k++;
			kfinal = k;
		}
		k++;

		for (v = 0; v < (kfinal - kint); v++)
		{
			rowNames[i][v] = name[kint + v];
		}
		rowNames[i][v] = '\0';

	}

}

//Method to set the column name by accessing its index
void DataFrame::setColName2(int col, char* name)
{
	colNames[col] = name;
}

//Method to set the row name by accessing its index
void DataFrame::setRowName2(int row, char* name)
{
	rowNames[row] = name;
}

//Method to set the table name by accessing its row and col indexes and their values using variable val
int** DataFrame::setTable(int row, int col, int val)
{
	table[row][col] = val;
	return table;
};

//This method is a getter, it returns the column name
char** DataFrame::getColNames(char a) {
	return colNames;
};

//This method is a getter, it returns the row name
char** DataFrame::getRowNames(char a) {
	return rowNames;
};

// This menthod accesses and return the tmp variable.
//For every 1th column until its length is less than rLen(length of row)   and accessing the every row until ith col is less than no of cols(noCols). Thus returns the table values for that kth column
DataFrame* DataFrame::getRows(int* rows, int rLen)
{
	DataFrame* tmp = new DataFrame(rLen, noCols);

	for (int i = 0; i < rLen; i++)
	{
		(*tmp).setRowName2(i, rowNames[rows[i]]);
	}
	for (int i = 0; i < noCols; i++)
	{
		(*tmp).setColName2(i, colNames[i]);
	}
	for (int i = 0; i < rLen; i++)
	{
		for (int k = 0; k < noCols; k++)
		{
			(*tmp).setTable(i, k, table[rows[i]][k]);
		}
	}
	return tmp;
};

// This menthod accesses and return the tmp1 variable.
//For every 1th column until its length is less than cLen(length of column)   and accessing the every row until ith row is less than no of rows(noRows). Thus returns the table values for that kth column

DataFrame* DataFrame::getColumns(int* columns, int cLen)
{
	DataFrame* tmp1 = new DataFrame(noRows, cLen);

	for (int i = 0; i < cLen; i++)
	{
		(*tmp1).setColName2(i, colNames[columns[i]]);
	}
	for (int i = 0; i < noRows; i++)
	{
		(*tmp1).setRowName2(i, rowNames[i]);
	}
	for (int i = 0; i < noRows; i++)
	{
		for (int k = 0; k < cLen; k++)
		{
			(*tmp1).setTable(i, k, table[i][columns[k]]);
		}

	}

	return tmp1;
};

//This method returns the variable temp2 after accessing both row name and column name and thus returning the table value
DataFrame* DataFrame::getRowsCols(int* rows, int rLen, int* cols, int cLen)
{
	DataFrame* tmp2 = new DataFrame(rLen, cLen);
	for (int i = 0; i < rLen; i++)
	{
		(*tmp2).setRowName2(i, rowNames[rows[i]]);
	}
	for (int i = 0; i < cLen; i++)
	{
		(*tmp2).setColName2(i, colNames[cols[i]]);
	}
	for (int i = 0; i < rLen; i++)
	{
		for (int k = 0; k < cLen; k++)
		{
			(*tmp2).setTable(i, k, table[rows[i]][k]);
		}
	}
	return tmp2;
};

//The display method displays the rows and columns by the ith column and kth row and displays the table as a final result
void DataFrame::display() {


	for (int i = 0; i < noCols; i++)
	{
		cout << colNames[i] << "\t";
	}
	cout << endl;
	for (int k = 0; k < noRows; k++)
	{
		cout << rowNames[k] << "\t";
	}
	cout << endl;
	for (int k = 0; k < noRows; k++)
	{
		for (int j = 0; j < noCols; j++) {
			cout << table[k][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
};

// Main function: Begining of the execution
int main() {
	int c, r;
	char* var1 = new char[40];
	char* var2 = new char[40];
	int tmp1 = 0;
	int selectC[3];
	int selectR[10];

	// Read the dataframe from input
	// First line: two numbers seperated by space;
	// first number is the number of rows (r) and
	// second number is the number of columns (c)

//REading the first dataframe
	cin >> r >> c;
	DataFrame* firstDF = new DataFrame(r, c);

	//accessing setColName and setRowNaame methods to contruct the table content
	cin >> var1;
	(*firstDF).setColName(c, var1);
	cin >> var2;
	(*firstDF).setRowName(r, var2);

	for (int i = 0; i < r; i++)
	{
		for (int k = 0; k < c; k++)
		{
			cin >> tmp1;
			(*firstDF).setTable(i, k, tmp1);
		}
	}
	(*firstDF).display();


	// Second line: strings seperated by a comma (c of them); representing column names
	// Third line: strings seperated by a comma (r of them); representing row names
	// Fourth line and more: c number of integers in each of the r rows (seperated by)
	// a space between integers in the same row.
	// TODO: Student completes code for the above comment block to get them as input
	// using the display method, print (in the same format as the input):
	// - the column names of the dataframe
	// - the row names of the dataframe
	// - the contents of the table in dataframe
	// TODO: Student completes code for the above comment block
	// Execute the following code
	// Read the column numbers that you want to extract


	for (int i = 0; i < 3; i++)
		cin >> selectC[i];
	DataFrame* tempColumns = (*firstDF).getColumns(selectC, 3);
	(*tempColumns).display();



	// Hardcoding the row names as in input
	(*tempColumns).setRowName2(2, (char*) "Jack");
	(*tempColumns).setRowName2(3, (char*)"Peter");
	(*tempColumns).display();


	// Displaying the rows by accessing via row index and extract rows
	for (int i = 0; i < 2; i++)
		cin >> selectR[i];
	DataFrame* tempRows = (*firstDF).getRows(selectR, 2);
	(*tempRows).display();



	// Displaying the columns by accessing via column index and extract columns
	(*tempRows).setColName2(2, (char*)"Scores");
	(*tempRows).setColName2(3, (char*)"Values");
	(*tempRows).display();


	//We can return the 2,3 rows x column dataframe by accessing selectR and selectC
	DataFrame* tempColsRows = (*firstDF).getRowsCols(selectR, 2, selectC, 3);
	(*tempColsRows).display();
	/*
	delete tempRows;
	delete tempColumns;
	delete tempColsRows;

	// Sample Code for you and you must execute this
	DataFrame* myTable = new DataFrame(5,5);
	for (int i =0; i < 5; i++) {
	for (int j=0; j < 5; j++) {
	(*myTable)[i][j] = i*j;
	}
	}
	(*myTable).display();
	delete myTable;
	*/

	cout << "End" << endl;

}