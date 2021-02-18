//
//  main.c
//  queue_lesson
//
//  Created by Gavin Tynan on 1/30/20.
//  Copyright © 2020 Gavin Tynan. All rights reserved.
//

#include <stdio.h>
#define INIT_SIZE 10

struct queue {
    int* elements;
    int front;
    int numElements;
    int queueSize;
};

void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
int peek(struct queue* qPtr);

int main(int argc, const char * argv[]) {

    int i;
    
    return 0;
}

void init(struct queue* qPtr) {
    
}
