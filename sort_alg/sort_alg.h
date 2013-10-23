#pragma once

#include "../select_alg/select_alg.h"
#include <vector>

namespace bps
{

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

}

