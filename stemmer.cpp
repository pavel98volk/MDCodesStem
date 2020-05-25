#include "stemmer.h"
#include <utility>
#include "string.h"
#include <iostream>
/* rus + ukr
const std::string UkStemmer::vowel[] = {"а","е","и","о","у","ю","я","і","ї","є"};//length 10+1;
const std::string UkStemmer::perfectiveground[]={"ив","ивши","ившись","ыв","ывши","ывшись"};
const std::string UkStemmer::perfectiveground_a_ya[]={"в","вши","вшись"};
const std::string UkStemmer::adjective[] = {"ими","ій","ий","а","е","ова","ове","ів","є","їй","єє","еє","я","ім","ем","им","ім","их","іх","ою","йми","іми","у","ю","ого","ому","ої"};
const std::string UkStemmer::reflexive[] = {"ся","cь","си"}; //to check;
const std::string UkStemmer::participle[] = {"(ий","ого","ому","им","ім","а","ій","у","ою","ій","і","их","йми","их)"}; //to check;
const std::string UkStemmer::verb[] = {"сь","ся","ив","ать","ять","у","ю","ав","али","учи","ячи","вши","ши","е","ме","ати","яти","є"}; //to check;
const std::string UkStemmer::noun[] = {"а","ев","ов","е","ями","ами","еи","и","ей","ой","ий","й","иям","ям","ием","ем","ам","ом","о","у","ах","иях","ях","ы","ь","ию","ью","ю","ия","ья","я","і","ові","ї","ею","єю","ою","є","еві","ем","єм","ів","їв","ю"};
const std::string UkStemmer::rvre[] = {"а","е","и","о","у","ю","я","і","ї","є"}; //to check;
const std::string UkStemmer::deriviational[] = {"[^аеиоуюяіїє][аеиоуюяіїє]+[^аеиоуюяіїє]+[аеиоуюяіїє].*(?<=о)сть?$"}; //to check;
*/
const std::string UkStemmer::vowel[] = {"а","е","и","о","у","ю","я","і","ї","є"};//length 10+1;
// not used (for now)
const std::string UkStemmer::consonant[] = {"б","в","г","ґ","д","ж","з","й","к","л","м","н","п","р","с","т","ф","х","ц","ч","ш","щ"};
//https://webpen.com.ua/pages/Pravopys_Pryholosnyh/6_extension_doubling_consonants.html
const std::string UkStemmer::doubledConsonant[] = {"б","в","г","ґ","д","ж","з","к","л","м","н","п","р","с","т","ф","х","ц","ч","ш","щ"};//length 10+1;
// дієприслівник
const std::string UkStemmer::dieprislivnik[] = {"учи", "ючи","ачи","ячи"};
const std::string UkStemmer::perfectivegerund[]={"ив","ивши","ившись"}; //  http://litopys.org.ua/ukrmova/um207.htm //diepricmetnikoviy zvorot
const std::string a_ya[]={"а","я"};
const std::string UkStemmer::perfectivegerund_a_ya[]={"в","вши","вшись"};
// http://uk.wikipedia.org/wiki/Прикметник + http://wapedia.mobi/uk/Прикметник
const std::string UkStemmer::adjective[] = {"ими","ій","ий","а","е","ова","ове","ів","є","їй","єє","еє","я","ім","ем","им","ім","их","іх","ою","йми","іми","у","ю","ого","ому","ої"};
// http://uk.wikipedia.org/wiki/Рефлексивне_дієслово
const std::string UkStemmer::reflexive[] = {"ся","cь","си"}; //to check;
// http://uk.wikipedia.org/wiki/Дієприкметник
const std::string UkStemmer::participle[] = {"ий","ого","ому","им","ім","а","у","ою","ій","і","их","йми","их"}; //to check;
//
const std::string UkStemmer::verb[] = {"сь","ся","ив","ать","ять","у","ю","ав","али","учи","ячи","вши","ши","е","ме","ати","яти","є"}; //to check;
//
const std::string UkStemmer::noun[] = {"а","ев","ов","е","ями","ами","еи","и","ей","ой","ий","й","иям","ям","ием","ем","ам","ом","о","у","ах","иях","ях","ы","ь","ию","ью","ю","ия","ья","я","і","ові","ї","ею","єю","ою","є","еві","ем","єм","ів","їв","ю"};
//
const std::string UkStemmer::deriviational[] = {"[^аеиоуюяіїє][аеиоуюяіїє]+[^аеиоуюяіїє]+[аеиоуюяіїє].*(?<=о)сть?$"}; //to check;

/// from doc 
const std::string UkStemmer::super_suffix[] = {"ш","iш"}; //найвищого степіня порівняння; після най

// ideas - remove (completely) apostrophy if it is first in ending and 1:1
//

//preprocessing a) to lower, b) fix ', (probably remove since it can later be restored 1:1 relation),
void UkStemmer::preprocess(std::string&word){
    return;
}
void UkStemmer::remove_double_cons(std::string&word){
    if(word.length()<4) return;
    std::string letter = word.substr(word.length()-2);
    if(letter == word.substr(word.length()-4,2)){
        for(const std::string& cons: doubledConsonant){
            if(letter == cons) {
                word = word.substr(0,(word.length()-2));
            }
        }
    }
    // if(word.substr(word.length()-2)  = word[word.length()-2])
}
inline void remove_symbol(std::string& word,const std::string &symbol){
    std::string::size_type n = symbol.length();
    for (std::string::size_type i = word.find(symbol);
        i != std::string::npos;
        i = word.find(symbol))
        word.erase(i, n);
}
bool UkStemmer::remove_ending(std::string&stemmed, const std::string endings[], int arrlen){
    int strlen;
    for(int i=0; i<arrlen;++i){
        strlen = endings[i].length();
        if(strlen >stemmed.length()) continue;
        if(stemmed.compare(stemmed.length()-strlen,stemmed.length(), endings[i])==0){
            stemmed = stemmed.substr(0,stemmed.length()-strlen);
            return true;
        }
    }
    return false;
}
bool UkStemmer::remove_ending(std::string&stemmed, const std::string endings[], int arrlen, const std::string prefix[], int prefixlen){ //prefix must exist but we don't delete it
    int strlen;
    for(int i=0; i<arrlen;++i){
        strlen = endings[i].length();
        if(strlen >stemmed.length()) continue;
        if(stemmed.compare(stemmed.length()-strlen,stemmed.length(), endings[i])==0){
            for(int j=0; j<prefixlen;++j){
                if(stemmed.compare(stemmed.length()-strlen - prefix[j].length(),prefix[j].length(), prefix[j])==0){
                    stemmed = stemmed.substr(0,stemmed.length()-strlen);
                    return true;
                }
            }
        }
    }
    return false;
}
std::string UkStemmer::stem(std::string word){
    UkStemmer::preprocess(word);

    int a = word.length();
    int seq_len = 0; //the length of a vowel sequence (for UTF-8)
    int seq_pos  = word.length();
    int temp = 0; 
    for(std::string v: vowel){ // probably can be implemented better
        temp = word.find(v);
        if(temp>-1 && temp <seq_pos){
            seq_pos = temp;
            seq_len = v.length();
            }
    }
    //here if the word has no vovels (or ends with a first vowel) it must be returned
    if(seq_pos == word.length()) return word;
    seq_pos+=seq_len;
    std::string start = word.substr(0,seq_pos);
    //word now is equal to it's last part
    word = word.substr(seq_pos);
    //step 1
    if(!(remove_ending(word,dieprislivnik,sizeof(dieprislivnik)/sizeof(std::string)) ||
                    remove_ending(word,dieprislivnik,sizeof(dieprislivnik)/sizeof(std::string),a_ya,2)  )){
        if(!remove_ending(word,perfectivegerund,sizeof(perfectivegerund)/sizeof(std::string))){
            remove_ending(word,reflexive,sizeof(reflexive)/sizeof(std::string));
            if(remove_ending(word,adjective,sizeof(adjective)/sizeof(std::string))){
                        remove_ending(word,participle,sizeof(participle)/sizeof(std::string));
            }else{
                if(!remove_ending(word,verb,sizeof(verb)/sizeof(std::string))){
                            remove_ending(word,noun,sizeof(noun)/sizeof(std::string));
                }
            }
        }
    }
    if(word.length() <2) return start+word; // less  than 1 UTF-8 ukranian symbol
    //step 2
    // remove vowel at the end (from document, has positive results) (probably better to remove only on letter (и in russian))
    remove_ending(word,vowel,sizeof(vowel)/sizeof(std::string));
    //if(word.substr(word.length()-2,2)=="и") word = word.substr(0,word.length()-2);

    //remove super (from document, unuseful (negative tests, because it comes with NAI)
    //remove_ending(word,super_suffix,sizeof(super_suffix)/sizeof(std::string));

    //remove double consonants, еx: тінню , has positive result
    remove_double_cons(word);


    return start+word;

}
/*
int main(){
    std::string word;
    std::cin>> word;
    std::cout<<UkStemmer::stem(word)<<" ";
    //std::cout << stemmed;
}*/
/*
int main(){
    std::string a[] = {"'Привіт","як","твої","справи","(це ж тест??)","малювати","і","Оплатіте", "будь","ласка", "зробіть", "погашення", "боргу","заборгованостей",
                  "Рефлексивного", "і", "тямущий"};
    std::string stemmed[sizeof(a)/sizeof(std::string)];
    for(int i =0 ; i<sizeof(a)/sizeof(std::string);++i) std::cout<<UkStemmer::stem(a[i])<<" ";
    //std::cout << stemmed;
}
  */  

/*

    def __s(self, st, reg, to):
        orig = st
        self.RV = re.sub(reg, to, st)
        return (orig != self.RV)


    def stem_word(self, word):
        ''' Find the basis (stem) of a word.
        1. word - source word (UTF-8 encoded string)
        2. returns the stemmed form of the word (UTF-8 encoded string) '''

        word = self.__ukstemmer_search_preprocess(word)
        if not re.search('[аеиоуюяіїє]', word):
            stemma = word
        else:
            p = re.search(self.rvre, word)
            start = word[0:p.span()[1]]
            self.RV = word[p.span()[1]:]

            # Step 1
            if not self.__s(self.RV, self.perfectiveground, ''):

                self.__s(self.RV, self.reflexive, '')
                if self.__s(self.RV, self.adjective, ''):
                    self.__s(self.RV, self.participle, '')
                else:
                    if not self.__s(self.RV, self.verb, ''):
                        self.__s(self.RV, self.noun, '')
            # Step 2
            self.__s(self.RV, 'и$', '')

            # Step 3
            if re.search(self.derivational, self.RV):
                self.__s(self.RV, 'ость$', '')

            # Step 4
            if self.__s(self.RV, 'ь$', ''):
                self.__s(self.RV, 'ейше?$', '')
                self.__s(self.RV, 'нн$', u'н')

            stemma = start + self.RV
        return stemma
    

    def stemWord(self, word):
        ''' Find the basis (stem) of a word.
        1. word - source word (UTF-8 encoded string)
        2. returns the stemmed form of the word (UTF-8 encoded string)
        
        This method is used to simulate the PyStemmer interface (https://github.com/snowballstem/pystemmer). '''

        return self.stem_word(word)


*/