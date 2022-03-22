#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
};

struct node* createNode(int num){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = num;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;

    return temp;
}

void insert(struct node **head, int *size, int num){
    *size = *size + 1;

    struct node *temp = createNode(num);

    if(*size == 1){
        *head = temp;
    }
    else{
        int digits = floor(log2(*size)) + 1;   // Calculates Digits in Binary Representation of 'size'.
        int arr[digits-1]; // Stores digits in Binary Representation of 'size', except the first digit.
        
        int tempSize = *size;
        for(int i = digits-2; i >= 0; i--){
            arr[i] = tempSize%2;
            tempSize = tempSize/2;
        }

        // The array now stores the binary digits of 'size', except the first digit.
        // Traversing through this array gives us the direction to enter our element at.
        struct node *itr = *head;
        for(int i = 0; i < digits-2; i++){
            if(arr[i] == 0){
                itr = itr->left;
            }
            else{
                itr = itr->right;
            }
        }
        if(arr[digits-2] == 0){
            itr->left = temp;
            temp->parent = itr;
        }
        else{
            itr->right = temp;
            temp->parent = itr;
        }
    }
}

void bracketify(struct node **head){
    if(*head == NULL){
        printf(" ( ) ");
        return;
    }
    else{
        struct node *itr = *head;
        printf("( %d ", itr->data);
        bracketify(&(itr->left));
        bracketify(&(itr->right));
        printf(" ) ");
    }
}

void generateDot(struct node **head, char *str){
    if(*head == NULL){
        return;
    }
    else{
        struct node *itr = *head;

        generateDot(&(itr->left), str);
        if(itr->parent){
            char buff[3];
            snprintf(buff, 3, "%d", itr->parent->data);
            strcat(str, buff);
            strcat(str, "--");
            snprintf(buff, 3, "%d", itr->data);
            strcat(str, buff);
            strcat(str, "\n");
        }
        generateDot(&(itr->right), str);
    }
}

int main(){
    struct node *head = NULL;

    int choice, x;
    int size = 0;
    while(1){
        printf("Menu: 1. Insert, 2. View, 3. Exit: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:{
                printf("Enter data: ");
                scanf("%d", &x);
                insert(&head, &size, x);
                break;
            }

            case 2:{
                bracketify(&head);

                char str[5555] = "";
                generateDot(&head, str);

                FILE *fhand = fopen("1.dot", "w");
                fputs("graph G{\n", fhand);
                fputs(str, fhand);
                fputs("}\n", fhand);

                fclose(fhand);
                printf("\nOpening visualizer, please don't quit\n");
                system("dot -Tpng 1.dot -o 1.png");
                system("1.png");

                break;
            }

            default:{
                return 0;
            }
        }
    }
}