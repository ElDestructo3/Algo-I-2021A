/********************************
IMPORTANT:
Your submission will not be graded if this is not correctly filled.

Name: Vishal Ravipati
Roll Number: 20CS10076
HackerRank ID: eldestructojr3
********************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <string.h>
#include <stdlib.h>

using namespace std;

// For Queue Size
#define SIZE 5000
// A tree node
struct node
{
    int data;
    struct node *right,*left;
};
 
// A queue node
struct Queue
{
    int front, rear;
    int size;
    struct node* *array;
};
 
// A utility function to create a new tree node
struct node* newNode(int data)
{
    struct node* temp = (struct node*) malloc(sizeof( struct node ));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
 
// A utility function to create a new Queue
struct Queue* createQueue(int size)
{
    struct Queue* queue = (struct Queue*) malloc(sizeof( struct Queue ));
 
    queue->front = queue->rear = -1;
    queue->size = size;
 
    queue->array = (struct node**) malloc
                   (queue->size * sizeof( struct node* ));
 
    int i;
    for (i = 0; i < size; ++i)
        queue->array[i] = NULL;
 
    return queue;
}
 
// Standard Queue Functions
int isEmpty(struct Queue* queue)
{
    return queue->front == -1;
}
 
int isFull(struct Queue* queue)
{  return queue->rear == queue->size - 1; }
 
int hasOnlyOneItem(struct Queue* queue)
{  return queue->front == queue->rear;  }
 
void Enqueue(struct node *root, struct Queue* queue)
{
    if (isFull(queue))
        return;
 
    queue->array[++queue->rear] = root;
 
    if (isEmpty(queue))
        ++queue->front;
}
 
struct node* Dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
 
    struct node* temp = queue->array[queue->front];
 
    if (hasOnlyOneItem(queue))
        queue->front = queue->rear = -1;
    else
        ++queue->front;
 
    return temp;
}
 
struct node* getFront(struct Queue* queue)
{  return queue->array[queue->front]; }
 
// A utility function to check if a tree node
// has both left and right children
int hasBothChild(struct node* temp)
{
    return temp && temp->left && temp->right;
}
 
// Function to insert a new node in complete binary tree
void insert(struct node **root, int data, struct Queue* queue)
{
    // Create a new node for given data
    struct node *temp = newNode(data);

    // If the tree is empty, initialize the root with new node.
    if (!*root)
        *root = temp;
 
    else
    {
        // get the front node of the queue.
        struct node* front;
        front = getFront(queue);
        while (front->data == -1) {
            Dequeue(queue);
            front = getFront(queue);
        } 
        // If the left child of this front node doesnt exist, set the
        // left child as the new node
        if (!front->left)
            front->left = temp;
 
        // If the right child of this front node doesnt exist, set the
        // right child as the new node
        else if (!front->right)
            front->right = temp;
 
        // If the front node has both the left child and right child,
        // Dequeue() it.
        if (hasBothChild(front)){
            if (front->left->data == -1 ) {
                front->left = NULL;
            }
            if (front->right->data == -1 ) {
                front->right = NULL;
            }
            Dequeue(queue);
        }
    }
 
    // Enqueue() the new node for later insertions
    Enqueue(temp, queue);
}




void dfs(struct node* current, struct node* parent,int* covered,int* size,int* sensors) {
    if (current==NULL) {
        return;
    }

    dfs(current->left,current,covered,size,sensors);
    dfs(current->right,current,covered,size,sensors);
    
    int currentCovered=0;
    int leftChildCovered=0;
    int rightChildCovered=0;
    int parentCovered=0;
    
    for (int i=0;i<*size;i++) {
        if (current->data==covered[i]) {
            currentCovered=1;
            
        }
        if (current->left!=NULL) {
            if(current->left->data==covered[i]){
                leftChildCovered=1;
            }
        }
        else {
            leftChildCovered=1;
        }
        if (current->right!=NULL) {
            if(current->right->data==covered[i]){
                rightChildCovered=1;
            }
        }
        else {
            rightChildCovered=1;
        }
        if (parent!=NULL) {
            if(parent->data==covered[i]){
                parentCovered=1;
            }
        }
        
    }
    if ((parent==NULL)&&(currentCovered==0)) {
        (*sensors)++;
        
      
        covered[(*size)++]=current->data;
        
        
        
        if (current->left!=NULL) {
            covered[(*size)++]=current->left->data;
            
            
           
        }
        if (current->right!=NULL) {
            covered[(*size)++]=current->right->data;
            
            
            
        }
        if (parent!=NULL) {
            covered[(*size)++]=parent->data;
            
            
            
            
        }
        return;
    }
    else if (leftChildCovered==0||rightChildCovered==0) {
        (*sensors)++;
        
      
        covered[(*size)++]=current->data;
        
        
        
        if (current->left!=NULL) {
            covered[(*size)++]=current->left->data;
            
            
           
        }
        if (current->right!=NULL) {
            covered[(*size)++]=current->right->data;
            
            
            
        }
        if (parent!=NULL) {
            covered[(*size)++]=parent->data;
            
            
            
            
        }
        return;
    }
        
    
}

int minSensorRequired(struct node* root,int* covered,int* size, int* sensors) {
    dfs(root,NULL,covered,size,sensors);
    return (*sensors);
    
}

int main() {
    // Read the inputs from stdin and print output to stdout.
    // For creating the tree, initialize a struct node called root. 
    // struct node* root = NULL;
    // struct Queue* queue = createQueue(SIZE);
    // insert each element of array into tree by using this: insert(&root, array[i], queue)
    int n;
    cin>>n;
    for (int i=0;i<n;i++) {
        int tree_size;
        struct node* root=NULL;
        struct Queue* queue = createQueue(SIZE);
        cin>>tree_size;
        int *tree_arr= (int*) malloc(tree_size*sizeof(int));
        for (int i=0;i<tree_size;i++) {
            cin>>tree_arr[i];
            insert(&root,tree_arr[i],queue);
        }
        
        int covered[100000]={0};
        int sensors=0;
        int size=0;
        
        minSensorRequired(root,covered,&size,&sensors);
        cout<<sensors<<endl;
        
        
    }
    return 0;
}