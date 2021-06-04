#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

class ProfileDataController
{
    public:

        /***** Constructor *****/
        ProfileDataController();

        /***** Insert Functions *****/
        void insertUser(string name, string age, string occupation); //writes to profileDataFile

        /***** Get Functions *****/
        string getUserName(int index);
        string getUserAge(int index);
        string getUserOccupation(int index);
        string getUserInfo(int index); //returns in the format of name[20],age[3],occupation[30]

        /***** General Functions *****/
        void closeFile();
        
    private:
        string profileDataFile;
        ofstream out;
        ifstream in;


};
