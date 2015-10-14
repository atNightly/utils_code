#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main()
{
	int count = 0;
//__sync_fecth_and*  这类函数都是先返回运算前的值，然后运算

	assert(__sync_fetch_and_add(&count,10) == 0);
	assert(count == 10);
	
	assert(__sync_fetch_and_sub(&count,10) == 10);
	assert(count == 0);

//__sync_*_and_fetch  这类函数则是相反先运算，然后然后运算后的值
	assert(__sync_add_and_fetch(&count,10) == 10);
	assert(count == 10);

	assert(__sync_sub_and_fetch(&count,10) == 0);
	assert(count == 0);

//比较，交换
	//如果count的值和0相等则把10写入,并返回true
	assert(__sync_bool_compare_and_swap(&count,0,10) == true);
	assert(count == 10);

	//如果count的值和10相等，则把0写入，并返回0
	assert(__sync_val_compare_and_swap(&count,10,0) == 10);
	assert(count == 0);

//将count设置为10，然后返回count操作之前的值
	assert(__sync_lock_test_and_set(&count,10) == 0);
	assert(count == 10);

//将count置为0
	__sync_lock_release(&count);
	assert(count == 0);
}
