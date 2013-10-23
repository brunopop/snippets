#pragma once

namespace bps
{
	/// <summary>
	/// Count the number of set bits in n.
	/// </summary>
	long count_bits(long n)
	{     
		unsigned int c; // c accumulates the total bits set in n
		for (c = 0; n; c++) 
			n &= n - 1; // clear the least significant bit set
		return c;
	};
}

