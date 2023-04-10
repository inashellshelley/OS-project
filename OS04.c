#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

int numResources,
    numProcesses;
int *res;
int **allo;
int **maxRequirement;
int **needed;
int *SafeSequence;
int numProcessran = 0;

pthread_mutex_t lockResources;
pthread_cond_t condition;

bool getSafeSequence();
void* processCode(void* );

int main(int arguc, char** arguv) {
	srand(time(NULL));

        printf("\n The number of processes are: ");
        scanf("%d", &numProcesses);

        printf("\n The number of resources: ");
        scanf("%d", &numResources);

        res = (int *)malloc(numResources * sizeof(*res));
        printf("\n The resources available currently (R1, R2 ...): ");
		for(int i=0; i<numResources; i++)
		scanf("%d", &res[i]);

        allo = (int **)malloc(numProcesses * sizeof(*allo));
        for(int i=0; i<numProcesses; i++)
                allo[i] = (int *)malloc(numResources * sizeof(**allo));

        maxRequirement = (int **)malloc(numProcesses * sizeof(*maxRequirement));
        for(int i=0; i<numProcesses; i++)
                maxRequirement[i] = (int *)malloc(numResources * sizeof(**maxRequirement));

   
        printf("\n");
        for(int i=0; i<numProcesses; i++) {
                printf("\n Resourcees allocated to process %d (R1, R2 ...):  ", i+1);
                for(int j=0; j<numResources; j++)
                        scanf("%d", &allo[i][j]);
        }
        printf("\n");

        for(int i=0; i<numProcesses; i++) {
                printf("\n Maximum resources required by process %d (R1, R2, ...): ", i+1);
                for(int j=0; j<numResources; j++)
                        scanf("%d", &maxRequirement[i][j]);
        }
        printf("\n");

        needed = (int **)malloc(numProcesses * sizeof(*needed));
        for(int i=0; i<numProcesses; i++)
                needed[i] = (int *)malloc(numResources * sizeof(**needed));

        for(int i=0; i<numProcesses; i++)
                for(int j=0; j<numResources; j++)
                        needed[i][j] = maxRequirement[i][j] - allo[i][j];

	SafeSequence = (int *)malloc(numProcesses * sizeof(*SafeSequence));
        for(int i=0; i<numProcesses; i++) SafeSequence[i] = -1;

        if(!getSafeSequence()) {
                printf("\nThe system has been led to an UNSAFE STATE! \n");
                exit(-1);
        }

        printf("\n\nSafe Sequence: ");
        for(int i=0; i<numProcesses; i++) {
                printf("%-3d", SafeSequence[i]+1);
        }

        printf("\nProcess execution.. \n\n");
        sleep(1);
	
	pthread_t processes[numProcesses];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

	int processNumber[numProcesses];
	for(int i=0; i<numProcesses; i++) processNumber[i] = i;

        for(int i=0; i<numProcesses; i++)
                pthread_create(&processes[i], &attr, processCode, (void *)(&processNumber[i]));

        for(int i=0; i<numProcesses; i++)
                pthread_join(processes[i], NULL);

        printf("\nProcesses Completed \n");	
	
        free(res);
        for(int i=0; i<numProcesses; i++) {
                free(allo[i]);
                free(maxRequirement[i]);
		free(needed[i]);
        }
        free(allo);
        free(maxRequirement);
	free(needed);
        free(SafeSequence);
}


bool getSafeSequence() {
        int tempRes[numResources];
        for(int i=0; i<numResources; i++) tempRes[i] = res[i];

        bool done[numProcesses];
        for(int i=0; i<numProcesses; i++) done[i] = false;
        int numdone=0;
        while(numdone < numProcesses) {
                bool safe = false;

                for(int i=0; i<numProcesses; i++) {
                        if(!done[i]) {
                                bool possible = true;

                                for(int j=0; j<numResources; j++)
                                        if(needed[i][j] > tempRes[j]) {
                                                possible = false;
                                                break;
                                        }

                                if(possible) {
                                        for(int j=0; j<numResources; j++)
                                                tempRes[j] += allo[i][j];
                                        SafeSequence[numdone] = i;
                                        done[i] = true;
                                        ++numdone;
                                        safe = true;
                                }
                        }
                }

                if(!safe) {
                        for(int k=0; k<numProcesses; k++) SafeSequence[k] = -1;
                        return false;
                }
        }
        return true;
}

void* processCode(void *arg) {
        int p = *((int *) arg);
        pthread_mutex_lock(&lockResources);

        while(p != SafeSequence[numProcessran])
                pthread_cond_wait(&condition, &lockResources);

        printf("\n--> Process %d", p+1);
        printf("\n\t Allocated : ");
        for(int i=0; i<numResources; i++)
                printf("%3d", allo[p][i]);

        printf("\n\t Need: ");
        for(int i=0; i<numResources; i++)
                printf("%3d", needed[p][i]);

        printf("\n\tAvailable : ");
        for(int i=0; i<numResources; i++)
                printf("%3d", res[i]);

        printf("\n"); sleep(1);

        printf("\t Resource Allocated");
        printf("\n"); sleep(1);
        printf("\tProcess code is running.. ");
        printf("\n"); sleep(rand()%3 + 2);
        printf("\tProcess code completed.. ");
        printf("\n"); sleep(1);
        printf("\t Releasing Resource.. ");
        printf("\n"); sleep(1);
        printf("\t Resource Released ");

	for(int i=0; i<numResources; i++)
                res[i] += allo[p][i];

        printf("\n\t Availability: ");
        for(int i=0; i<numResources; i++)
                printf("%3d", res[i]);
        printf("\n \n");

        sleep(1);

        numProcessran++;
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&lockResources);
	pthread_exit(NULL);
}
