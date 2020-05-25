#ifndef ukstemmer_header
#define ukstemmer_header

#include <utility> 
#include <string>
#include "inttypes.h"
#include "math.h"

// literature:
//http://math.ivanovo.ac.ru/dalgebra/Khashin/cutil/porter.html
class UkStemmer{
    public:
    static const std::string vowel[];
    static const std::string dieprislivnik[];
    static const std::string perfectivegerund[];
    static const std::string perfectivegerund_a_ya[];
    static const std::string adjective[];
    static const std::string reflexive[];
    static const std::string participle[];
    static const std::string verb[];
    static const std::string noun[];
    static const std::string rvre[];
    static const std::string deriviational[];

    static const std::string consonant[];
    static const std::string doubledConsonant[];
    static const std::string super_suffix[];
    
    public:
    UkStemmer(){};
    static std::string stem(std::string word);
    private:
    static bool remove_ending(std::string&stemmed, const std::string endings[],int arrlen);
    static bool remove_ending(std::string&stemmed, const std::string endings[], int arrlen, const std::string prefix[], int prefixlen);
    static void remove_double_cons(std::string &stemmed);
    static void preprocess(std::string&stemmed);
};
#endif 