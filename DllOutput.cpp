#define PNN_DLL _declspec(dllexport)

#include"DllOutput.h"
#include"PNN.h"

PNN pnn;

void SetParams(int c_count, int*c_s_count, int f_count) {
	pnn.setParams(c_count,c_s_count,f_count);
}
void SetTrainingSamples(double* samples) {
	pnn.setTrainingSamples(samples);
}

void Classify(double* sample) {
	pnn.classify(sample);
}
int GetClass() {
	return pnn.getClass();
}
double GetProb() {
	return pnn.getProb();
}