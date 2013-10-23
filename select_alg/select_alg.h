#pragma once

#include <vector>

namespace bps
{
	// TODO: fix it
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

	/// <summary>
	/// Find the weighted median of an array.
	/// All elements are supposed distinct and not sorted.
	/// The sum of all weights is supposed to equal 1.
	/// sum is the sum of the weights of the elements that are smaller than those in array.
	/// The first call of FindWeightedMedian is FindWeightedMedian(A, W, 0),
	/// where A is the original array with weights W.
	/// The algorithm terminates in O(n) time in the worst case.
	/// </summary>
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
	};
}

