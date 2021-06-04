#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node 
{
    string name; //the key 
    int index; //the line that the record is located on the csv file
    int color; //0 -> black, 1 -> red

    //pointers to parent, left child, and right child 
    node* parent;
    node* left;
    node* right;

    node(string Name, int Index) { name = Name; index = Index; color = 1; parent = NULL; left = NULL; right = NULL; }
};

class RedBlackTree
{
    public:
        /***** Constructor *****/
        RedBlackTree();

        /***** Get Functions *****/
        int getIndex(string name);
        vector<int> getUsers(vector<int>& userList, string name1, string name2); //for the range query

        /***** Insert Functions *****/
        void insertUser(string name, int index);

        /***** Print Functions for Testing *****/
        void inOrder();
        void inOrderHelper(node* n);
        
    private:
        node* root;
        node* null;

        /***** Utility Functions *****/
        void leftRotation(node* n);
        void rightRotation(node* n);
        void fixInsertion(node* n);
        
        /***** Helper Functions *****/
        void insertUserHelper(node* &rootNode, node* parentNode, string name, int index);
        node* getIndexHelper(node* n, string name);
        void getUsersHelper(vector<int>& userList, node* &n, string name1, string name2);


};