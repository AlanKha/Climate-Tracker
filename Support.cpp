// Alan Khalili
// Support.cpp I wrote this file to contain the code for the classes and functions that I will be using in my program
// Here I declared all libraries I would need. These are more specifically defined in "Support.h"
#include "Support.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <list>
#include <iomanip>
#include <queue>
#include <set>

using namespace std;
// operator overloads for location_map. Basically sorts the map that the structs will be sorted in
bool location::operator<(const location &other) const
{
    if (city < other.city && state == other.state) // compare first by city, then state
        return true;
    if (state < other.state)
        return true;
    return false;
}

void location::print() // here is the print for the header of each location
{
    cout << "------------------------------------------" << endl;
    cout << city << ", " << state << " (" << geocode << ")" << endl;
    cout << "------------------------------------------" << endl;
}

void rawdata::print() // here is my print statment for rawdata
{
    cout << setw(5) << month << setw(6) << fixed << setprecision(2) << precip << setw(6) << temp << endl;
}

void database::init_rawdata(string filename) // here is my function to parse the given file and store into my caches/maps
{
    ifstream fin(filename); // first check if it's a valid file
    if (!fin)
    {
        cerr << "error: cannot open " << filename << "\nusage: ./Prog1 [-rawdata] datafile" << endl;
        return exit(1);
    }
    string line;
    while (getline(fin, line)) // get all of the lines in the file
    {
        extract_rawdata(line); // replaced all spaces with underscores and commas with spaces
        rawdata rd;            // declared a rawdata and location struct
        location loc;

        stringstream ss(line);
        ss >> rd.month >> loc.city >> loc.state >> loc.geocode >> rd.precip >> rd.temp; // parsed the line

        if (location_map.find(loc) == location_map.end()) // check if the location is already in the map
        {                                                 // if not, create a new index in the map and fill it in.
            list<rawdata> new_list;
            new_list.push_back(rd);
            rawdata_cache.push_back(new_list);
            location_map[loc] = rawdata_cache.size() - 1;
        }
        else
        { // otherwise, just add the rawdata to the list
            rawdata_cache[location_map[loc]].push_back(rd);
        }
    }
}

void database::print_rawdata()
{ // here is my print statment for the rawdata
    for (map<location, int>::iterator it = location_map.begin(); it != location_map.end(); it++)
    {                                              // iterate throught location map
        const_cast<location &>(it->first).print(); // print header
        for (list<rawdata>::iterator it2 = rawdata_cache[it->second].begin(); it2 != rawdata_cache[it->second].end(); it2++)
        { // print rawdata
            it2->print();
        }
    }
}

summary::summary()
{ // here is my summary constructor. I just set all values to 0, and handle them in the += operator
    N = 0;
    precip_avg = 0.0;
    precip_max = 0.0;
    precip_min = 0.0;
    temp_avg = 0.0;
    temp_max = 0.0;
    temp_min = 0.0;
}

void database::init_summary()
{ // here is my summary initializer. I create a new vector of summary structs for each location and month and then fill them in with the rawdata
    for (map<location, int>::iterator it = location_map.begin(); it != location_map.end(); it++)
    { // loop through every location
        vector<summary> new_vector;
        for (int i = 0; i < 12; i++)
        { // create a new months vector and append a summary for each month
            summary new_summary;
            new_vector.push_back(new_summary);
        }
        summary_cache.push_back(new_vector);        // append the new vector to the summary_cache
        geocode_map[it->first.geocode] = it->first; // fill in the geocode_map

        state_map[it->first.state].insert(it->first.geocode); // fill in the state_map
    }
    extract_summary(); // extract the data from rawdata_cache
}

void summary::operator+=(const rawdata &other)
{ // += operator. I just add the new rawdata to the summary and handle the rest in the print function
    if (N == 0)
    { // if this is an empty month, I set all values to be from the new rawdata
        N++;
        precip_avg = other.precip;
        precip_max = other.precip;
        precip_min = other.precip;
        temp_avg = other.temp;
        temp_max = other.temp;
        temp_min = other.temp;
    }
    else
    { // otherwise find total, max, min, etc.
        N++;
        precip_avg += other.precip;
        temp_avg = (temp_avg * (N - 1) + other.temp) / N;
        if (precip_min > other.precip)
        {
            precip_min = other.precip;
        }
        if (precip_max < other.precip)
        {
            precip_max = other.precip;
        }
        if (temp_min > other.temp)
        {
            temp_min = other.temp;
        }
        if (temp_max < other.temp)
        {
            temp_max = other.temp;
        }
    }
}

void summary::print(int month)
{ // here is my print for the summaries. A lot of iomanip to match a specific format
    string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    cout << months[month] << ": "
         << setw(5) << fixed << setprecision(2) << precip_min << " " // set precision to 2 for precip
         << setw(5) << precip_max << " "
         << setw(5) << precip_avg / N << " : "
         << setw(5) << setprecision(1) << temp_min << " " // set precision to 1 for temp
         << setw(5) << temp_max << " "
         << setw(5) << temp_avg << endl;
}

void database::print_summary(string target)
{                                                  // here is my print for the summaries.
    queue<string> q;                               // I use a queue to handle multiple locations to ensure it is sorted by the geocode
    if (state_map.find(target) != state_map.end()) // first check if given target is a state
    {                                              // if so, loop through every geocode in the state and add it to the queue
        for (set<string>::iterator it = state_map[target].begin(); it != state_map[target].end(); it++)
        {
            q.push(*it);
        }
    }
    else if (geocode_map.find(target) != geocode_map.end()) // then check if it's a geocode
    {                                                       // if so, just add it to the queue
        q.push(target);
    }
    else // otherwise, print error
    {
        cout << "Target not found!" << endl;
        return;
    }

    while (!q.empty())
    {// loop through the queue and print the summaries
        string temp = q.front();
        geocode_map[temp].print(); // print the header
        for (int i = 0; i < 12; i++)
        { //print each month
            summary_cache[location_map[geocode_map[temp]]][i].print(i);
        }
        q.pop(); //remove the geocode from the queue
    }
}

void database::extract_rawdata(string &line)
{ // here is my function to replace all spaces with underscores and commas with spaces
    for (int i = 0; i < int(line.length()); i++)
    {
        if (line[i] == ' ')
        {
            line[i] = '_';
        }
        else if (line[i] == ',')
        {
            line[i] = ' ';
        }
    }
}

void database::extract_summary()
{ // here is my function to extract the rawdata from the rawdata_cache and fill in the summary_cache
    for (map<location, int>::iterator it = location_map.begin(); it != location_map.end(); it++)
    { //loop through every location
        for (list<rawdata>::iterator it2 = rawdata_cache[it->second].begin(); it2 != rawdata_cache[it->second].end(); it2++)
        { //loop through every rawdata
            summary_cache[it->second][it2->month - 1] += *it2; //use += operator to fill in the summary_cache
        }
    }
}
