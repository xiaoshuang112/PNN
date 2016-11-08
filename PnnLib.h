
#ifdef PNNLIB_EXPORTS
#define PNNLIB_API __declspec(dllexport)
#else
#define PNNLIB_API __declspec(dllimport)
#endif




PNNLIB_API int   Pnninit(int Feature);//此函数在程序启动时调用一次即可，返回1 初始化成功，-1则失败；
PNNLIB_API int   Pnnpredict(double*test_data,int length,int*class_num,double*prob);//test_data为输入数组，length为数组长度，依次为返回类别和概率。
PNNLIB_API void  Pnnrelease();//退出时调用