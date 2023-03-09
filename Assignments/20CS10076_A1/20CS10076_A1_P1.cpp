#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct operatorNode {
    char data;
    struct operatorNode* next;
};
struct operatorStack {
    int size;
    struct operatorNode* top;
};
struct operatorStack* createStack() {
    struct operatorStack* new_stack;
	new_stack=(struct operatorStack*) malloc(1000*sizeof(struct operatorNode*));
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
char peek(struct operatorStack* stack) {
    if (!isEmpty(stack)) {
		return (stack->top)->data;
	}
    return '~';
	
}
char pop(struct operatorStack* stack) {
    char temp=' ';
    if (!isEmpty(stack)) {
        temp=(stack->top)->data;
        stack->top=(stack->top)->next;
		stack->size--;
		return temp;
		
	}
    return '~';
}
void push(struct operatorStack* stack, char op) {
	struct operatorNode* element = (struct operatorNode*) malloc(sizeof(struct operatorNode));
	element->data=op;
	element->next=stack->top;
	stack->top=element;
	stack->size++;
}

int isOperand(char ch) {
	
	return isdigit(ch);
}

int precedence(char op1,char op2) {
	int value_1=0,value_2=0;
    if ((op1== '/')||(op1=='%')||(op1=='*')) {
	    value_1=1;
	}
	if ((op2== '/')||(op2=='%')||(op2=='*')) {
	    value_2=1;
	}
	
	return value_1>=value_2;
}




char* convert(const char *exp,char *output_string) {
	
    struct operatorStack* new_stack= createStack();
	
    int j=0;
    for (int i=0;exp[i];i++) {
        if (isOperand(exp[i])||(exp[i]==' ')) {
            output_string[j++]=exp[i];
        }
        else if (exp[i]=='(') {
            push(new_stack,'('); 
			i++;  
        }
        
		else if (exp[i]==')') {
            while ((peek(new_stack)!='(')&&(!isEmpty(new_stack))) {
                output_string[j++]=pop(new_stack);
            }
            pop(new_stack); //discard (
        }
        else {
            while(precedence(peek(new_stack),exp[i])&&(!isEmpty(new_stack))&&(peek(new_stack)!='(')) {
                output_string[j++]=pop(new_stack);
            }
            push(new_stack,exp[i]);
			
        }
           
        
    }
    while (!isEmpty(new_stack)) {
		output_string[j++]=' ';
        output_string[j++]=pop(new_stack);
    }
    output_string[j++]='\0';
	cout << exp << endl;
	    
	return output_string;
}

int main() {
	string line;
	ifstream input_file("input.txt");
	ofstream part_1_output_file("20CS10076_A1_P1_output.txt");
	char output_string[1000] = {'\0'};
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			// First part: Implement convert function and associated linked list impl. of stack 
			char* rp_exp = convert(line.c_str(),output_string);
			part_1_output_file << rp_exp << endl;
		}
		input_file.close();
	}
	else cout << "Unable to open file"; 
	part_1_output_file.close();
    
	return 0;
}

