
#include "stdafx.h"
#include "PnnLib.h"
#include "PnnData.h"
#include<math.h>
#include "malloc.h"

double *s_Data = NULL;
double vdistance[s_Sample_num] = {0};
double prob[s_class_num] = {0};

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

void calDistance(double*test_data) 
{

	for (int i = 0; i < s_Sample_num; i++) //trainingSampleCount 是标准样本层总样本数
	{
		double sum = 0;
		for (int j = 0; j < feature; j++) 
		{
			sum += (test_data[j] - s_Data[i*feature + j])*(test_data[j] - s_Data[i*feature + j]);
		}
		vdistance[i] = sqrt(sum);
	}
}

double activate(double param) 
{
	double ss = 0.1;//高斯型函数中的σ值
	double v = exp(param/(-2*pow(ss,2)));
	return v;
}

void calresult(int*class_num,double*prob) 
{
	double sum = 0;
	for (int i = 0; i < s_class_num;i++)
	{
		sum = 0;
		for (int j = 0; j < s_num; j++)
		{
			sum+= activate(vdistance[i*s_num + j]);
		}
		prob[i] = sum;
	}

	int index = 0;
	double prob_sum = 0;
	double max = prob[0];
	for (int i = 0; i < s_class_num; i++) 
	{//找出最大值，并求和
		if (max < prob[i]) 
		{
			max = prob[i];
			index = i;
		}
		prob_sum += prob[i];
	}
	*class_num = index;
	*prob = prob[index] / prob_sum;
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

PNNLIB_API int Pnnpredict(double*test_data,int length,int*class_num,double*prob)
{
	if (feature!=length)
	{
		return -1;//
	}

	transformToUnit(test_data, 1);
	calDistance(test_data) ;
	calresult(class_num, prob) ;

	return 1;
}

PNNLIB_API void  Pnnrelease()
{
	if (NULL!=s_Data)
	{
		free(s_Data);
		s_Data = NULL;
	}
}
