#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


/*
Name: Vishal Ravipati
Roll Number: 20CS10076
Hackerrank ID: eldestructojr3
*/

int main() {
    long long t=0;
    cin>>t;
    while (t--) {
        long long n,x;    
        cin>>n>>x;
        long long * arr= new long long[n];
        for (long long i=0;i<n;i++) {
            cin>>arr[i];
        }
                
        long long health=x;
        long long count=0;                                   // count stores the number of poisons taken
        long long min=0;                                     // to store the most negative value and index
        long long min_index=0;
        long long * visited = new long long[n];               // array to store the poisons taken
        for (int i=0;i<n;i++) {
            visited[i]=0;
        }
        for (long long i=0;i<n;i++) {
            if (arr[i]<min) {                                // storing the minimum value and its index encountered till index i
                min=arr[i];
                min_index=i;
            }
            health+=arr[i];                                  // take the poison and mark visited
            count++;
            visited[i]=1;
            if (health<=0) {                                 // if health becomes 0 or less remove the poison with most negative effect
                count--;
                
                health-=min;
                visited[min_index]=0;
                min =0;
                for (long long j=0;j<=i;j++) {               // finding the most negative poison visited without the removed poison
                    if (arr[j]<min&&visited[j]==1) {
                        min=arr[j];
                        min_index=j;
                    }
                }
            }
        }
        cout<<count<<endl;                                   
        
    }
}