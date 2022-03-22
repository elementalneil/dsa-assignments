#include<stdio.h>
#include<stdlib.h>
//defining structure for BST node
struct node
{
    int data;
    struct node *parent;
    struct node *left;
    struct node *right;
};
struct node *root =NULL;
struct node *createNode(int k) 
{
    struct node *T = (struct node *)malloc(sizeof(struct node));
    
    T->data = k;
    T->parent =NULL;
    T->left = NULL;
    T->right = NULL;    
    return T;
}
//program to  insert new node to tree.
void insert(struct node *node, int x ) 
{
    struct node* y= createNode(x);
    if (node == NULL) 
    {
        node = y;
        return;
    }
    

    if (x < node->data)
    {
        node->left = y;
        y->parent = node;
    }    
    else 
    if(x > node->data)
    {
        node->right = y;
        y->parent = node;
    }
}

int flag = -1;
int search( struct node* node , int key)
{
    // if the key is not present in the key
    if (node == NULL)
    {
        printf("Key is not found %d\n",flag);        
    }

    // searching for key in tree and setting value of flag if found to 1.
    if ( node->data == key )
    {
        flag = 1;
        printf("%d",flag);        
    }

    // if the given key is less than the root node- then left subtree otherwise - the right subtree

    if (key < node->data) 
    {
        search(node->left, key);
    }
    else 
    {
        search(node->right, key);
    }
}

int minimum;
struct node* minValueNode(struct node* node)
{
    struct node* current = node;
 
    // loop down to find the leftmost leaf 
    while (current && current->left != NULL)
        current = current->left;
    minimum = current->data;
    return current;
}

int maximum;
struct node* maxValueNode(struct node* node)
{
    struct node* current = node;
 
    // loop down to find the righttmost leaf node
    while (current && current->right != NULL)
        current = current->right;
    maximum = current->data;
    return current;
}
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL)
        return root;
 
    // the key to be deleted is smaller than the root key, it lies in left subtree
    if (key < root->data)
        root->left = deleteNode(root->left, key);    
    else
    // key to be deleted is greater than the root's key,  it lies in right subtree
        if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    // the key is same as root's key, then this is the node to be deleted
    {
        // empty tree
        if (root->left==NULL && root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minValueNode(root->right);
 
        //copying inorder successor content to this node
        root->data = temp->data;
 
        // deleting inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main()
{
    char option;
    int n,key;
    int temp;
    //CREATING MENU OPTION LIST.
    printf("a. CREATE AND INSERT A NODE IN TREE T.\nd. DELETE A NODE (IF NOT PRESENT : -1)\ns. SEARCH THE KEY\nm. MINIMUM VALUE IN T\nx. MAXIMUM VALUE IN T\ne. EXIT\n\n");

    while(1)
    {
        scanf("%c",&option);

        switch(option)
        {
            case 'a'://inserting a node to tree
                scanf("%d",&n);
                insert(root,n);
                break;
            case 'd':
                scanf("%d",&key);
                deleteNode(root,key);               
                break;
            case 's':
                printf("Input\t");
                scanf("%d",&key);
                search(root , key);
                printf("\t%d",temp);
                break;
            case 'm':
                printf("%d",minValueNode(root));
                break;
            case 'x':
                printf("%d",maxValueNode(root));
                break;
            case 'e':
                exit(0);
                break;
        }
    }
    return 0;
}