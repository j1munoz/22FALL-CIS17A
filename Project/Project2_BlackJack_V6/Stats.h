#ifndef STATS_H
#define STATS_H
#include <string>
using namespace std;

class Stats {
    private:
        string name;
        int sum = 0;
    public:
        Stats() {name = ""; sum = 0;}
        void setName(string name) {this->name = name;}
        string getName() const {return name;}
        void setSum(int sum) {this->sum += sum;}
        int getSum() const {return sum;}
};

#endif /* STATS_H */
