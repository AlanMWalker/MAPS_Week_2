/********************************************************

SortOut - basic integer sorting and file output program

This version uses a bubble sort. Each row of numbers is
sorted independently.

*********************************************************/

#include <fstream>			//for file output
#include <iostream>			//for console output
#include <conio.h>			//for kbhit

#include "hr_time.h"

using namespace std;

#define MAX_ROWS 2000
#define MAX_COLS 1000

int _data[MAX_ROWS][MAX_COLS];

void getData(void);
void sortData(void);
void testData(void);
void outputData(void);

CStopWatch timer1, timer2;

int main(void)
{
	getData();

	timer1.startTimer();
	sortData();
	timer1.stopTimer();

	testData();

	timer2.startTimer();
	outputData();
	timer2.stopTimer();

	cout << "\nsort time = " << timer1.getElapsedTime() << " seconds" << endl;
	cout << "output time = " << timer2.getElapsedTime() << " seconds" << endl;
	cout << "combined time = " << timer1.getElapsedTime() + timer2.getElapsedTime() << " seconds" << endl;
	cout << "\n\nDone.";
	while (!_kbhit());  //to hold console	
}


void getData()
{
	srand(123); //arbitrary random number seed
	for (int i = 0; i < MAX_ROWS; i++)
		for (int j = 0; j < MAX_COLS; j++)
			_data[i][j] = rand(); //RAND_MAX = 32767
}


void sortData()
{
	void bubble(int * a, int n);
	void bubbleAsm();

	cout << "sorting data...";

	//for (int i = 0; i < MAX_ROWS; i++) {
		//bubble sort row i
		//bubble(_data[i], MAX_COLS);
		bubbleAsm();
	//}
}

void bubble(int * a, int max)
{
	for (int n = max - 1; n >= 0; n--) {
		for (int j = 0; j < n; j++) {
			if (a[j] > a[j + 1]) {
				//swap
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}

void bubbleAsm()
{
	//cout << "sorting data...";
	for(int i=0; i<MAX_ROWS; i++){
		//bubble sort row i
		__asm{
			lea edx, _data	//point edx to start of data
			mov eax, i		//store row number in eax
			imul eax,4000	//memory address offset is 4000*i
			add edx,eax		//point edx to start of row

			mov ecx, MAX_COLS	//set outer loop counter to MAX_COLS
nextbubble:		dec ecx		//decrement the outer loop counter
			cmp ecx,0		//compare outer loop counter to zero
			jz  endsort		//if counter is zero, end of sort
			mov eax,edx		//point eax to start of row
			mov ebx,ecx		//set inner counter to ecx
nextnum:		mov esi,[eax]	//store number
			cmp esi,[eax+4]	//compare it to the next number
			jle noswap		//don't swap if number <= next number			
				mov edi,[eax+4]	//swap
				mov [eax],edi	//
				mov [eax+4],esi	//
noswap:		dec ebx			//decrement inner counter
			cmp ebx,0		//compare inner counter with zero
			jz nextbubble	//if zero, start the next bubble 
			add eax,4		//otherwise point to next number
			jmp nextnum
endsort:
		}
	}
}


void testData()
{
	cout << "\n\ndata[0][0]                   = " << _data[0][0];					//=87 for srand(123)
	cout << "\ndata[MAX_ROWS/2][MAX_COLS/2] = " << _data[MAX_ROWS / 2][MAX_COLS / 2];	//=16440 for srand(123)
	cout << "\ndata[MAX_ROWS-1][MAX_COLS-1] = " << _data[MAX_ROWS - 1][MAX_COLS - 1];	//=32760 for srand(123)
}


void outputData()
{
	ofstream sodata;
	sodata.open("sodata.txt");
	cout << "\n\noutputting data to sodata.txt...";

	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			sodata << _data[i][j] << "\t";
		}
		sodata << "\n";
	}

	sodata.close();
}

