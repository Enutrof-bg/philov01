#include "philosophers.h"

int main()
{
	long test = get_time_ms() - (get_time_ms() + 100);

	printf("test:%ld", test);
}