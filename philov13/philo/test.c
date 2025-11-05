# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	printf("%ld\n", tv.tv_sec);
	printf("%ld\n", tv.tv_usec);

	// printf("%ld\n", tv.tv_sec * 1000 + tv.tv_usec / 1000);

	long now =  tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%ld\n", now);

	sleep(2);

	gettimeofday(&tv, NULL);
	long apres =  tv.tv_sec * 1000 + tv.tv_usec / 1000;

	printf("%ld\n", apres - now);

	long elapsed = apres - now;

	if (elapsed >= time_to_die)
	{
		
	}

}