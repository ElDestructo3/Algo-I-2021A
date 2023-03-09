#include <iostream>
#include <string.h>
#include <cstring>
#include <stdlib.h>
using namespace std;
#define MAX 1000000000;

/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name: Vishal Ravipati
Roll Number: 20CS10076
HackerRank ID: eldestructojr3
********************************/

// your code here

typedef struct {
char * color ;
int npetals;
int leaves;
int radius;
int height;
} Flower;

int main()
{
    int t=0;
    cin>>t;
         
    Flower* dictionary;                               // creating an array of structures for storing input
    dictionary=(Flower*) malloc(t*sizeof(Flower));    // allocating memory to array      
    for (int i=0;i<t;i++) {
        
        char str[MAX];                                // read input as a whole
        cin>>str;
        char temp[MAX]; 
        int num=0,temp_num=0;                         // will hold place of comma
        if (str[0]=='w') {
            dictionary[i].color= (char*) "white"; 
            num=6;                                    // move num to after comma
            
        }
        else {
            dictionary[i].color= (char*) "yellow";
            num=7;
        }
        while (str[num]!=',') {
            temp[temp_num++]=str[num++];              // copy part between commas into a temporary string
        }
        num++;                                        // move num to after comma
        temp[temp_num]='\0';
        temp_num=0;
        dictionary[i].npetals=atoi(temp);             //convert string to integer
        
        while (str[num]!=',') {
            temp[temp_num++]=str[num++];
        }
        num++;
        temp[temp_num]='\0';
        temp_num=0;
        dictionary[i].leaves=atoi(temp);
        
        while (str[num]!=',') {
            temp[temp_num++]=str[num++];
        }
        num++;
        temp[temp_num]='\0';
        temp_num=0;
        dictionary[i].radius=atoi(temp);
        
        while (str[num]!=',') {
            temp[temp_num++]=str[num++];
        }
        num++;
        temp[temp_num]='\0';
        temp_num=0;
        dictionary[i].height=atoi(temp);
        
    }
    for (int i=0;i<t;i++) {                           //bubble sort dictionary on the basis of integer parameters
        for (int j=i+1;j<t;j++) {
            
            if (dictionary[i].npetals>dictionary[j].npetals) {
                int temp_np=dictionary[i].npetals;
                dictionary[i].npetals=dictionary[j].npetals;
                dictionary[j].npetals=temp_np;
            }
            else if (dictionary[i].leaves>dictionary[j].leaves) {
                int temp_np=dictionary[i].leaves;
                dictionary[i].leaves=dictionary[j].leaves;
                dictionary[j].leaves=temp_np;
            }
            else if (dictionary[i].radius>dictionary[j].radius) {
                int temp_r=dictionary[i].radius;
                dictionary[i].radius=dictionary[j].radius;
                dictionary[j].radius=temp_r;
            }
            else if (dictionary[i].height>dictionary[j].height) {
                int temp_h=dictionary[i].height;
                dictionary[i].height=dictionary[j].height;
                dictionary[j].height=temp_h;
            }
        }
    }
    int k=0;
    for (int i=0;i<t;i++) {     // in sorted dictionary, flowers with same integer parameters will be adjacent so i+1
        if ((dictionary[i].npetals==dictionary[i+1].npetals)&&(dictionary[i].leaves==dictionary[i+1].leaves)&&(dictionary[i].radius==dictionary[i+1].radius)&&(dictionary[i].height==dictionary[i+1].height)) {
            if ((dictionary[i].color[0]=='w')&&(dictionary[i+1].color=='y')) { // checking which one is white flower
                cout<<dictionary[i].color<<','<<dictionary[i].npetals<<','<<dictionary[i].leaves<<','<<dictionary[i].radius<<','<<dictionary[i].height<<endl;
                k=1;       // setting k to 1 if atleast one flower related to princess is found
            }
            else if ((dictionary[i+1].color[0]=='w')&&(dictionary[i].color=='y')) {
                cout<<dictionary[i+1].color<<','<<dictionary[i+1].npetals<<','<<dictionary[i+1].leaves<<','<<dictionary[i+1].radius<<','<<dictionary[i+1].height<<endl;
                k=1;
            }
        }
    }
    if (k==0) {                                       // if no match is found, k is 0, hence outputting RIP
        cout<<"RIP"<<endl;
    }
    return 0;
}