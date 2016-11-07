
#ifdef PNNLIB_EXPORTS
#define PNNLIB_API __declspec(dllexport)
#else
#define PNNLIB_API __declspec(dllimport)
#endif




PNNLIB_API int  Pnninit(int Feature);//此函数在程序启动时调用一次即可，返回1 初始化成功，-1则失败；
