#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
struct data_struct{
	int i;
	float k;
};

pthread_key_t key; //这是全局的，每一个线程都可以访问这个key，
				   //但是每一个线程都有自己的一个key/value数组
			       //所以key对应的值是不同的

void* child(void *arg)
{	
	struct data_struct *p_data;
	if((p_data = (struct data_struct*)pthread_getspecific(key)) == NULL) {
		p_data = (struct data_struct*)malloc(sizeof(data_struct));
		p_data->i = 100;
		pthread_setspecific(key,p_data); //给这个key设置数据
	} else {
		printf("get_data:%d\n",p_data->i);
	}
	printf("struct_data的地址为0x%p\n",p_data);
	printf("=============================\n"); //为什么地址是0呢
	cout << p_data->i << endl; //应该输出200
	while(1);
}

void destructor(void *x)
{
	struct data_struct *p_data = static_cast<data_struct*>(x);
	free(p_data);
}
int main()
{
	pthread_t tid1,tid2;
	pthread_key_create(&key,destructor); //创建线程局部存储
	pthread_create(&tid1,NULL,child,NULL);
	pthread_create(&tid2,NULL,child,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
