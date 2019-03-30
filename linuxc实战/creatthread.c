#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void thread()
{
	pthread_t thid = pthread_self();
	printf("i am a pthread\n my tid=%u\n",thid);

}
int main()
{
	pthread_t id[3];
	int i, ret[3];
	for(i=0; i<3; i++){
		ret[i] = pthread_create(&id[i], NULL, (void*)thread, NULL);
		if(ret[i]!=0)
		{
			printf("create pthread error\n");
			exit(1);
		}
	}
	printf("this is main process.\n");
	for(i=0; i<3; i++)
		pthread_join(id[i], NULL);
//	printf("this is main process.\n");
	return 0;
}
