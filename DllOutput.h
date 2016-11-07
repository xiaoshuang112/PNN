#pragma once
#ifdef PNN_DLL
#else
#define PNN_DLL _declspec(dllimport)
#endif

//���ò�����c_countΪ���������c_s_count��һά���飩Ϊÿ�������ѵ����������f_countΪ�����ռ��ά��
extern "C" PNN_DLL void SetParams(int c_count, int*c_s_count, int f_count);

//����ѵ���������������к�SetParams�����е�c_s_count�������Ӧ
extern "C" PNN_DLL void SetTrainingSamples(double* samples);

//��ʼ������̣�sampleΪ����������
extern "C" PNN_DLL void Classify(double* sample);

//��ȡ�����������������ĸ��ࣩ
extern "C" PNN_DLL int GetClass();

//��ȡ���������жϵ���ȷ�ʣ�
extern "C" PNN_DLL double GetProb();