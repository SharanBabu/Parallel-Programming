#include <stdio.h>
#include<mpi.h>
#include<sys/time.h>
int n;
float a[10][11];
float b[10][11];

int main(int argc, char *argv[]) {
	int i, j,cnt,max,ival;
	struct timeval t1,t2;
	float t;
	float rtem[10],rtem2[10];
	int rank,np,tag=1,source,dest,no,nor,nor2;
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	FILE *fin = fopen("gauss.in", "r");
	fscanf(fin, "%d", &n);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n + 1; ++j)
			fscanf(fin, "%f", &a[i][j]);
	fclose(fin);
	cnt=100;
	if(rank==0)
	{
	if ((n%np)!=0) {
			printf("Number of processes (%d) must divide evenly into problem size (%d).\n",np,n);
			fflush(stdout);
			MPI_Abort(MPI_COMM_WORLD,1);
		}
	else
	{
		gettimeofday(&t1,NULL);	
		int k,r,l;
		for(i=0;i<n-1;i++)
		{
			max = i;
			for (j = i + 1; j < n; ++j)
				if (a[j][i] > a[max][i])
					max = j;
			for (j = 0; j < n + 1; ++j) {
				t = a[max][j];
				a[max][j] = a[i][j];
				a[i][j] = t;
			}
			for(dest=i+1 ; dest<np ; dest++){
				MPI_Send(&i,1, MPI_FLOAT, dest,tag,MPI_COMM_WORLD);
			   MPI_Send(&n,1, MPI_FLOAT, dest,tag,MPI_COMM_WORLD);
				MPI_Send(&a,cnt, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
			}

		for(dest=i+1 ; dest<np ; dest++)
		{
           	 MPI_Recv(&nor,1, MPI_FLOAT,dest , 2, MPI_COMM_WORLD, &stat);
		    MPI_Recv(&rtem,n+1, MPI_FLOAT,dest , 2, MPI_COMM_WORLD, &stat);
		for(r=0;r<=n;r++)
			{
				a[nor][r]=rtem[r];
			}
		}

	}
///sending the modified buffer to all for reverse substitution
		for (i = n - 1; i >= 0; --i) 
		{
			a[i][n] = a[i][n] / a[i][i];
			a[i][i] = 1.0;
			printf("%d is changed %f",i,a[i][i]);	
			ival=i;
			for(dest=n-i ; dest<np ; dest++){
				MPI_Send(&ival,1, MPI_FLOAT, dest,tag,MPI_COMM_WORLD);
				MPI_Send(&a,cnt, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
			}
		for(dest=n-i ; dest<np ; dest++)
			{
	            MPI_Recv(&nor2,1, MPI_FLOAT,dest , 2, MPI_COMM_WORLD, &stat);
		    MPI_Recv(&rtem2,n+1, MPI_FLOAT,dest , 2, MPI_COMM_WORLD, &stat);
			for(r=0;r<=n;r++)
			{
				a[nor2][r]=rtem2[r];
			}
		}

	}
//
//final answer
printf("\nthe resultant matrix\n\n");
for (i = 0; i < n; ++i) {
		for (j = 0; j < n + 1; ++j)
			printf("%.2f\t", a[i][j]);
		printf("\n");
	}
	gettimeofday(&t2,NULL);	
	long io=t1.tv_usec;
 	long jo=t2.tv_usec;
 	printf("\ndifftime   : %.6ld\n",jo-io);
}
}
else
	{
		int j,k,i,g;
		int iter;
		float tem[10];
		float tem2[10];
		for(iter=0;iter<rank;iter++)
		{
			MPI_Recv(&i, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &stat);
			MPI_Recv(&n, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &stat);
			no=100;
			MPI_Recv(&b,no, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &stat);
	/// forward substitution of algo
			k=rank;
			for (j = n; j >= i; --j){
				b[k][j] -= b[k][i]/b[i][i] * b[i][j];
				tem[j]=b[k][j];
			}
			nor=rank;
			MPI_Send(&nor,1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
			MPI_Send(&tem,n+1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
		}
	////

///reverse elimination
		for(iter=0;iter<rank;iter++)
		{
			MPI_Recv(&ival,1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &stat);
			MPI_Recv(&b,no, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &stat);
			i=ival;
			j=(n-1)-rank;
			printf("n value %d the j is %d operated by %d\n",n,j,rank);
			b[j][n] -= b[j][i] * b[i][n];
			b[j][i] = 0;
			for(g=0;g<n+1;g++)
			{
			tem2[g]=b[j][g];
			}
		nor2=j;
		MPI_Send(&nor2,1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&tem2,n+1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
		}
	}	
	MPI_Finalize();
	return 0;
}


