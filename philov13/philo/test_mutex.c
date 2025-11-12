#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_t mutex1;
	// pthread_mutex_t mutex2;
	int			 compteur1;
	int			 compteur2;
}   t_data;

//Sans mutex, les routines vont s'executer en meme temps
//Avec mutex, un thread va lock le mutex, 
//et l'autre thread sera en attente que le mutex se unlock
//Le mutex permet l'execution d'un block de code sans interference par d'autre thread
void *routine1(void *arg)
{
	t_data *data = (t_data *)arg;


	// pthread_mutex_lock(&data->mutex1);


	printf("salut\n");
	usleep(1000000);
	printf("%d, %d\n", data->compteur1, data->compteur2);


	// pthread_mutex_unlock(&data->mutex1);

	return NULL;
}

int main()
{
	t_data data;
	data.compteur1 = 42;
	data.compteur2 = 10;

	pthread_mutex_init(&data.mutex1, NULL);
	// pthread_mutex_init(&data.mutex2, NULL);



	// Les deux thread executent la fonction routine1
	pthread_create(&data.thread1, NULL, routine1, &data);
	pthread_create(&data.thread2, NULL, routine1, &data);
	
	
	pthread_join(data.thread1, NULL);
	pthread_join(data.thread2, NULL);


	pthread_mutex_destroy(&data.mutex1);
	// pthread_mutex_destroy(&data.mutex2);
}