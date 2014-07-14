#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <sys/time.h>
#define THRESHOLD 0.75
#define MAX(x,y) ( (x)>(y) ? (x) : (y) )
using namespace std;

double similarity_score(char a,char b);
double find_array_max(double array[],int length);
void insert_at(char arr[], int n, int idx, char val);
int ind;
double mu,delta;


int algorithm(string seq_a,string seq_b){

  
  mu=1;delta=1;                                 // Parameters for Smith Waterman Algorithm 
  int N_a = seq_a.length();                     // get the actual lengths of the sequences
  int N_b = seq_b.length();
 
  ////////////////////////////////////////////////

  // initialize H
  double H[N_a+1][N_b+1];     
  for(int i=0;i<=N_a;i++){
    for(int j=0;j<=N_b;j++){
      H[i][j]=0.;
    }
  } 

  double temp[4];
  int I_i[N_a+1][N_b+1],I_j[N_a+1][N_b+1];     // Index matrices to remember the 'path' for backtracking
  
  // populating score matrix

  for(int i=1;i<=N_a;i++){
    for(int j=1;j<=N_b;j++){
      temp[0] = H[i-1][j-1]+similarity_score(seq_a[i-1],seq_b[j-1]); 
      temp[1] = H[i-1][j]-delta;                  
      temp[2] = H[i][j-1]-delta;                 
      temp[3] = 0.;
      H[i][j] = find_array_max(temp,4);
      switch(ind){
      case 0:                                  // score in (i,j) stems from a match/mismatch
   	I_i[i][j] = i-1;
	I_j[i][j] = j-1;
	break;
      case 1:                                  // score in (i,j) stems from a deletion in sequence A
     	I_i[i][j] = i-1;
	I_j[i][j] = j;
	break;
      case 2:                                  // score in (i,j) stems from a deletion in sequence B
      	I_i[i][j] = i;
	I_j[i][j] = j-1;
	break;
      case 3:                                  // (i,j) is the beginning of a subsequence
      	I_i[i][j] = i;
	I_j[i][j] = j;	
	break;
      }
    }
  }

  // Print the matrix H to the console
  /*cout<<"**********************************************"<<endl;
  cout<<"The scoring matrix is given by  "<<endl<<endl;
  for(int i=1;i<=N_a;i++){
    for(int j=1;j<=N_b;j++){
      cout<<H[i][j]<<" ";
    }
    cout<<endl;
    }*/

//optimising the smith watterman algorithm to look for local similarity better
double M[N_a+1][N_b+1];     
  for(int i=1;i<=N_a;i++){
    for(int j=1;j<=N_b;j++){
      if(H[i][j]==0)
	M[i][j]=0;
      else if(seq_a[i-1]==seq_b[j-1])
	M[i][j]=H[i-1][j-1];
      else 
	M[i][j]=MAX(MAX(MAX(MAX(MAX(M[i-1][j],H[i-1][j]),M[i][j-1]),H[i][j-1]),M[i-1][j-1]),H[i-1][j-1]);
  }
}
 for(int i=1;i<=N_a;i++){
    for(int j=1;j<=N_b;j++){
	H[i][j]=M[i][j];
 }
}
  // search H for the maximal score
  double H_max = 0.;
  int i_max=0,j_max=0;
  for(int i=1;i<=N_a;i++){
    for(int j=1;j<=N_b;j++){
      if(H[i][j]>H_max){
	H_max = H[i][j];
	i_max = i;
	j_max = j;
      }
    }
  }

  //cout<<H_max<<endl;
  
     // Backtracking from H_max
  int current_i=i_max,current_j=j_max;
  int next_i=I_i[current_i][current_j];
  int next_j=I_j[current_i][current_j];
  int tick=0;
  char consensus_a[N_a+N_b+2],consensus_b[N_a+N_b+2];
  float zzz=0;          // to calculate relative local similarity
  while(((current_i!=next_i) || (current_j!=next_j)) && (next_j!=0) && (next_i!=0)){

    if(next_i==current_i)  
	{
		consensus_a[tick] = '-';                  // deletion in A
		zzz-=mu;
	}
    else 
	{
                  consensus_a[tick] = seq_a[current_i-1];   // match/mismatch in A
		zzz+=similarity_score(seq_a[current_i-1],seq_b[current_j-1]);
	}

    if(next_j==current_j)  {
			consensus_b[tick] = '-';                  // deletion in B
			zzz-=mu;
			}
    else                 {
	  consensus_b[tick] = seq_b[current_j-1];   // match/mismatch in B
	zzz+=similarity_score(seq_a[current_i-1],seq_b[current_j-1]);
	}

    current_i = next_i;
    current_j = next_j;
    next_i = I_i[current_i][current_j];
    next_j = I_j[current_i][current_j];
    tick++;
    }
 
 // Output of the consensus to the console
  /*cout<<endl<<"***********************************************"<<endl;
  cout<<"The alignment of the sequences"<<endl<<endl;
  for(int i=0;i<N_a;i++){cout<<seq_a[i];}; cout<<"  and"<<endl;
  for(int i=0;i<N_b;i++){cout<<seq_b[i];}; cout<<endl<<endl;
  cout<<"is for the parameters  mu = "<<mu<<" and delta = "<<delta<<" given by"<<endl<<endl;  
  for(int i=tick-1;i>=0;i--) cout<<consensus_a[i]; 
 cout<<endl;
 for(int j=tick-1;j>=0;j--) cout<<consensus_b[j];
  cout<<endl;
 cout<<"\n=====\tzzz="<<zzz<<"\t"<<N_a<<"\t"<<N_b<<endl; */
 float similarity=(float)(zzz/MAX(N_a,N_b));
 //cout<<"\n=====\tsimilarity:"<<similarity<<endl;
 if(similarity>THRESHOLD)                         // threshold that is fixed depending on the type of document and level of accuracy needed
 {
	return 1;
 }
 else
 {
        return 0;
 }
} // END of algorithm




double similarity_score(char a,char b){

  double result;
  if(a==b){
      result=1.;                 // result : parameter in smith waterman algorithm
    }
  else{
      result=-mu;
    }
  return result;
}

/////////////////////////////////////////////////////////////////////////////

double find_array_max(double array[],int length){

  double max = array[0];           
  ind = 0;

  for(int i = 1; i<length; i++){
      if(array[i] > max){
	max = array[i];
	ind = i; 
      }
  }
  return max;                    // return highest value in array
}


