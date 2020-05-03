#include "pch.h"
#include <iostream>
#include <fstream>
#include <omp.h>
#include <ctime>

void oddEvenSort(int * arr, int size)
{
	for (int i = 0; i < size; i++) {
		bool swapped = false;

		#pragma omp parallel for
		for (int j = 0; j < size - 1; j += 2) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}

		#pragma omp parallel for
		for (int j = 1; j < size - 1; j += 2) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}

		if (swapped == false) {
			break;
		}
	}
}

void combSort(int * arr, int size)
{
	double fakt = 1.2473309;

	int gap = size;
	bool swapped = true;

	while (gap != 1 || swapped == true)
	{
		gap /= fakt;

		if (gap < 1) {
			gap = 1;
		}

		if (gap == 1) {
			oddEvenSort(arr, size);
			break;
		}

		swapped = false;
		
	    #pragma omp parallel for
		for (int i = 0; i < size - gap; i++)
		{
			if (arr[i] > arr[i + gap])
			{
				std::swap(arr[i], arr[i + gap]);
				swapped = true;
			}
		}
	}
}


int main(int argc, char ** argv)
{
	const int size = 10000000;
	int * arr = new int[size];

	std::ifstream input;
	input.open("input10m.txt");

	for (int i = 0; i < size; i++) {
		input >> arr[i];
	}

	clock_t start = std::clock();

	omp_set_dynamic(0);
	omp_set_num_threads(1);
	combSort(arr, size);

	double duration = (std::clock() - start) / double(CLOCKS_PER_SEC);
	std::cout << "Time taken: " << duration << " seconds." << std::endl;

	system("PAUSE");
	return 0;
}