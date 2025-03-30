#include "roman.h"

int main(){
    /*test constructors*/
    roman r; //standart constructor
    std::cout << r << std::endl; // Zero

    //test constructor roman(const std::string)
    try{ 
        roman("XIIksadk"); //incorrect symbols
    }catch(RomanException &e){
        std::cout << e.what() << std::endl; 
    }
    try{ 
        roman("IIXVIII"); //incorrect sequence
    }catch(RomanException &e){
        std::cout << e.what() << std::endl; 
    }
    try{ 
        roman("XXXXVI"); //incorrect repeats of one-size literals
    }catch(RomanException &e){
        std::cout << e.what() << std::endl; 
    }
    try{ 
        roman("XCXCV"); //incorrect repeats of two-size literals
    }catch(RomanException &e){
        std::cout << e.what() << std::endl; 
    }

    //test constructor roman(const int)
    try{ 
        roman(-23); //input parameter out of minimum range
    }catch(RomanException &e){
        std::cout << e.what() << std::endl; 
    }
    try{ 
        roman(4001); //input parameter out of maximum range
    }catch(RomanException &e){
        std::cout << e.what() << std::endl; 
    }

    //right inputs
    std::cout << roman("MMMCMXCIX") << " " << roman(356) << std::endl; // MMMCMXCIX CCCLVI

    //test binary ariphmetical operators +/-
    roman r1("MMMCMXCIX"), r2("II"); 
    std::cout << r1 + r2 << std::endl; //result is out of maximum range, output "Zero"
    roman r3, r4("II"); 
    std::cout << r3 - r4 << std::endl; //result is out of minimum range, output "Zero"
    
    roman r5("XXII"), r6("XVI");
    std::cout << r5 + r6 << " "<< r5 - r6 << std::endl; //output XXXVIII VI

    //test assignment operator =
    roman r7(5);
    std::cout << r7 << std::endl; //V
    r7 = "VVX"; //incorrect initialize
    std::cout << r7 << std::endl; //still V

    r7 = "LVII"; //correct initialize
    std::cout << r7 << std::endl; //LVII

    //test unar operators <, >, ==
    roman r8("LXXVII"), r9("CIII"); //77 103
    std::cout << std::boolalpha << (r8 > r9) << std::endl; //false
    std::cout << std::boolalpha << (r8 < r9) << std::endl; //true
    std::cout << std::boolalpha << (r8 == r9) << std::endl; //false
    r9 = r8;
    std::cout << std::boolalpha << (r8 >= r9) << std::endl; //true
    std::cout << std::boolalpha << (r8 <= r9) << std::endl; //true
    std::cout << std::boolalpha << (r8 != r9) << std::endl; //false

    //test istream operator
    roman ur;
    std::cin >> ur;
    std::cout << ur << std::endl;
    return 0;
}