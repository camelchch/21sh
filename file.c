#include <stdio.h>
#include <unistd.h>
int main(){
char str[20];
read (0, str, 10);
str[1]= 0;
printf("%s\n", str);
return (0);
}
