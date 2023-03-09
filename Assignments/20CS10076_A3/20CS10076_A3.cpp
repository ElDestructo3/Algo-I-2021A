#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name: Vishal Ravipati
Roll Number: 20CS10076
HackerRank ID: eldestructojr3
********************************/

using namespace std;

struct battalion{
    char beta;
    int  num;

};


void print_soldiers_left(struct battalion* different_battalions,int m) {
    for (int i=0;i<m;i++) {
        cout<<"There are "<< different_battalions[i].num<<" units left in "<<different_battalions[i].beta<<"-battalion"<<endl;
    }
}

void setup_2d_array(char **arr_type, int **arr_seq, int r,int c,int grid_size)
{
    for(int i = 0; i < grid_size; i++)
    {
        for(int j = 0; j < grid_size; j++)
        {
            if(i==r && j==c)
            {
                arr_type[i][j]='*';
                arr_seq[i][j]=-1;
                
            }   
            else
            {
                arr_type[i][j]='@';
                arr_seq[i][j]=0;
                
            } 
        }
    }



}

void print_array(char **arr_type, int **arr_seq, int grid_size)
{
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++)
            printf("%c \t",arr_type[i][j]);
         printf("\n");
    }

    printf("\n");

    // The grid is sequence
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++)
           printf("%6d \t", arr_seq[i][j]);
         printf("\n");
    }


    printf("\n");

}
// x and y carry top left coordinate of square in input, count is for checking index of unit
void assign_units(struct battalion* battalion, char** strategy, int** sequence,int n,int x,int y,int m,int* count) {
    
    if (n==2) {                                                 // base case of recursion
        char unit=' ';
        (*count)++;
        int max_num=0;
        int index=0;
            for (int k=0;k<m;k++) {                             // finding battalion with most troops
                if (battalion[k].num>max_num) {
                    max_num=battalion[k].num;
                    unit=battalion[k].beta;
                    index=k;
                }
// instead of sorting, I traversed the array to find max unit directly in order to preserve order of input           
            }
            for (int k=0;k<m;k++) {             // incase multiple battalions have same troops, consider priority
                if ((battalion[k].num==max_num)&&(battalion[k].beta<unit)) {
                    unit=battalion[k].beta;
                    index=k;
                }
            }
        battalion[index].num--;
            for (int i=0;i<n;i++) {
                for (int j=0;j<n;j++) {                     // assign troops to cells unoccupied
                    if (sequence[x+i][y+j]==0) {
                        sequence[x+i][y+j]=*count;
                        strategy[x+i][y+j]=unit;
                    }
                }
            }
        return;
    }
    
    int mine_x=0,mine_y=0;                   // for n!=2, finding cell with either mine or preoccupied troops 
    for (int i=x;i<x+n;i++) {
        for (int j=y;j<y+n;j++) {
            if (sequence[i][j]!=0) {
                mine_x=i;
                mine_y=j;
            }
        }
    }
    // subsequent loops divides square into 4 sub-squares and find which subsquare consists the troop or mine
    if ((mine_x<x+n/2)&&(mine_y<y+n/2)) {  
    /*placing troops on corners(near centre of main square) of other 3 subsquares in order to create identical subproblems for recursion*/
        char unit=' ';
        (*count)++;
        int max_num=0;
        int index=0;                   
            for (int k=0;k<m;k++) {
                if (battalion[k].num>max_num) {
                    max_num=battalion[k].num;
                    unit=battalion[k].beta;
                    index=k;
                }
                        
            }
            for (int k=0;k<m;k++) {
                if ((battalion[k].num==max_num)&&(battalion[k].beta<unit)) {
                    unit=battalion[k].beta;
                    index=k;
                }
            }
        battalion[index].num--;
            sequence[x+n/2][y+n/2]=*count;
            strategy[x+n/2][y+n/2]=unit;  
            sequence[x+n/2][y+n/2-1]=*count;
            strategy[x+n/2][y+n/2-1]=unit;
            sequence[x+n/2-1][y+n/2]=*count;
            strategy[x+n/2-1][y+n/2]=unit;
    }
    else if ((mine_x<x+n/2)&&(mine_y>=y+n/2)) {
        char unit=' ';
        (*count)++;
        int max_num=0;
        int index=0;
            for (int k=0;k<m;k++) {
                if (battalion[k].num>max_num) {
                    max_num=battalion[k].num;
                    unit=battalion[k].beta;
                    index=k;
                }
                        
                }
            for (int k=0;k<m;k++) {
                if ((battalion[k].num==max_num)&&(battalion[k].beta<unit)) {
                    unit=battalion[k].beta;
                    index=k;
                }
            }
        battalion[index].num--;
            sequence[x+n/2][y+n/2]=*count;
            strategy[x+n/2][y+n/2]=unit;  
            sequence[x+n/2][y+n/2-1]=*count;
            strategy[x+n/2][y+n/2-1]=unit;
            sequence[x+n/2-1][y+n/2-1]=*count;
            strategy[x+n/2-1][y+n/2-1]=unit;        
    }
    else if ((mine_x>=x+n/2)&&(mine_y>=y+n/2)) {
        char unit=' ';
        (*count)++;
        int max_num=0;
        int index=0;
            for (int k=0;k<m;k++) {
                if (battalion[k].num>max_num) {
                    max_num=battalion[k].num;
                    unit=battalion[k].beta;
                    index=k;
                }
                        
                }
            for (int k=0;k<m;k++) {
                if ((battalion[k].num==max_num)&&(battalion[k].beta<unit)) {
                    unit=battalion[k].beta;
                    index=k;
                }
            }
        battalion[index].num--;
            sequence[x+n/2-1][y+n/2-1]=*count;
            strategy[x+n/2-1][y+n/2-1]=unit;  
            sequence[x+n/2][y+n/2-1]=*count;
            strategy[x+n/2][y+n/2-1]=unit;
            sequence[x+n/2-1][y+n/2]=*count;
            strategy[x+n/2-1][y+n/2]=unit;        
    }    
    else if ((mine_x>=x+n/2)&&(mine_y<y+n/2)) {
        char unit=' ';
        (*count)++;
        int max_num=0;
        int index=0;
            for (int k=0;k<m;k++) {
                if (battalion[k].num>max_num) {
                    max_num=battalion[k].num;
                    unit=battalion[k].beta;
                    index=k;
                }
                        
                }
            for (int k=0;k<m;k++) {
                if ((battalion[k].num==max_num)&&(battalion[k].beta<unit)) {
                    unit=battalion[k].beta;
                    index=k;
                }
            }
        battalion[index].num--;
            sequence[x+n/2][y+n/2]=*count;
            strategy[x+n/2][y+n/2]=unit;  
            sequence[x+n/2-1][y+n/2-1]=*count;
            strategy[x+n/2-1][y+n/2-1]=unit;
            sequence[x+n/2-1][y+n/2]=*count;
            strategy[x+n/2-1][y+n/2]=unit;        
    }
    // calling recursively the smaller subproblems
    assign_units(battalion,strategy,sequence,n/2,x,y,m,count);
    assign_units(battalion,strategy,sequence,n/2,x+n/2,y+n/2,m,count);
    assign_units(battalion,strategy,sequence,n/2,x+n/2,y,m,count);
    assign_units(battalion,strategy,sequence,n/2,x,y+n/2,m,count);
}


int main()
{
    // take inputs from the command line correctly
    int n,m,x,y;
    char **strategy;
    int **sequence;
    
    cin>>n; 
    cin>>x>>y;
    cin>>m;
    
    strategy = (char**) malloc (n*sizeof(char*));           //dynamic memory allocation for storing data
    for (int i=0;i<n;i++) {
        strategy[i]= (char*) malloc(n*sizeof(char));
    }
    sequence = (int**) malloc (n*sizeof(int*));
    for (int i=0;i<n;i++) {
        sequence[i]= (int*) malloc(n*sizeof(int));
    }
    
      
    setup_2d_array(strategy,sequence,x,y,n);
    /* use the structure type_battalion and create a array "different_battalions" to 
       get the types and number of units per type */
	struct battalion* different_battalions= (struct battalion*) malloc(m*sizeof(struct battalion));
    
    for (int i=0;i<m;i++) {
        cin>>different_battalions[i].beta>>different_battalions[i].num;
        
    }
    int num=0;
    int* count=&num;
    assign_units(different_battalions,strategy,sequence,n,0,0,m,count);
  	//uncomment the following two lines when submitting to moodle/testing your code on custom input
    print_array(strategy,sequence,n);
    printf("\n");
  	
  	//you only need to print this when submitting the code to HackerRank.
    print_soldiers_left(different_battalions,m);
    return 0;
    
    free(different_battalions);
    for (int i=0;i<n;i++) {
        free(sequence[i]);
    }
    free(sequence);
    for (int i=0;i<n;i++) {
        free(strategy[i]);
    }
    free(strategy);
    
    return 0;
}