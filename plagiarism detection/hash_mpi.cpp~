#include <fstream>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<omp.h>
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
///start of file structures
struct tfile
{
	char sentence[30][20];
	int lineno,nwords;
}t_a[50],t_b[50];
int tlines=0,tlines2=0;
struct hfile
{
	int sentence[30];
	char wsentence[105];  //added newly
	int lineno,nwords;
}h_a[50],h_b[50];
int hlines=0;
//end
using namespace std;
typedef unsigned int RKHash;       
const unsigned int hashBase = 256;
const unsigned int prime = 97;      // prime <= 2^32 / (hashBase + 1)
unsigned int highOffset = 0;
 
void hashInit(size_t len) {
  highOffset = 1;
  for (size_t i = 0; i < len - 1; ++i) {
    highOffset = (highOffset * hashBase) % prime;
  }
}
 
RKHash hash(const void *data, size_t len) {
  unsigned char *p = (unsigned char*) data;
  RKHash hash = 0;
  for (size_t i = 0; i < len; ++i) {
    hash = ((hash * hashBase) + p[i]) % prime;
  }
  return hash;
}
void checkfile(int open, char filename[]){

  if (open){cout << "Error: Can't open the file "<<filename<<endl;exit(1);}
  else cout<<"Opened file "<<filename<<endl;
}
 
string read_sequence(ifstream& f,int z)
{
  // overflows.
  string seq;
  int k=0,j;
  int i;
  char line[5000];
  while( f.good() )
    {
      f.getline(line,5000);
	for(i=0;line[i]!='\0';i++)
	{
		line[i]=toupper(line[i]);
	}
     	if(z==1)
          {
      for(i = 0; line[i] != '\0'; ++i)
	{
	j=0;
	for(;line[i]!='.';i++)
	{
	
	k=0;
		for(;line[i]!=' ';i++)
		{
			t_a[tlines].sentence[j][k++]=line[i];
		}	
	t_a[tlines].sentence[j][k++]='\0';j++;
	}
	t_a[tlines].nwords=j;
	t_a[tlines].lineno=tlines;
	tlines++;
fflush(stdout);
       	}

    
	fflush(stdout);
    
 } 	
    else
    {
	
      for(i = 0; line[i] != '\0'; ++i)
	{
	
	j=0;
	for(;line[i]!='.';i++)
	{
	
	k=0;
		for(;line[i]!=' ';i++)
		{
			t_b[tlines2].sentence[j][k++]=line[i];
		}	
	t_b[tlines2].sentence[j][k++]='\0';j++;
	}
	t_b[tlines2].nwords=j;
	t_b[tlines2].lineno=tlines2;
	tlines2++;
       fflush(stdout);
      cout<<tlines;
	  int c = toupper(line[i]);
	  
	  seq.push_back(char(c));
	}

    
	fflush(stdout);
	

}
}
  return seq;
}

int main(int argc , char **argv)
{
  	
string seq_a,seq_b;
int k;
 ifstream stream_seq_b;                      // first define the input-streams for seq_a and seq_b
  stream_seq_b.open(argv[1]);            // the same for seq_b
  checkfile(! stream_seq_b,argv[1]);
  seq_b = read_sequence(stream_seq_b,1);
  ifstream stream_seq_a;
  stream_seq_a.open(argv[2]);            // open the file for input
  checkfile(! stream_seq_a,argv[2]);     // check, whether the file was opened successfully
  seq_a = read_sequence(stream_seq_a,2);  
cout<<seq_a<<"\n"<<seq_b;
//
//
int p,i,j;
for(i=0;i<tlines;i++)
	{
		//cout<<"line no : "<<t_a[i].lineno<<"\n";
		h_a[i].lineno=t_a[i].lineno;
		#pragma omp parallel  for private(j,p) num_threads(4)
		for(j=0;j<t_a[i].nwords;j++)
		{
			p=hash(t_a[i].sentence[j],strlen(t_a[i].sentence[j]));
			h_a[i].sentence[j]=p;
			//cout<<p;
			//cout<<t_a[i].sentence[j];cout<<" ";
		}
		h_a[i].nwords=t_a[i].nwords;
	}
cout<<"\nThe hash file \n";
	/*for(i=0;i<tlines;i++)
	{
		cout<<"line no : "<<h_a[i].lineno<<"\n";
		for(j=0;j<h_a[i].nwords;j++)
		{
			cout<<h_a[i].sentence[j];cout<<" ";
		}
		
	}*/
	char str[5],sent[1000],sent2[1000],sentarr[1000],sent2arr[1000];
	
	for(i=0;i<tlines;i++)
	{
		strcpy(sent,"");  //added newly
		for(j=0;j<h_a[i].nwords;j++)
		{
		
			sprintf(str,"%d0",h_a[i].sentence[j]);
			strcat(sent,str);
		}
		strcat(sent,"#");
		//fflush(stdout);
		//cout<<sent;
		//sent[strlen(sent)+1]='\0';
		strcpy(h_a[i].wsentence,sent); //added newly
		fflush(stdout);
		cout<<h_a[i].wsentence;
	}
for(i=0;i<tlines2;i++)
	{
		
		h_b[i].lineno=t_b[i].lineno;
		#pragma omp parallel  for private(j,p) num_threads(4)
		for(j=0;j<t_b[i].nwords;j++)
		{

			p=hash(t_b[i].sentence[j],strlen(t_b[i].sentence[j]));
			h_b[i].sentence[j]=p;
			
		}
		h_b[i].nwords=t_b[i].nwords;
	}
	
	
	
	for(i=0;i<tlines2;i++)
	{
		strcpy(sent2,""); //added newly
		for(j=0;j<h_b[i].nwords;j++)
		{
			sprintf(str,"%d0",h_b[i].sentence[j]);
			strcat(sent2,str);
		}
		strcat(sent2,"#");
//		fflush(stdout);
//		cout<<sent;
		//sent2[strlen(sent2)+1]='\0';
		strcpy(h_b[i].wsentence,sent2); //added newly
		fflush(stdout);
		cout<<h_b[i].wsentence;
	}
///
cout<<"\nMatching......";
int no_of_match[4]={0};
///parallel comparison between src and des
//printf("the total number of lines:%d and tlines 2:%d\n",tlines,tlines2);
omp_set_num_threads(4);
int ii,jj;
#pragma omp parallel private(ii,jj) 
{
int size,id;
id=omp_get_thread_num();
size=tlines/4;
//cout<<"\n============size :"<<size;
for(ii=id*size;ii<(id+1)*size;ii++)
{
        cout<<"\n===============i :"<<ii<<" in "<<id;
	for(jj=0;jj<tlines2;jj++)
	{
		 mu=1;delta=1;                                 // Parameters for Smith Waterman Algorithm 
  int N_a = strlen(h_a[ii].wsentence);                     // get the actual lengths of the sequences
  int N_b = strlen(h_b[ii].wsentence);
 
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
      temp[0] = H[i-1][j-1]+similarity_score(h_a[ii].wsentence[i-1],h_b[jj].wsentence[j-1]); 
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
      else if(h_a[ii].wsentence[i-1]==h_b[jj].wsentence[j-1])
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
                  consensus_a[tick] = h_a[ii].wsentence[current_i-1];   // match/mismatch in A
		zzz+=similarity_score(h_a[ii].wsentence[current_i-1],h_b[jj].wsentence[current_j-1]);
	}

    if(next_j==current_j)  {
			consensus_b[tick] = '-';                  // deletion in B
			zzz-=mu;
			}
    else                 {
	  consensus_b[tick] = h_b[jj].wsentence[current_j-1];   // match/mismatch in B
	zzz+=similarity_score(h_a[jj].wsentence[current_i-1],h_b[jj].wsentence[current_j-1]);
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
	no_of_match[id]++;
 }
 else
 {
  //      return 0;
 }
	}
}
}

int nnnn=0;
for(i=0;i<4;i++)
{
	nnnn+=no_of_match[i];
}
float per=(float)(nnnn/MAX(tlines,tlines2))*100;
cout<<"\nPer :"<<per<<"\t"<<nnnn<<"\t"<<tlines<<"\t"<<tlines2;
cout<<"\nPlagiarism percentage = "<<(float)((nnnn/(MAX(tlines,tlines2)))*100);
//omp
	return 0;	
}
