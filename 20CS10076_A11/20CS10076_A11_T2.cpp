/********************************

Name: Vishal Ravipati
Roll Number: 20CS10076
HackerRank ID: eldestructojr3
********************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
// using same functions from part1, hence comments only on changed parts
typedef struct HashNode {
    string key;
    int value;
    int polarity;                                        // adding a polarity term for checking magnetic influence
} HashNode;

typedef struct HashTable{
    int size;
    HashNode *array;
} HashTable;

int hashFunction(string key, int size){                          // applying hash function by polynomial hashing
    int p=31;             
    long long sum = 0;                                           // taking long long to prevent overflow
    long long pow=1;
    for(int i = 0;i<key.length();i++){
        sum += (key[key.length()-i-1]-'a'+1)*pow;               // taking remainders at each step to reduce calculations
        sum%=size;
        pow=(pow*p);
        
        
    }
    return (int) (sum+size) % size;
}

void initTable(HashTable *table, int size){
    table->size = size;
    table->array = new HashNode[size];
    for(int i = 0; i < size; i++){
        table->array[i].key = "";
        table->array[i].value = 0;
        table->array[i].polarity = 0;                            // making polarity 0
    }
}

int search(HashTable *table, string key){
    int index = hashFunction(key, table->size);
    while(table->array[index].key != ""){
        if(table->array[index].key == key){
            return table->array[index].value;
        }
        index = (index+1)%table->size;                           
    }
    return -1;
}

int insert(HashTable *table, string key, int value){
    int index = hashFunction(key, table->size);
    int flag=index;
    while(table->array[index].key != ""){
        if(table->array[index].key == key){
            table->array[index].value = value;
            return index;
        }
        index = (index+1)%table->size;
        if (index == flag){
            return -1;
        }
    }
    table->array[index].key = key;
    table->array[index].value = value;
    table->array[index].polarity = 0;                                  // setting polarity 0
    return index;
}

int deleteKey(HashTable *table, string key){
    int index = hashFunction(key, table->size);
    int flag=index;
    while(table->array[index].key != ""){
        if(table->array[index].key == key){
            table->array[index].key = "";
            table->array[index].value = 0;
            table->array[index].polarity = 0;                         // setting polarity 0
            return index;
        }
        index = (index+1)%table->size;
        if (index == flag){
            return -1;
        }
    }
    return -1;
}

int increaseValue(HashTable *table, string key){
    int index = hashFunction(key, table->size);
    int flag=index;
    while(table->array[index].key != ""){
        if(table->array[index].key == key){
            table->array[index].value++;
            return index;
        }
        index = (index+1)%table->size;
        if (index == flag){
            return -1;
        }
    }
    return -1;
}

bool isVowel(char c){                                                           // checks if char is vowel
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return true;
    }
    return false;
}

bool isSuperior(string key) {                                           // checks if string is superior using isVowel
    for(int i = 0; i < key.length(); i++){
        if(isVowel(key[i])){
            return true;
        }
    }
    return false;
}
// the array of strings will store ith magnet at ith index
int createArray(HashTable *table, int n, int I,string* arr){
        
    int i=0;                                                 
    
    while(i<n) {                                            // running through number of magnets
        int index=-1,max_value=0;
        for (int j=0;j<table->size;j++) {                  // greedily searching for magnets with maximum value, to place earlier. Also using polarity to verify if magnet can be placed, polarity=0 means magnet is eligible for placement
            if (table->array[j].value>max_value && table->array[j].polarity==0) {
                index=j;
                max_value=table->array[j].value;             
            }
        }
        if (index==-1) {                                 // if no eleigible magnet is found, arrangement is impossible
            return -1;
        }
        arr[i++]=table->array[index].key;                // updating array with key
        table->array[index].value--;                     // updating number of magnets
        if (table->array[index].value==0) {
            deleteKey(table,table->array[index].key);     // deleting entry if magnets become 0
        }
        table->array[index].polarity=I;
        for (int j=0;j<table->size;j++) {
            if (table->array[j].polarity!=0) {
                table->array[j].polarity--;               // as one magnet has been placed, we have to update polarity values for other magnets
            }
        }

    }
    return 0;
}

void print(string* arr, int n,ofstream &out){                           // printing strings of array based on the pattern
    out<< arr[0];
    for(int i = 1; i < n; i++){
        if (isSuperior(arr[i])&& isSuperior(arr[i-1])) {     // both superior-> hash
            out<<" # "<<arr[i];
        }
        else if (isSuperior(arr[i])&& !isSuperior(arr[i-1])) { // one superior -> | 
            out<<" | "<<arr[i];
        }
        else if (!isSuperior(arr[i])&& isSuperior(arr[i-1])) {
            out<<" | "<<arr[i];
        }
        else {                                                // both inferior -> empty space
            out<<" "<<arr[i];
        }
    }
    out<<endl;
}


int main() {
    ifstream in("input_P2.txt");
    ofstream out("20CS10076_O11_P2.txt");
    int t;                                                    // reading input
    in>>t;
    while(t--) {
        int n,I;
        in>>n;
        in>>I;
        HashTable *table = new HashTable;
        initTable(table, 1000);                               // creating table of size 1000
        for (int i=0;i<n;i++) {
            string key;
            in>>key;
            if (search(table, key) == -1) {                 // if input key doesnt exist insert in table
                insert(table, key, 1);
            }
            else {
                increaseValue(table, key);                  // else increase magnet value
            }
        }
        
        string* arr = new string[n];                       // creating array for storing strings
        if (createArray(table, n, I, arr)==0) {
            print(arr, n,out);                            // if creating array is possible then print the array
        }
        else {
            out<<"-1"<<endl;                         // otherwise print -1
        }

    }
}