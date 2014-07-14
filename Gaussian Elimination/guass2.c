#include <stdio.h>
#include<time.h>
#include<sys/time.h>
int n;
float a[10][11];

void forwardSubstitution() {
	int i, j, k, max;
	float t;
	for (i = 0; i < n; ++i) {
		max = i;
		for (j = i + 1; j < n; ++j)
			if (a[j][i] > a[max][i])
				max = j;
	printf("the maximum %d\n",max);
		
		for (j = 0; j < n + 1; ++j) {
			t = a[max][j];
			a[max][j] = a[i][j];
			a[i][j] = t;
		}
		printf("the swapped old %f, new %f",a[max][i],a[i][i]);
		for (j = n; j >= i; --j){
			for (k = i + 1; k < n; ++k)
				{
				a[k][j] -= a[k][i]/a[i][i] * a[i][j];
				
				}}
	

	
}


}

void reverseElimination() {
//printf("into reverse elimination");                          //for bringing the matrix to upper triangular form
	int i, j;
	for (i = n - 1; i >= 0; --i) {
		a[i][n] = a[i][n] / a[i][i];
		a[i][i] = 1;
		for (j = i - 1; j >= 0; --j) {
			a[j][n] -= a[j][i] * a[i][n];
			a[j][i] = 0;
			printf("j:%d --%f\n",j,a[j][n]);
		}
	}
}

void gauss() {
	int i, j;

	forwardSubstitution();
	reverseElimination();
	
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n + 1; ++j)
			printf("%.2f\t", a[i][j]);
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	int i, j;
	
	FILE *fin = fopen("gauss.in", "r");
	fscanf(fin, "%d", &n);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n + 1; ++j)
			fscanf(fin, "%f", &a[i][j]);
	fclose(fin);
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);	
	gauss();
	gettimeofday(&t2,NULL);	
	long io=t1.tv_usec;
 	long jo=t2.tv_usec;
 	printf("\ndifftime   : %.6ld\n",jo-io);
	return 0;
}


