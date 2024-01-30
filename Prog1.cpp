//Alan Khalili
//Prog1.cpp I wrote this program to take in a csv rawdata file, parse it, and then either return the rawdata or summarize it by location
#include <iostream>
#include <string>
#include "Support.h" //here I included the header file that contains all the classes and functions I will be using

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3) //check for too many/little arguments
    {
        cerr << "usage: " << argv[0] << " [-rawdata] datafile" << endl;
        return 1;
    }
    string filename = argv[argc - 1]; 
    bool rawdata = (argc == 3 && string(argv[1]) == "-rawdata"); //parse the arguments
    if(!rawdata && argc == 3)
    {
        cerr << "usage: " << argv[0] << " [-rawdata] datafile" << endl;
        return 1;
    }

    database db; //create my database object
    db.init_rawdata(filename); //get rawdata processed and stored in the database

    if (rawdata) //send the program based on the proper flags
    {
        db.print_rawdata(); //just print all given data after properly storing
    }
    else
    {
        db.init_summary();
        while (true) //enter a loop to prompt the user for a location to summarize
        {
            string input;
            cout << "print> ";
            cin >> input;
            if(cin.eof())
                break;
            db.print_summary(input); //send input to print_summary()
        }
        cout << endl;
    }

    return 0;
}
