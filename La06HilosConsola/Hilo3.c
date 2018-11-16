#include <pthread.h>
#include <stdio.h>
void* computo(void* arg) {
	int candidato = 2;
	int n = *((int*) arg);
	while (1) {
		int factor;
		int es_primo = 1;
		for (factor = 2; factor < candidato; ++factor)
			if (candidato % factor == 0) {
				es_primo = 0;
				break;
			}
		if (es_primo) {
			n--;
			if (n == 0)
				return (void*)candidato;
		}
		++candidato;
	}
	return NULL;
}
int main() {
	pthread_t thread;
	int iesimo_primo = 10000;
	int primo;
	pthread_create(&thread, NULL, computo, &iesimo_primo);
	pthread_join(thread, (void*) &primo);
	pthread_exit;
	printf("El %d iesimo numero primo es %d.\n", iesimo_primo, primo);
	return 0;
}
