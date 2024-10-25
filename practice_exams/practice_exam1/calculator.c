#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist.h"

node* addition(node* num1, node* num2) {
    node* result = NULL;
    int carry = 0; 

    //TODO: Write code to add two numbers represented by num1 and num2

    while (num1 != NULL || num2 != NULL || carry != 0){
        int sum = carry;

        if (num1 != NULL) {   
            sum += num1->v;
            num1 = num1->next;
        }

        if (num2 != NULL) {
            sum += num2->v;
            num2 = num2->next;
        }

        carry = sum / 10; // if sum is greater than 10, carry would be 1:
                          // 18 / 10 --> 1 (not 1.8 because they are both integers)
        sum %= 10; // if sum is greater than 10, then the remainder stays
                   // if sum isn't greater than 10, then sum remains the same
                   // 18 % 10 --> 8
                   // 5 % 10 --> 5


        node * newNode = new_node(sum); 
        if (result == NULL) {
            result = newNode;
        }
        
        prepend(result, newNode);
    }

    return result;
}

node* subtraction(node *num1,node *num2){
    node *result = NULL;
    int borrow = 0;
    //TODO: Write code to subtract num2 from num1

    int difference = 0;
    while (num1 || num2 || borrow) {
        int val1 = 0, val2 = 0;
        // int difference = borrow;
        if (num1) {
            val1 = num1->v;
            num1 = num1->next;
        }

        if (num2) {
            val2 = num2->v;
            num2 = num2->next;
        }


        val1 -= borrow;
        if (val1 < val2) {
            val1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        difference = val1 - val2;

        // difference = val2 - val1;
        // if (difference < 0) {
        //     borrow += 10;
        // } 
        
        // 3 - 5 -> -2 + 10 --> 8
        // 13 - 5 --> 8

        node * newNode = new_node(difference); 
        if (result == NULL) {
            result = newNode;
        }
        
        prepend(result, newNode);
    }
    
    return result;
}


node *remove_leading_zeros(node *num){
    node *temp = num;
    while(temp!=NULL && temp->v == 0){
        node *temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    return temp;
}

int main(int argc,char *argv[]){
    if(argc < 3){
        printf("Usage: ./calculator number1 number2\n");
        exit(0);
    }
    node *num1=NULL,*num2 = NULL;
    node *sum = NULL;
    node *difference = NULL;

    for(int i=0;i<strlen(argv[1]);i++){
        if(!isdigit(argv[1][i])){
            printf("Invalid inputin number1\n");
            exit(0);
        }
        num1 = prepend(num1,new_node(argv[1][i]-'0'));
    }
    for(int i=0;i<strlen(argv[2]);i++){
        if(!isdigit(argv[2][i])){
            printf("Invalid input in number2\n");
            exit(0);
        }
        num2 = prepend(num2,new_node(argv[2][i]-'0'));
    }
    sum = addition(num1,num2);
    difference = subtraction(num1,num2);

    sum = remove_leading_zeros(sum);
    difference = remove_leading_zeros(difference);
    
    print_list(sum);
    print_list(difference);

    delete_list(num1);
    delete_list(num2);
    delete_list(sum);
    delete_list(difference);
    return 0;
}
