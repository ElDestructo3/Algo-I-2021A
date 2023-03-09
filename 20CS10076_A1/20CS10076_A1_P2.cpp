#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct operatorNode {
    int data;
    struct operatorNode* next;
};
struct operatorStack {
    int size;
    struct operatorNode* top;
};
struct operatorStack* createStack() {
    struct operatorStack* new_stack;
	new_stack=(struct operatorStack*) malloc(1000*sizeof(struct operatorNode));
	new_stack->size=0;
	new_stack->top=NULL;
	return new_stack;
}
bool isEmpty(struct operatorStack* stack) {
	if (stack->top==NULL) {
		return true;
	}
	return false;
}
int peek(struct operatorStack* stack) {
    if (!isEmpty(stack)) {
		return (stack->top)->data;
	}
    return -1;
	
}
int pop(struct operatorStack* stack) {
    int temp=0;
    if (!isEmpty(stack)) {
        temp=(stack->top)->data;
        stack->top=(stack->top)->next;
		stack->size--;
		return temp;
		
	}
    return -1;
}
void push(struct operatorStack* stack, int op) {
	struct operatorNode* element = (struct operatorNode*) malloc(sizeof(struct operatorNode));
	element->data=op;
	element->next=stack->top;
	stack->top=element;
	stack->size++;
}

int isOperand(char ch) {
	return isdigit(ch);
}

int evaluate(const char* rp_exp) {
	cout << rp_exp << endl;
    int num=0;
    
    struct operatorStack* new_stack=createStack();
    for (int i=0;rp_exp[i];i++) {
		if (rp_exp[i]==' ') {
			continue;
		}

        else if (isOperand(rp_exp[i])) {
            int temp=0;
			while (isOperand(rp_exp[i])) {
				temp=temp*10 + (int)(rp_exp[i]-'0');
				i++;
			}
			i--;
			push(new_stack,temp);
        }
		else {
			int num_1=pop(new_stack);
			int num_2=pop(new_stack);
			
			switch (rp_exp[i])
            {
            case '+': push(new_stack, num_2 + num_1); break;
            case '-': push(new_stack, num_2 - num_1); break;
            case '*': push(new_stack, num_2 * num_1); break;
            case '/': push(new_stack, num_2/ num_1); break;
            case '%': push(new_stack, num_2% num_1); break;
            }
			
		}
    }
	
    num=pop(new_stack);
	return num;
}

int main() {
	string line;
	ifstream input_file("20CS10076_A1_P1_output.txt");
	ofstream part_2_output_file("20CS10076_A1_P2_output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			// Second part: Implement evaluate function and associated linked list impl. of stack
			part_2_output_file << evaluate(line.c_str()) << endl;
		}
		input_file.close();
	}
	else cout << "Unable to open file"; 
	part_2_output_file.close();
	
    return 0;
	
}

