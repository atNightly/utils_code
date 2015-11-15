#include <stdio.h>

#define min(X,Y)			\
({ typeof (X) x_ = (X);		\
   typeof (Y) y_ = (Y);		\
   (x_ < y_)?x_:y_;})


#define min2(X,Y)			\
({ typeof (X) x_ = (X);		\
   typeof (Y) y_ = (Y);		\
   x_})
int main()
{
	int x = 19;
	int y = 20;
	printf("%d\n",min(x,y));
	min2(x,y);
}
