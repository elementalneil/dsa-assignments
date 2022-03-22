#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int data;
    struct node *left, *right, *parent;
};

struct node* createNode(int num){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = num;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;

    return temp;
}

void insert(struct node **head, int num){
    struct node *temp = createNode(num);
    if(*head == NULL){
        *head = temp;
    }
    else{
        struct node *itr = *head;

        while(1){
            if(num >= itr->data){
                if(itr->right){
                    itr = itr->right;
                }
                else{
                    itr->right = temp;
                    temp->parent = itr;
                    break;
                }
            }
            else{
                if(itr->left){
                    itr = itr->left;
                }
                else{
                    itr->left = temp;
                    temp->parent = itr;
                    break;
                }
            }
        }
    }
}

struct node* minValue(struct node **head){
    struct node *itr = *head;

    while(itr->left != NULL){
        itr = itr->left;
    }

    return itr;
}

struct node* maxValue(struct node **head){
    struct node *itr = *head;

    while(itr->right != NULL){
        itr = itr->right;
    }

    return itr;
}

struct node* search(struct node **head, int num){
    if(*head == NULL){
        return NULL;
    }
    else{
        struct node *itr = *head;

        if(num < itr->data){
            return search(&(itr->left), num);
        }
        else if(num > itr->data){
            return search(&(itr->right), num);
        }
        else{
            return itr;
        }
    }
}

int childCount(struct node **head){
    int count = 0;
    if((*head)->left != NULL) count++;
    if((*head)->right != NULL) count++;

    return count;
}

void viewInorder(struct node **head, int *arr, int *index){
    if(*head == NULL){
        return;
    }
    else{
        struct node *itr = *head;

        viewInorder(&(itr->left), arr, index);
        *index = *index + 1;
        *(arr+*index) = itr->data;
        viewInorder(&(itr->right), arr, index);
    }
}

int deleteNode(struct node **head, int num){
    struct node *temp = search(head, num);

    int returnData;
    if(!temp){
        return -1;
    }
    else{
        returnData = temp->data;
    }

    // Case for leaf node
    if(childCount(&temp) == 0){
        if(temp->parent->data > temp->data){    // Deleting left node.
            temp->parent->left = NULL;
            free(temp);
        }
        else{                                   // Deleting right node.
            temp->parent->right = NULL;
            free(temp);
        }
        free(temp);
    }

    // Case for only one child
    else if(childCount(&temp) == 1){
        if(temp->left){                        // When child is a left child
            struct node *prev = temp->parent;
            struct node *next = temp->left;
            prev->left = next;
            next->parent = prev;
        }
        else{                                  // When child is a right child
            struct node *prev = temp->parent;
            struct node *next = temp->right;
            prev->right = next;
            next->parent = prev;
        }
    }

    // Case for two children
    else{
        int arr[100];
        int index = -1;
        viewInorder(&(temp->right), arr, &index);
        int successor = arr[0];

        struct node *itr = search(&temp, successor);

        deleteNode(head, successor);
        temp->data = successor;
    }

    return returnData;
}

int main(){
    struct node *head = NULL;

    char choice[2];
    int x;

    while(1){
        scanf("%s", choice);

        // Adding node
        if(!strcmp(choice,"a")){
            scanf("%d", &x);
            insert(&head, x);
        }
        // Deleting Node
        else if(!strcmp(choice,"d")){
            scanf("%d", &x);
            printf("%d\n", deleteNode(&head, x));
        }
        // Search Node
        else if(!strcmp(choice,"s")){
            scanf("%d", &x);
            if(search(&head, x))
                printf("%d\n", 1);
            else
                printf("%d\n", -1);
        }
        // Minimum Node
        else if(!strcmp(choice,"m")){
            struct node *temp = minValue(&head);
            if(temp)
                printf("%d\n", temp->data);
            else
                printf("Empty Tree\n");
        }
        // Maximum Node
        else if(!strcmp(choice,"x")){
            struct node *temp = maxValue(&head);
            if(temp)
                printf("%d\n", temp->data);
            else
                printf("Element Not Found\n");
        }
        // Exit Condition
        else{
            printf("Test");
            break;
        }
    }
}