
#ifdef PNNLIB_EXPORTS
#define PNNLIB_API __declspec(dllexport)
#else
#define PNNLIB_API __declspec(dllimport)
#endif




PNNLIB_API int   Pnninit(int Feature);//�˺����ڳ�������ʱ����һ�μ��ɣ�����1 ��ʼ���ɹ���-1��ʧ�ܣ�
PNNLIB_API int   Pnnpredict(double*test_data,int length,int*class_num,double*prob);//test_dataΪ�������飬lengthΪ���鳤�ȣ�����Ϊ�������͸��ʡ�
PNNLIB_API void  Pnnrelease();//�˳�ʱ����