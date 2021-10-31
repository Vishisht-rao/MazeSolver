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

int start = 8;
int goal = 280;
int numStates = 289;
double discountFactor = 0.9;
double learnRate = 0.5;
int maxEpochs = 5000;
double F[289][289];
double R[289][289];
double Q[289][289];

struct nextStateLength
{
    int states[4];
    int length; 
}nextStates[289];

struct range
{
    int low;
    int high;
};

void initialiseF() {
    F[0][1] = 1;
    F[2][3] = 1;
    F[3][4] = 1;
    F[5][6] = 1;
    F[6][7] = 1;
    F[7][8] = 1;
    F[8][9] = 1;
    F[9][10] = 1;
    F[10][11] = 1;
    F[11][12] = 1;
    F[12][13] = 1;
    F[13][14] = 1;
    F[15][16] = 1;
    F[17][18] = 1;
    F[19][20] = 1;
    F[21][22] = 1;
    F[22][23] = 1;
    F[25][26] = 1;
    F[26][27] = 1;
    F[27][28] = 1;
    F[28][29] = 1;
    F[29][30] = 1;
    F[31][32] = 1;
    F[32][33] = 1;
    F[35][36] = 1;
    F[37][38] = 1;
    F[39][40] = 1;
    F[41][42] = 1;
    F[43][44] = 1;
    F[44][45] = 1;
    F[46][47] = 1;
    F[52][53] = 1;
    F[53][54] = 1;
    F[56][57] = 1;
    F[59][60] = 1;
    F[62][63] = 1;
    F[64][65] = 1;
    F[66][67] = 1;
    F[68][69] = 1;
    F[70][71] = 1;
    F[72][73] = 1;
    F[74][75] = 1;
    F[77][78] = 1;
    F[79][80] = 1;
    F[82][83] = 1;
    F[85][86] = 1;
    F[86][87] = 1;
    F[88][89] = 1;
    F[89][90] = 1;
    F[91][92] = 1;
    F[92][93] = 1;
    F[93][94] = 1;
    F[95][96] = 1;
    F[97][98] = 1;
    F[98][99] = 1;
    F[102][103] = 1;
    F[104][105] = 1;
    F[105][106] = 1;
    F[106][107] = 1;
    F[109][110] = 1;
    F[111][112] = 1;
    F[114][115] = 1;
    F[119][120] = 1;
    F[122][123] = 1;
    F[123][124] = 1;
    F[125][126] = 1;
    F[126][127] = 1;
    F[127][128] = 1;
    F[129][130] = 1;
    F[132][133] = 1;
    F[134][135] = 1;
    F[137][138] = 1;
    F[138][139] = 1;
    F[140][141] = 1;
    F[142][143] = 1;
    F[143][144] = 1;
    F[146][147] = 1;
    F[147][148] = 1;
    F[150][151] = 1;
    F[151][152] = 1;
    F[153][154] = 1;
    F[155][156] = 1;
    F[156][157] = 1;
    F[158][159] = 1;
    F[159][160] = 1;
    F[164][165] = 1;
    F[166][167] = 1;
    F[167][168] = 1;
    F[170][171] = 1;
    F[172][173] = 1;
    F[174][175] = 1;
    F[175][176] = 1;
    F[176][177] = 1;
    F[177][178] = 1;
    F[178][179] = 1;
    F[181][182] = 1;
    F[184][185] = 1;
    F[185][186] = 1;
    F[188][189] = 1;
    F[190][191] = 1;
    F[193][194] = 1;
    F[195][196] = 1;
    F[197][198] = 1;
    F[199][200] = 1;
    F[199][216] = 1;
    F[201][202] = 1;
    F[202][203] = 1;
    F[208][209] = 1;
    F[210][211] = 1;
    F[214][215] = 1;
    F[217][218] = 1;
    F[219][220] = 1;
    F[224][225] = 1;
    F[226][227] = 1;
    F[229][230] = 1;
    F[231][232] = 1;
    F[233][234] = 1;
    F[234][235] = 1;
    F[235][236] = 1;
    F[236][237] = 1;
    F[239][240] = 1;
    F[241][242] = 1;
    F[243][244] = 1;
    F[244][245] = 1;
    F[247][248] = 1;
    F[251][252] = 1;
    F[253][254] = 1;
    F[257][258] = 1;
    F[259][260] = 1;
    F[260][261] = 1;
    F[263][264] = 1;
    F[265][266] = 1;
    F[267][268] = 1;
    F[269][270] = 1;
    F[272][273] = 1;
    F[275][276] = 1;
    F[276][277] = 1;
    F[278][279] = 1;
    F[280][281] = 1;
    F[281][282] = 1;
    F[283][284] = 1;
    F[284][285] = 1;
    F[285][286] = 1;
    F[286][287] = 1;
    F[287][288] = 1;
    F[17][34] = 1;
    F[34][51] = 1;
    F[51][68] = 1;
    F[85][102] = 1;
    F[119][136] = 1;
    F[136][153] = 1;
    F[170][187] = 1;
    F[187][204] = 1;
    F[204][221] = 1;
    F[221][238] = 1;
    F[238][255] = 1;
    F[255][272] = 1;
    F[1][18] = 1;
    F[35][52] = 1;
    F[52][69] = 1;
    F[103][120] = 1;
    F[137][154] = 1;
    F[154][171] = 1;
    F[188][205] = 1;
    F[205][222] = 1;
    F[239][256] = 1;
    F[256][273] = 1;
    F[2][19] = 1;
    F[53][70] = 1;
    F[104][121] = 1;
    F[121][138] = 1;
    F[155][172] = 1;
    F[189][206] = 1;
    F[206][223] = 1;
    F[223][240] = 1;
    F[257][274] = 1;
    F[20][37] = 1;
    F[71][88] = 1;
    F[122][139] = 1;
    F[173][190] = 1;
    F[190][207] = 1;
    F[224][241] = 1;
    F[258][275] = 1;
    F[4][21] = 1;
    F[38][55] = 1;
    F[55][72] = 1;
    F[123][140] = 1;
    F[157][174] = 1;
    F[208][225] = 1;
    F[242][259] = 1;
    F[259][276] = 1;
    F[5][22] = 1;
    F[56][73] = 1;
    F[73][90] = 1;
    F[90][107] = 1;
    F[141][158] = 1;
    F[175][192] = 1;
    F[192][209] = 1;
    F[226][243] = 1;
    F[23][40] = 1;
    F[57][74] = 1;
    F[91][108] = 1;
    F[108][125] = 1;
    F[125][142] = 1;
    F[210][227] = 1;
    F[261][278] = 1;
    F[7][24] = 1;
    F[41][58] = 1;
    F[58][75] = 1;
    F[143][160] = 1;
    F[194][211] = 1;
    F[228][245] = 1;
    F[245][262] = 1;
    F[262][279] = 1;
    F[25][42] = 1;
    F[59][76] = 1;
    F[93][110] = 1;
    F[144][161] = 1;
    F[178][195] = 1;
    F[212][229] = 1;
    F[246][263] = 1;
    F[43][60] = 1;
    F[60][77] = 1;
    F[94][111] = 1;
    F[128][145] = 1;
    F[145][162] = 1;
    F[162][179] = 1;
    F[196][213] = 1;
    F[213][230] = 1;
    F[230][247] = 1;
    F[247][264] = 1;
    F[44][61] = 1;
    F[78][95] = 1;
    F[112][129] = 1;
    F[146][163] = 1;
    F[163][180] = 1;
    F[180][197] = 1;
    F[214][231] = 1;
    F[265][282] = 1;
    F[62][79] = 1;
    F[96][113] = 1;
    F[113][130] = 1;
    F[164][181] = 1;
    F[198][215] = 1;
    F[232][249] = 1;
    F[249][266] = 1;
    F[46][63] = 1;
    F[80][97] = 1;
    F[114][131] = 1;
    F[131][148] = 1;
    F[182][199] = 1;
    F[216][233] = 1;
    F[250][267] = 1;
    F[30][47] = 1;
    F[64][81] = 1;
    F[115][132] = 1;
    F[132][149] = 1;
    F[166][183] = 1;
    F[183][200] = 1;
    F[251][268] = 1;
    F[268][285] = 1;
    F[14][31] = 1;
    F[31][48] = 1;
    F[48][65] = 1;
    F[82][99] = 1;
    F[99][116] = 1;
    F[133][150] = 1;
    F[201][218] = 1;
    F[252][269] = 1;
    F[15][32] = 1;
    F[32][49] = 1;
    F[49][66] = 1;
    F[83][100] = 1;
    F[100][117] = 1;
    F[117][134] = 1;
    F[151][168] = 1;
    F[168][185] = 1;
    F[219][236] = 1;
    F[253][270] = 1;
    F[33][50] = 1;
    F[67][84] = 1;
    F[84][101] = 1;
    F[101][118] = 1;
    F[135][152] = 1;
    F[169][186] = 1;
    F[203][220] = 1;
    F[237][254] = 1;
    F[271][288] = 1;

    
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
    pthread_t id1,id2;
    
    printf("\nSetting up maze...");

    initialiseF();
    for(int i=0; i<numStates; i++) {
        for(int j=0; j<numStates; j++) {
            if(F[i][j] == 1) F[j][i] = 1.0;
            else R[i][j] = -1.0;
        }
    }
    init_nextstates();
    R[281][280] = 10.0; R[280][280] = 10.0;

    printf("\nDone setting up maze!");

    printf("\nRunning Episodes...");
    struct range *Rg1 = (struct range*)malloc(sizeof(struct range));
    Rg1->low = 0;
    Rg1->high = 144;

    struct range *Rg2 = (struct range*)malloc(sizeof(struct range));
    Rg2->low = 145;
    Rg2->high = 288;
    
    pthread_create(&id1,NULL,train,(void*)Rg1);
    pthread_create(&id2,NULL,train,(void*)Rg2);
   
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    printf("\nDone running episodes");  

    printf("\nThe Q matrix is: \n ");
    display();

    printf("\nUsing Q to go from 0 to goal (%d)", goal);
    printf("\nThreaded\n");

    walk();
    system("python3 Animation.py < Animate.txt &");

}
