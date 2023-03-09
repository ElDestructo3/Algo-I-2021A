/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name: Vishal Ravipati
Roll Number: 20CS10076
HackerRank ID: eldestructojr3
********************************/

#include<iostream>
#include<climits>


using namespace std;

int find(int* parent, int i) {
    if (parent[i]==-1) {
        return i;
    }
    return find(parent,parent[i]);
}

void Union(int * parent, int x, int y) {
    parent[x]=y;
}


// function which returns the Max Power that is achievable by  a Loki
int Dijkstra(int **mat, int N, int src,int *distance,int**MST)
{
    // array to store the length value for each vertex
    bool visited[N];  // boolean array to check if a vertex has already been included in the max power path
 
    int ans = 0;

    //initialising weights of all the vertices as MIN as we want max length path
    // initially none of the vertices are in the path, thus all have value false
    for(int i = 0; i < N; i++)
    {
        distance[i] = INT_MIN;
        visited[i] = false;
    } 

    // defining distance of source vertex as 0 
    distance[src] = 0;

    int max, idx = -1;

    for(int i = 0; i < N; i++)
    {
        max=INT_MIN;

        // finding the vertex with the max weight to include in the path
        for(int j = 0; j < N; j++)
        {
            if(visited[j] == false && distance[j] > max)
            {
                max = distance[j];
                idx = j;
            }
        }
        visited[idx] = true;   // the max distance vertex is included in max_power path 
        ans+= distance[idx]; 
        

        //updating the len value of neighbours of the vertex chosen
        for(int j = 0; j < N; j++)
        {
            if((mat[idx][j] > 0) && visited[j] == false)
            {
                if(mat[idx][j] > distance[j]) {
                    distance[j] = mat[idx][j];
                    MST[j][idx]=mat[j][idx];               // storing in MST
                    
                }
                    
                    
            }
        }
    }   
    
    cout<<ans<<endl;
    return ans;
}


int main()
{
    // taking the input
    int N, Q, M;
    cin>>N>>Q;
    M = (N*(N-1))/2;
    
    
    
    // initial adjacency matrix
    int **mat = new int*[N];
    for(int i = 0; i < N; i++)
    {
        mat[i] = new int[N];
        for(int j = 0; j < N; j++)
            mat[i][j] = 0;      // to show that there is no node between i and j
    }
    
    int **MST = new int*[N];       // for storing MST
    for(int i = 0; i < N; i++)
    {
        MST[i] = new int[N];
        for(int j = 0; j < N; j++)
            MST[i][j] = 0;      
    }
    
    for(int i = 0; i < M; i++)
    { 
        int x, y,w;
        cin>>x>>y>>w;
        mat[x-1][y-1]=w;
        mat[y-1][x-1]=w;
    }
    
    int *distance = new int[N];
    
    for(int i = 0; i < N; i++)
    {
        distance[i] = INT_MAX;
        
    }
    // finding max power for our Loki
    int ans=Dijkstra(mat, N, 0,distance,MST);

    //finding max power for remaining Q loki
    int temp_cost;
    for(int i = 0; i < Q; i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        /*if (MST[x-1][y-1]||MST[y-1][x-1]) {                // if edge in MST simply increase by the difference
            int t_ans=ans+w-(mat[y-1][x-1]);
            
            cout<<t_ans<<endl;
            continue;
        }*/
        // If the edge is not in MST.We attempt to add the edge, which creates a cycle. After that, we aim to delete the smallest edge in the cycle formed to get the ideal MST
       
        temp_cost = mat[x-1][y-1];
        //MST[x-1][y-1] = w;
        //MST[y-1][x-1] = w;
        
        mat[x-1][y-1] = w;
        mat[y-1][x-1] = w;
        Dijkstra(mat, N, 0,distance,MST);
        /*min_edge=INT_MAX;
        int * t_parent= new int[N];
        
        for (int i=0;i<N;i++) {
            t_parent[i]=-1
        }
        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                if (MST[i][j]) {
                    int x=find(t_parent,i);
                    int y=find(t_parent,j);
                    if (x==y) {
                        if (min_edge<x) {
                            cout<<ans+x-min_edge<<endl;
                            break;
                        }
                    }
                    else {
                        if (min_edge>mat[i][parent[i]]) {
                            mat[i][parent[i]]=min_edge;
                        }
                        Union(parent,x,y);
                    }
                }
            }*/
            
            
            
        
        mat[x-1][y-1] = temp_cost;
        mat[y-1][x-1] = temp_cost;
    }

    return 0;
}