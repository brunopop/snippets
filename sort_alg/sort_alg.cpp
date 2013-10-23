#include "sort_alg.h"
#include <iostream>
#include <time.h>

using namespace bps;

int main(int argc, char* argv[])
{
	// Compare sorting algorithms
	int numTests = 10;

	float avg_quick_simple = 0;
	float avg_quick_inplace = 0;
	float avg_mergesort = 0;
	float avg_bubble = 0;
	float avg_wiggly = 0;

	for (int i=0; i< numTests; i++)
	{

		std::vector<int> array(65536, 0);
		for (std::vector<int>::iterator it=array.begin(); it!=array.end(); ++it)
		{
			*it = std::rand() - RAND_MAX/2;
		}

		std::cout << "Original array:\n\t";
		std::vector<int>::iterator it=array.begin();
		int count = 0;
		while (count < 15)
		{
			std::cout << " " << *it;
			++it;
			count++;
		}
		std::cout << std::endl;

		clock_t time_quicksort = clock();
		std::vector<int> sorted_arrray = QuickSortSimple(array);
		time_quicksort = clock() - time_quicksort;
		std::cout << "Sorted array using simple quicksort:\n\t";
		count = 0;
		it = sorted_arrray.begin();
		while (count < 15)
		{
			std::cout << " " << *it;
			++it;
			count++;
		}
		std::cout << std::endl;
		std::cout << "Time: " << float(time_quicksort)/CLOCKS_PER_SEC << " s\n" << std::endl;
		avg_quick_simple += float(time_quicksort)/CLOCKS_PER_SEC;

		std::vector<int> myarrray_inplace = array;
		clock_t time_quicksort2 = clock();
		QuickSortInPlace(myarrray_inplace, 0, myarrray_inplace.size()-1);
		time_quicksort2 = clock() - time_quicksort2;
		std::cout << "Sorted array using in-place quicksort:\n\t";
		count = 0;
		it = myarrray_inplace.begin();
		while (count < 15)
		{
			std::cout << " " << *it;
			++it;
			count++;
		}
		std::cout << std::endl;
		std::cout << "Time: " << float(time_quicksort2)/CLOCKS_PER_SEC << " s\n" << std::endl;
		avg_quick_inplace += float(time_quicksort2)/CLOCKS_PER_SEC;

		clock_t time_mergesort = clock();
		std::vector<int> myarray_mergesort = sort(array);
		time_mergesort = clock() - time_mergesort;
		std::cout << "Sorted array using mergesort:\n\t";
		count = 0;
		it = myarray_mergesort.begin();
		while (count < 15)
		{
			std::cout << " " << *it;
			++it;
			count++;
		}
		std::cout << std::endl;
		std::cout << "Time: " << float(time_mergesort)/CLOCKS_PER_SEC << " s\n" << std::endl;
		avg_mergesort += float(time_mergesort)/CLOCKS_PER_SEC;

		std::vector<int> sorted_bubble = array;
		clock_t time_bubblesort = clock();
		BubbleSort(sorted_bubble);
		time_bubblesort = clock() - time_bubblesort;
		std::cout << "Sorted array using bubblesort:\n\t";
		count = 0;
		it = sorted_bubble.begin();
		while (count < 15)
		{
			std::cout << " " << *it;
			++it;
			count++;
		}
		std::cout << std::endl;
		std::cout << "Time: " << float(time_bubblesort)/CLOCKS_PER_SEC << " s\n" << std::endl;
		avg_bubble += float(time_bubblesort)/CLOCKS_PER_SEC;

		clock_t time_wiggly = clock();
		std::vector<int> wiggly_array = WigglySort(array);
		time_wiggly = clock() - time_bubblesort;
		std::cout << "Wiggly array:\n\t";
		count = 0;
		it = wiggly_array.begin();
		while (count < 15)
		{
			std::cout << " " << *it;
			++it;
			count++;
		}
		std::cout << std::endl;
		std::cout << "Time: " << float(time_wiggly)/CLOCKS_PER_SEC << " s\n" << std::endl;
		avg_wiggly += float(time_wiggly)/CLOCKS_PER_SEC;

	}

	avg_quick_simple /= numTests;
	std::cout << "Average time for simple quicksort: " << avg_quick_simple << " s" << std::endl;
	avg_quick_inplace /= numTests;
	std::cout << "Average time for in-place quicksort: " << avg_quick_inplace << " s" << std::endl;
	avg_mergesort /= numTests;
	std::cout << "Average time for mergesort: " << avg_mergesort << " s" << std::endl;
	avg_bubble /= numTests;
	std::cout << "Average time for bubblesort: " << avg_bubble << " s" << std::endl;
	avg_wiggly /= numTests;
	std::cout << "Average time for wiggle sort: " << avg_wiggly << " s" << std::endl;

	return 0;
}

