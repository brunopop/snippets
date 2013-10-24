#pragma once

namespace bps
{
	template<class T>
	int BinarySearch(T& value, T* array, int imin, int imax)
	{
		if (imin == imax)
		{
			if (array[imin] == value)
				return imin;
			else
				return -1;
		}
		int icenter = imin + (imax - imin)/2;
		if (array[icenter] == value)
			return icenter;
		else if (value < array[icenter])
			return BinarySearch(value, array, imin, icenter);
		else
			return BinarySearch(value, array, icenter+1, imax);
	};
}

