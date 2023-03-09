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
// level function computes level of the node where they meet and also stores the path till the node
int level(int data,struct node *root,int *arr,int *num) {      
    int level=0;
    while (root->data!=data) {
        arr[(*num)++]=root->data;
        
        level++;
        if (root->data>data) {
            root=root->left;
        }
        else {
            root=root->right;
        }
        
    }
    
    arr[(*num)++]=root->data;
    return level;
}
// damage_level function computes the sum of damages at a given level
int damage_level(int level, struct node *root) {
    
    
    if (level==0){
        return root->data;
    }
    int left_damage=0,right_damage=0;
    if (root->left) {
        left_damage=damage_level(level-1,root->left);
    }
    if (root->right) {
        right_damage=damage_level(level-1,root->right);
    }
    return left_damage+right_damage;
    
    
}
// returns damage level of the node where luke and leia meet
int lowest_meet_damage(struct node* root,int luke, int leia) {
    
    while (root!=NULL) {
        if (root->data>luke && root->data>leia) {
            root=root->left;
        }
        else if (root->data<leia && root->data<luke) {
            root=root->right;
        }
        else {
            break;
        }
    }
    return root->data;
}
// checks whether luke and leia nodes exist in the tree
int search(struct node* root, int data) {
    if (root==NULL) {
        return 0;
    }
    if (root->data==data) {
        return 1;
    } 
    if (root->data<data) {
        return search(root->right,data);
    
    }
    return search(root->left,data);
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
        int luke,leia,threshold;
        cin>>luke>>leia>>threshold;
        if ((!search(root,luke))||(!search(root,leia))) {   // output result in case node not in tree
            cout<<"Case #"<<i+1<<": -1"<<endl;
            continue;
        }
        int meet_damage=lowest_meet_damage(root,luke,leia);   
        int path[100]={0}; 
        int num=0;                                         // path and num for storing path through bst
        int meet_level=level(meet_damage,root,path,&num);
        int final_damage=0;
        int final_meet_level=meet_level;
        int flag=0;
        int total_damage=damage_level(final_meet_level,root);
        
        while(final_meet_level>=0) {                      // loop checks threshold condition
            if (damage_level(final_meet_level,root)<threshold) {
                flag=1;                                   // if condition is satisfied
                
                final_damage=path[final_meet_level];      // compute damage of node where luke and leia meet
                
                break;
            }
            final_meet_level--;                           // checks higher level
            
        }
        
        if (flag==1) {
            cout<<"Case #"<<i+1<<": "<<meet_damage<<" "<<meet_level<<" "<<total_damage<<" Escaped!"<<" "<<final_damage<<endl;
        }
        else {
            cout<<"Case #"<<i+1<<": "<<meet_damage<<" "<<meet_level<<" "<<total_damage<<" Trapped!"<<endl;
        }
        
        
    }
    return 0;
}