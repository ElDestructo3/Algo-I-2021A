/********************************

Name: Vishal Ravipati
Roll Number: 20CS10076
HackerRank ID: eldestructojr3
********************************/

#include <iostream>
#include <string>

using namespace std;

typedef struct HashNode {                                        // structure for hashnode
    string key;
    int value;
} HashNode;
 
typedef struct HashTable{                                        // structure for hashtable
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

void initTable(HashTable *table, int size){         // initialising table by creating array and filling with null values 
    table->size = size;
    table->array = new HashNode[size];
    for(int i = 0; i < size; i++){
        table->array[i].key = "";
        table->array[i].value = 0;
    }
}

int search(HashTable *table, string key){           // search if there is a key
    int index = hashFunction(key, table->size);     // finding first place of search
    int flag=index;                                  // storing initial value
    while(table->array[index].key != ""){
        if(table->array[index].key == key){         
            return table->array[index].value;       // return index on match
        }
        index = (index+1)%table->size;              // otherwise linear probing with circular indexing
        if (index == flag){                // if while probing we come back to initial index it means key doesnt exist
            return -1;
        }
        
    }
    
    return -1;                                  
}

int insert(HashTable *table, string key, int value){      // insert in table     
    int index = hashFunction(key, table->size);
    int flag=index;                              
    while(table->array[index].key != ""){                 // finding empty space, starting with hash value
        if(table->array[index].key == key){ 
            table->array[index].value = value;            // updating on match
            return index;
        }
        index = (index+1)%table->size;                    
        if (index == flag){                               // if no spot found table is full so return
            return -1;
        }
    }
    table->array[index].key = key;                        // insert on initial hash value
    table->array[index].value = value;
    return index;
    
}

int deleteKey(HashTable *table, string key){               // delete from table
    int index = hashFunction(key, table->size);
    int flag=index;
    while(table->array[index].key != ""){                  // searching for key
        if(table->array[index].key == key){
            table->array[index].key = "";                  // setting to 0
            table->array[index].value = 0;
            return index;
        }
        index = (index+1)%table->size;
        if (index == flag){
            return -1;                                     // returning if key not found
        }
    }
    return -1;
}

int increaseValue(HashTable *table, string key){           
    int index = hashFunction(key, table->size);
    int flag=index;
    while(table->array[index].key != ""){                  // finding key, then increasing value
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

void printTable(HashTable *table){                         // printing as per pattern
    for(int i = 0; i < table->size; i++){
        cout << "(" <<table->array[i].key << "," << table->array[i].value << ") ";
    }
    cout<<endl;
}

int main() {
    int t;
    cin>>t;
    while(t--){
        int size;
        cin>>size; 
        HashTable *table = new HashTable;
        initTable(table, size);
        int num;
        cin>>num;
        while(num--){
            int value;
            string key,operation;                              // operation for checking which operation to perfrom
            cin>>operation>>key;
            if (operation=="I") {                               // insert operation
                cin>>value;
                insert(table, key, value);
                
            }
            else if (operation=="IV") {                         // increase value operation
                
                increaseValue(table, key);
            }

            else {
                deleteKey(table, key);                           // delete operation
                
            }
            
            
        }
        printTable(table);                                       //print
    }
    
}
