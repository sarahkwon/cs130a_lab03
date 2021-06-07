#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include "RedBlackTree.h"
#include "FriendshipGraph.h"
#include "ProfileDataController.h"
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
   FriendshipGraph friendshipGraph;
   ProfileDataController profileDataController;
   RedBlackTree redBlackTree;
   ifstream in;
   int currentIndex = 0;

   //open input file and insert each user into the respective data structures 
   in.open(argv[1]);
   string currentLine = "";
   getline(in, currentLine);

   string name = "";
   string age = "";
   string occupation = "";
   string friends = "";
   string temp = "";
   while (getline(in, currentLine))
   {
      istringstream ss(currentLine);
      getline(ss, name, ',');
      getline(ss, age, ',');
      getline(ss, occupation, ',');
      getline(ss, temp, '"'); //skips the quotation mark for friends
      getline(ss, friends, '"'); //gets friends without the quotations 

      profileDataController.insertUser(name, age, occupation);
      redBlackTree.insertUser(name, currentIndex);
      friendshipGraph.insertUserAndTheirFriends(name, currentIndex, friends); 
      currentIndex++;
   }



   while (true)
   {
      cout << "------------------------------------------------------------------------------" << endl;
      cout << "Select one of the options: " << endl;
      cout << "1: insert a new user" << endl; 
      cout << "2: add friend" << endl;
      cout << "3: get user profile" << endl;
      cout << "4: create query" << endl;
      cout << "5: exit program" << endl;

      string ans = "";
      cout << "Your input: ";
      getline(cin, ans);

      int input = stoi(ans);

      if (input == 1)
      {
         string name = "";
         string age = "";
         string occupation = "";
         string friends = "";

         cout << "------------------------------------------------------------------------------" << endl;
         cout << "Enter user's name: ";
         std::getline(cin, name);
         cout << "Enter user's age: ";
         std::getline(cin, age);
         cout << "Enter user's occupation: ";
         std::getline(cin, occupation);
         cout << "Enter user's friends. End each name with a comma (e.g. John Park,Sienna J Williams,): ";
         std::getline(cin, friends);

         profileDataController.insertUser(name, age, occupation);
         redBlackTree.insertUser(name, currentIndex);
         friendshipGraph.insertUser(name, currentIndex); //each newly inserted user starts off with no friends

         //makes a vector of the new user's friends so that we can make friendships with the existing users 
         vector<string> newUserFriends;
         istringstream ss(friends);
         string token = "";
         while (getline(ss, token, ','))
         {
            newUserFriends.push_back(token);
         }

         //for each of the new User's friends, create a friendship between them in the friendship graph
         for (string s : newUserFriends)
         {
            int indexOfFriend = redBlackTree.getIndex(s);
            friendshipGraph.createFriendship(name, currentIndex, s, indexOfFriend);    
         }

         currentIndex++;

      } else if (input == 2)
      {
         string name1 = "";
         string name2 = "";

         cout << "------------------------------------------------------------------------------" << endl;
         cout << "Enter the name of the first user: ";
         std::getline(cin, name1);
         cout << "Enter the name of the second user: ";
         std::getline(cin, name2);

         int index1 = redBlackTree.getIndex(name1);
         int index2 = redBlackTree.getIndex(name2);

         friendshipGraph.createFriendship(name1, index1, name2, index2);

      } else if (input == 3)
      {
         string name = "";

         cout << "------------------------------------------------------------------------------" << endl;
         cout << "Enter user name: ";
         std::getline(cin, name);

         int index = redBlackTree.getIndex(name);
         if (index == -1)
         {
            cout << "--------------------------------------" << endl;
            cout << name << " does not exist in the database." << endl;
         } else 
         {
            cout << "--------------------------------------" << endl;
            cout << "Name: " << profileDataController.getUserName(index) << endl;
            cout << "Age: " << profileDataController.getUserAge(index) << endl;
            cout << "Occupation: " << profileDataController.getUserOccupation(index) << endl;
         }

      } else if (input == 4)
      {
         cout << "------------------------------------------------------------------------------" << endl;
         cout << "Select the type of query you would like to create:" << endl; 
         cout << "1: Friendship query - get the profiles of a specified user's friends" << endl;
         cout << "2: Range query - get the profiles of all users between name A and name B" << endl;
         cout << "3: Go back to the previous menu" << endl;
         cout << "4: Exit Program" << endl;

         string ans2 = "";
         cout << "Your input: ";
         getline(cin, ans2);

         int input2 = stoi(ans2);

         if (input2 == 1)
         {
            string name = "";
            ofstream out;
            out.open("FriendshipQuery.csv");
            cout << "Please enter the name of the user: ";
            std::getline(cin, name);

            int index = redBlackTree.getIndex(name);
            if (index == -1)
            {
               cout << "--------------------------------------" << endl;
               cout << name << " does not exist in the database." << endl;
            } else 
            {
               vector<string> userInfo = friendshipGraph.getUserFriends(index);
               //creates the heading of the file at the top
               out << left << setw(20) << "NAME";
               out << left << " | ";
               out << left << setw(3) << "AGE";
               out << left << " | ";
               out << left << setw(30) << "OCCUPATION";
               out << left << " | ";
               out << endl;
            
               //for each friend in the user's friend list, append to the file FriendshipQuery.csv
               for (string s : userInfo)
               {
                  index = redBlackTree.getIndex(s);
                  out << profileDataController.getUserName(index); 
                  out << left << " | ";
                  out << profileDataController.getUserAge(index);
                  out << left << " | ";
                  out << profileDataController.getUserOccupation(index);
                  out << left << " | ";
                  out << endl;
               }
            }

         } else if (input2 == 2)
         {
            string name1 = "";
            string name2 = "";
            ofstream out;
            out.open("RangeQuery.csv");
            cout << "Enter the name of the first user: ";
            std::getline(cin, name1);
            cout <<"Enter the name of the second user: ";
            std::getline(cin, name2);

            vector<int> userList; 

            redBlackTree.getUsers(userList, name1, name2);
            //creates the heading of the file at the top
            out << left << setw(20) << "NAME";
            out << left << " | ";
            out << left << setw(3) << "AGE";
            out << left << " | ";
            out << left << setw(30) << "OCCUPATION";
            out << left << " | ";
            out << endl;

            for (int i : userList)
            {
               out << profileDataController.getUserName(i); 
               out << left << " | ";
               out << profileDataController.getUserAge(i);
               out << left << " | ";
               out << profileDataController.getUserOccupation(i);
               out << left << " | ";
               out << endl;
            }

         } else if (input2 == 3)
         {
            continue;
         } else if (input2 == 4)
         {
            exit(1);
         } else 
         {
            cout << "------------------------------------------------------------------------------" << endl;
            cout << "Invalid input. Please enter a number between 1-4." << endl;
         }

      } else if (input == 5)
      {
         exit(0);
      } else
      {
         cout << "------------------------------------------------------------------------------" << endl;
         cout << "Invalid input. Please enter a number between 1-4." << endl; 
      }

      cout << "------------------------------------------------------------------------------" << endl;
      cout << "Would you like to make another selection?" << endl;
      cout << "1: yes" << endl;
      cout << "2: no (exit program)" << endl;

      string ans3 = "";
      cout << "Your input: ";
      getline(cin, ans3);

      int input3 = stoi(ans3);

      if (input3 == 1)
      {
         continue;
      } else
      {
         exit(2);
      }
   }

}

