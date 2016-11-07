#pragma once
#ifdef PNN_DLL
#else
#define PNN_DLL _declspec(dllimport)
#endif

//设置参数，c_count为类别总数，c_s_count（一维数组）为每类包含的训练样本数，f_count为特征空间的维数
extern "C" PNN_DLL void SetParams(int c_count, int*c_s_count, int f_count);

//输入训练样本，样本排列和SetParams函数中的c_s_count参数相对应
extern "C" PNN_DLL void SetTrainingSamples(double* samples);

//开始分类过程，sample为待分类样本
extern "C" PNN_DLL void Classify(double* sample);

//获取分类结果（样本属于哪个类）
extern "C" PNN_DLL int GetClass();

//获取分类结果（判断的正确率）
extern "C" PNN_DLL double GetProb();