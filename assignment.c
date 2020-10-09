
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXROWS      10000  // maximum number of rows that the input file can have
#define NUMRIDINGS   338    // number of ridings

#define NUMCOLS      3      // number of columns in data
#define ID           0      // index of voter ID in data
#define RIDING       1      // index of riding number in data
#define VOTE         2      // index of vote in data

#define NUMPARTIES   4      // number of parties to vote for
#define NOPARTY     -1      // number to represents a party that doesn't exist
#define NDP          0      // number to represent NDP party
#define CONSERVATIVE 1      // number to represent Conservative party
#define LIBERAL      2      // number to represent Liberal party
#define GREEN        3      // number to represent Green party
int to_array( char filename[], int data[][NUMCOLS] );
void compute_riding_results(int data[][NUMCOLS], int result[][NUMPARTIES], int num_votes);
int index_of_max(int array[], int length);
int calculate_winner(int counts_per_riding[][NUMPARTIES], int winners[]);
int calculate_popular_vote(int counts_per_riding[][NUMPARTIES]);
void to_party_name(char dest[], int party_num);
void to_file(char filename[], int riding_vote_counts[][NUMPARTIES], int riding_winners[], char election_winner[], char popular_winner[]);

//new function added
void to_party_name1(char dest1[], int party_num1);

int h=0;
int main(void)
{

    int row=0;
   	char dest[100];
   	char dest1[100];
   	char name[100];
   	char save[100];
    int data[MAXROWS][NUMCOLS];
    //memset(data,0,sizeof(data));
    int ridnigs_perparty[NUMRIDINGS][NUMPARTIES];
    memset(ridnigs_perparty,0,sizeof(ridnigs_perparty));
    printf("input file name to open \n");
    gets(name);
    printf("input file name to save the result \n");
    gets(save);
    row=to_array(name,data);
    // printf( "%d",row);
    if(row== -1 || row == 0)
    {
        printf("program terminated");
     	return 0;
    }

     compute_riding_results(data,ridnigs_perparty,row);
     //index_of_max(int array[], int length);
     int winners[NUMRIDINGS];

   	 int ewinner=calculate_winner(ridnigs_perparty, winners);

   	 int popwinner=calculate_popular_vote(ridnigs_perparty);

   	 to_party_name(dest,ewinner);

   	 to_party_name1(dest1,popwinner);

     to_file(save,ridnigs_perparty,winners,dest, dest1);

     return 0;

 }
int to_array(char filename[],int data[][NUMCOLS])
{  //printf("%s",filename);
	FILE *file;
	char *line ,*number;
	char help[256];
    h=0;
	file=fopen(filename,"r");
	if(file==NULL)
		return -1;
	while(!feof(file))
	{    //printf("%d\n",file);
         int w=0;
		 //fscanf(file,"%s",line);
		 fscanf(file,"%s",help);
		 number=strtok(help,"\t");
		 while(number!=NULL)
		 {
		 	data[h][w]=atoi(number);
		 	number=strtok(NULL,"t");
		 	w++;

		 }
		 fscanf(file,"%s",help);
		 number=strtok(help,"\t");
         while(number!=NULL)
		 {
		 	data[h][w]=atoi(number);
		 	number=strtok(NULL,"\t");
		 	w++;

		 }
		  fscanf(file,"%s",help);
		 number=strtok(help,"\t");
         while(number!=NULL)
		 {
		 	data[h][w]=atoi(number);
		 	number=strtok(NULL,"\t");
		 	w++;

		 }
		 h++;
	}
	fclose(file);

	/*for(int i=0;i<h;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",data[i][j]);
		}
		printf("\n");
	}
    printf("%d ",h);*/
	//printf("%d",h);

	return h;
}

// compute_riding_results function
void compute_riding_results(int data[][NUMCOLS], int result[][NUMPARTIES], int num_votes)
{
	for(int i=0;i<num_votes;i++)
	{
		int a=data[i][1],b=data[i][2];
		result[a][b]++;
	}
}

// max index of array
int index_of_max(int array[], int length)
{
	int a=-1000;
	int index,index1;
	for(int i=0;i<length;i++)
	{
		if(array[i]>a)
		{
			a=array[i];
			index=i;

		}
		if(array[i]>=a)
		{
			index1=i;
		}
	}
	if(index==index1)
		return index;
	else
		return -1;
}

int calculate_winner(int counts_per_riding[][NUMPARTIES], int winners[])
{
     int party0=0,party1=0,party2=0,party3=0;

  	for(int i=0;i< NUMRIDINGS ;i++)
  	{
  		int a=-10000;
  		int index,index1;
  		for(int j=0;j<4;j++)
  		{
          if(counts_per_riding[i][j]>a)
		{
			a=counts_per_riding[i][j];
			index=j;

		}
		if(counts_per_riding[i][j]>=a)
		{
			index1=j;
		}
  		}
  		if(index1==index)
  			winners[i]=index;
  		else
  			winners[i]=-1;
  	}

   for(int i=0;i<NUMRIDINGS;i++)
   {
   	if(winners[i]==0)
   		party0++;
   	else if(winners[i]==1)
   		party1++;
   	else if(winners[i]==2)
   		party2++;
   	else if(winners[i]==3)
   		party3++;

   }

   if(party0 > party1 && party0 > party2 && party0 > party3)
   		return 0;
   	else if(party1 > party0 && party1 > party2 && party1 > party3 )
   		return 1;
   	else if(party2 > party0 && party2 > party1 && party2 > party3)
   		return 2;
   	else if(party3 >party0 && party3 > party1 && party3 > party2)
   		return 3;
   	else
   		return -1;
}

//popular votes
int calculate_popular_vote(int counts_per_riding[][NUMPARTIES])
{

	int counta=0,countb=0,countc=0,countd=0;
	for(int i=0;i<NUMRIDINGS;i++)
	{
		for(int j=0;j<NUMPARTIES;j++)
		{
			if(j==0)
				counta+=counts_per_riding[i][j];
			else if(j==1)
				countb+=counts_per_riding[i][j];
			else if(j==2)
				countc+=counts_per_riding[i][j];
			else
				countd+=counts_per_riding[i][j];
		}

	}
     if(counta > countb && counta > countc && counta > countd)
   		return 0;
   	else if(countb > counta && countb > countc && countb > countd)
   		return 1;
   	else if(countc > counta && countc > countb && countc > countd)
   		return 2;
   	else if(countd > counta && countd > countb && countd > countc)
   		return 3;
   	else
   		return -1;
}

void to_party_name(char dest[], int party_num)
{
    char a[]="NOT NAMED";
    char b[]="NDP";
    char c[]="CONSERVATIVE";
    char d[]="LIBERAL";
    char e[]="GREEN";
	if(party_num==-1)
		strcpy(dest,a);
	else if(party_num==0)
		strcpy(dest,b);
	else if(party_num==1)
		strcpy(dest,c);
	else if(party_num==2)
	strcpy(dest,d);
	else
		strcpy(dest,e);
}

void to_party_name1(char dest1[], int party_num1)
{
	char a[]="NOT NAMED";
    char b[]="NDP";
    char c[]="CONSERVATIVE";
    char d[]="LIBERAL";
    char e[]="GREEN";
	if(party_num1==-1)
		strcpy(dest1,a);
	else if(party_num1==0)
		strcpy(dest1,b);
	else if(party_num1==1)
		strcpy(dest1,c);
	else if(party_num1==2)
	strcpy(dest1,d);
	else
		strcpy(dest1,e);
}
void to_file(char filename[], int riding_vote_counts[][NUMPARTIES], int riding_winners[], char election_winner[], char popular_winner[])
{
//printf("%s  %s",election_winner, popular_winner);
   FILE *fptr;
   fptr=fopen("result_2.txt","w");

   fprintf(fptr,"Winner of the election : %s\n\nWinner of the popular vote: %s\n\n\tRIDING#\t\t NDP\t  CONSERVATIVE \t\tLIBERAL\t\t GREEN\t WINNING PARTY\n",election_winner,popular_winner);
   for(int i=0;i<NUMRIDINGS;i++)
    {  fprintf(fptr,"\t  %d\t\t",i);
    	for(int j =0 ;j<NUMPARTIES;j++)
    	{
    		fprintf(fptr,"  %d\t\t",riding_vote_counts[i][j]);

    	}
    	if(riding_winners[i]==0)
    		fprintf(fptr,"%s\n","NDP");
    	else if(riding_winners[i]==1)
            fprintf(fptr,"%s\n","CONSERVATIVE");
    	else if(riding_winners[i]==2)
    		fprintf(fptr,"%s\n","LIBERAL");
    	else if(riding_winners[i]==3)
    		fprintf(fptr,"%s\n","GREEN");
    	else
    		fprintf(fptr,"%s\n","NOTNAMED");
    }
   fclose(fptr);
   printf("result stored in %s",filename);
 //for showing output
   /* printf("Winner of the election  %s \n",election_winner );
    printf("C",popular_winner);
    printf("RIDING#\t NDP\t  CONSERVATIVE \tLIBERAL\t WINNING PARTY\n");
    for(int i=0;i<NUMRIDINGS;i++)
    {   printf("%d\t",i);
    	for(int j =0 ;j<NUMPARTIES;j++)
    	{
    		printf("%d\t",riding_vote_counts[i][j]);
    	}
    	if(riding_winners[i]==0)
    		printf("%s\n","NDP");
    	else if(riding_winners[i]==1)
    		printf("%S\n""CONSERVATIVE");
    	else if(riding_winners[i]==2)
    		printf("%s\n","LIBERAL");
    	else if(riding_winners[i]==3)
    		printf("%s\n","GREEN");
    	else
    		printf("%s\n","NOTNAMED");
    }*/
}
