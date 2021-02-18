//
//  main.c
//  StackWork
//
//  Created by Gavin Tynan on 1/29/20.
//  Copyright © 2020 Gavin Tynan. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int choice;
    char exp[SIZE], c, valid;
    stack myStack;
    
    initialize(&myStack);
    while(1) {
        valid = 1;
        printf("1Enter Expression. 2Exit. Enter Choice");
        scanf("%d", &choice);
        if(choice == 2) {
            break;
            
        }
        else if(choice == 1) {
            printf("Enter Expression");
            scanf(" %[^\n]s", exp);
            printf("your exp,: %s", exp);
            for(int i = 0; exp[i] != '\0'; i++) {
                if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
                    push(&myStack, exp[i]);
                
                
                else if(exp[i] == ')') {
                    c = pop(&myStack);
                    if(c == 'I' || c != '(') {
                        valid = 'I'
                        printf("Invalid at %d", i);
                        break;
                    }//inner if
                }//outer else
                /*else if(exp[i] == '}') {
                    c = pop(&myStack);
                    if(c == 'I' || c != '{') {
                        valid = 'I'
                        printf("Invalid at %d", i);
                        break;
                    }//inner if
                }//outer else*/
                
                else if(exp[i] == ']') {
                    c = pop(&myStack);
                    if(c == 'I' || c != '[') {
                        valid = 'I'
                        printf("Invalid at %d", i);
                        break;
                    }//inner if
                }//outer else
            }
        }
    }
}
    return 0;
}
