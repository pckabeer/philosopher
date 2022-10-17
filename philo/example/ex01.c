#include <pthread.h>
#include <stdio.h>
#include<unistd.h>
#define NUM_THREADS 3

void *print_numbers(void *threadid)
{
	static char c = '0';
	printf("%c\n", c);
	c++;
	if (c- 1 == '9')
		c = '1';
	return (threadid);
}

void *print_char(void *threadid)
{
	static char c1 = 'a';
	printf("%c\n", c1);
	c1++;
	if (c1- 1 == 'z')
		c1 = 'z';
	return (threadid);
}

void *print_hash(void *threadid)
{

		printf("#\n");
		return (threadid);
}




int main(int ac, char **av)
{
	pthread_t threads[NUM_THREADS];
	// pthread_t is the data type used to uniquely identify a thread. It is returned by pthread_create() and used by the application in function calls that require a thread identifier.
	// https://stackoverflow.com/questions/1759794/how-to-print-pthread-t
	// The pthread_self() function returns the ID of the thread in which it is invoked.
	long i;
	int j;

	i = 0;
	while(1)
	{
		pthread_create(&threads[0], NULL, print_numbers, (void *)0);
		pthread_create(&threads[1], NULL, print_char, (void *)1);
		pthread_create(&threads[2], NULL, print_hash, (void *)2);

       // usleep(200);
        pthread_create(&threads[0], NULL, print_numbers, (void *)0);
		pthread_create(&threads[1], NULL, print_char, (void *)1);
		pthread_create(&threads[2], NULL, print_hash, (void *)2);

         //usleep(200);
        pthread_create(&threads[0], NULL, print_numbers, (void *)0);
		pthread_create(&threads[1], NULL, print_char, (void *)1);
		pthread_create(&threads[2], NULL, print_hash, (void *)2);

         //usleep(200);
        pthread_create(&threads[0], NULL, print_numbers, (void *)0);
		pthread_create(&threads[1], NULL, print_char, (void *)1);
		pthread_create(&threads[2], NULL, print_hash, (void *)2);

        //usleep(200);
        pthread_create(&threads[0], NULL, print_numbers, (void *)0);
		pthread_create(&threads[1], NULL, print_char, (void *)1);
		pthread_create(&threads[2], NULL, print_hash, (void *)2);

		pthread_exit(NULL);
	}
	

}