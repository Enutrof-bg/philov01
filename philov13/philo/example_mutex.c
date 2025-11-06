#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data
{
	pthread_mutex_t mutex1;
	pthread_mutex_t mutex2;
	int			 compteur1;
	int			 compteur2;
}   t_data;
	
// routine1 lock mutex1 et routine2 lock mutex2
// ensuite routine1 va essayer de lock mutex2
// et routine2 va essayer de lock mutex1
// ce qui va provoquer un DEADLOCK
// car les deux threads attendent chacun l'autre pour continuer

// ROUTINE 1: Lock mutex1 puis mutex2
void *routine1(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
		
	printf("Thread 1 démarré\n");
		
	for (i = 0; i < 3; i++)
	{
		printf("\n[Thread 1] Tentative de lock mutex1...\n");
		pthread_mutex_lock(&data->mutex1);
		printf("[Thread 1] Mutex1 verrouillé!\n");
		
		sleep(1); // Laisse le temps à l'autre thread de lock mutex2
		
		printf("[Thread 1] Tentative de lock mutex2...\n");
		pthread_mutex_lock(&data->mutex2);
		printf("[Thread 1] Mutex2 verrouillé!\n");
		
		//Ne passe jamais ici car deadlock possible


		data->compteur1++;
		data->compteur2++;
		pthread_mutex_unlock(&data->mutex2);
		pthread_mutex_unlock(&data->mutex1);
	}
		
	printf("[Thread 1] Terminé\n");
	return NULL;
}

// ROUTINE 2: Lock mutex2 puis mutex1
void *routine2(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
		
	printf("Thread 2 démarré\n");
		
	for (i = 0; i < 3; i++)
	{
		printf("\n[Thread 2] Tentative de lock mutex2...\n");
		pthread_mutex_lock(&data->mutex2);
		printf("[Thread 2] Mutex2 verrouillé!\n");
		
		sleep(1);
		
		printf("[Thread 2] Tentative de lock mutex1...\n");
		pthread_mutex_lock(&data->mutex1);
		printf("[Thread 2] Mutex1 verrouillé!\n");
		
		// Ne passera jamais ici car DEADLOCK possible


		data->compteur1 += 2;
		data->compteur2 += 2;
		pthread_mutex_unlock(&data->mutex1);
		pthread_mutex_unlock(&data->mutex2);
		usleep(100000);
	}
		
	printf("[Thread 2] Terminé\n");
	return NULL;
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	t_data data;
		
	data.compteur1 = 0;
	data.compteur2 = 0;
		
	printf("Thread 1 lock: mutex1 puis mutex2\n");
	printf("Thread 2 lock: mutex2 puis mutex1\n");
		
	// Initialise les mutex
	if (pthread_mutex_init(&data.mutex1, NULL) != 0)
	{
		printf("Erreur: Initialisation mutex1 échouée\n");
		return (1);
	}
	if (pthread_mutex_init(&data.mutex2, NULL) != 0)
	{
		printf("Erreur: Initialisation mutex2 échouée\n");
		pthread_mutex_destroy(&data.mutex1);
		return (1);
	}
		

	// Crée les thread
	// lance routine1 dans thread1 et routine2 dans thread2
	if (pthread_create(&thread1, NULL, routine1, &data) != 0)
	{
		pthread_mutex_destroy(&data.mutex1);
		pthread_mutex_destroy(&data.mutex2);
		printf("Erreur: Création thread1 échouée\n");
		return (1);
	}
	if (pthread_create(&thread2, NULL, routine2, &data) != 0)
	{
		pthread_mutex_destroy(&data.mutex1);
		pthread_mutex_destroy(&data.mutex2);
		printf("Erreur: Création thread2 échouée\n");
		return (1);
	}


	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
		
	// Détruit les mutex
	pthread_mutex_destroy(&data.mutex1);
	pthread_mutex_destroy(&data.mutex2);
	return (0);
}
