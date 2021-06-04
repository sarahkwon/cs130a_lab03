#include "RedBlackTree.h"
#include <iostream>
#include <string>

using namespace std; 

RedBlackTree::RedBlackTree()
{
    null = new node("", -1);
    null->left = null;
    null->right = null;
    null->color = 0;
    root = null;
}

  /* ---- ---------------- */
 /***** GET FUNCTIONS *****/
/* --------------------- */
int RedBlackTree::getIndex(string name)
{
    return getIndexHelper(root, name)->index; //index of -1 means that name is not in the tree
}

vector<int> RedBlackTree::getUsers(vector<int>& userList, string name1, string name2)
{
    getUsersHelper(userList, root, name1, name2); 
    return userList;
}

  /* ------------------------ */
 /***** INSERT FUNCTIONS *****/
/* ------------------------ */
void RedBlackTree::insertUser(string name, int index)
{
    insertUserHelper(root, NULL, name, index);
}

  /* ------------------------- */
 /***** UTILITY FUNCTIONS *****/
/* ------------------------- */
void RedBlackTree::leftRotation(node* n)
{
    node* y = n->right;
    n->right = y->left;

    if (y->left != null)
    {
        y->left->parent = n;
    }

    y->parent = n->parent;
    if (n->parent == NULL) 
    {
        root = y;
    } else if (n == n->parent->left)
    {
        n->parent->left = y;
    } else
    {
        n->parent->right = y;
    }

    y->left = n;
    n->parent = y;
}

void RedBlackTree::rightRotation(node* n)
{
    node* y = n->left;
    n->left = y->right;

    if (y->right != null)
    {
        y->right->parent = n;
    }

    y->parent = n->parent;
    if (n->parent == NULL)
    {
        root = y;
    } else if (n == n->parent->right)
    {
        n->parent->right = y;
    } else
    {
        n->parent->left = y;
    }

    y->right = n;
    n->parent = y;
}

void RedBlackTree::fixInsertion(node* n)
{
    node* u = null; //u is the uncle of node n
    node* gp = null;  //gp is the grandfather of node n

    gp = n->parent->parent;

    while (n->parent->color == 1)
    {
        //parent is the left child of its grandparent
        if (n->parent == gp->left)
        {
            u = gp->right;

            //case 1a: n's uncle is red 
            if (u->color == 1)
            {
                gp->color = 1; //RED
                n->parent->color = 0; //BLACK
                u->color = 0; //BLACK
                n = gp;

            }
             else 
            {
                //n is the right child of parent
                if (n == n->parent->right)
                {
                    n = n->parent;
                    leftRotation(n);
                }

                //n is the left child of parent 
                n->parent->color = 0; //BLACK
                gp->color = 1; //RED
                rightRotation(gp);                

            }

        //parent is the right child of grandparent 
        } else 
        {
            u = gp->left;

            //case 2a: uncle is red
            if (u->color == 1)
            {
                u->color = 0; //BLACK
                n->parent->color = 0; //BLACK
                gp->color = 1; //RED
                n = gp; 
            } else
            {
                //n is the left child of parent
                if (n == n->parent->left)
                {
                    n = n->parent;
                    rightRotation(n);
                }

                //n is the right child of parent
                gp->color = 1; //RED
                n->parent->color = 0; //BLACK
                leftRotation(gp);  

            }
        } 
        if (n == root) {
            break;
        }

    }
   root->color = 0;
}



  /* ------------------------ */
 /***** HELPER FUNCTIONS *****/
/* ------------------------ */
void RedBlackTree::insertUserHelper(node* &n, node* parentNode, string name, int index)
{

    //standard BST insertion 
    if (n == null)
    {
        n = new node(name, index); 
        n->parent = parentNode;
        n->left = null;
        n->right = null;
        if (n->parent == NULL)
        {
            root = n; 
            root->color = 0;
            return;
        }

		if (n->parent->parent == NULL) {
			return;
		}
    
        fixInsertion(n);
        return;
    }

    if (name < n->name) //if less than 
    {
        insertUserHelper(n->left, n, name, index);
    } else //if greater than alphabetically 
    {
        insertUserHelper(n->right, n, name, index);
    }

}


node* RedBlackTree::getIndexHelper(node* n, string name)
{
    if (n == null || name == n->name)
    {
        return n;
    }

    if (name < n->name)
    {
        return getIndexHelper(n->left, name);
    } else 
    {
        return getIndexHelper(n->right, name);
    }

}

void RedBlackTree::getUsersHelper(vector<int>& userList, node* &n, string name1, string name2)
{
   if (n == null)
   {
       return;
   } 

   if (name1 < n->name)
   {
       getUsersHelper(userList, n->left, name1, name2);
   }

   if (name1 <= n->name && name2 >= n->name)
   {
       userList.push_back(n->index);
   }

   if (name2 > n->name)
   {
       getUsersHelper(userList, n->right, name1, name2);
   }
}


  /* ----------------------------------- */
 /***** PRINT FUNCTIONS FOR TESTING *****/
/* ----------------------------------- */
void RedBlackTree::inOrder() {
    inOrderHelper(root);
  }

void RedBlackTree::inOrderHelper(node* n) {
    if (n == null) {
      return;
    }
    inOrderHelper(n->left);
    cout << n->name << "," << n->index << " Color: " << n->color << endl;
    inOrderHelper(n->right);
  }
