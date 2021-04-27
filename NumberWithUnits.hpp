#ifndef NUMBERWITHUNITS
#define NUMBERWITHUNITS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;
namespace ariel
{
class  NumberWithUnits
{
private:
    double value;
    std::string unit;
    
public:
    static unordered_map<string,unordered_map<string, double>> map;//hashmap key(unit) -> hashmap(key(unit)->int)
     NumberWithUnits(double val,std::string u)
     {
        if(map.find(u)==map.end())
        {
            throw logic_error("this unit doesnt in the map");
        }
        value=val;
        unit=u;
     }
    ~ NumberWithUnits()
    {

    }

     static void read_units(std::ifstream& units_file);

     NumberWithUnits operator+=(const  NumberWithUnits& other);
     NumberWithUnits operator-=(const  NumberWithUnits& other);
     NumberWithUnits operator+(const  NumberWithUnits& other);
     NumberWithUnits operator-(const  NumberWithUnits& other);
     NumberWithUnits operator+ ();
     NumberWithUnits operator- ();
     


      bool operator<(const  NumberWithUnits& other)const;
      bool operator>(const  NumberWithUnits& other)const;
      bool operator<=(const  NumberWithUnits& other)const;
      bool operator>=(const  NumberWithUnits& other)const;
      bool operator==(const  NumberWithUnits& other)const;
      bool operator!=(const  NumberWithUnits& other)const;

     NumberWithUnits& operator++();
     NumberWithUnits operator++(int dummy);
     NumberWithUnits& operator--();
     NumberWithUnits operator--(int dummy);

     NumberWithUnits operator*(double d);

     friend std::ostream& operator<<(std::ostream& output,const NumberWithUnits& num);
     friend std::istream& operator>>(std::istream& input,NumberWithUnits& num);
     friend NumberWithUnits operator*(double d,NumberWithUnits n);
     
};

}
#endif