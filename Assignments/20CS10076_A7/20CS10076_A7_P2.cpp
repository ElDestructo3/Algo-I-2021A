#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <climits>
 
using namespace std;
/*
Name: Vishal Ravipati
Roll Number: 20CS10076
Hackerrank ID: eldestructojr3
*/

long long temp_max(long long a, long long b) {
    if (a>b) return a;
    return b;
}

long long temp_min(long long a, long long b) {
    if (a>b) return b;
    return a;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    long long t;
    cin>>t;
    while (t--) {
        
        long long x,n,k;
        
        
        cin>>n>>x>>k;
        long long arr[n];
        for (long long i=0;i<n;i++) {
            cin>>arr[i];
        }
        
        long long defend[n];
        for (long long i=0;i<n;i++) {
            defend[i]=0;
            for (long long j=temp_max(0,i-k);j<=temp_min(i+k,n-1);j++) {
                defend[i]+=arr[j];                  // generating battlement array
            }
        }

        long long min_val=LLONG_MAX;
        for (long long i=0;i<n;i++) {
            if (defend[i]<min_val) {
                min_val=defend[i];                  // save min_value
            }
        }
 // setting up binary search between possible values
 // min value is if the calculated minimum doesnt change, max value is if all x changes happen to min element                
        long long right= min_val+x;
        long long left=min_val;
        long long ans= min_val;
        
        while(left<=right) {
            long long temp[n];                      // creating copy of battalian array for use during loop
            for (long long i=0;i<n;i++) {
                temp[i]=defend[i];
            }
            long long mid= left+ (right-left)/2 ;   // assuming that middle value is the answer
            
            long long num=0;                  // num stores the number of changes needed to obtain minimum value of mid
            for (long long i=0;i<n;i++) {
                if (temp[i]<mid) {
                    
                    num+=mid-temp[i];
                    long long count=mid-temp[i];
                    for (long long j=i+1;j<=temp_min(i+2*k,n-1);j++) { // move to farthest point to make changes
                        temp[j]+=(count);
                        
                    }
                    temp[i]=mid;
                }
            }
            
            if (num>x) {             // if number of changes is more than max possible, than max minimum value is lower
                right= mid-1; 
            }
            else {                   // otherwise save mid as answer and check if a higher minimum value is possible
                ans=mid;
                left=mid+1;
            }
            
        }
        cout<<ans<<endl;
    }
    return 0;
}