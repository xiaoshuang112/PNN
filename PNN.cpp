#include "PNN.h"
#include<math.h>

/*构造函数*/
PNN::PNN() {	
	class_count = 0;
	
}

PNN::~PNN() {
	if (class_count != 0) {
		delete class_count;
	}
	if (d != 0) {
		delete d;
	}
	if (X != 0) {
		delete X;
	}
	if (e != 0) {
		delete e;
	}
	if (p != 0) {
		delete p;
	}
	if (s != 0) {
		delete s;
	}
	
}

/*初始化网络*/
void PNN::initNetwork() {
	d = new double[featureCount];
	X = new double[trainingSampleCount*featureCount];
	e = new double[trainingSampleCount];
	p = new double[trainingSampleCount];
	s = new double[classCount];
	transformToUnit(X);
}

/*矩阵归一化*/
void PNN::transformToUnit(double* a/*[Y][N]*/) 
{
	for (int i = 0; i < trainingSampleCount; i++) 
	{
		double sum = 0;
		for (int ii = 0; ii < featureCount; ii++) 
		{
			sum += a[i*featureCount+ii] * a[i*featureCount + ii];
		}
		double factor = sqrt(sum);
		for (int ii = 0; ii < featureCount; ii++) 
		{
			a[i*featureCount + ii] = a[i*featureCount + ii] / factor;
		}
	}
}

/*计算距离向量*/
void PNN::calDistance() {
	
	for (int i = 0; i < trainingSampleCount; i++) //trainingSampleCount 是标准样本层总样本数
	{
		double sum = 0;
		for (int ii = 0; ii < featureCount; ii++) 
		{
			sum += (d[ii] - X[i*featureCount + ii])*(d[ii] - X[i*featureCount + ii]);
		}
		e[i] = sqrt(sum);
	}
}

/*激活函数*/
double PNN::activateFun(double param) {
	double ss = 0.1;//高斯型函数中的σ值
	double v = exp(param/(-2*pow(ss,2)));
	return v;
}

/*计算初始概率向量*/
void PNN::calp() 
{
	for (int i = 0; i < trainingSampleCount; i++) 
	{
		p[i] = activateFun(e[i]);
	}
}

/*计算概率和向量*/
void PNN::calpsum() {
	int index = 0;//记录所遍历到的p数组元素的引索
	for (int i = 0; i < classCount; i++) 
	{
		double sum = 0;
		for (int ii = 0; ii < class_count[i]; ii++) //class_count[i] 第I类标注了样本的个数
		{
			sum += p[index + ii];
		}
		index += class_count[i];
		s[i] = sum;
	}
}

/*计算所属类别和准确概率*/
void PNN::calresult() 
{
	int index = 0;
	double sum = 0;
	double max = s[0];
	for (int i = 0; i < classCount; i++) 
	{//找出最大值，并求和
		if (max < s[i]) 
		{
			max = s[i];
			index = i;
		}
		sum += s[i];
	}
	c = index;
	prob = s[c] / sum;
}

/*模拟，data为待测样本*/
void PNN::classify(double* data) {
	for (int i = 0; i < featureCount; i++) 
	{
		d[i] = data[i];
	}
	transformToUnit(d);
	calDistance();
	calp();
	calpsum();
	calresult();
}

/*获取待测样本所属类别*/
int PNN::getClass() {
	return c;
}

/*获取准确概率*/
double PNN::getProb() {
	return prob;
}

void PNN::setParams(int c_count, int*c_s_count, int f_count) // 1
{
	classCount = c_count;
	class_count = new int[c_count];
	trainingSampleCount = 0;
	for (int i = 0; i < c_count; i++) {
		class_count[i] = c_s_count[i];
		trainingSampleCount += c_s_count[i];
	}
	featureCount = f_count;
	
	initNetwork();
}

void PNN::setTrainingSamples(double* samples)
{
	for (int i = 0; i < featureCount*trainingSampleCount; i++) 
	{
		X[i] = samples[i];
	}
}
