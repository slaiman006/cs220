#include <stdio.h>
#include <stdlib.h>
int main()
{
	int num =10;
	int m=0;
	int *grades = (int *)malloc (num * sizeof(*grades));
	for(int i =0; i<num;i++)
		grades[i] = rand()%100;
	for(int i =0; i<num;i++)
		if (grades[m]<=grades[i])
			m=i;
	for(int i =0; i<num;i++)
		printf("%d   ", grades[i]);
	printf("\n\n");
	free(grades);
	printf(" max grade is %d\n", grades[m]);
	return 0;
}
