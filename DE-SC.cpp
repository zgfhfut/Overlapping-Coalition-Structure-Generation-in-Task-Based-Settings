// BDE-OCSG.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include "stdio.h"
#include "stdlib.h"
#include "math.h"


#include "time.h"

#include "string.h"
/********************************************************************/
#include "random.h"       /*Random Number Generator*/
/********************************************************************/

# define INF 1.0e14
# define EPS 1.0e-14

# define PI 3.14159265358979

#define maxpop   30  /*Max population */

#define maxagent   20 /*Max no. of agents */
#define maxgoal    10 /*Max no. of goals */
#define maxresource    13/*Max no. of resources */

#define min(a,b) (((a)<(b))?(a):(b))
/********************************************************************/
#define MAX_EXPERIMENT  30  /*Experimental times*/

#define MAX_GENERATION  500  /*Max no. of generation*/
/********************************************************************/
/********************************************************************/
double seed;      /*Random Seed*/
double pcross;        /*Cross-over Probability*/
double pmut_b;          /*Mutation Probability*/


//#define str_alg "case1-zhang"
//#define str_alg "case1-our"


#define no_suite  13
//int num_one_operations;
//int num_zero_operations;


int Resource_Agent[maxagent][maxresource] = {
	18,16,16,17,18,11,18,14,12,13,11,11,16,
	13,14,15,21,17,11,17,14,14,13,10,12,16,
	18,14,15,18,13,10,13,14,13,14,9,15,18,
	17,15,16,18,16,12,17,13,12,16,10,17,13,
	15,18,16,16,17,9,13,15,10,16,14,14,17,
	14,17,14,19,19,11,12,11,15,18,12,13,18,
	17,18,17,20,16,8,14,13,10,13,9,16,13,
	12,17,14,14,14,12,14,11,15,17,14,14,17,
	17,17,12,15,16,11,13,15,14,17,10,14,12,
	18,18,16,18,12,12,16,13,15,12,13,17,18,
	12,13,13,19,18,8,15,13,10,14,14,11,14,
	17,13,13,18,12,10,19,15,15,16,11,14,16,
	18,17,16,18,15,9,19,15,12,16,14,16,18,
	18,13,13,19,16,11,18,11,13,12,12,16,15,
	12,14,12,14,12,9,19,12,11,13,11,15,18,
	13,12,16,19,19,9,16,15,13,17,14,11,13,
	18,16,15,20,14,8,18,10,12,13,10,11,18,
	12,17,12,21,15,12,18,12,12,16,11,15,19,
	16,12,13,19,13,10,17,14,11,17,13,14,19,
	18,17,27,17,40,44,20,12,26,31,26,16,21, };

int Resource_Goal[maxgoal][maxresource] = {
	13,7,11,11,5,4,11,5,4,5,6,12,7,//10,//5,4,//8,9,//8,11,//8,9,//10,5,10,
	12,10,4,18,7,6,12,10,5,15,10,8,6,//8,//9,8,//10,9,//7,7,//12,9,//10,15,10,
	6,10,8,16,6,9,10,9,7,12,8,11,14,//10,//15,5,//17,5,//6,12,//7,14,//9,11,4,
	6,5,5,12,6,12,10,10,10,14,12,13,12,//15,//9,10,//18,4,//11,5,//9,13,//8,8,13,
	9,16,8,11,11,12,12,7,5,10,10,10,14,//5,//9,11,//16,8,//8,9,//4,14,//6,9,8,
	12,7,9,5,13,8,13,9,9,5,9,11,10,//8,//6,4,//7,9,//5,11,//6,9,//5,14,13,
	11,12,9,9,18,4,11,6,8,6,9,10,15,//14,//12,8,//12,9,//9,6,//13,11,//7,15,8,
	12,5,17,9,21,12,4,15,13,14,8,7,13,//9,//10,6,//5,14,//5,11,//11,12,//5,6,9,
	11,17,13,21,11,6,9,12,6,8,7,6,11,//14,//13,18,//17,6,//9,11,//11,5,//11,14,13,
	12,13,16,8,12,6,16,4,21,15,3,6,7,//12,//7,8,//9,12,//17,15,//14,10,//5,12,6,
};



int Interest_Set[maxagent][maxgoal] = {
	1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 1, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 0, 0, 1, 0, 0,
	0, 1, 0, 0, 0, 0, 1, 0, 0, 1,
	0, 1, 0, 0, 1, 0, 0, 0, 0, 1,
	0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 1, 0, 0, 1, 0,
	0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
};


int Reward_Goal[maxgoal] = {
	79, 70, 60, 67, 79, 58, 78, 69, 68, 55,
};










typedef struct       /*individual properties*/
{
	int bincode[maxgoal][maxagent]; /*list of real variables*/
	int fitness;/*Fitness values */

}individual;        /*Structure defining individual*/

typedef struct
{
	individual ind[maxpop]; /*Different Individuals*/
	individual *ind_ptr;

}population;             /*Population Structure*/

typedef struct
{
	individual ind[2 * maxpop]; /*Different Individuals*/
	individual *ind_ptr2;

}population2;             /*Population Structure*/


/********************************************************************/
void input(); /*Input Parameters from user*/
void bininit(population *pop_ptr);/*initializes the population*/

void bincross(population *old_pop_ptr, population *mate_pop_ptr, population *new_pop_ptr);/*binary crossover*/
void binmutate(population *old_pop_ptr, population *mate_pop_ptr);/*binary mutation*/

void pop_repair(population *pop_ptr);


void xiao_repair(individual *ind_ptr);

double AMFunction(double x);//bit string generating function

void func(population *pop_ptr);/*evaluate the value of the function*/

void keepbetter(population *old_pop_ptr, population *new_pop_ptr);
bool no_needed(int agent_res[maxresource], int goal_res[maxresource]);



/********************************************************************/
void sleep(clock_t wait)
{
	clock_t goal;
	goal = wait + clock();
	while (goal > clock());
}


int _tmain(int argc, _TCHAR* argv[])
{
	FILE *obj_ptr;
	char file1[500];
	sprintf_s(file1, "E:\\xiao3\\SC\\SC\\DE-SC\\expriment3\\resource\\relax\\val_suite%d.txt", no_suite);
	fopen_s(&obj_ptr, file1, "w+");


	FILE *tim_ptr;
	char file2[500];
	sprintf_s(file2, "E:\\xiao3\\SC\\SC\\DE-SC\\expriment3\\resource\\relax\\tim_suite%d.txt", no_suite);
	fopen_s(&tim_ptr, file2, "w+");

	FILE *enc_ptr;
	char file3[500];
	sprintf_s(file3, "E:\\xiao3\\SC\\SC\\DE-SC\\expriment3\\resource\\relax\\enc_suite%d.txt", no_suite);
	fopen_s(&enc_ptr, file3, "w+");

	int int_exp = 0;
	int num_goal;

	for (int_exp = 0; int_exp < MAX_EXPERIMENT; int_exp++)
	{
		sleep((clock_t)3 * CLOCKS_PER_SEC);

		printf_s("experiment %d\n", int_exp + 1);

		clock_t start, finish;
		double duration = 0;

		int g = 0;
		int s, i, j;
		start = clock();
		//num_one_operations = 0;
		//num_zero_operations = 0;

		int best_index = 0;

		population oldpop, newpop, matepop, *old_pop_ptr, *new_pop_ptr, *mate_pop_ptr;//Defining the population Structures

		input();

		seed = (1.0 / (MAX_EXPERIMENT + 1))*(int_exp + 1);
		warmup_random(seed);

		old_pop_ptr = &(oldpop);
		new_pop_ptr = &(newpop);
		mate_pop_ptr = &(matepop);

		for (s = 0; s < maxpop; s++)
		{
			old_pop_ptr->ind[s].fitness = 0;
			new_pop_ptr->ind[s].fitness = 0;
			mate_pop_ptr->ind[s].fitness = 0;

			for (i = 0; i < maxgoal; i++)
			{
				for (j = 0; j < maxagent; j++)
				{
					old_pop_ptr->ind[s].bincode[i][j] = -1;
					new_pop_ptr->ind[s].bincode[i][j] = -1;
					mate_pop_ptr->ind[s].bincode[i][j] = -1;
				}
			}
		}

		old_pop_ptr = &(oldpop);
		bininit(old_pop_ptr);

		old_pop_ptr = &(oldpop);
		//start = clock();
		pop_repair(old_pop_ptr);
		//finish = clock();
		//duration += (double)(finish - start) / CLOCKS_PER_SEC;

		old_pop_ptr = &(oldpop);
		func(old_pop_ptr);

		for (g = 0; g < MAX_GENERATION; g++)
		{
			old_pop_ptr = &(oldpop);
			mate_pop_ptr = &(matepop);
			binmutate(old_pop_ptr, mate_pop_ptr); //binary Mutation

			old_pop_ptr = &(oldpop);
			mate_pop_ptr = &(matepop);
			new_pop_ptr = &(newpop);
			bincross(old_pop_ptr, mate_pop_ptr, new_pop_ptr);//binary Cross-over

			new_pop_ptr = &(newpop);

			//start = clock();
			pop_repair(new_pop_ptr);
			//finish = clock();
			//duration += (double)(finish - start) / CLOCKS_PER_SEC;

			new_pop_ptr = &(newpop);
			func(new_pop_ptr);//----------FUNCTION EVALUATION-----------

			//-------------------SELECTION KEEPING Better Individuals--------------
			old_pop_ptr = &(oldpop);
			new_pop_ptr = &(newpop);
			keepbetter(old_pop_ptr, new_pop_ptr);

		}
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;

		old_pop_ptr = &(oldpop);
		//report
		fprintf_s(tim_ptr, "%5.4f, ", duration);
		//////////////////////////////////////////////////////////////////////////	
		best_index = 0;
		for (s = 0; s < maxpop; s++)
		{
			if (old_pop_ptr->ind[s].fitness>old_pop_ptr->ind[best_index].fitness)
			{
				best_index = s;
			}
		}
		fprintf_s(obj_ptr, "%d, ", old_pop_ptr->ind[best_index].fitness);
		//////////////////////////////////////////////////////////////////////////
		fprintf_s(enc_ptr, "%s", "encoding is shown as below:\n");
		for (i = 0; i < maxgoal; i++)
		{
			for (j = 0; j < maxagent; j++)
			{
				fprintf_s(enc_ptr, "%d,  ", old_pop_ptr->ind[best_index].bincode[i][j]);
			}
			fprintf_s(enc_ptr, "%s", "\n");
		}
		fprintf_s(enc_ptr, "%s", "\n");

		//num_goal = 0;
		//for (i = 0; i < maxgoal; i++)
		//{
		//	for (j = 0; j < maxagent; j++)
		//	{
		//		if (old_pop_ptr->ind[0].bincode[i][j] == 1)
		//		{
		//			num_goal++;
		//			break;
		//		}
		//	}
		//}

		//fprintf_s(enc_ptr, "%d", num_goal);
		//fprintf_s(enc_ptr, "%s", "\n");

	}

	fclose(enc_ptr);
	fclose(obj_ptr);
	fclose(tim_ptr);

	printf_s("successful!\n");
	getchar();

	return 0;
}

void input()
{

	/*the crossover probability*/
	pcross = 0.1;// 0.25;//

	/*the mutation probability*/
	pmut_b = 2.0;// 1.0;

}

void bininit(population *pop_ptr)
{
	int i, j, s;
	double d;
	pop_ptr->ind_ptr = &(pop_ptr->ind[0]);

	for (s = 0; s < maxpop; s++)
	{
		for (i = 0; i < maxgoal; i++)
		{
			for (j = 0; j < maxagent; j++)
			{
				/*Generate a Random No. if it is less than 0.5 it generates a 0 in the string otherwise 1*/
				d = randomperc();
				if (d >= 0.5)
				{
					pop_ptr->ind_ptr->bincode[i][j] = 1;
				}
				else
				{
					pop_ptr->ind_ptr->bincode[i][j] = 0;
				}
			}
		}

		pop_ptr->ind_ptr->fitness = 0;

		pop_ptr->ind_ptr = &(pop_ptr->ind[s + 1]);

	}

	pop_ptr->ind_ptr = &(pop_ptr->ind[0]);
}


void func(population *pop_ptr)
{
	int i, j, s;

	int reward = 0;

	int demo = 0;

	bool success;

	for (s = 0; s < maxpop; s++)
	{
		reward = 0;

		for (i = 0; i < maxgoal; i++)
		{

			success = false;
			for (j = 0; j < maxagent; j++)
			{
				if (pop_ptr->ind[s].bincode[i][j] == 1)// the agent a_j is in coalition C_i
				{

					success = true;
					break;

				}
			}

			if (success)
			{
				reward += Reward_Goal[i];
			}

		}

		pop_ptr->ind[s].fitness = reward;
	}
}

void xiao_repair(individual *ind_ptr)
{

	int i, j, k, r;

	int save_row[maxgoal] = { -1 };//record the selected row
	int row = 0;
	int demo_row = 0;
	int selected = 0;//the current row

	for (i = 0; i < maxgoal; i++)
		save_row[i] = i;//save the row index

	double rnd1, rnd2, rnd3;

	int total[maxresource] = { 0 };
	bool Is_satisfied = true;



	int num_zero = 0;
	int is_zero[maxagent] = { -1 };//the index for bits ``0'' in a row
	int demo_zero = 0;

	int zero_ava[maxagent] = { -1 };
	int num_zero_ava = 0;

	int num_one = 0;
	int is_one[maxagent] = { -1 };//the index for bits ``1'' in a row
	int demo_one;

	int availabe[maxagent] = { -1 };
	int num_ava = 0;
	//int total_need;// The sum of all resources required by the goal now



	int agent;//the a_j which is selected.
	int agent_index;

	//int demo_res1;
	int demo_res2;


	int total_con;




	int Residual_Goal[maxgoal][maxresource] = { 0 };

	int Residual_Resource_Agent[maxagent][maxresource] = { 0 };

	int Contribution_Agent[maxagent][maxgoal][maxresource] = { 0 };

	for (j = 0; j < maxagent; j++)
	{
		for (k = 0; k < maxresource; k++)
		{
			Residual_Resource_Agent[j][k] = Resource_Agent[j][k];
		}
	}

	for (i = 0; i < maxgoal; i++)
	{
		for (k = 0; k < maxresource; k++)
		{
			Residual_Goal[i][k] = Resource_Goal[i][k];
		}
	}

	for (j = 0; j < maxagent; j++)
	{
		for (i = 0; i < maxgoal; i++)
		{
			for (k = 0; k < maxresource; k++)
			{
				Contribution_Agent[j][i][k] = 0;
			}
		}
	}
	row = maxgoal - 1;
	//row = maxgoal;

	while (row >= 0)
	{
		num_one = 0;
		num_zero = 0;

		for (j = 0; j < maxagent; j++)
		{
			is_one[j] = -1;
			zero_ava[j] = -1;
		}

		Is_satisfied = true;

		for (k = 0; k < maxresource; k++)
			total[k] = 0;

		rnd1 = randomperc();
		rnd1 = row * rnd1;
		demo_row = (int)floor(rnd1);
		selected = save_row[demo_row];//select randomly a row
		/****************************************************************************************/
		//determine whether the goal can be satisfied?
		for (j = 0; j < maxagent; j++)
		{
			if (Interest_Set[j][selected] == 1)
			{
				for (k = 0; k < maxresource; k++)
					total[k] += Residual_Resource_Agent[j][k];
			}

			if (ind_ptr->bincode[selected][j] == 1)
			{
				if (Interest_Set[j][selected] == 1 && !no_needed(Residual_Resource_Agent[j], Residual_Goal[selected]))
				{
					is_one[num_one] = j;
					num_one++;
				}
				else
				{
					ind_ptr->bincode[selected][j] = 0;
				/*	num_zero_operations++;*/
				}
			}
			else//the bit is "0"
			{
				if (Interest_Set[j][selected] == 1 && !no_needed(Residual_Resource_Agent[j], Residual_Goal[selected]))
				{
					is_zero[num_zero] = j;
					num_zero++;
				}
			}
		}

		for (k = 0; k < maxresource; k++)
		{
			if (Resource_Goal[selected][k] > total[k])//the total resources of all the valid agents cannot satisfy the needs of the selected goal
			{
				Is_satisfied = false;
				break;
			}
		}

		if (!Is_satisfied)//cannot satisfy
		{
			for (j = 0; j < num_one; j++)
			{
				if (ind_ptr->bincode[selected][is_one[j]] == 1)
				{
					ind_ptr->bincode[selected][is_one[j]] = 0;//let all bits ``1'' exit from the coalition
					//num_zero_operations++;
				}
			}
		}
		else//can satisfy
		{


			num_one--;
			num_zero--;


			//printf("%s", "interest:");
			//for (j = 0; j < maxagent; j++)
			//{
			//	printf("%d, ", Interest_Set[j][selected]);
			//}
			//printf("\n");
			//printf("%s", "bin_code:");
			//for (j = 0; j < maxagent; j++)
			//{
			//	printf("%d, ", ind_ptr->bincode[selected][j]);
			//}
			//printf("\n");
			//printf("\n");



			for (k = 0; k < maxresource; k++)
			{
				if (Residual_Goal[selected][k] > 0)
				{
					num_ava = 0;
					for (j = 0; j <= num_one; j++)
					{
						if (Residual_Resource_Agent[is_one[j]][k]>0)
						{
							availabe[num_ava] = is_one[j];
							num_ava++;
						}
					}

					num_ava--;

					while ((Residual_Goal[selected][k] > 0) && (num_ava >= 0))//
					{
						rnd2 = randomperc();
						rnd2 = num_ava * rnd2;
						demo_one = (int)floor(rnd2);

						agent = availabe[demo_one];


						for (j = 0; j <= num_one; j++)
						{
							if (is_one[j] == agent)
							{
								agent_index = j;
								break;
							}
						}

						while (agent_index < num_one)
						{
							is_one[agent_index] = is_one[agent_index + 1];//delete the checked column
							agent_index++;
						}
						num_one--;


						for (r = 0; r < maxresource; r++)
						{

							demo_res2 = min(Residual_Resource_Agent[agent][r], Residual_Goal[selected][r]);

							Contribution_Agent[agent][selected][r] = demo_res2;
							Residual_Goal[selected][r] -= demo_res2;
							Residual_Resource_Agent[agent][r] -= demo_res2;
						}


						while (demo_one < num_ava)
						{
							availabe[demo_one] = availabe[demo_one + 1];//delete the checked column
							demo_one++;
						}
						num_ava--;
					}
				}
			}

			if (num_one >= 0)//some bits ``1'' are useless
			{
				for (j = 0; j <= num_one; j++)
				{
					ind_ptr->bincode[selected][is_one[j]] = 0;//covert
					//num_zero_operations++;
				}
			}


			for (k = 0; k < maxresource; k++)
			{
				if (Residual_Goal[selected][k] > 0)
				{

					num_zero_ava = 0;
					for (j = 0; j <= num_zero; j++)
					{
						if (Residual_Resource_Agent[is_zero[j]][k] > 0)
						{
							zero_ava[num_zero_ava] = is_zero[j];
							num_zero_ava++;
						}
					}

					num_zero_ava--;


					while ((Residual_Goal[selected][k] > 0) && (num_zero_ava >= 0))//
					{
						rnd3 = randomperc();
						rnd3 = num_zero_ava * rnd3;
						demo_zero = (int)floor(rnd3);

						agent = zero_ava[demo_zero];

						ind_ptr->bincode[selected][agent] = 1;//convert


						for (j = 0; j <= num_zero; j++)
						{
							if (is_zero[j] == agent)
							{
								agent_index = j;
								break;
							}
						}
						while (agent_index < num_zero)
						{
							is_zero[agent_index] = is_zero[agent_index + 1];//delete the checked column
							agent_index++;
						}
						num_zero--;

						for (r = 0; r < maxresource; r++)
						{
							demo_res2 = min(Residual_Resource_Agent[agent][r], Residual_Goal[selected][r]);

							Contribution_Agent[agent][selected][r] = demo_res2;
							Residual_Goal[selected][r] -= demo_res2;
							Residual_Resource_Agent[agent][r] -= demo_res2;
						}

						while (demo_zero < num_zero_ava)
						{
							zero_ava[demo_zero] = zero_ava[demo_zero + 1];//delete the checked column
							demo_zero++;
						}

						num_zero_ava--;

					}
				}

			}

		}


		//for (j = 0; j < maxagent; j++)
		//{
		//	total_con = 0;
		//	for (r = 0; r < maxresource; r++)
		//	{
		//		total_con += Contribution_Agent[j][selected][r];

		//	}
		//	if (total_con>0)
		//		ind_ptr->bincode[selected][j] = 1;
		//	else
		//		ind_ptr->bincode[selected][j] = 0;
		//}








		/****************************************************************************************/
		while (demo_row <row)
		{
			save_row[demo_row] = save_row[demo_row + 1];//delete the checked row
			demo_row++;
		}

		row--;
	}
}


void pop_repair(population *pop_ptr)
{
	int s;

	pop_ptr->ind_ptr = &(pop_ptr->ind[0]);

	for (s = 0; s < maxpop; s++)
	{
		xiao_repair(pop_ptr->ind_ptr);
		pop_ptr->ind_ptr = &(pop_ptr->ind[s + 1]);
	}

}

void bincross(population *old_pop_ptr, population *mate_pop_ptr, population *new_pop_ptr)//Single point crossover
{
	int s, i, j;
	double rnd2;

	for (s = 0; s < maxpop; s++)
	{
		for (i = 0; i < maxgoal; i++)
		{
			for (j = 0; j < maxagent; j++)
			{
				rnd2 = randomperc();

				if (rnd2 <= pcross)
					new_pop_ptr->ind[s].bincode[i][j] = mate_pop_ptr->ind[s].bincode[i][j];
				else
					new_pop_ptr->ind[s].bincode[i][j] = old_pop_ptr->ind[s].bincode[i][j];
			}
		}
	}


}

double AMFunction(double x)//bit string generating function
{
	double a = 0, b = 1.0, c = 1.0, d = 0;

	double temp = 0;

	double A = 0;

	A = 2 * PI * c * (x - a);

	temp = sin(2 * PI * (x - a)* b *cos(A)) + d;

	return temp;
}

void binmutate(population *old_pop_ptr, population *mate_pop_ptr)/*binary mutation*/
{
	int s, i, j;

	double rnd1, rnd2, rnd3;

	double demo = 0;

	int p1 = 0, p2 = 0, p3 = 0;

	for (s = 0; s < maxpop; s++)
	{
		do{
			rnd1 = randomperc();
			rnd1 = (maxpop - 1)* rnd1;
			p1 = (int)floor(rnd1);

			rnd2 = randomperc();
			rnd2 = (maxpop - 1)* rnd2;
			p2 = (int)floor(rnd2);

			rnd3 = randomperc();
			rnd3 = (maxpop - 1)* rnd3;
			p3 = (int)floor(rnd3);

		} while (s == p1 || s == p2 || s == p3 || p1 == p2 || p1 == p3 || p2 == p3);

		for (i = 0; i < maxgoal; i++)
		{
			for (j = 0; j < maxagent; j++)
			{
				demo = old_pop_ptr->ind[p1].bincode[i][j] + pmut_b*(old_pop_ptr->ind[p2].bincode[i][j] - old_pop_ptr->ind[p3].bincode[i][j]);
				//then convert to binary bit
				if (AMFunction(demo)>0)
					mate_pop_ptr->ind[s].bincode[i][j] = 1;
				else

					mate_pop_ptr->ind[s].bincode[i][j] = 0;
			}
		}
	}
}

void keepbetter(population *old_pop_ptr, population *new_pop_ptr)
{
	int s, i, j;

	for (s = 0; s < maxpop; s++)
	{
		if (new_pop_ptr->ind[s].fitness >= old_pop_ptr->ind[s].fitness)
		{
			old_pop_ptr->ind[s].fitness = new_pop_ptr->ind[s].fitness;

			for (i = 0; i < maxgoal; i++)
			{
				for (j = 0; j < maxagent; j++)
				{
					old_pop_ptr->ind[s].bincode[i][j] = new_pop_ptr->ind[s].bincode[i][j];
				}
			}
		}

	}
}
bool no_needed(int agent_res[maxresource], int goal_res[maxresource])
{
	int k = 0;

	for (k = 0; k < maxresource; k++)
	{
		if (min(goal_res[k], agent_res[k]) > 0)// has required resource
		{
			return false;
		}
	}

	return true;
}