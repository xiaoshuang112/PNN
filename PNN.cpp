#include "PNN.h"
#include<math.h>

/*���캯��*/
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

/*��ʼ������*/
void PNN::initNetwork() {
	d = new double[featureCount];
	X = new double[trainingSampleCount*featureCount];
	e = new double[trainingSampleCount];
	p = new double[trainingSampleCount];
	s = new double[classCount];
	transformToUnit(X);
}

/*�����һ��*/
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

/*�����������*/
void PNN::calDistance() {
	
	for (int i = 0; i < trainingSampleCount; i++) //trainingSampleCount �Ǳ�׼��������������
	{
		double sum = 0;
		for (int ii = 0; ii < featureCount; ii++) 
		{
			sum += (d[ii] - X[i*featureCount + ii])*(d[ii] - X[i*featureCount + ii]);
		}
		e[i] = sqrt(sum);
	}
}

/*�����*/
double PNN::activateFun(double param) {
	double ss = 0.1;//��˹�ͺ����еĦ�ֵ
	double v = exp(param/(-2*pow(ss,2)));
	return v;
}

/*�����ʼ��������*/
void PNN::calp() 
{
	for (int i = 0; i < trainingSampleCount; i++) 
	{
		p[i] = activateFun(e[i]);
	}
}

/*������ʺ�����*/
void PNN::calpsum() {
	int index = 0;//��¼����������p����Ԫ�ص�����
	for (int i = 0; i < classCount; i++) 
	{
		double sum = 0;
		for (int ii = 0; ii < class_count[i]; ii++) //class_count[i] ��I���ע�������ĸ���
		{
			sum += p[index + ii];
		}
		index += class_count[i];
		s[i] = sum;
	}
}

/*������������׼ȷ����*/
void PNN::calresult() 
{
	int index = 0;
	double sum = 0;
	double max = s[0];
	for (int i = 0; i < classCount; i++) 
	{//�ҳ����ֵ�������
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

/*ģ�⣬dataΪ��������*/
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

/*��ȡ���������������*/
int PNN::getClass() {
	return c;
}

/*��ȡ׼ȷ����*/
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
