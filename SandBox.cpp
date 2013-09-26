#include <vector>
#include <list>
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>

template<class T> std::vector<T> QuickSortSimple(std::vector<T> &array)
{
	// Trivial case
	if (array.size() <= 1) return array;
	// Pick pivot
	T pivot = array[array.size()/2];
	// Separate smaller elements from greater elements
	std::vector<T> smaller, greater;
	std::vector<T>::iterator it = array.begin();
	unsigned int i=0;
	// First half of the array
	for (; i<array.size()/2; i++)
	{
		if (array[i] > pivot) greater.push_back(array[i]);
		else smaller.push_back(array[i]);
	}
	// Skip pivot
	i++;
	// Second half of the array
	for (; i<array.size(); i++)
	{
		if (array[i] > pivot) greater.push_back(array[i]);
		else smaller.push_back(array[i]);
	}
	// Recursively sort
	smaller = QuickSortSimple(smaller);
	greater = QuickSortSimple(greater);
	// Concatenate
	std::vector<T> sorted_array;
	sorted_array.insert(sorted_array.begin(), smaller.begin(), smaller.end());
	sorted_array.push_back(pivot);
	sorted_array.insert(sorted_array.end(), greater.begin(), greater.end());
	return sorted_array;
};

template<class T> void QuickSortInPlace(std::vector<T> &array, int begin, int end)
{
	// Stopping criterion: array must have 2 or more elements
	if (begin < end)
	{
		int left = begin;
		int right = end;
		// Pick pivot between left and right
		T pivot = array[left + (right-left)/2];
		while (left <= right)
		{
			while (array[left] < pivot) left++;
			while (array[right] > pivot) right--;
			if (left <= right)
			{
				// Swap left and right
				T tmp = array[left];
				array[left] = array[right];
				array[right] = tmp;
				left++;
				right--;
			}
		}
		QuickSortInPlace(array, begin, right);
		QuickSortInPlace(array, left, end);
	}
};

template<class T> std::vector<T> sort(std::vector<T> &array)
{
	// If input list contains only one element,
	// consider it sorted and return it
	if (array.size() <= 1) return array;
	// Else, divide the input list in two,
	// sort each half separately, then merge them
	std::vector<T>::iterator begin_left = array.begin();
	std::vector<T>::iterator end_left = begin_left + array.size()/2;
	std::vector<T> left (begin_left, end_left);
	std::vector<T> sorted_left = sort(left);
	std::vector<T>::iterator begin_right = end_left;
	std::vector<T>::iterator end_right = array.end();
	std::vector<T> right (begin_right, end_right);
	std::vector<T> sorted_right = sort(right);
	return merge(sorted_left, sorted_right);
};

template<class T> std::vector<T> merge(std::vector<T> &left, std::vector<T> &right)
{
	std::vector<T> result;
	std::vector<T>::iterator it_left, it_right;
	it_left = left.begin(); it_right = right.begin();
	while (it_left != left.end() || it_right != right.end())
	{
		if (it_left != left.end() && it_right != right.end())
		{
			if (*it_left > *it_right)
			{
				result.push_back(*it_right++);
			}
			else
			{
				result.push_back(*it_left++);
			}
		}
		else if (it_left != left.end())
		{
			result.push_back(*it_left++);
		}
		else if (it_right != right.end())
		{
			result.push_back(*it_right++);
		}
	}
	return result;
};

template<class T> void BubbleSort(std::vector<T> &array)
{
	int n = array.size();
	while (n > 0)
	{
		int m = 0;
		for (int i=1; i<n; i++)
		{
			if ( array[i-1] > array[i] )
			{
				// Swap
				T tmp = array[i-1];
				array[i-1] = array[i];
				array[i] = tmp;
				m = i;
			}
		}
		n = m;
	}
};

template<class T> std::vector<T> WigglySort(std::vector<T> &array)
{
	T med = QuickSelect(array, array.size()/2);
	std::vector<T> smaller, greater;
	int numMed = 0;
	for (std::vector<T>::iterator it=array.begin(); it!=array.end(); ++it)
	{
		if (*it == med) numMed++;
		else if (*it < med) smaller.push_back(*it);
		else greater.push_back(*it);
	}
	std::vector<T> wiggly;
	std::vector<T>::iterator s=smaller.begin(), g=greater.begin();
	bool turn = true;
	if (greater.size() > smaller.size()) turn = !turn;
	while (s != smaller.end() || g != greater.end())
	{
		if (s != smaller.end() && g != greater.end())
		{
			if (turn) wiggly.push_back(*s++);
			else wiggly.push_back(*g++);
			turn = !turn;
		}
		else if (s != smaller.end())
		{
			wiggly.push_back(*s++);
			wiggly.push_back(med);
		}
		else
		{
			wiggly.push_back(*g++);
			wiggly.push_back(med);
		}
	}
	return wiggly;
};

//template<class T> T MedianOfMedians(std::vector<T> &array)
//{
//	int n = array.size();
//	int numMedians = n/5;
//	for (int i=0; i<numMedians; i++)
//	{
//		// Get the median of five elements
//		int left = 5*i;
//		int right = left + 4;
//		if (right > n-1) right = n-1;
//	}
//};

template<class T> T QuickSelect(std::vector<T> &array, unsigned int k)
{
	if (array.size() < 2) return array[0];
	T pivot = array[array.size()/2];
	// T pivot = MedianOfMedians(array);
	std::vector<T> smaller, greater;
	for (std::vector<T>::iterator it=array.begin(); it!=array.end(); ++it)
	{
		if (*it < pivot)
		{
			smaller.push_back(*it);
		}
		else if (*it > pivot)
		{
			greater.push_back(*it);
		}
	}
	if (k < smaller.size())
	{
		return QuickSelect(smaller, k);
	}
	else if (k > array.size() - greater.size())
	{
		return QuickSelect(greater, k - (array.size() - greater.size()));
	}
	else
	{
		return pivot;
	}
};

// Find the weighted median of an array
// All elements are supposed distinct and not sorted
// The sum of all weights is supposed to equal 1
// sum is the sum of the weights of the elements that are smaller than those in array
// The first call of FindWeightedMedian is FindWeightedMedian(A, W, 0),
// where A is the original array with weights W.
// The algorithm terminates in O(n) time in the worst case
template<class T> T FindWeightedMedian(std::vector<T> &array, std::vector<double> &weights, double sum)
{
	int n = array.size();
	// If the array has one element, then it is the weighted median
	if (n <= 1) return array[0];
	// If n is even, the index of the median is n/2
	int median_k = n/2-1;
	// If n is odd, the index of the median is (n+1)/2
	if (n % 2 != 0) median_k = (n+1)/2-1;
	// Find the median of A
	T median = QuickSelect(array, median_k);
	// Partition A into B and C
	// smaller contains elements that are <= median
	// greater contains elements that are > median
	std::vector<T> smaller, greater;
	// smaller_weights and greater_weights contain corresponding weights
	std::vector<double> smaller_weights, greater_weights;
	// At the same time, compute the weighted sum for smaller elements
	double w_sum = 0;
	for (unsigned int i=0; i<array.size(); i++)
	{
		if (array[i] > median)
		{
			greater.push_back(array[i]);
			greater_weights.push_back(weights[i]);
		}
		else
		{
			smaller.push_back(array[i]);
			smaller_weights.push_back(weights[i]);
			w_sum += weights[i];
		}
	}
	// If w_sum is >= 1/2 then the weighted median is in smaller
	// Otherwise, it is in greater
	if (w_sum + sum >= 0.5)
	{
		return FindWeightedMedian(smaller, smaller_weights, sum);
	}
	else
	{
		return FindWeightedMedian(greater, greater_weights, w_sum + sum);
	}
}

int maxSubsequence(std::vector<int> &array, int &begin, int &end)
{
	std::vector<int> result(array.size(), 0);
	result[0] = array[0];
	int currMax = array[0];

	int local_begin = 0;
	int local_end = 0;
	int global_begin = 0;
	int global_end = 0;

	for (unsigned int i=1; i<array.size(); i++)
	{
		if (array[i] > currMax + array[i])
		{
			currMax = array[i];
			local_begin = i;
		}
		else
		{
			currMax = currMax + array[i];
		}
		local_end = i;
		if (result[i-1] > currMax)
		{
			result[i] = result[i-1];
		}
		else
		{
			result[i] = currMax;
			global_begin = local_begin;
			global_end = local_end;
		}
	}
	begin = global_begin;
	end = global_end;
	return result[array.size()-1];
};

// O(sqrt(n))
bool isPrime(int n)
{
	int sqrtn = (int) std::sqrt(double(n));
	for (int i=2; i<=sqrtn; i++)
	{
		if (n % i == 0) return false;
	}
	return true;
};

// O(n*sqrt(n))
bool GoldbachsConjecture(int n, int *p, int *q)
{
	bool isGoldbach = false;
	int i = 2;
	for (i; i<=n/2; i++) // order n/2 worst case
	{
		if (isPrime(i) && isPrime(n-i)) // order 2 * sqrt(n) worst case
		{
			isGoldbach = true;
			break;
		}
	}
	*p = i;
	*q = n-i;
	return isGoldbach;
};

std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

int main(int argc, char* argv[])
{
	// Find the weighted median of an array in O(n) time
	int elems[] = {10, -20, 9, 8, 15, -12, 6, 5, 4, 2, -5, 3, 1};
	double weights[] = {0.01, 0.2, 0.1, 0.05, 0.03, 0.01, 0.21, 0.17, 0.03, 0.03, 0.1, 0.04, 0.02};
	int weighted_median = FindWeightedMedian(std::vector<int>(elems, elems+sizeof(elems)/sizeof(int)),
												std::vector<double>(weights, weights+sizeof(weights)/sizeof(double)), 0.0);


	// Goldbach's conjecture
	int n = 41;
	int p = 0, q = 0;
	bool isGoldbach = GoldbachsConjecture(n, &p, &q);


	// Max subsequence
	int array[] = {10, -20, 9, 8, 3, -12, 6, 3, 4, 1, -5, 3, 1};
	std::vector<int> arr(array, array+sizeof(array)/sizeof(int));
	int begin = 0, end = 0;
	int res = maxSubsequence(arr, begin, end);
	

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

