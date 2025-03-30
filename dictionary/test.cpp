#include "dictionary.h"

int main(){
    dictionary<std::string, int> d1 = {{ //test dictionary with pararmeter constructor
        {"A", 1},
        {"B", 2},
        {"C", 3}
    }};
    d1.output();
    /*  A : 1
        B : 2
        C : 3
    */
    std::cout << std::endl;
    d1.add("D", 5); //add new pair "key-value"
    d1.output();
    /*  A : 1
        B : 2
        C : 3
        D : 5
    */
   std::cout << d1.count << std::endl;
   std::cout << std::boolalpha << d1.contains_key("A") << " " << d1.contains_key("H") << std::endl;
   //output true false
   std::cout << std::boolalpha << d1.contains_val(0) << " " << d1.contains_val(1) << std::endl;
   //output false true
   try{
        d1.remove("H");
    }catch(DictException &e){ //catches exception key doesn't exists
        std::cout << e.what() << std::endl;
    }
    
    try{ //delete pair and save value
        int v;
        d1.remove("A", v);
        d1.output();
        /* 
        B : 2
        C : 3
        D : 5
        */
        std::cout << v << " " << d1.count << std::endl; //output 1 3
    }catch(DictException &e){
        std::cout << e.what() << std::endl;
    }
    dictionary<std::string, int> d2 = {{ //test dictionary with pararmeter constructor
        {"A", 1},
        {"C", 3}
    }};

    std::cout << std::boolalpha << d2.try_add("C", 8) << std::endl; //false, cause key already exists
    std::cout << std::boolalpha << d2.try_add("E", 8) << std::endl; //true, add new pair
    d2.output();
    /* 
    A : 1
    C : 3
    E : 8
    */
    int v1;
    std::cout << std::boolalpha << d2.try_get_value("E", v1) << " " << v1 << std::endl; //true, save 8
    std::cout << std::boolalpha << d2.try_get_value("H", v1) << " " << v1 << std::endl; //false, v2 still 8
    dictionary<std::string, int> months; 
    months = {
        {"Jan", 1},
        {"Feb", 2},
        {"Mar", 3}
    };
    std::cout << std::boolalpha << months.try_add("Apr", 4) << std::endl; //true, add new pair
    months.output();
    std::cout << std::endl;
    int v2;
    months.remove("Mar", v2);
    months.output();
    std::cout << v2 << std::endl;
    try{
        months.remove("Jun", v2);
    }catch(DictException &e){
        std::cout << e.what() << std::endl;
    }
    months.output();
    std::cout << v2 << std::endl;
    for(auto k : months.keys){
        std::cout << k << " ";
    }
    std::cout << std::endl << months["Jan"] << " " << months["Feb"] << std::endl;
    try{
        months["Oct"]; //doesn't existing key
    }catch(DictException &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}