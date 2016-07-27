// C program to demonstrate insert operation in binary search tree
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

struct node
{
    int key;
    node *left;
    node *right;
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  new node();
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

int lca(node *root, int u, int v){

    if(u < root->key && v < root->key){
        return lca(root->left, u, v);
    }else if(u > root->key && v > root->key){
        return lca(root->right, u, v);
    }else{
        return root->key;
    }

}

int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    cout<< "print inoder traversal of the BST:"<<endl;
    inorder(root);
    cout<<"print lca of 60  and 80"<<endl;
    cout<<lca(root, 60, 80)<<endl;

    return 0;
}
