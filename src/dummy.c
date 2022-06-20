#include <stdio.h>

int main()
{
    printf("int = %d\nlong = %d\nlong long = %d\n",
        sizeof(int), sizeof(long), sizeof(long long));
    return 0;
}