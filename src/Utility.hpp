/**
 * Utility function(s).
 * Need to stop repeating my random number code so I'm putting it here.
 */

#ifndef BATTLESHIP_UTILITY
#define BATTLESHIP_UTILITY

#include <ctime>
#include <random>


namespace util
{
	inline int Rand(int low, int high)
	{
		// Get system time resource
		struct timespec tm;
		clock_gettime(CLOCK_REALTIME, &tm);

		// Get rand num generator engine & functor with clock nanosec as seed
		static std::minstd_rand0 e{tm.tv_nsec};
		std::uniform_int_distribution<int> ud{low, high};

		return ud(e);
	}
};

#endif //BATTLESHIP_UTILITY
