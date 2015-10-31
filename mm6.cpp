#include <chrono>
#include <iostream>

using namespace std;

const int NUM_ROWS{ 10000 };
const int NUM_COLUMS{ 1000 };
int elements[NUM_ROWS][NUM_COLUMS];
int* pElements[NUM_ROWS][NUM_COLUMS];

int main(int argc,char* argv[])
{
	for(int i{ 0 }; i < NUM_ROWS; ++i)
	{
		for(int j{ 0 };j < NUM_COLUMS;++j)
		{
			elements[i][j] = i * j;
			pElements[i][j] = new int{elements[i][j]};
		}
	}

	auto start = chrono::high_resolution_clock::now();
	for(int i{0}; i < NUM_ROWS; ++i)
	{
		for(int j{0};j < NUM_COLUMS;++j)
		{
			const int result{ elements[j][i]};
		}
	}

	auto end = chrono::high_resolution_clock::now();
	auto different = end - start;

	cout << "Time taken for j then i: "
		 << chrono::duration_cast<chrono::microseconds>(different).count()
		 << "microseconds!" << endl;

	start = chrono::high_resolution_clock::now();
	for(int i{0}; i< NUM_ROWS;++i)
	{
		for(int j{0};j < NUM_COLUMS;++j)
		{
			const int result{ elements[i][j]};
		}
	}

	end = chrono::high_resolution_clock::now();
	different = end - start;

	cout << "Time taken for i then j:"
		 << chrono::duration_cast<chrono::microseconds>(different).count()
		 << "microseconds" << endl;

	start = chrono::high_resolution_clock::now();
	for(int i{0};i < NUM_ROWS;++i)
	{
		for(int j{0};j < NUM_COLUMS;++j)
		{
			const int result{ *(pElements[i][j])};
		}
	}

	end = chrono::high_resolution_clock::now();
	different =  end - start;

	cout << "Time taken for pointers with i then j:"
		 << chrono::duration_cast<chrono::microseconds>(different).count()
		 << "microseconds" << endl;

	return 0;
}
