/*
Alan Khalili
 Lab 2: Program That uses a linked list to store precipitation and tempurature data from cities, and calculate their monthly averages, mins and max.
*/
#include <string>
#include <iostream>
#include <iomanip>

#include "Support.h"

using namespace std;

//This is my operator overload. I just took the city and state strings of the location structs and compared them < than means alphabetically first.
bool location::operator<(const location &next) const {
    if (state < next.state)
        return true;
    else if (state > next.state) {
        return false;
    } else if (city < next.city && state == next.state) {
        return true;
    }
    return false;

}
//This is my second operator overload. Same thing just seeing if geocode is same.
bool location::operator==(const location &next) const {
    return geocode == next.geocode;
}

//This is my constructor for the node.
list::node::node(const location &n_station) {
    //First thing i do is set the size of the arrays to the 12 month of the year.
        station = n_station;
        N = new int[12];
        total_precip = new float[12];
        max_precip = new float[12];
        min_precip = new float[12];
        total_temp = new int[12];
        max_temp = new int[12];
        min_temp = new int[12];
//Now I fill every 12 with 0 to prevent an error.
		for(int i = 0; i < 12; i++){
			N[i] = 0;
			total_precip[i] = 0;
			max_precip[i] = 0;
            min_precip[i] = 0;
			total_temp[i] = 0;
			max_temp[i] = 0;
            min_temp[i] = 0;
		}
		next = nullptr; //initializing next pointer.
}

//Here is my deconstructor for the node.
list::node::~node() {
    //All im doing is delete each array.
    delete[] N;
    delete[] total_precip;
    delete[] min_precip;
    delete[] max_precip;
    delete[] total_temp;
    delete[] min_temp;
    delete[] max_temp;

}
//Here is my own function that I added myself. I made sure to add this to the header file. I did this to save some time and confusion in my insert function.
void list::node::fill(const data &d) {
    //First I check for an empty node
	if(N[d.month-1] == 0){
        total_precip[d.month-1] = d.precip;
        max_precip[d.month-1] = d.precip;
        min_precip[d.month-1] = d.precip;
        total_temp[d.month-1] = d.temp;
        max_temp[d.month-1] = d.temp;
        min_temp[d.month-1] = d.temp;
    }
    else{
        //If it's not empty I find the max/mins and increase the totals
        if(d.precip < min_precip[d.month-1]) {
            min_precip[d.month - 1] = d.precip;
        }
        if(d.precip > max_precip[d.month-1]){
            max_precip[d.month-1] = d.precip;
        }
        if(d.temp < min_temp[d.month-1]){
            min_temp[d.month-1] = d.temp;
        }
        if(d.temp > max_temp[d.month-1]){
            max_temp[d.month-1] = d.temp;
        }
        total_precip[d.month-1] += d.precip;
        total_temp[d.month-1] += d.temp;
    }
	N[d.month-1]++; //Here i incriment N for finding averrages.

}
//Here is my print. It's pretty standard.
void list::node::print_station() {
    cout << "------------------------------------------\n";
    cout << station.city << ", " << station.state << " (" << station.geocode << ")" << endl;
    cout << "------------------------------------------\n";
}
//Here is my print_data. I used iomanip because I was having issues with the grade checker.
void list::node::print_data() {
    string month_conversion[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for(int i = 0; i < 12; i++){
    cout << setw(3) << left << month_conversion[i] << ":" << setfill(' ') << fixed << setprecision(2) << setw(6) << right << total_precip[i]<< setfill(' ') << fixed << setprecision(2) << setw(6) << right << total_precip[i] / N[i] << setfill(' ') << fixed << setprecision(2) << setw(6) << right << max_precip[i] << setfill(' ') << fixed << setprecision(2) << setw(6) << right << min_precip[i] << " :" << setfill(' ') << setw(4) << right << total_temp[i] / N[i] << setfill(' ') << setw(4) << right << max_temp[i] << setfill(' ') << setw(4) << right << min_temp[i] << endl;
      }
}

//Here is my list constructor. Just declares head.
list::list() {
    head = new node();
}
//Here is my deconstructor. It works by moving head and deleting a pointer until there is nothing left.
list::~list() {
    while(head->next != nullptr){
        node *temp = head->next;
        head->next = temp->next;
        delete temp;
    }
    delete head;
}
//Here is my insert function.
void list::insert(const location &l, const data &d) {
	//Here I insert the first node into if the list is empty
	if (head->next == nullptr) {
		node *newNode = new node(l);
		newNode->fill(d);
		head->next = newNode;
	}
	else {
		//Here I declare a pointer called entry. I use it to find where the next node goes.
		node *entry = head;
		//checks if it is less. If it is it redoes the loop.
		while (entry->next != nullptr && entry->next->station < l) {
			entry = entry->next;
		}
		//when it find's where it's supposed to be, it fills in the data.
		if (entry->next != nullptr && entry->next->station == l) {
			entry->next->fill(d);
		}
		//Otherwise, it'll make a new node.
		else {
			node *newNode = new node(l);
			newNode->fill(d);
			newNode->next = entry->next;
			entry->next = newNode;
		}
	}
}

//Here is my print function.
void list::print(const char *code) {
    node *finder = head->next; //I declare another pointer to find where to print stuff out.
    //Here is what I do when the user does not enter a code
    if(code == NULL){
        while(finder != nullptr){
            finder->print_station();
            finder->print_data();
            finder = finder->next;
        }
    }
    //Here is what I do when the user does enter a code
    else{
        while(code != finder->station.geocode){
		finder = finder->next;
		}
		finder->print_station();
		finder->print_data();
        }
    }
