//Gavin Tynan
//Final Term Assignment 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

struct treeNode
{
    char word[MAX];
    struct treeNode *LNode;
    struct treeNode *RNode;
}*node;

void searchWord(char word[], struct treeNode **BigNode, struct treeNode **Pos){
    
    struct treeNode *ptr, *tempPtr;
    if (node == NULL){
        *Pos = NULL;
        *BigNode = NULL;
        return;
    }
    if (strcmp(word, node->word) == 0){
        *Pos = node;
        *BigNode = NULL;
        return;
    }
    if (strcmp(word, node->word) < 0)
        ptr = node->LNode;
    else
        ptr = node->RNode;
    
    tempPtr = node;
    
    while (ptr != NULL){
        if (strcmp(word, ptr->word) == 0){
            *Pos = ptr;
            *BigNode = tempPtr;
            return;
        }
        tempPtr = ptr;
        
        if (strcmp(word, ptr->word) <= 0)
            ptr = ptr->LNode;
        else
            ptr = ptr->RNode;
    }
    *Pos = NULL;
    *BigNode = tempPtr;
}

void insertWord(char word[]){
    
    struct treeNode *BigNode, *Pos, *temp;
    searchWord(word, &BigNode, &Pos);
    
    if (Pos != NULL){
        return;
    }
    
    temp = (struct treeNode*) malloc(sizeof(struct treeNode));
    strcpy(temp->word, word);
    temp->LNode = NULL;
    temp->RNode = NULL;
    
    if (BigNode == NULL)
        node = temp;
    else
        if (strcmp(word, BigNode->word) <= 0)
            BigNode->LNode = temp;
        else
            BigNode->RNode = temp;
}

void bothNodesEmpty(struct treeNode *BigNode, struct treeNode *Pos){
    
    if (BigNode == NULL)
        node = NULL;
    else
        if (Pos == BigNode->LNode)
            BigNode->LNode = NULL;
        else
            BigNode->RNode = NULL;
}

void oneNodeEmpty(struct treeNode *BigNode, struct treeNode *Pos){
    
    struct treeNode *child;
    if (Pos->LNode != NULL)
        child = Pos->LNode;
    else
        child = Pos->RNode;
    if (BigNode == NULL)
        node = child;
    else
        if (Pos == BigNode->LNode)
            BigNode->LNode = child;
        else
            BigNode->RNode = child;
}

void noNodesEmpty(struct treeNode *BigNode, struct treeNode *Pos){
    
    struct treeNode *ptr, *tempPtr, *next, *prev;
    tempPtr = Pos;
    ptr = Pos->RNode;
    while (ptr->LNode != NULL){
        tempPtr = ptr;
        ptr = ptr->LNode;
    }
    next = ptr;
    prev = tempPtr;
    if (next->LNode == NULL && next->RNode == NULL)
        bothNodesEmpty(prev, next);
    else
        oneNodeEmpty(prev, next);
    if (BigNode == NULL)
        node = next;
    else
        if (Pos == BigNode->LNode)
            BigNode->LNode = next;
        else
            BigNode->RNode = next;
    next->LNode = Pos->LNode;
    next->RNode = Pos->RNode;
}

int deleteWord(char word[],FILE* fout)
{
    struct treeNode *BigNode, *Pos;
    if (node == NULL)
    {
        fprintf(fout, "The Tree Is Empty");
        return 0;
    }
    
    searchWord(word, &BigNode, &Pos);
    if (Pos == NULL)
    {
        fprintf(fout, "Item is not in tree");
        return 0;
    }
    if (Pos->LNode == NULL && Pos->RNode == NULL)
        bothNodesEmpty(BigNode, Pos);
    if (Pos->LNode != NULL && Pos->RNode == NULL)
        oneNodeEmpty(BigNode, Pos);
    if (Pos->LNode == NULL && Pos->RNode != NULL)
        oneNodeEmpty(BigNode, Pos);
    if (Pos->LNode != NULL && Pos->RNode != NULL)
        noNodesEmpty(BigNode, Pos);
    fprintf(fout, "\n%s: Deleted", Pos->word);
    free(Pos);
    return 1;
}


int preOrder(struct treeNode *ptr, FILE* fout)
{
    if (node == NULL)
    {
        fprintf(fout, "The Tree Is Empty");
        return 0;
    }
    if (ptr != NULL)
    {
        fprintf(fout, "%s ", ptr->word);
        preOrder(ptr->LNode, fout);
        preOrder(ptr->RNode, fout);
    }
    return 1;
}

void inOrder(struct treeNode *ptr,FILE* fout)
{
    if (node == NULL)
    {
        fprintf(fout, "The Tree Is Empty");
        return;
    }
    if (ptr != NULL)
    {
        inOrder(ptr->LNode, fout);
        fprintf(fout, "%s ", ptr->word);
        inOrder(ptr->RNode, fout);
    }
}

void postOrder(struct treeNode *ptr,FILE* fout)
{
    if (node == NULL)
    {
        fprintf(fout, "The Tree Is Empty");
        return;
    }
    if (ptr != NULL)
    {
        postOrder(ptr->LNode, fout);
        postOrder(ptr->RNode, fout);
        fprintf(fout, "%s ", ptr->word);
    }
}
void alphabetic(struct treeNode *ptr)
{
    if (ptr != NULL)
    {
        alphabetic(ptr->LNode);
        alphabetic(ptr->RNode);
    }
}

int CountBefore(struct treeNode* ptr, char searchword[]) {
    int count = 0;
    
    if(ptr != NULL) {
        if(strcmp(ptr->word, searchword) < 0) {
            count++;
        }
        count += CountBefore(ptr->LNode, searchword);
        count += CountBefore(ptr->RNode, searchword);
    }
    return count;
}


int tc = 0;
int TotalCharacter(struct treeNode *ptr)
{
    
    if (ptr != NULL)
    {
        TotalCharacter(ptr->LNode);
        tc = tc + (strlen(ptr->word));
        //printf("\nStrlen : %lu", (strlen(ptr->word)));
        TotalCharacter(ptr->RNode);
        
    }
    return tc;
}
int max(int a, int b)
{
    return (a >= b) ? a : b;
}

int height (struct treeNode *ptr){
    if (ptr == NULL)
        return 0;
    return 1 + max(height(ptr->LNode), height(ptr->RNode));
}

int isBalanced(struct treeNode* ptr, FILE* fout){
    int lh=0;
    int rh=0;
    if (ptr == NULL)
        return 1;
    
    lh = height(ptr->LNode);
    rh = height(ptr->RNode);
    
    if (abs(lh - rh) <= 1 && isBalanced(ptr->LNode, fout) && isBalanced(ptr->RNode, fout)) {
        fprintf(fout, "\nThis Tree is Balanced");
        return 1;
    }
    fprintf(fout, "\nThis Tree is NOT Balanced");
    return 0;
}

int main()
{
    
    char word[MAX];
    int numOfReadWords, numOfSearchWords, numOfDeleteWords, i;
    node = NULL;
    struct treeNode *Pos;
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    
    
    if (fin == NULL){
        puts("Error: file could not be opened.");
        return 0;
    }
    
    fscanf(fin, "%d %d %d", &numOfReadWords, &numOfSearchWords, &numOfDeleteWords);
    
    for (i = 1; i <= numOfReadWords; i++){
        fscanf(fin, "%s", word);
        insertWord(word);
    }
    
    fprintf(fout,"Pre Order: ");
    preOrder(node, fout);
    fprintf(fout,"\nIn Order: ");
    inOrder(node, fout);
    fprintf(fout,"\nPost Order: ");
    postOrder(node, fout);
    fprintf(fout,"\nTotal Characters: %d",TotalCharacter(node));
    
    fprintf(fout,"\nheight of Left: %d",height(node -> LNode));
    fprintf(fout,"\nheight of Right: %d",height(node -> RNode));
    isBalanced(node, fout);
    fprintf(fout,"\n\nSearch Phase:");
    
    for (i = 1; i <= numOfSearchWords; i++)
    {
        struct treeNode *temp = node;
        
        fscanf(fin, "%s", word);
        int flag = 0;
        while (temp != NULL)
        {
            if (strcmp(word, temp->word) == 0)
            {
                fprintf(fout,"\n%s: Found.", word);
                fprintf(fout,"\nItems before: %d", CountBefore(node, word));
                flag = 1;
                break;
            }
            if (strcmp(word, temp->word) <= 0)
                temp = temp->LNode;
            else
                temp = temp->RNode;
        }
        if (flag == 0)
            fprintf(fout,"\n%s: Not Found.", word);
    }
    
    fprintf(fout,"\n\nDelete Phase:");
    
    for (i = 1; i <= numOfDeleteWords; i++){
        fscanf(fin, "%s", word);
        deleteWord(word, fout);
    }
    
    fprintf(fout,"\n");
    fprintf(fout,"\nIn Order: ");
    inOrder(node, fout);
    return 0;
}
