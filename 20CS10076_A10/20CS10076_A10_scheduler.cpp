#include <iostream>

using namespace std;

/*
Name: Vishal Ravipati
Roll Number: 20CS10076
Hackerrank ID: eldestructojr3
*/

typedef struct {                        // defining structure for each friend
    int id;
    int cost;
    int lectures;
    int start;
} person;

bool largerPriority(person p1, person p2) {             // assigning greater priority to p1 based on cost and id
    if (p1.cost!=p2.cost) return p1.cost>p2.cost;
    return p1.id<p2.id;
}

typedef struct {                         // defining heap structure
    person personList[100000];
    int heapsize;
} heap;
// functions for computing parent, left and right of node in heap
int parent(int index) {                  
    return (index-1)/2 ;
}

int left(int index) {
    return 2*index+1;
}

int right (int index) {
    return 2*index+2;
}
// swapping two people
void swapPerson(person& p1, person& p2) {
    person temp=p1;
    p1=p2;
    p2=temp;
}
// applying max heapify procedure
void maxHeapify(heap* maxHeap, int index) {
    int left_idx= left(index);
    int right_idx= right(index);
    int largest= index;
    if (left_idx<maxHeap->heapsize&& largerPriority(maxHeap->personList[left_idx],maxHeap->personList[largest])) {
        largest=left_idx;
    }
    if (right_idx<maxHeap->heapsize&& largerPriority(maxHeap->personList[right_idx],maxHeap->personList[largest])) {
        largest=right_idx;
    }
    if (largest!=index) {
        swap(maxHeap->personList[largest],maxHeap->personList[index]);
        maxHeapify(maxHeap,largest);
    }
} 
// inserting person p into maxheap maintaining max heap property
void insertMaxHeap(heap* maxHeap, person p) {
    (maxHeap->heapsize)++;
    int temp=(maxHeap->heapsize)-1;
    maxHeap->personList[temp]=p;
    
    while(temp!=0 && largerPriority(maxHeap->personList[temp],maxHeap->personList[parent(temp)])){
        swapPerson(maxHeap->personList[temp],maxHeap->personList[parent(temp)]);
        temp=parent(temp);
    }
}

// extracting person with max priority
int extractMax(heap* maxHeap, person* p) {
    if (maxHeap->heapsize<1) return -1;
    person temp=maxHeap->personList[0];
    
    maxHeap->personList[0]=maxHeap->personList[maxHeap->heapsize-1];
    (maxHeap->heapsize)--;
    maxHeapify(maxHeap,0);
    *p=temp;
    return 0;

}

void merge(person* personList, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    person L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = personList[l + i];
    for (j = 0; j < n2; j++)
        R[j] = personList[m + 1 + j];
  
    
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i].start <= R[j].start) {
            personList[k] = L[i];
            i++;
        }
        else {
            personList[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        personList[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        personList[k] = R[j];
        j++;
        k++;
    }
}
  

void mergeSort(person* personList, int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(personList, l, m);
        mergeSort(personList, m + 1, r);
  
        merge(personList, l, m, r);
    }
}

// scheduling activities
void scheduler(person* personList, int N, int D) {
    int workshop_days=0;                   // tracking progress of days of lecture
    int* worshopID= new int[D];            // storing the id of friends takung lectures
    
    int t_cost=0;
    for (int i=0;i<N;i++) {
        t_cost+=personList[i].cost*(personList[i].lectures);      // finding cost if no one took lecture
    }
    heap* maxHeap= new heap;
    maxHeap->heapsize=0;
    while (workshop_days<D) {                                   // running loop for each day
        for (int i=0;i<N;i++) {
            if (personList[i].start==workshop_days+1) {         // adding friends with start time equal to day of workshop into heap
                insertMaxHeap(maxHeap,personList[i]);
            }
            
        }
        
        person temp;                                              // storing max priority person
        if (extractMax(maxHeap,&temp)==0) {                  
            worshopID[workshop_days]=temp.id;                     // storing id of the person taking lecture
            t_cost-=temp.cost;                                    // subtracting cost as lecture is taken
            temp.lectures--;                                      // reducing lectures
            if (temp.lectures!=0) insertMaxHeap(maxHeap,temp);    // if lectures are pending return to heap
        }
        workshop_days++;
        
    }
    cout<<t_cost<<endl;                                           // printing cost and id
    for (int i=0;i<D;i++) {
        cout<<worshopID[i]<<" ";
    }

}

int main() {
    int N,D;
    cin>>N>>D;
    person* personList= new person[N];                   // alloting memory for stroing persons
    for (int i=0;i<N;i++) {
        cin>>personList[i].id>>personList[i].start>>personList[i].lectures>>personList[i].cost;        //reading input
    }
    mergeSort(personList,0,N-1);                             // sorting based on start time
    scheduler(personList,N,D);                            // scheduling workshop
  
}