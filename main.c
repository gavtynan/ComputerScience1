//
//  main.c
//  finalterm_assignment_1
//
//  Created by Gavin Tynan on 3/13/20.
//  Copyright © 2020 Gavin Tynan. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Covid19{
    int x;
    int y;
};

struct Covid19* ReadData(FILE * fpIn, int *x1, int *y1, int *k, int *Q);
struct Covid19* FilterData(struct Covid19* Data, int x1, int y1, int k, int *Q);
void merge(struct Covid19* Data, int l, int m, int k);
void mergeSort(struct Covid19* Data, int l, int k);
int binarySearch(struct Covid19* Data, int x, int y, int Q);
int SearchPhase(struct Covid19* Data, int Q);
void printArr(struct Covid19* Data, int size, FILE * fpOut);

int main(){
    FILE * fpIn;
    FILE * fpOut;
    struct Covid19* Data;
    int x1;
    int y1;
    int k;
    int Q;
    
    fpIn = fopen("in.txt", "r");
    fpOut = fopen("out.txt", "w");
    Data = ReadData(fpIn, &x1, &y1, &k, &Q);
    Data = FilterData(Data, x1, y1, k, &Q);
    mergeSort(Data, 0, Q-1);
    printArr(Data, Q, fpOut);
    fclose(fpIn);
    fclose(fpOut);
    SearchPhase(Data, Q);
    
    return 0;
} //end main

struct Covid19* ReadData(FILE *fpIn, int *x1, int *y1, int *k, int *Q) {
    fscanf(fpIn, "%d", x1);
    fscanf(fpIn, "%d", y1);
    fscanf(fpIn, "%d", k);
    fscanf(fpIn, "%d", Q);
    
    struct Covid19* Data = (struct Covid19*) malloc(*Q * sizeof(struct Covid19));
    
    for(int i = 0; i < *Q; i++) {
        fscanf(fpIn, "%d", &Data[i].x);
        fscanf(fpIn, "%d", &Data[i].y);
    }//end for
    return Data;
}//end ReadData

void mergeSort(struct Covid19* Data, int l, int k) {
    
    if (l < k) {
        
        int m = (l+k)/2; // Same as (l+k)/2 butt no overflow
        mergeSort(Data, l, m); // Time to sort both sides
        mergeSort(Data, m+1, k);
        
        //printf("TestAAA l=%d k=%d m=%d\n", l, k, m);
        
        merge(Data, l, m, k);
    }//end if
}//end merge

void printArr(struct Covid19* Data, int size, FILE * fpOut) {
    
    for (int i=0; i < size; i++) {
        fprintf(fpOut, "%d %d\n", Data[i].x, Data[i].y);
    }//end for
}//end printArr

struct Covid19* FilterData(struct Covid19* Data, int x1, int y1, int k, int *Q) {
    
    int j = 0;
    int filter = 0;
    int filterSize;
    
    for (int i = 0; i < *Q; i++) {
        
        if(pow(Data[i].x - x1, 2) + pow(Data[i].y-y1, 2) > pow(k,2))
            filter++;
    }//end for
    
    filterSize = *Q - filter;
    
    struct Covid19* Corona = (struct Covid19*)malloc(filterSize * sizeof(struct Covid19));
    
    for(int i = 0; i < *Q; i++) {
        
        if(pow(Data[i].x - x1, 2) + pow(Data[i].y-y1, 2) <= pow(k,2)) {
            
            Corona[j].x = Data[i].x;
            Corona[j].y = Data[i].y;
            j++;
        }//end if
    }//end for
    *Q = filterSize;
    return Corona;
}//end FilterData

void merge(struct Covid19* Data, int l, int m, int k) {
    
    int i;
    int j;
    int q;
    int temp1 = m - l + 1;
    int temp2 = k - m;
    
    struct Covid19* LeftSide = (struct Covid19*) malloc(temp1 * sizeof(struct Covid19));//creating temp arrays
    struct Covid19* RightSide = (struct Covid19*) malloc(temp2 * sizeof(struct Covid19));//creating temp arrays
    
    for (i = 0; i < temp1; i++) {// Copying info into temp1&2 arrays L[] and R[]
        LeftSide[i] = Data[l + i];
    }//end for
    
    for (j = 0; j < temp2; j++) {
        RightSide[j] = Data[m + 1+ j];
    }//end for
    
    //first index's thingys?
    i = 0;
    j = 0;
    q = l;
    
    while (i < temp1 && j < temp2) {
        if(LeftSide[i].x != RightSide[j].x) {
            if (LeftSide[i].x <= RightSide[j].x) {
                Data[q] = LeftSide[i];
                i++;
            }//end if
            else {
                Data[q] = RightSide[j];
                j++;
            }//end else
        }//end if
        else if(LeftSide[i].x == RightSide[j].x) {
            if (LeftSide[i].y <= RightSide[j].y) {
                Data[q] = LeftSide[i];
                i++;
            }//end if
            else {
                Data[q] = RightSide[j];
                j++;
            }//end else
        }//end else if
        q++;
    }//end big while
    //coping the left over elements of RightSide and LeftSide
    while (i < temp1) {
        Data[q] = LeftSide[i];
        i++;
        q++;
    }//end while
    
    while (j < temp2) {
        Data[q] = RightSide[j];
        j++;
        q++;
    }//end while
}//end merge

int binarySearch(struct Covid19* Data, int x, int y, int Q) {
    int l = 0;
    int h = Q - 1;
    int j = 0;
    int k = Q - 1;
    int mid;
    int mid2;
    while (l <= h) {
        mid = (l + h) / 2;
        // Check if item is present at mid
        if ((Data[mid].x == x) && (Data[mid].y == y))
            return mid+1;
        // If item greater, ignore left half
        if ((Data[mid].x < x) || ((Data[mid].x == x) && (Data[mid].y < y)))
            l = mid + 1;
        
        // If item is smaller, ignore right half
        else
            h = mid - 1;
    }//end while
    // if we reach here, then element was
    // not present
    return -1;
}//end binarySearch

int SearchPhase(struct Covid19* Data, int Q) {
    int x;
    int y;
    int Datasrch;
    while(1) {
        printf("\nEnter and X and Y coordinate\n");
        printf("Example: -2 (SPACE) 2\n");
        printf("\nSearch Input: ");
        scanf("%d %d", &x, &y);
        printf("\n~~~~~~ Results: ");
        
        if((x == -999) || (y == -999)) {
            printf("Quit ~~~~~~\n");
            break;
        }//end if
        
        Datasrch = binarySearch(Data, x, y, Q);
        
        if(Datasrch == -1) {
            printf("Non-Existent ~~~~~~\n");
        }//end if
        else {
            printf("Found at record %d ~~~~~~\n", Datasrch);
        }//end else
    }//end while 1
    return 0;
}
