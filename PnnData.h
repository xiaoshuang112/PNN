#ifndef PNNDATA_H
#define PNNDATA_H

#define s_class_num 2 // ��׼�����������
#define feature     2    // ������������ά�ȣ�
#define s_num       2 // ÿһ���׼�����������������׼��������ͳһ��
#define s_Sample_num 4 // ��׼�������������� = s_class_num*s_num

struct PNN
{
	int i;
};

void Arrayinit(double*data);

#endif