/*
OPTIMIZATIONS:
	*Use of Macros
        *dividing the input among the threads based on the chunk size.
        *use of temporary varaibles for array elements-reducing the memory access.
        *scanning the input file directly using dup.
        
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/time.h>
#include "mpi.h"
#define min(a,b) (a<b?a:b)
#define max(m,n) (m>n?m:n)
#define STLEN 20
//algo -levenshtein 

int leven(char s[],char t[]) 
				{        
                                       int i,j,m,n;
				       int p;
				       int d[20][20];
				       m=strlen(s); 
  			               n=strlen(t);
				       for(i=0;i<=m;i++)
                                          d[i][0]=i;
				       for(j=0;j<=n;j++)
                                          d[0][j]=j;
					for(i=1;i<=m;i++)
                                        {	
	           				for(j=1;j<=n;j++)
						{
						  if(s[i-1]==t[j-1])
							 d[i][j]=d[i-1][j-1];
						  else
							d[i][j]=min(d[i-1][j],min(d[i][j-1],d[i-1][j-1]))+1;
						}
                                        }
					p=d[m][n];

					return p;
				}
				
				
int main(int argc ,char *argv[])
{
long int tim[100],st,en;
int nop,k,n,fd,flg=0,iter=0,i=0,levendist=0,threshtemp=0,low,high;
int sugg_cnt=0,suggtemp=0,j=0;
int input_file_iter=0,dest,tag=1,source;
int sendbuf,recvbuf,sugg_arr[100],flag[100];
float threshold=0.0;
char input[100][STLEN];
char word[STLEN];
char wordlist[5000][STLEN];//to hold the input words
char ch[STLEN];
int rank;
float chunk;
char suggestions[100][10][STLEN];  // array holding the suggestions for the input words-each of length 20
struct timeval start,end;
recvbuf=0;
MPI_Status stat;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &nop);
fd=open("words.txt",2);
if(fd==-1)
	{
	exit(0);
	}
close(0);
dup2(fd,0);
while(scanf("%s",wordlist[iter++])!=-1);
iter--;
close(fd);
fd=open("input.txt",2);
if(fd==-1)
	{
	exit(0);
	}
close(0);
dup2(fd,0);//duplicating the standard input with file as input
scanf("%f",&threshold);//scanning the threshold from the input file
scanf("%d",&sugg_cnt); //scanning the number of suggestions from the input file
threshold/=100; //getting the threshold value from the percentage given--to compare with the value returned from the algo
while(scanf("%s",input[input_file_iter++])!=-1);
sendbuf=input_file_iter-1;
close(fd);
if(rank==0)
{
for(dest=1 ; dest<nop ; dest++)
   MPI_Send(&sendbuf, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
   chunk=1.0*sendbuf/nop;// calculating the chunk size to be sent to each threads
   low=0;
   high=chunk;
 ///root thread processing 
for(j=low;j<high;j++)
	{
	flg=0;
	suggtemp=0;
	threshtemp=threshold*strlen(input[j])+1;	
	gettimeofday(&start,NULL);                                                   
	for(i=0;i<iter;i++)
		{
		levendist=leven(input[j],wordlist[i]);
			if(levendist<threshtemp)
			    {
			     if(suggtemp>=sugg_cnt)
			       break; 
			          if(levendist==0)
				     {
					flg=1;                       
       					break;
				     }   
         			strcpy(suggestions[j][suggtemp++],wordlist[i]);       
     				
    				}	
		}
	  gettimeofday(&end,NULL);                                                                 
	  st=start.tv_usec;
	  en=end.tv_usec;
  	  tim[j]=en-st; 
 
	sugg_arr[j]=suggtemp;
	flag[j]=flg;
	
	}

}
else
{
MPI_Recv(&recvbuf, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
chunk=1.0*recvbuf/nop;
low=rank*chunk;
high=(rank+1)*chunk;
if(low>=input_file_iter-1)
low=input_file_iter-1;
if(high>=input_file_iter-1)
high=input_file_iter-1;
}

for(j=low;j<high;j++)
	{
	flg=0;
	suggtemp=0;
	threshtemp=threshold*strlen(input[j])+1;	
		gettimeofday(&start,NULL);
	for(i=0;i<iter;i++)
		{
		levendist=leven(input[j],wordlist[i]);
			if(levendist<threshtemp)
			    {
			     if(suggtemp>=sugg_cnt)
			       break; 
			          if(levendist==0)
				     {
					flg=1;                       
       					break;
				     }   
         			strcpy(suggestions[j][suggtemp++],wordlist[i]);       
     				
    				}	
		}
	  gettimeofday(&end,NULL);                                                                 
	  st=start.tv_usec;
	  en=end.tv_usec;
  	  tim[j]=en-st; 
 
	sugg_arr[j]=suggtemp;
	flag[j]=flg;
	
	}


for(i=low;i<high;i++)
{
printf("%s : \n",input[i]);
if(flag[i]==1)
printf(" correct word\n ");
else
	{
	printf("incorrect word \n");
	printf("suggestions for the word :  ");
	n=sugg_arr[i];
	for(j=0;j<n;j++)
	printf("%s  ",suggestions[i][j]);
	}
printf("time taken for  %s is %ld \n",input[i],tim[i]);	
printf("\n");
}

MPI_Finalize();
return 0;
}


