/*****************************************
IMPORTANT: 
Write your Name, Roll number and Hackerrank ID here.

Name: Vishal Ravipati
Roll Number: 20CS10076
Hackerrank ID: eldestructojr3
*****************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <string.h>
#include <stdlib.h>

#define SIZE 100000                                          // define max size of queue as per question
using namespace std;

typedef struct {
    int * Arr;
    int queue_size, start_id, end_id;
} QUEUE;

void init(QUEUE *qP, int size) {
    //qP = (QUEUE*) malloc(sizeof(QUEUE));
    //qP->Arr=(int*) malloc(size*sizeof(int));
    
    qP->queue_size=0;
    
    qP->start_id=0;
    qP->end_id=size-1;
    
}

int isempty(QUEUE qP) {
    if (qP.queue_size==0) {
        return 1;
    }
    return 0;
}

void enqueue(QUEUE *qP, int data) {
    qP->end_id= (qP->end_id+1)%(SIZE);
    qP->Arr[qP->end_id]=data;  
    qP->queue_size++;
}

int dequeue(QUEUE *qP) {
    if (isempty(*qP)) {
        return -1;
    }
    int item=qP->Arr[qP->start_id];
    qP->start_id=(qP->start_id+1)%(SIZE);
    qP->queue_size--;
    return item;
}

void display_queue(QUEUE *qP) {
    for (int i=qP->start_id;i<qP->end_id;i++) {
        cout<<qP->Arr[i]<<',';
    }
    cout<<endl;
    
}

void conquer(int** adjacency_matrix,QUEUE* qP,int n,int m) {
    int out_index=0,in_index=0;                       // used for detecting cycle within graph
    int arr[n]={0};                                   // used for storing out-degree of nodes in graph
    
    for (int i=0;i<n;i++) {                           // check if any node has indegree 0
        int sum=0;
        for (int j=0;j<n;j++) {
            sum+=adjacency_matrix[i][j];
        }
        if (sum==0) {
            in_index=1;
        }
    }
    for (int i=0;i<n;i++) { 
        for (int j=0;j<n;j++) {                       
            arr[i]+=adjacency_matrix[i][j];           //finding outdegree for node i
        }
        
        if (arr[i]==0) {                              // check if any node has outdegree 0
            out_index=1;
        }
        
    }
    
    // if the graph has no node with indegree or outdegree 0 it means that there is a cycle in the graph
    if ((in_index!=1)||(out_index!=1)) {      
        cout<<"unconquerable"<<endl;
        return;
    }
    
    for (int i=0;i<n;i++) {                  // performing topological sort, firstly by enqueuing nodes with outdegree 0
        if (arr[i]==0) {
            enqueue(qP, i);
            
                       
        }
    }
    int temp_count=0;
    while(!isempty(*qP)) {
        int temp=qP->Arr[qP->start_id];
        
        dequeue(qP);
        if (temp_count==0) {
            cout<<temp;
            temp_count++;
        }
        else {
            cout<<","<<temp;                  // outputting nodes from queue
        }
        
        for (int j=0;j<n;j++) {
            if (adjacency_matrix[j][temp]) {
                arr[j]--;
                if (arr[j]==0) {
                    enqueue(qP, j);
                }
            }
        }
        
    }
    cout<<endl;
    /* if a DAG has n nodes, maximum number of nodes possible are nC2. So, if a DAG has m nodes, nC2-m edges can be added without forming cycle. In the problem, this corresponds to the number of matches possible
    */
    int num_matches= n*(n-1)/2 - m;
    cout<<num_matches<<endl;
        
    arr[n]={0};
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            arr[i]+=adjacency_matrix[i][j];         //recreating outdegree matrix as it was used up in topological sort
        }
    }
     // Adding possible connections, also comparing outdegrees to ensure that matches are created in the correct order
    if (num_matches>0) {                            
        
        for (int i=0;i<n;i++) {
            for (int j=i+1;j<n;j++) {
                if ((arr[i]>arr[j])&&(adjacency_matrix[i][j]==0)) {       
                    adjacency_matrix[i][j]=1;
                    cout<<j<<" "<<i<<endl;
                    arr[i]++;
                }
                else if ((arr[i]<=arr[j])&&(adjacency_matrix[j][i]==0)) {
                    adjacency_matrix[j][i]=1;
                    cout<<i<<" "<<j<<endl;
                    arr[j]++;
                }
            }
        }
    }
    
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,m;
    cin>>n>>m;
     // creating adjacency matrix for storing graph and allocating memory  
    int** adj_mat=(int**) malloc (n*sizeof(int*));         
    for (int i=0;i<n;i++) {
        adj_mat[i]=(int*) malloc(n*sizeof(int));
        
    }
    for (int i=0;i<n;i++) {                         // setting matrix to 0 
        for (int j=0;j<n;j++) {
            adj_mat[i][j]=0;
        }
    }
    
    for (int i=0;i<m;i++) {                         // reading input and creating graph
                                                    
        int temp_1,temp_2;
        cin>>temp_1>>temp_2;
                                      
        adj_mat[temp_2][temp_1]=1;                  // we consider the edge to be outgoing from winner to loser
    }
    
    
    
    QUEUE* qP=(QUEUE*) malloc(sizeof(QUEUE));
    qP->Arr=(int*) malloc((100000)*sizeof(int));    //allocating memory
    
    
    init(qP,100000);                                //initialise queue
    
    conquer(adj_mat,qP,n,m);                     
    for (int i=0;i<n;i++) {                         //free memory
        free(adj_mat[i]);
    }
    free(adj_mat);
    return 0;
}

/* Code ends here */