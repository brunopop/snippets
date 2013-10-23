#pragma once

namespace bps
{
	int FindIndex(int* array, int imin, int imax)
	{
		if (imin == imax)
		{
			if (array[imin] == imin)
				return imin;
			else
				return -1;
		}
		int icenter = (imin + imax) / 2;
		if (array[icenter] == icenter)
			return icenter;
		else if (array[icenter] < icenter)
			FindIndex(array, icenter+1, imax);
		else
			FindIndex(array, imin, icenter);
	};
}

