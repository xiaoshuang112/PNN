
#include "stdafx.h"
#include "PnnLib.h"
#include "PnnData.h"
#include<math.h>
#include "malloc.h"

double *s_Data = NULL;

void  transformToUnit(double* Array ,int num) 
{
	for (int i = 0; i < num; i++) 
	{
		double sum = 0;
		for (int j = 0; j < feature; j++) 
		{
			sum += Array[i*feature+j] * Array[i*feature+j];
		}
		double factor = sqrt(sum);
		for (int j = 0; j < feature; j++) 
		{
			 Array[i*feature+j] =  Array[i*feature+j] / factor;
		}
	}
}

void calDistance() 
{

	for (int i = 0; i < s_Sample_num; i++) //trainingSampleCount 是标准样本层总样本数
	{
		double sum = 0;
		for (int j = 0; j < feature; j++) 
		{
			sum += (d[j] - X[i*featureCount + ii])*(d[ii] - X[i*featureCount + ii]);
		}
		e[i] = sqrt(sum);
	}
}


PNNLIB_API int Pnninit(int Feature)
{
	if (feature==Feature)
	{
		s_Data = (double *)malloc(s_Sample_num*feature*sizeof(double));
		Arrayinit(s_Data);
		transformToUnit(s_Data,s_Sample_num);//归一化
		return 1;
	}

	return -1;
}

int Pnnpredict(double*test_data,int length,int*class_num,float*prob)
{
	if (feature!=length)
	{
		return -1;//
	}

	transformToUnit(test_data, 1);

	return 1;
}
