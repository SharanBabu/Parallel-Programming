#include <fstream>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
///start of file structures
struct tfile
{
	char sentence[30][20];
	int lineno,nwords;
}t_a[50],t_b[50];
int tlines=0;
struct hfile
{
	int sentence[30];
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
	tlines++;fflush(stdout);
      cout<<tlines;
	  int c = toupper(line[i]);
	  //if( c != 'A' && c != 'G' && c != 'C' && c != 'T' )
	   // continue;
	  //cout << char(c);
	  seq.push_back(char(c));
	}
//cout<<line;
    
	fflush(stdout);
	cout<<"\nThe file ";
	for(i=0;i<tlines;i++)
	{
		cout<<"line no : "<<t_a[i].lineno<<"\n";
		for(j=0;j<t_a[i].nwords;j++)
		{
			cout<<t_a[i].sentence[j];cout<<" ";
		}
		
	}
    
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
			t_b[tlines].sentence[j][k++]=line[i];
		}	
	t_b[tlines].sentence[j][k++]='\0';j++;
	}
	t_b[tlines].nwords=j;
	t_b[tlines].lineno=tlines;
	tlines++;fflush(stdout);
      cout<<tlines;
	  int c = toupper(line[i]);
	  
	  seq.push_back(char(c));
	}
//cout<<line;
    
	fflush(stdout);
	cout<<"\nThe file ";
	for(i=0;i<tlines;i++)
	{
		cout<<"line no : "<<t_a[i].lineno<<"\n";
		for(j=0;j<t_a[i].nwords;j++)
		{
			cout<<t_a[i].sentence[j];cout<<" ";
		}
		
	
    }

}
}
  return seq;
}

int main(int argc , char **argv)
{
  /*hashInit(6);
  RKHash h=hash("insri",strlen("srini"));
  cout<<h<<"\n";
h=hash("isnri",strlen("srini"));
  cout<<h<<"\n";
h=hash("iisrn",strlen("srini"));
  cout<<h;	*/
	/*FILE *fp=fopen("src1","r");
	FILE *fs=fopen("hashsrc","wb");
	int k=0;
        char c,str[100],no[100];
	while( (!feof(fp)))
		{
			k=0;
			while( ((c=fgetc(fp))!='.') && (!feof(fp)))
			{
				str[k]=c;
				k++;
			}
			str[k]='\0';
			cout<<str<<"\t"<<hash(str,strlen(str))<<"\n";
//			cout<<fprintf(fs,"%d",hash(str,strlen(str)))<<"\n";
			sprintf(no,"%d",hash(str,strlen(str)));
			fwrite (no,1,sizeof(no),fs);
		}*/
string seq_a,seq_b;
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
	for(i=0;i<tlines;i++)
	{
		cout<<"line no : "<<h_a[i].lineno<<"\n";
		for(j=0;j<h_a[i].nwords;j++)
		{
			cout<<h_a[i].sentence[j];cout<<" ";
		}
		
	}
}
