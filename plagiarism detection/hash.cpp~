#include <fstream>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include "watt.cpp"
///start of file structures
struct tfile
{
	char sentence[300][200];
	int lineno,nwords;
}t_a[5000],t_b[5000];
int tlines=0,tlines2=0;
struct hfile
{
	int sentence[300];
	int lineno,nwords;
}h_a[5000],h_b[5000];
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
      
	  int c = toupper(line[i]);
	  //if( c != 'A' && c != 'G' && c != 'C' && c != 'T' )
	   // continue;
	  //cout << char(c);
	  seq.push_back(char(c));
	}
//cout<<line;
    
	fflush(stdout);
	/*cout<<"\nThe file ";
	for(i=0;i<tlines;i++)
	{
		cout<<"line no : "<<t_a[i].lineno<<"\n";
		for(j=0;j<t_a[i].nwords;j++)
		{
			cout<<t_a[i].sentence[j];cout<<" ";
		}
		
	}*/
    
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
//cout<<line;
    
	fflush(stdout);
	/*cout<<"\nThe file ";
	for(i=0;i<tlines2;i++)
	{
		cout<<"line no : "<<t_a[i].lineno<<"\n";
		for(j=0;j<t_a[i].nwords;j++)
		{
			cout<<t_a[i].sentence[j];cout<<" ";
		}
		
	
    }*/

}
}
  return seq;
}

int main(int argc , char **argv)
{
 struct timeval ts,te; 	
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
		//strcpy(sent,"");
		//cout<<"line no : "<<h_a[i].lineno<<"\n";
		for(j=0;j<h_a[i].nwords;j++)
		{
			//cout<<h_a[i].sentence[j];cout<<" ";
			sprintf(str,"%d0",h_a[i].sentence[j]);
			strcat(sent,str);
		}
		strcat(sent,"#");
		//cout<<"\n====="<<sent<<"\n";
	}

for(i=0;i<tlines2;i++)
	{
		
		h_b[i].lineno=t_b[i].lineno;
		for(j=0;j<t_b[i].nwords;j++)
		{
			p=hash(t_b[i].sentence[j],strlen(t_b[i].sentence[j]));
			h_b[i].sentence[j]=p;
			
		}
		h_b[i].nwords=t_b[i].nwords;
	}
	cout<<"\nThe hash file 2\n";
	/*for(i=0;i<tlines2;i++)
	{
		cout<<"line no : "<<h_b[i].lineno<<"\n";
		for(j=0;j<h_b[i].nwords;j++)
		{
			cout<<h_b[i].sentence[j];cout<<" ";
		}
		
	}*/
	
	
	for(i=0;i<tlines2;i++)
	{
		//strcpy(sent2,"");
		//cout<<"line no : "<<h_b[i].lineno<<"\n";
		for(j=0;j<h_b[i].nwords;j++)
		{
			
			sprintf(str,"%d0",h_b[i].sentence[j]);
			strcat(sent2,str);
		}
		strcat(sent2,"#");
		//cout<<"\n====="<<sent2<<"\n";
	}
///
int t,t2,t1;
t=0;
float no_of_match=0;
cout<<"\nMatching......";
gettimeofday(&ts,NULL);
for(i=0;i<tlines;i++)
{
k=0;
	//cout<<"\nLine no: "<<i<<" of src with\n";
	while(sent[t++]!='#')
	{
		sentarr[k++]=sent[t];
	}
	t++;
	sentarr[k]='\0';
	t2=0;
	for(j=0;j<tlines2;j++)
	{
		//cout<<"line no : "<<j<<" of des\n";
		k=0;
		//t2=t1;
		while(sent2[t2++]!='#')
		{
		sent2arr[k++]=sent2[t2];
		}
		t2++;
		sent2arr[k]='\0';
//cout<<sentarr<<sent2arr;
	if(algorithm(sentarr,sent2arr))
	{
		no_of_match+=1;    
		cout<<"!!!!!!!!Similarity is high for the sentence "<<i<<" or src and "<<j<<" of des!!!!!!!!!!\n";
	}
		
	}
}
gettimeofday(&te,NULL);
cout<<"\nPercentage of plagiarism :"<<(float)(no_of_match/MAX(tlines,tlines2))*100;
///
long int u=ts.tv_usec;
long int v=te.tv_usec;
 printf("difftime   : %.6ld\n",v-u);
	return 0;	
}
