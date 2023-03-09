#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* 
Name:  Vishal Ravipati
Roll Number: 20CS10076
Hackerrank ID: eldestructojr3
*/

typedef struct _node {                                      // creating node structure
    int rank;
    struct _node* parent;
} node;




node* find(node* x) {                                       // finding root using path compression
    if (x->parent!=x) {
        x->parent=find(x->parent);
    }
    return x->parent;
}

void unionNode(node* x,node *y) {                           // performing union of nodes using union by rank
    
    if (x->rank>y->rank) {
        y->parent=x;
    }
    else if (x->rank<y->rank) {
        x->parent=y;
    
    }
    else {
        x->rank++;
        y->parent=x;
        
    }
    
} 

int check_edge(int num,int type) {                          // check if edge type (int type) is present in graph
    while(num) {
        int temp=num%10;
        if (temp==type ) return 1;
        num/=10;
    }
    return 0;
}


int descend_num(int num) {                           // arranging digits of edge type in descending order for printing
    int ans=0;
    for (int i=9;i>=0;i--) {
        int temp=num;
        while (temp) {
            if (temp%10==i) {
                ans*=10;
                ans+=temp%10;
            }
            temp/=10;
        }
    }
    return ans;
}

void print_graph(int** graph,int n) {              // print graph
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if (graph[i][j]==0) {
                cout<<"0    ";
            }
            else {
                int temp=graph[i][j];              // each graph number consists of digits of edge type
                int num=0;
                while (temp) {
                    cout<<temp%10;                 // printing out edge type
                    if (temp>10) cout<<"#";        // checking if more than one edge type is present
                    temp/=10;
                    
                    num++;
                    
                }
                cout<<"    ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}


int check_1(int** graph, node*C, int n) {         // consider path traversal w.r.t edge type 1
    int num=0;
    int count=0;
    node* a;
    node* b;
    for (int i=0;i<n;i++) {
        for (int j=i+1;j<n;j++) {
            if (check_edge(graph[i][j],1)||check_edge(graph[i][j],3)) {     // checking presence of edge
                count++;
                
                a=find(&C[i]);
                b=find(&C[j]);
                if (a==b) num++;                  // if two nodes are already connected increment obsolete edge count
                else {
                    unionNode(a,b);
                }
                
            }
        }
    }
    if (count<n-1) return -1;                     // if edges are less than minimum required output -1
    
    return num;
}
                 
int check_2(int** graph, node*C, int n) {          // same as above but w.r.t edge type 2
    int num=0;
    int count=0;
    node* a;
    node* b;
    for (int i=0;i<n;i++) {
        for (int j=i+1;j<n;j++) {
            if (check_edge(graph[i][j],2)||check_edge(graph[i][j],3)) {
                count++;
                
                a=find(&C[i]);
                b=find(&C[j]);
                if (a==b) num++;
                else {
                    unionNode(a,b);
                }
                
            }
        }
    }
    if (count<n-1)  return -1;
    
    return num;
}
                
void maxEdgesToRemove(int** graph, int a,int b, int n) {  // if there are edges of both 1(/2) and 3 types, remove 1(/2) as it is redundant
    int count=0; 
    for (int i=0;i<n;i++) {
        for (int j=i+1;j<n;j++) {
            if ((check_edge(graph[i][j],1)||check_edge(graph[i][j],2))&&check_edge(graph[i][j],3)) {
                count++;
            }
        }
    }
    if (a==-1||b==-1) cout<<"Edges Removed = "<<-1;
    else {
        cout<<"Edges Removed = "<<count+a+b;
    }
   
}


int main() {
    int n,m;
    cin>>n>>m;
    
    int** arr= new int*[n];
    for (int i=0;i<n;i++) {
        arr[i]=new int[n];
        for (int j=0;j<n;j++) {
            arr[i][j]=0;

        }
    }
    for (int i=0;i<m;i++) {
        int type,a,b;
        cin>>type>>a>>b;
        arr[a][b]=descend_num(arr[a][b]*10+type);                   // storing graph values such that digits are on descending order and represent edge types
        arr[b][a]=descend_num(arr[b][a]*10+type);
    }

    print_graph(arr,n);
    
    node * C;                                         // memory for nodes
    C= new node[n];
    for (int i=0;i<n;i++) {
        
        C[i].rank=0;
        C[i].parent=&(C[i]);
        
    }
    
    int a=check_1(arr,C,n);
    
    
    
    node * D;                                          // creating another set for checking for edge type 2
    D= new node[n]; 
    for (int i=0;i<n;i++) {
        
        D[i].rank=0;
        D[i].parent=&(D[i]);
        
    }
    
    int b=check_2(arr,D,n);
    
    
   maxEdgesToRemove(arr,a,b,n);           
    
    
}