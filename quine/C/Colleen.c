#include<stdio.h>
/*quine*/
void f(){return;}
int main(){f();/*2*/char*a="#include<stdio.h>%c/*quine*/%cvoid f(){return;}%cint main(){f();/*2*/char*a=%c%s%c;printf(a,10,10,10,34,a,34,10);}%c";printf(a,10,10,10,34,a,34,10);}
