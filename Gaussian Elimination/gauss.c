#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>
#include<string.h>
int main()
{
int fd,i=0,j=0,k,l,maxi,u,m=3,n=4,te,temp,g;
int input[3][4];
close(0);
fd=open("input1.txt",0);
dup2(fd);
while(scanf("%d",&input[i][j++])!=-1)
{
if(j==4)
{
i++;
j=0;
}
}
for(i=0;i<3;i++)
{
for(j=0;j<4;j++)
{

printf("%d\t",input[i][j]);
}
printf("\n");
}
//gauss-elimination algo
i=0;
j=0;
while(i<m && j<n)
{
maxi=i;
for(k=i+1;k<m;k++)
	{
		if(abs(input[k][j]) > abs(input[maxi][j]))
		{
			maxi=k;
		}
	}
printf("\nthe maxi is :%d\n for %d iteration\n",maxi,j);
if(input[maxi][j]!=0)
{
//swapping the rows
for(g=0;g<4;g++)
{
temp=input[i][g];
input[i][g]=input[maxi][g];
input[maxi][g]=temp;

}//
//
printf("\nprinting the swapped\n");

for(i=0;i<3;i++)
{
for(j=0;j<4;j++)
{

printf("%d\t",input[i][j]);
}
printf("\n");
}
//
input[i][j]=input[i][j]/input[i][j];
//equivalent to dividing the row i by input[i][j]
	for(u=i+1;u<m;u++)
	{
		input[u][j]=input[u][j]-input[i][j]*input[u][j];
	}
i=i+1;
}
j=j+1;
}//while

printf("after algo\n");
//after applying algo
for(i=0;i<3;i++)
{
for(j=0;j<4;j++)
{

printf("%d\t",input[i][j]);
}
printf("\n");
}
//

}
