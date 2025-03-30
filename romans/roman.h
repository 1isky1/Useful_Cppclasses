#ifndef ROMANS_H
#define ROMANS_H
#include "dictionary.h" //include my user class from upper folder :)

/* This class intended for simple convert from int to roman and contrariwise 
    Also defined simple ariphmetical funtions such as summa, difference; compare operators >, < and ==;
    input, output operators
    Working ariphmetical range from 1 (except 0 as "Zero") to 3999.
*/

class RomanException : public std::exception /*define user-exception class that inherits from
    std::exception*/
{
    public:
    RomanException(const char* umsg)
    : _msg(umsg){}

    const char* what() const throw(){
        return _msg.c_str();
    }
    private:
    std::string _msg;
};

class roman{ //main Roman class
    public:
    roman() { r = "Zero"; }; //std constructor, initializes by "Zero"
    roman(const int _ui){ //constructor with int number, convert to roman string
        if(_ui > 0 && _ui < 4000){ //checking correct range
            r = to_roman(_ui);
        }
        else{
            r = "Zero";
            throw RomanException("Error! Acceptable range for roman numerals - from 1 (except 0 as 'Zero') to 3999.");}
    }
    roman(std::string const& _us){ //constructor with string, initializes r field
        switch (check_input(_us))
        {
        case 0:
            throw RomanException("Error! Incorrect symbols in roman entry: the entry must contain the correct symbols as upper-case latin literals and only these ones -> 'M', 'D', 'C', 'L', 'X', 'V', and 'I'.");
            r = "Zero";
            break;
        case 1:
            throw RomanException("Error! Incorrect sequence of roman literals: the entry must contain the correct sequence of letters from the largest to the smallest value. For example CXXIII (123): 100->20->3.");
            r = "Zero";
            break;
        case 2:
            throw RomanException("Error! Incorrect repeat of roman literal digits: the number of repetitions of single-character digits (e.g. 'I', 'V', 'X' etc) should not exceed 3 characters in one entry, and two-character digits (e.g. 'CM', 'CD', 'IV' etc) should not exceed 1.");
            r = "Zero";
            break;
        default:
            r = _us;
            break;
        }
    }
    roman& operator=(std::string const &s){
        if(check_input(s) == -1) this->r = s;
        return *this;
    }
    roman& operator=(roman const &rn) noexcept{
        this->r = rn.r;
        return *this;
    }
    int to_int() noexcept{
        int result = 0;
        if(r != "Zero"){
            std::string buff = r;
            std::vector<std::string> rk = romans.keys;
            for(std::vector<std::string>::iterator it = rk.begin(); buff.length() > 0;){
                int ti = buff.find(*it);
                if(ti == 0){
                    int count = 0;
                    for(;ti == 0;){
                        buff = buff.substr((*it).length(), buff.length()-1); count++;
                        ti = buff.find(*it);
                    }
                    result += romans[*it] * count;
                }
                it++;
            }
        }
        return result;
    }          
    //binary ariphmetic operators
    friend roman operator+(roman& r1, roman& r2) noexcept{
        int res = r1.to_int() + r2.to_int();
        try{ 
            return roman(res);
        }catch(RomanException){
            return roman();
        }
    }
    friend roman operator-(roman& r1, roman& r2) noexcept{
        int res = r1.to_int() - r2.to_int();
        try{ 
            return roman(res);
        }catch(RomanException){
            return roman();
        }
    }
    friend bool operator>(roman& r1, roman& r2) noexcept{
        return r1.to_int() > r2.to_int();
    }
    friend bool operator<(roman& r1, roman& r2) noexcept{
        return r1.to_int() < r2.to_int();
    }
    friend bool operator>=(roman& r1, roman& r2) noexcept{
        return r1.to_int() >= r2.to_int();
    }
    friend bool operator<=(roman& r1, roman& r2) noexcept{
        return r1.to_int() <= r2.to_int();
    }
    friend bool operator==(roman& r1, roman& r2) noexcept{
        return r1.to_int() == r2.to_int();
    }
    friend bool operator!=(roman& r1, roman& r2) noexcept{
        return r1.to_int() != r2.to_int();
    }
    friend std::ostream& operator <<(std::ostream&, roman const& _r) noexcept{
        std::cout << _r.r;
        return std::cout;
    }
    friend std::istream& operator >>(std::istream&, roman& _r) noexcept{
        std::string _us;
        std::cin >> _us;
        if(_r.check_input(_us) == -1) _r.r = _us;
        return std::cin;
    }
    private:
    std::string r; //main field for keeping roman number
    dictionary<std::string, int> romans = {{ //dictionary of all main roman literal digits
        {"M", 1000},
        {"CM", 900},
        {"D", 500},
        {"CD", 400},
        {"C", 100},
        {"XC", 90},
        {"L", 50},
        {"XL", 40},
        {"X", 10},
        {"IX", 9},
        {"V", 5},
        {"IV", 4}, 
        {"I", 1}
    }};
    std::string char_multiply(std::string const s, int const c){//private function for generate string of repeating character
        std::string res;
        for(int i = 0; i < c; i++){
            res += s;
        }
        return res;
    }
    int check_input(const std::string _ur){ //returns a number of error and throws an exception if error occured
        //checking correct literals
        std::string buff = _ur;
        std::string liters = "MDCLXVI";
        for(char c : buff){
            if(liters.find(c) == -1){
                return 0; }
        }
        //checking correct sequence
        for(std::vector<std::string>::iterator it = romans.keys.begin(); it != romans.keys.end();){
            if(buff.find(*it) == 0) buff = buff.substr((*it).length(), buff.length()-1);
            else it++;
        }
        if(buff.length() > 0){
            return 1; }
        /* code */   
        //checking correct repeats of literals
        buff = _ur; //update buffer
        for(std::vector<std::string>::iterator it = romans.keys.begin(); it != romans.keys.end();){
            int ti = buff.find(*it);
            if(ti == 0){
                int count = 0;
                for(;ti == 0;){
                    buff = buff.substr((*it).length(), buff.length()-1); count++;
                    ti = buff.find(*it);
                }
                if(((*it).length() == 1 && count > 3) || //counting one-size literals for e.g. C, D, X, I etc
                ((*it).length() == 2 && count > 1)) //counting two-size literals for e.g. CM, CD, etc
                {return 2;}
            }
            it++;
        }
        //if it's all right in input return -1
        return -1;
    }
    std::string to_roman(const int num){
        if(num > 0){
            std::string result;
            std::vector<std::string> rk = romans.keys;
            int buff_n = num;
            for(std::vector<std::string>::iterator it = rk.begin();it != rk.end();){
                try{
                    if(buff_n % romans[*it] != buff_n){
                        result += char_multiply(*it, buff_n / romans[*it]);
                        buff_n %= romans[*it];
                    }
                    it++;
                }catch(DictException){ return "Zero"; }
            }
            return result;
        }
        return "Zero";
    }
};
#endif