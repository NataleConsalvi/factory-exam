#ifndef DELIV_H
#define DELIV_H


#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


using std::unordered_map;
using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::ostream;
using std::stringstream;

#define MIN_DELAY 10

template<typename T, typename U>
string map2str(unordered_map<T,U> m) {
    stringstream ss;
    int i=0;
    ss << "{\n";
    for (auto& els : m){
        if (i > 0){
            ss << "," << endl;
        }        
        ss << " " << els.first << " : " << els.second;
        i += 1;
    };
    ss << endl << "}";
    return ss.str();
}

template<typename T>
string vec2str(const vector<T> vec){
    stringstream ss;
    int i=0;
    for (const T& el : vec){
        if (i>0){
            ss << ", ";
        }
        ss << el;
        i++;
    }
    return ss.str();
}

template<typename T, typename U>
string pair2str(const std::pair<T, U> p){
    stringstream ss;
    ss << "pair(" << p.first << "," << p.second << ")";
    return ss.str();
}

struct Date {    
    int year;    
    int month;  // 1-12 inclusi
    int day;    // 1-31 inclusi
    
    // Overrides default ostream << behaviour      
    friend ostream& operator<<(ostream& os, const Date& date);      
};


inline ostream& operator<<(ostream& os, const Date& date){
    os << "Date(";
    os << date.year << "," << date.month << "," << date.day << ")";
    return os;
};

struct Time {
    int hour;   // 0->11 incluse
    int minute; // 0 -> 59 inclusi

    friend ostream& operator<<(ostream& os, const Time& time);      
};


inline ostream& operator<<(ostream& os, const Time& time){
    os << "Time(";
    os << time.hour << "," << time.minute << ")";
    return os;
};





#endif // DELIV
