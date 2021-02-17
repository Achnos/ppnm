#include<stdio.h>
    void f(int* i){*i=0;}
    int main(){
    	int i=1; f(&i); printf("i=%i\n",i);
    	return 0; }
