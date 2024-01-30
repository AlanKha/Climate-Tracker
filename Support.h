//Alan Khalili
//Support.h I wrote this file to contain the code for the classes and functions that I will be using in my program

#ifndef SUPPORT
#define SUPPORT
//here I included all the libraries I will be using
#include <map> //map for location_map
#include <unordered_map> //unordered_map for state_map and geocode_map
#include <vector> //vector for rawdata_cache and summary_cache
#include <list> //list for rawdata_cache
#include <set> //set for state_map
#include <string> //string for location, state, and geocode

using namespace std;

struct location { //every location will have a city, state, and geocode
  string city;
  string state;
  string geocode;

  bool operator<(const location &other) const; //operator overload for location_map
  void print();
};

struct rawdata { //every rawdata will have a month, precip, and temp
  int month;
  float precip;
  int temp;

  void print(); 
};

struct summary { //every summary will have a location, N, precip_avg, precip_max, precip_min, temp_avg, temp_max, and temp_min
  int N;

  float precip_avg; //this is more like a total precip counter, and it will be divided by N at print time
  float precip_max;
  float precip_min;

  float temp_avg;
  float temp_max;
  float temp_min;

  summary(); //constructor
  void operator+=(const rawdata &other); //operator overload for summary_cache
  void print(int month);
};

class database { //this is my database class
  public: 
    void init_rawdata(string filename); //this function will take in a filename and parse the rawdata into the rawdata_cache
    void print_rawdata(); //this function will print the rawdata_cache

    void init_summary(); //this function will take the rawdata_cache and parse it into the summary_cache
    void print_summary(string target); //this function will take in a location and print the summary_cache for that location

  private:
    void extract_rawdata(string &line); //this function will take in a line and replace all spaces with underscores and commas with spaces
    void extract_summary(); //this function will take in a line and replace all spaces with underscores and commas with spaces

    map <location,int> location_map; //this map will store the location and the index of the rawdata_cache
    vector< list<rawdata> > rawdata_cache; //this cache will store the rawdata

    unordered_map <string, set<string> > state_map; //this map will store the state and the set of geocodes
    unordered_map <string, location> geocode_map; //this map will store the geocode and the location
    vector<vector <summary> > summary_cache; //this cache will store the summary
};

#endif
