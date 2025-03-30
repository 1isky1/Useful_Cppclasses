#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>
#include <exception>
#include <algorithm>
#include <string>
#include <iostream>

/*Define a new exception class for dictionary exceptions that inherits from
std::exception*/ 
class DictException : public std::exception 
{
    public:
    DictException(const char* umsg)
    : _msg(umsg){}

    const char* what() const throw(){
        return _msg.c_str();
    }
    private:
    std::string _msg;
};
template <typename _Tkey, typename _Tvalue> class dictionary{ /* dictionary class with const pairs of unique keys 
    and values on C++ : C# Dictionary<TKey,TValue> analog */
/* includes main methods and properties from standart C# data structure */
    public:
    dictionary(){ count = 0; }; //standard constructor, initializes empty vector
    dictionary(const std::vector<std::pair<_Tkey, _Tvalue>> &_id){ //constructor with std::vector parameter
        //check if user vector has two or more equal keys
        std::vector<_Tkey> ik = _get_keys(_id);
        bool ch = std::any_of(ik.begin(), ik.end(), [&](auto e){ 
            return std::count(ik.begin(), ik.end(), e) > 1;});
        if(!ch){ //if new parameter dictionary has unique keys
            //then set class parameters
            _d = _id;
            count = _id.size();
            keys = ik;
            values = _get_values(_id);
        }
        else{
            count = 0;
            throw DictException("Error: input dictionary has two or more same keys!");
        }
    }                                                 
    ~dictionary(){ //destructor, clears all key-value pairs
        _d.clear();
        count = 0;
        keys.clear(); values.clear();
    }
        
    //main properties of C# Dictionary<TKey,TValue>
    size_t count;                       //count all pairs "key-value" of _d
    std::vector<_Tkey> keys;              //all keys collection of _d
    std::vector<_Tvalue> values;            //all values collection of _d
    _Tvalue& operator[](const _Tkey k){        //operator analog Item[TKey]
        for(int i = 0; i < keys.size(); i++){
            if(keys[i] == k) return values[i];
        }
        throw DictException("Error: key doesn't exist!");
    }
    dictionary& operator=(const std::vector<std::pair<_Tkey, _Tvalue>> &_td){
        //same algorithm as in parameter constructor
        std::vector<_Tkey> ik = _get_keys(_td);
        bool ch = std::any_of(ik.begin(), ik.end(), [&](auto e){ 
            return std::count(ik.begin(), ik.end(), e) > 1;});
        if(!ch){
            this->_d = _td;
            this->count = _td.size();
            this->keys = ik;
            this->values = _get_values(_td);
            return *this;
        }
        else{
            throw DictException("Error: input dictionary has two or more same keys!");
        }
    } 
    //main methods
    void add(const _Tkey k, const _Tvalue v){ //adding input key and value to end of dictionary
        if(!contains_key(k)){
            std::pair<_Tkey, _Tvalue> t{k, v};
            _d.push_back(t);
            //update data in properties
            count = _d.size();
            keys = _get_keys(_d); values = _get_values(_d);
        }
        else{
            throw DictException("Error: key doesn't exist!");
        }
    }
    bool contains_key(const _Tkey k) const noexcept{ //check if input key exists
        return std::find(keys.begin(), keys.end(), k) != keys.end();
    }
    bool contains_val(const _Tvalue v) const noexcept{ //check if input value exists
        return std::find(values.begin(), values.end(), v) != values.end();
    }
    void remove(const _Tkey k){ //delete pair "key-value" from input key if it exists
        if(contains_key(k)){
            std::pair<_Tkey, _Tvalue> t; //temp pair for removing
            for(auto p : _d){
                if(p.first == k) t = p; //search and save pair to delete
            }
            _d.erase(std::find(_d.begin(), _d.end(), t));
            //update data in properties
            count = _d.size();
            keys = _get_keys(_d); values = _get_values(_d);
        }
        else throw DictException("Error: key doesn't exist!"); //otherwise key not found
    }
    void remove(const _Tkey k, _Tvalue &v){ //delete pair "key-value" from input key and save value to v variable
        if(contains_key(k)){
            for(auto p : _d){ //search right pair
                if(p.first == k) v = p.second; //and saving value to input variable
            }
            this->remove(k);
        }
        else throw DictException("Error: key doesn't exist!"); //otherwise key not found
    }
    bool try_add(const _Tkey k, const _Tvalue v) noexcept{ //add pair key-value, if successfully returns true, otherwise - false
        size_t old_count = count; //save previous dictionary size in var
        try{
            this->add(k, v);
        }catch(DictException){ return false; }
        return true;
    }
    bool try_get_value(const _Tkey k, _Tvalue &v) const noexcept{ //return value from key to variable, 
        //if successfully returns true, otherwise - false
        if(contains_key(k)){
            for(auto p : _d){ //search right pair
                if(p.first == k) v = p.second; //and saving value to input variable
            }
            return true;
        }
        return false;
    }
    void output(){
        for(auto p : _d){
            std::cout << p.first << " : " << p.second << std::endl;
        }
    }
    private:
    std::vector<std::pair<_Tkey, _Tvalue>> _d; //main dictionary
    std::vector<_Tkey> _get_keys(const std::vector<std::pair<_Tkey, _Tvalue>> &_td){  //private method initializes and return a new vector of all dictionary keys
        std::vector<_Tkey> rv;
        for(auto p : _td){ rv.push_back(p.first); }
        return rv;
    }
    std::vector<_Tvalue> _get_values(const std::vector<std::pair<_Tkey, _Tvalue>> &_td){ //private method initializes and return a new vector of all dictionary values
        std::vector<_Tvalue> rv;
        for(auto p : _td){ rv.push_back(p.second); }
        return rv;
    }
};
#endif