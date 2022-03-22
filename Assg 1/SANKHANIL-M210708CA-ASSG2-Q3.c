#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int roll;
    int marks;
    struct node *left, *right, *parent;
};

struct node* createNode(int r, int m){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->roll = r;
    temp->marks = m;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;

    return temp;
}

void insert(struct node **head, int r, int m){
    struct node *temp = createNode(r, m);
    if(*head == NULL){
        *head = temp;
    }
    else{
        struct node *itr = *head;

        while(1){
            if(num >= itr->marks){
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

int childCount(struct node **head){
    int count = 0;
    if((*head)->left != NULL) count++;
    if((*head)->right != NULL) count++;

    return count;
}

struct node* search(struct node **head, int m){
    if(*head == NULL){
        return NULL;
    }
    else{
        struct node *itr = *head;

        if(m < itr->marks){
            return search(&(itr->left), num);
        }
        else if(m > itr->marks){
            return search(&(itr->right), num);
        }
        else{
            return itr;
        }
    }
}

int deleteNode(struct node **head, int m){
    struct node *temp = search(head, m);

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
    int n;
    scanf("%d", &n);

    struct node *head = NULL;

    while(n--){
        int x;
        scanf("%d", &x);
        insert(&head, x);
    }
}