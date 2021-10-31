#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

int start = 0;
int goal = 41;
int numStates = 42;
double discountFactor = 0.9;
double learnRate = 0.5;
int maxEpochs = 2500;
double F[42][42];
double R[42][42];
double Q[42][42];

struct nextStateLength
{
    int states[4];
    int length; 
}nextStates[42];

struct range
{
    int low;
    int high;
};

void initialiseF() {
    F[0][1] = 1.0; F[0][7] = 1.0; F[1][2] = 1.0; F[2][1] = 1.0; F[2][3] = 1.0; F[2][9] = 1.0;
    F[3][2] = 1.0; F[3][10] = 1.0; F[4][5] = 1.0; F[4][11] = 1.0; F[5][4] = 1.0; F[5][6] = 1.0; F[5][12] = 1.0;
    F[6][5] = 1.0; F[7][0] = 1.0; F[7][8] = 1.0; F[8][7] = 1.0; F[9][2] = 1.0; F[9][16] = 1.0;
    F[10][3] = 1.0; F[11][4] = 1.0; F[11][18] = 1.0; F[12][5] = 1.0; F[12][13] = 1.0;
    F[13][12] = 1.0; F[13][20] = 1.0; F[14][15] = 1.0; F[14][21] = 1.0;
    F[15][14] = 1.0; F[15][16] = 1.0; F[15][22] = 1.0;
    F[16][9] = 1.0; F[16][15] = 1.0; F[16][17] = 1.0; F[16][23] = 1.0;
    F[17][16] = 1.0; F[17][18] = 1.0; F[18][11] = 1.0; F[18][17] = 1.0; F[18][25] = 1.0;
    F[19][20] = 1.0; F[19][26] = 1.0; F[20][13] = 1.0; F[20][19] = 1.0;
    F[21][14] = 1.0; F[21][28] = 1.0; F[22][15] = 1.0; F[22][29] = 1.0;
    F[23][16] = 1.0; F[23][24] = 1.0; F[24][23] = 1.0; F[24][31] = 1.0;
    F[25][18] = 1.0; F[25][32] = 1.0; F[26][19] = 1.0; F[26][27] = 1.0;
    F[27][26] = 1.0; F[27][34] = 1.0; F[28][21] = 1.0; F[28][35] = 1.0;
    F[29][22] = 1.0; F[29][30] = 1.0; F[30][29] = 1.0; F[30][37] = 1.0;
    F[31][24] = 1.0; F[32][25] = 1.0; F[32][39] = 1.0; F[33][40] = 1.0;
    F[34][27] = 1.0; F[34][41] = 1.0; F[35][28] = 1.0; F[35][36] = 1.0; F[36][35] = 1.0;
    F[37][30] = 1.0; F[37][38] = 1.0; F[38][37] = 1.0; F[39][32] = 1.0; F[39][40] = 1.0;
    F[40][33] = 1.0; F[40][39] = 1.0; F[41][34] = 1.0; F[41][41] = 1.0;
}


void init_nextstates()
{
	for(int i=0;i<numStates;i++)
	{
		for(int j=0;j<4;j++)
		{
			nextStates[i].states[j] = -1;
		}
		int k=0;
		for(int j=0;j<numStates;j++)
		{
			if(F[i][j])
			{
				nextStates[i].states[k] = j;
				k++;
			}
		}
        nextStates[i].length = k;
	}
}


/*---------------------------*/

unsigned long get_time_diff_in_usecs(struct timeval *from, struct timeval *to)
{
   return (to -> tv_sec - from -> tv_sec) * 1000000 + (to -> tv_usec - from -> tv_usec);
}


/*---------------------------*/

void *train(void* rng) {

    int in_while=0;
    struct timeval start_time, end_time;
    int seed_p = 11;

    gettimeofday(&start_time, NULL);
    for(int i=0; i<maxEpochs; i++) {
        int currentState = (rand_r(&seed_p)%(((struct range*)rng)->high - ((struct range*)rng)->low + 1)) + ((struct range*)rng)->low;
        while(1) {
            int nextState = nextStates[currentState].states[rand_r(&seed_p)%(nextStates[currentState].length)];
            
            double maxQ = -9999.99;
            
            for(int j=0; j<nextStates[nextState].length; j++) 
            {
                int nextNextState = nextStates[nextState].states[j];
                double q = Q[nextState][nextNextState];
                if(q > maxQ) maxQ = q;
            }


            //Bellman Equation
            Q[currentState][nextState] = ((1.0-learnRate)*Q[currentState][nextState]) + (learnRate*(R[currentState][nextState] + (discountFactor*maxQ)));

            currentState = nextState;
            in_while++;
            if(currentState == goal) break;
        }
    }

    gettimeofday(&end_time, NULL);
    printf("\n\nTrain time: %lu usecs Max epochs: %d\n\n", get_time_diff_in_usecs(&start_time, &end_time), maxEpochs);
    printf("Train loop count: %d\n",in_while);
}

int findMax(int curr) {
    int max = 0;
    for(int i=1; i<numStates; i++) {
        if(Q[curr][i] > Q[curr][max]) max = i;
    }
    return max;
}

void walk() {
    int next;
    int curr = start;
    printf("\n%d -> ", curr);
    while(curr!=goal) {
        next = findMax(curr);
        printf("%d -> ", next);
        curr = next;
    }
    printf("Done!\n");  
}

void display() {
    FILE *fp;
    fp = fopen("Animate.txt","w");
    if(fp == NULL)
    {   
        printf("File not found\n");
    }
    int rows = numStates;
    int cols = numStates;
    for(int i=0;i<rows;i++)
    {
    	for(int j=0;j<cols;j++)
    	{
    		fprintf(fp,"%lf ",Q[i][j]);
    	}
    	fprintf(fp,"\n");
    }
    fclose(fp);
}

int main() {
    srand(0);
    pthread_t id1,id2,id3,id4;
    
    printf("\nSetting up maze...");
    initialiseF();

    for(int i=0; i<numStates; i++) {
        for(int j=0; j<numStates; j++) {
            if(F[i][j] == 1) F[j][i] = 1.0;
            else R[i][j] = -1.0;
        }
    }
    init_nextstates();

    R[34][41] = 10.0; R[41][41] = 10.0;

    printf("\nDone setting up maze!");

    printf("\nRunning Episodes...");
    
    struct range *Rg1 = (struct range*)malloc(sizeof(struct range));
    Rg1->low = 0;
    Rg1->high = 10;

    struct range *Rg2 = (struct range*)malloc(sizeof(struct range));
    Rg2->low = 11;
    Rg2->high = 20;
    
    struct range *Rg3 = (struct range*)malloc(sizeof(struct range));
    Rg3->low = 21;
    Rg3->high = 31;
    
    struct range *Rg4 = (struct range*)malloc(sizeof(struct range));
    Rg4->low = 32;
    Rg4->high = 41;
    

    pthread_create(&id1,NULL,train,(void*)Rg1);
    pthread_create(&id2,NULL,train,(void*)Rg2);
    pthread_create(&id3,NULL,train,(void*)Rg3);
    pthread_create(&id4,NULL,train,(void*)Rg4);
   
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    pthread_join(id3,NULL);
    pthread_join(id4,NULL);

    printf("\nDone running episodes");  

    printf("\nThe Q matrix is: \n ");
    display();
    printf("\nUsing Q to go from 0 to goal (%d)", goal);
    printf("\nThreaded\n");
    walk();
    system("python3 Animation.py < Animate.txt &");

}
