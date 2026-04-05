/*
	April 5, 2026
	Simple 1D area generation algorithm (from scratch).
	Synopsis:
		I think about the algorithm of some popular games like minecraft, skyrim, CatacalysmDDA, etc.
		i want to make somthing about it like a simple 1d infinite generation array.

	the code can:
		* genarate new area in the array
		* move location, left and right.
		* mark the starting pos.
*/

#include <iostream>
#include <vector>
#include <cstdio>

#include <chrono> // benchmark functions

#include <algorithm> // many utilities

std::vector<int> genVec(int num) // generate a vector with 0 as padding
{
	std::vector<int> vec = {};
	for(int i = 0; i < num; i ++)
	{
		vec.push_back(0);
	}
	return vec;
}

void printArr(std::vector<int> Vec)
{
		for(int v : Vec)
	{
		printf("%d", v);
	}
	printf("\n");
}

// utils/helper
class Benchmark // test the function (usage: create the object inside the function, and it prints the total amount of time the function has run)
{
public:
	Benchmark()
	{
		this->s = std::chrono::high_resolution_clock::now();
	}
	~Benchmark()
	{
		this->e = std::chrono::high_resolution_clock::now();
		auto sec = std::chrono::duration_cast<std::chrono::seconds>(this->e - this->s);
		auto m = std::chrono::duration_cast<std::chrono::microseconds>(this->e - this->s);
		std::cout << "Duration: " << sec.count() << "sec " << m.count() << "ms" << std::endl;
	}
private:
	std::chrono::high_resolution_clock::time_point s, e;
};

bool testRight(int index, std::vector<int> arr)
{
	return (index == (int)arr.size()-1);
}

bool testLeft(int index)
{
	return (index == 0);
}

void genAreaRight(std::vector<int> &arr)
{
	arr.push_back(0);
}

void movRight(int *pos, std::vector<int> &arr)
{
	if(testRight(*pos, arr)) { genAreaRight(arr); } // genarate area right
	std::swap(arr[*pos],arr[*pos+1]);
	*pos += 1;
}
//   x
// 0 0 0 
//   ^

void genAreaLeft(std::vector<int> &arr)
{
	arr.insert(arr.begin(), 0);
}

void movLeft(int *ori, int *pos, std::vector<int> &arr)
{
	if(testLeft(*pos)) // test if the left most dont exist
	{
		genAreaLeft(arr); // generate area left most
		*ori -= 1;
		std::swap(arr[*pos],arr[*pos+1]);
	}
	else
	{
		std::swap(arr[*pos],arr[*pos-1]);
		*pos -= 1;
	}
}

void printHelp()
{
	printf("1 - print array\na - move left\nd - move right\nq - exit the program\n");
}

int main()
{
	std::vector<int> arr = genVec(4);
	int curPos = 0; // current position
	int _x = 0; // array
	while(1)
	{
		char a;
		std::cin >> a; 
		// mark origin
		arr[_x*-1] = 7;
		// mark pos
		arr[curPos] = 1;
		switch(a)
		{
			case '1':
				printArr(arr);
				break;
			case 'q':
				return 0;
				break;
			case 'd':
				arr[_x*-1] = 0; // set the origin to 0 to avoid swapping the wrong value
				movRight(&curPos, arr);
				break;
			case 'a':
				arr[_x*-1] = 0;
				movLeft(&_x, &curPos, arr);
				break;
			default:
				printHelp();
				break;	
		};
	}
	return 0;
}
