#include "stdafx.h"
#include "PnnData.h"

double s_data[s_Sample_num*feature] = {
	1,2,
	2,1,
	-1,-2,
	-2,-1
};

void Arrayinit(double*data)
{
	memcpy(data, s_data, s_Sample_num*feature*sizeof(double));
}