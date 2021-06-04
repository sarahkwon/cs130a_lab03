#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct GraphNode 
{
    string name;
    int index; //index of the person on the csv file 
    vector<string> friendList;
};


class FriendshipGraph
{
    public:
        /***** Constructor *****/
        FriendshipGraph();

        /***** Get functions *****/
        vector<string> getUserFriends(int index); //use the rb tree to get their index, then use it as a parameter for this function 
        int getSize();

        /***** Insertion Functions *****/
        void insertUserAndTheirFriends(string name, int index, string friendList); //used when initializing the data structures given an input file
        void insertUser(string name, int index);

        /***** Edit objects that have already been inserted *****/ 
        void createFriendship(string name1, int index1, string name2, int index2); //make name1 and name2 friends (add each other to their respective friend list)

        /**** Utility Functions *****/
        void printAll();
        bool isFriends(string name1, int index1, string name2, int index2);
        
    private:
        vector<GraphNode> users; 
        int size; //position of last item will be size - 1

};


//it is an array and the index of an item in the array directly corresponds to the index of it in the csv file? so when you do a search
//function all you do is getUser(int index) and you will get the user at thati ndex
//if theres a find user, you can iterate through the red-black tree to find it, then return its index and use that value in the
//adjacency list to get information about them. 
//i will use a vector of graph nodes for the adjacency list because easier towork with lol and yeah. 

//to make a freindship query
//im pretty sure its just a list of everyones names? and then perform a search(string name) operation with the red black tree 
//on each name? 