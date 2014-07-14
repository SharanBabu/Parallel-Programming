/*
sharanbabu P M-20072206
finding the kth smallest using merge sort algorithm
the time on pentium machine for 4 this program-
real	0m0.046s
user	0m0.072s
sys	0m0.008s

*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 100000 ///assuming number of elements 100000
#define num 4 //assuming number of threads 4
void merge(int a[],int low,int mid,int high,int y)
{
int h,i,j,k,flag=0,m,t;
int cont=0;
int b[N];
h=low;i=low;j=mid+1;
looi:while(h<=mid && j<=high&&cont<y)
{
if(a[h]==a[h+1]&&h!=mid){h++;flag++;b[i]=a[h];goto looi;} //to check the presence of duplicate entries
if(a[j]==a[j+1]&&j!=high){j++;flag++;goto looi;} //to check the presence of duplicate entries
if(a[h]==a[j]&&h!=mid&&j!=high){j++;flag++;b[i]=a[h];goto looi;} //to check the presence of duplicate entries
if(a[h]<=a[j])
{
b[i]=a[h];
h=h+1;
}
else
{
b[i]=a[j];
j=j+1;
}
i=i+1;
cont++;
} 
if(h>mid)
{
for(k=j;k<=high;k++)
{
b[i]=a[k];
i=i+1;
}
}
else
{
for(k=h;k<=mid;k++)
{
b[i]=a[k];
i=i+1;
}
}
// assigning the empty slots with a number based on the flag set during the check of duplicate entries
for(m=0;m<flag;m++)
b[i++]=99999;//just a random number assumed to fill the empty slots if numbers are repeated in the array
for(k=low;k<=high;k++)
a[k]=abs(b[k]);
}
void merger(int a[],int low,int high,int u)
{
int mid,m;
if(low<high)
{
mid=(low+high)/2;
merger(a,low,mid,u);
merger(a,mid+1,high,u);
merge(a,low,mid,high,u);
}

}
void mergefin(int a[],int low,int high,int chunk,int u)
{
int mid;
//printf("merger\t");
if((high-low)>(chunk/2))
{
mid=(low+high)/2;
mergefin(a,low,mid,chunk,u);
mergefin(a,mid+1,high,chunk,u);
merge(a,low,mid,high,u);
}
}
int main()
{
int a[N],chunk;
int m,j,k,l,q,t;
//for(l=0,t=100000;l<N;l++,t--)
//a[l]=l;
for(l=0;l<N;l++)
scanf("%d",&a[l]);
scanf("%d",&q);
chunk=N/num;
//each thread will sort the array elememts allocated to them and return the array
#pragma omp parallel num_threads(num)
{
int start,end,tid,r;
tid=omp_get_thread_num();
start=tid*chunk;
end=start+chunk-1;
merger(a,start,end,q);
}
//master will merge the individually sorted array
mergefin(a,0,N-1,chunk,q);

printf("\noutput:%d",a[q-1]);
return 0;
}
