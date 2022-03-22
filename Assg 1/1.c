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

void deleteNode(struct node **head, int num){
    struct node *temp = search(head, num);

    if(!temp){
        printf("Does not exist!");
        return;
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
    while(1){
        printf("Menu: 1. Insert, 2. View, 3. Search, 4. Delete, 5. Exit: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:{
                printf("Enter data: ");
                scanf("%d", &x);
                insert(&head, x);
                break;
            }

            case 2:{
                int arr[50], index = -1;
                viewInorder(&head, arr, &index);
                for(int i = 0; i <= index; i++){
                    printf("%d ", arr[i]);
                }

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

            case 3:{
                printf("Enter search term: ");
                scanf("%d", &x);
                if(search(&head, x))
                    printf("Element found");
                else
                    printf("Element not found");
            
                break;
            }

            case 4:{
                printf("Enter deletion term: ");
                scanf("%d", &x);
                deleteNode(&head, x);

                break;
            }

            default:
                return 0;
        }
    }
}

// Command to generate png: dot -Tpng test.dot -o output.png