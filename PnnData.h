#ifndef PNNDATA_H
#define PNNDATA_H

#define s_class_num 2 // 标准向量集类别数
#define feature     2    // 特征数（向量维度）
#define s_num       2 // 每一类标准向量个数（所有类标准向量个数统一）
#define s_Sample_num 4 // 标准向量集向量总数 = s_class_num*s_num

struct PNN
{
	int i;
};

void Arrayinit(double*data);

#endif