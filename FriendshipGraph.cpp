#include "FriendshipGraph.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std; 

FriendshipGraph::FriendshipGraph()
{
    size = 0;
}

vector<string> FriendshipGraph::getUserFriends(int index)
{
    return users[index].friendList;
}

int FriendshipGraph::getSize()
{
    return size;
}

//use this for the initial read and insert from input file
void FriendshipGraph::insertUserAndTheirFriends(string name, int index, string friendList)
{
    GraphNode newUser; 
    newUser.name = name;
    newUser.index = index;
    
    istringstream ss(friendList);
    string token = "";
    while (getline(ss, token, ','))
    {
        newUser.friendList.push_back(token);
    }

    users.push_back(newUser);
    size++;
}

void FriendshipGraph::insertUser(string name, int index)
{
    GraphNode newUser; 
    newUser.name = name;
    newUser.index = index;

    users.push_back(newUser);
    size++;
}

//this function only works on already inserted users 
void FriendshipGraph::createFriendship(string name1, int index1, string name2, int index2) //go to index1, add name2, go to index2, add name1
{
    if (!isFriends(name1,index1,name2,index2))
    {
        users[index1].friendList.push_back(name2);
        users[index2].friendList.push_back(name1);
        cout << name1 << " and " << name2 << " are now friends!" << endl;
    } else
    {
        cout << "They are already friends!" << endl;
    }
    
}

bool FriendshipGraph::isFriends(string name1, int index1, string name2, int index2)
{
    for (string s : users[index1].friendList)
    {
        if (s == name2)
        {
            return true;
        }
    }

    return false;
}

void FriendshipGraph::printAll()
{
    for (GraphNode g : users)
    {
        cout << g.name << "," << g.index << ",";
        for (string s : g.friendList)
        {
            cout << s << ",";
        }
        cout << endl;
    }
}