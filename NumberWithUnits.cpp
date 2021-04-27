#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#define EPS 0.00001
#include "NumberWithUnits.hpp"
using namespace ariel;
using namespace std;
namespace ariel{


     unordered_map<string,unordered_map<string, double>> NumberWithUnits::map=unordered_map<string,unordered_map<string, double>>();
     void NumberWithUnits::read_units(ifstream& units_file)
     {
        std::string useless, unit1, unit2;
        double value2=0;
        while(units_file>>useless)
        {
            units_file>>unit1>>useless>>value2>>unit2;
            if(map.find(unit1)!=map.end())//check if map contains unit1
            {
                for(auto const& pair:map[unit1])
                {
                    map[pair.first][unit2]=1/pair.second*value2;
                }
                map[unit1][unit2]=value2;
            }
            else
            {
               unordered_map<string, double> temp_map=unordered_map<string, double>();
               for(auto const& pair:map[unit2])
                {
                    temp_map[pair.first]=pair.second*value2;
                    map[pair.first][unit1]=1/pair.second/value2;
                }
               temp_map[unit2]=value2;
               map[unit1]=temp_map;
            }
            if(map.find(unit2)!=map.end())
            {
                map[unit2][unit1]=1/value2;
                for(auto const& pair:map[unit1])
                {
                    if(map[unit2].find(pair.first)==map[unit2].end() && pair.first!=unit2)
                    {
                    map[unit2][pair.first]=pair.second/value2;
                    }
                }
            }
            else
            {
                unordered_map<string, double> temp_map=unordered_map<string, double>();
                for(auto const& pair:map[unit1])
                {
                    if(pair.first!=unit2)
                    {
                    temp_map[pair.first]=pair.second/value2;
                    }
                }
                temp_map[unit1]=1/value2;
                map[unit2]=temp_map;
            }
            
        }
     }

     NumberWithUnits NumberWithUnits::operator+=(const  NumberWithUnits& other)
     {
        
            if(this->unit==other.unit)
            {
                this->value=this->value+other.value;
                return *this;
            }
            else if(map[other.unit].find(this->unit)!=map[other.unit].end())//check if we can convert between the units
            {
                this->value=this->value+other.value*NumberWithUnits::map[other.unit][this->unit];
                return *this;
            }
            else{
                throw logic_error("diffrent types of units");
            }
        
        
     }
     NumberWithUnits NumberWithUnits::operator-=(const  NumberWithUnits& other)
     {
            if(this->unit==other.unit)
            {
                this->value=this->value-other.value;
                return *this;
            }
            else if(map[other.unit].find(this->unit)!=map[other.unit].end())//check if we can convert between the units
            {
                this->value=this->value-other.value*map[other.unit][this->unit];
                return *this;
            }
            else{
                throw logic_error("diffrent types of units");
            }
     }
     NumberWithUnits NumberWithUnits::operator+(const  NumberWithUnits& other)
     {
         
            if(this->unit==other.unit)
            {
                NumberWithUnits a{this->value+other.value, this->unit};
                return a;
            }
            else if(map[other.unit].find(this->unit)!=map[other.unit].end())
            {
                NumberWithUnits a{this->value+other.value*map[other.unit][this->unit], this->unit};
                return a;
            }
            else{
                throw logic_error("diffrent types of units");
                }
        }
     
     NumberWithUnits NumberWithUnits::operator-(const  NumberWithUnits& other)
     {
            if(this->unit==other.unit)
            {
                NumberWithUnits a{this->value-other.value,this->unit};
                return a;
            }
            else if(map[other.unit].find(this->unit)!=map[other.unit].end())
            {
                NumberWithUnits a{this->value-other.value*map[other.unit][this->unit], this->unit};
                return a;
            }
            else{
                throw logic_error("diffrent types of units");
                }
     }

    NumberWithUnits NumberWithUnits::operator+()
    {
         return NumberWithUnits{this->value,this->unit};
    }
    NumberWithUnits NumberWithUnits::operator-()
    {
       return NumberWithUnits{-(this->value),this->unit};
    }


     bool NumberWithUnits::operator<(const  NumberWithUnits& other)const
     {
            if(this->unit==other.unit)
            {
                if(this->value<other.value)
                {
                    return true;
                }
                return false;
            }
            else if(NumberWithUnits::map[other.unit].find(this->unit)!=map[other.unit].end())
            {
                if(this->value<other.value*map[other.unit][this->unit])
               {
                   return true;
               }
               return false;
            }
            else{throw logic_error("diffrent types of units");}
        }
     
     bool NumberWithUnits::operator>(const  NumberWithUnits& other)const
     {
            if(this->unit==other.unit)
            {
                if(this->value>other.value)
                {
                    return true;
                }
                return false;
            }
            else if(NumberWithUnits::map[other.unit].find(this->unit)!=map[other.unit].end())
            {
                if(this->value>other.value*map[other.unit][this->unit])
               {
                   return true;
               }
               return false;
            }
            else{throw logic_error("diffrent types of units");}
        }
     

     bool NumberWithUnits::operator<=(const  NumberWithUnits& other)const
     {
            if(this->unit==other.unit)
            {
                if(this->value<=other.value)
                {
                    return true;
                }
                return false;
            }
            else if(NumberWithUnits::map[other.unit].find(this->unit)!=map[other.unit].end())
            {
                if(this->value<other.value*map[other.unit][this->unit]||abs(this->value-other.value*map[other.unit][this->unit])<EPS)
               {
                   return true;
               }
               return false;
            }
            else{throw logic_error("diffrent types of units");}
        }
     

     bool NumberWithUnits::operator>=(const  NumberWithUnits& other)const
     {
            if(this->unit==other.unit)
            {
                if(this->value>=other.value)
                {
                    return true;
                }
                return false;
            }
            else if(NumberWithUnits::map[other.unit].find(this->unit)!=map[other.unit].end())
            {
                if(this->value>other.value*map[other.unit][this->unit]||abs(this->value-other.value*map[other.unit][this->unit])<EPS)
               {
                   return true;
               }
               return false;
            }
            else{throw logic_error("diffrent types of units");}
        }
     
     bool NumberWithUnits::operator==(const  NumberWithUnits& other)const
     {
          if(this->unit==other.unit)
            {
                if(abs(this->value-other.value)<EPS)
                {
                    return true;
                }
                return false;
            }
            else if(NumberWithUnits::map[other.unit].find(this->unit)!=map[other.unit].end())
            {
                if(abs(this->value-other.value*map[other.unit][this->unit])<EPS)
               {
                   return true;
               }
               return false;
            }
            else{throw logic_error("diffrent types of units");}
     }
     bool NumberWithUnits::operator!=(const  NumberWithUnits& other)const
     {
         if((*this)==other)
         {
            return false;
         }
         return true;
     }

     NumberWithUnits& NumberWithUnits::operator++()
     {
        ++this->value;
        NumberWithUnits a{this->value,unit};
        return *this;
     }
     NumberWithUnits NumberWithUnits::operator++(int dummy)
     {
        NumberWithUnits a{this->value,this->unit};
        this->value+=1;
        return a;
     }
     NumberWithUnits& NumberWithUnits::operator--()
     {
        this->value-=1;
        return *this;
     }
     NumberWithUnits NumberWithUnits::operator--(int dummy)
     {
         
        NumberWithUnits a{this->value,this->unit};
        this->value-=1;
        return a;
     }

    
     NumberWithUnits NumberWithUnits::operator*(double d)
     {
         
        NumberWithUnits a{d*this->value,this->unit};
        return a;
     }

    std::ostream& operator<<(std::ostream& output,NumberWithUnits const & num)
    {
        output <<num.value<< "[" <<num.unit<<"]";
        return output;
    }
    istream& operator>>(std::istream& input,NumberWithUnits& num)
    {
        char useless=' ';
        string temp_string,whole_string,unit;
        double val=0;
        //input>>val>>useless>>unit>>useless;
        while (!input.eof())
        {
            input>>temp_string;
            
            whole_string+=temp_string;
            if(whole_string[whole_string.length()-1]==']')//insert to whole sring untill its read ']'
            {
                break;
            }
        }
        replace(whole_string.begin(),whole_string.end(),']',' ');//replace the char ']' with ' '
        //input>>val>>useless>>unit>>useless;
        replace(whole_string.begin(),whole_string.end(),'[',' ');//replace the char '[' with ' '
        istringstream iss1(whole_string);
        iss1>>val>>unit;//read the value and the unit
        if(NumberWithUnits::map.find(unit)==NumberWithUnits::map.end())
        {
            throw logic_error("this unit doesnt in the map");
        }
        
        num.value=val;
        num.unit=unit;
        return input;
    }
    NumberWithUnits operator*(double d,NumberWithUnits n)
    {
         return n*d;
    }
}
