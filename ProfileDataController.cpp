#include "ProfileDataController.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std; 

ProfileDataController::ProfileDataController()
{
    profileDataFile = "profileData.csv";
    out.open(profileDataFile);
    in.open(profileDataFile);
}

void ProfileDataController::insertUser(string name, string age, string occupation)
{
    out << left << setw(20) << name;
    out << left << setw(3) << age;
    out << left << setw(30) << occupation;
    out << endl;
}

string ProfileDataController::getUserName(int index)
{
    in.seekg(54*index, ios::beg);

    char token[20] = "";
    in.read(token, 20);
    string result = "";
    for (int i = 0; i < 20; i++)
    {
        result += token[i];
    }

    return result;
}

string ProfileDataController::getUserAge(int index)
{
    in.seekg(54*index + 20, ios::beg);

    char token[3] = "";
    in.read(token, 3);
    string result = "";
    for (int i = 0; i < 3; i++)
    {
        result += token[i];
    }

    return result;
}

string ProfileDataController::getUserOccupation(int index)
{
    in.seekg(54*index + 23, ios::beg); //23 offset because occupation is after name[20] and age[3]

    char token[30] = "";
    in.read(token, 30);
    string result = "";
    for (int i = 0; i < 30; i++)
    {
        result += token[i];
    }

    return result;
}

string ProfileDataController::getUserInfo(int index)
{
    in.seekg(54*index, ios::beg); //we seek by multiples of 54 because the new line adds an extra character to each record
    
    char token[53] = "";
    in.read(token, 53);
    string result = "";
    for (int i = 0; i < 53; i++)
    {
        result += token[i];
    }

    return result;

}

void ProfileDataController::closeFile()
{
    out.close();
    in.close();
}