//Alan Khalili
//Here is my Support.h file. The only thing that I added was the fill function.

#include <string>

using namespace std;

struct location {
    string city;
    string state;
    string geocode;

    bool operator<(const location &) const;

    bool operator==(const location &) const;
};

struct data {
    int month;
    float precip;
    int temp;
};

class list {
    struct node {
        node(const location &n_station = location());

        ~node();

        void fill(const data &);//Here is the fill function. It just takes in data to make my insert look more tidy.

        void print_station();

        void print_data();

        location station;

        int *N;

        float *total_precip;
        float *max_precip;
        float *min_precip;

        int *total_temp;
        int *max_temp;
        int *min_temp;

        node *next;
    };

public:
    list();

    ~list();

    void insert(const location &, const data &);

    void print(const char *);


private:
    node *head;
};
