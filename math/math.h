#pragma once

#include <vector>

namespace bps
{
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
}

