#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree.h"   

struct tree 
{
        int data;
        struct tree *parent;
        struct tree *right;
        struct tree *left;
};

//return a pointer to a new tree with the specified left and right subtrees and data for its root
//O(n)
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
        struct tree *tr;
        tr = malloc(sizeof(struct tree));
        assert(tr != NULL);
        tr->data = data;
        tr->parent = NULL;
        if (right != NULL) //checks if there is a right child
        {   
                if (right->parent != NULL) //checks if right child has a parent
                {   
                        if (right->parent->right == right)
                                right->parent->right = NULL;
                        else 
                                right->parent->left = NULL;
                }   
                right->parent = tr; 
        }   
        tr->right = right;    
        if (left != NULL) //checks if there is a left child
        {   
                if (left->parent != NULL)
                {   
                        if (left->parent->left == left)
                                left->parent->left = NULL;    
                        else
                                left->parent->right = NULL;
                }   
                left->parent = tr; 
        }   
        tr->left = left;
        return tr; 
}

//deallocate memory for the entire subtree pointed to by root
//O(log n)
void destroyTree(struct tree *root)
{
        if (root == NULL) //basecase no root
        {
                free (root);
                return;
        }
        destroyTree(root->left);
        destroyTree(root->right);
}

//return the data in the root of the subtree pointed to by root
//O(1)
int getData (struct tree *root)
{
        return root->data;
}

//return the left subtree of the subtree pointed to by root
//O(1)
struct tree *getLeft(struct tree *root)
{
        return root->left;
}
//return the right subtree of the subtree pointed to by root
//O(1)
struct tree *getRight(struct tree *root)
{
        return root->right;
}

//return the parent subtree of the subtree pointed to by root
//O(1)
struct tree *getParent (struct tree *root)
{
        return root->parent;
}
//update the left subtree of root
//O(1)
void  setLeft(struct tree *root, struct tree *left)
{
        root->left = left;
}
//update the right subtree of root
//O(1)
void setRight (struct tree *root, struct tree *right)
{
        root->right = right;
}
