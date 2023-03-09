#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <climits>
/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name:Vishal Ravipati
Roll Number: 20CS10076
HackerRank ID: eldestructojr3
********************************/

using namespace std;

int days_in_month(int month) {
    if ((month==1)||(month==3)||(month==5)||(month=7)||(month==8)||(month==10)||(month==12)) {
        return 31;
    }
    if (month==2) {
        return 28;
    }
    return 30;
}

int convert_to_hours(int month, int day, int hour) {
    int days=day-1;
    for (int i=1;i<month;i++) {
        days+=days_in_month(i);
    }
    int hours=days*24+hour;
    return hours;
}



int solve1(int hours,int w,int j, int first_mid,int* dp, int* solve,int* check) {
    if (hours==0) return 0;
    if ((hours-first_mid)%24==0) return -1;
    if ((*check)==0) {
        if (dp[hours-w]!=1e9) {
            return 1+dp[hours-w];
        }
        else {
            dp[hours]=1+solve1(hours-w,w,j,first_mid,dp,solve,check);
            (*check)=1;
            return dp[hours-w];
        }
        
    }
    return 0;
    
}

    
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int s_year=0,s_month=0,s_day=0,s_hour=0,o_year=0,o_month=0,o_day=0,o_hour=0,w=0,j=0;
    cin>>s_year>>s_month>>s_day>>s_hour;
    cin>>o_year>>o_month>>o_day>>o_hour;
    cin>>w;
    cin>>j;
    s_month=-s_month;
    s_day=-s_day;
    o_month=-o_month;
    o_day=-o_day;
    int s_total_hours=convert_to_hours(s_month,s_day,s_hour);
    int o_total_hours=convert_to_hours(o_month,o_day,o_hour);
    //cout<<o_year<<' '<<o_month<<' '<<o_day<<' '<<o_hour;
    int num=0;
    int first_mid=24-s_hour;
    int hours=o_total_hours-s_total_hours;
    
    int size=hours+max(w,j);
    
    int* dp=(int*) malloc(size*sizeof(int));
    int* check=(int*) malloc(size*sizeof(int));
    for (int i=0;i<size;i++) {
        if ((i-first_mid)%24==0) {
            dp[i]=-1;
            
            check[i]=-1;
        }
        else {
            dp[i]=1e9;
            
            check[i]=0;
            
            
        }
    }
    dp[0]=0;
    check[0]=-1;
    for (int i=1;i*w<size;i++) {
        if (dp[i*w]!=-1) {
            dp[i*w]=i;
            check[i*w]=1;
        }
        /*if (i*w-j>0) {
            if (dp[i*w-j]!=-1) {
                if (dp[i*w-j]>1+dp[i*w]) {
                    check[i*w-j]=-1;
                    dp[i*w-j]=1+dp[i*w];
                }
            }
        }*/
        for (int k=1;i*w-k*j>0;k++) {
            if (dp[i*w-k*j]!=-1) {
                if (dp[i*w-k*j]>1+dp[i*w-(k-1)*j]) {
                    check[i*w-k*j]=1;
                    dp[i*w-k*j]=1+dp[i*w-(k-1)*j];
                }
            }
        }
       
        
    }
    
    
    if (dp[hours]==1e9) {
        cout<<0<<endl;
    }
    else {
        num=dp[hours];
        cout<<num<<endl;
        int i=0;
        while (true) {
            
            if (dp[i+w]==dp[i]+1&&(i+w<size)) {
                cout<<'w'<<endl;
                i+=w;
            }
            else {
                cout<<'a'<<endl;
                i-=j;
            }
            if (i==hours) {
                break;
            }
        }
    } 
    
    
    return 0;
}

 