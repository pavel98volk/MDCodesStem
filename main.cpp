#include "codes.h"
#include <iostream>
#include <fstream>
#include "stemmer.h"
#include <algorithm>
using namespace std;

ifstream::pos_type filesize(const char* filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg(); 
}

struct PairCompFirstGreater
{
    bool operator()( const pair<int,string>& lx, const pair<int,string>& rx ) const {
        return lx.first > rx.first;
    }
};
void setMostUsedSuffixesUnique(const char* fname, vector<string>&result_vector, int minimum_occurances){
	MultiDelimiterCodes& mdc2 = *new MultiDelimiterCodes();
	mdc2.ilen = 1000;
	mdc2.word_frequences(fname,true,true);
	//creating a map with all unique words for each suffix
	std::map<std::string,std::vector<int>> suffix_words;
	string suff;
	for(int i=0;i<mdc2.diff_words;i++){
		suff  =UkStemmer::stem(mdc2.Dict_i235[i]);
		suff  =mdc2.Dict_i235[i].substr(suff.length());
		if(suffix_words.find(suff)==suffix_words.end()){
			suffix_words.insert(make_pair(suff,std::vector<int>()));
		}
		suffix_words[suff].push_back(i);

	}
	//counting unique words for each suffix and sorting
	vector<pair<int,string>> suffix_words_array; //unique_word_count, suffix;
	for(auto iter = suffix_words.begin(); iter != suffix_words.end(); ++iter){
	    suffix_words_array.push_back(pair<int,string>(iter->second.size(),iter->first));
	}
	sort(suffix_words_array.begin(), suffix_words_array.end(),PairCompFirstGreater());
	// selecting the most used in different words suffixes
	for(auto el:suffix_words_array){
		if(el.first >= minimum_occurances){
			result_vector.push_back(el.second);
		}
	}
	delete &mdc2;
}
void benchmarkDocument(const char* fname,int minimum_suffix_occurances){
	MultiDelimiterCodes& mdc = *new MultiDelimiterCodes();
	int scdc_L=0;
	mdc.ilen=1000;
	double harm=0,u=0,su=100;
	unsigned int i,j,maxi4=100000,iter=100,uu=0,size,t,v,min_i,min_j,min_x,min_z,min_y;
	//inserted

/*	 // based on how common the suffix is
	for (long i=0; i< mdc2.diff_words;i++){
		if(mdc2.Dict_i235[i][0] == '.'){
			if(mdc2.i235_map[mdc2.Dict_i235[i]] <2) break;
			mdc.used_suffixes.push_back(mdc2.Dict_i235[i].substr(1));
		}
	}
*/
	setMostUsedSuffixesUnique(fname,mdc.used_suffixes, minimum_suffix_occurances);
	
	size=mdc.word_frequences(fname,true, true);// get the word frequences in the text

	long long dict_size  =0;
	int k = 0;
	for (long i=0; i< mdc.diff_words;i++){
		if(mdc.Dict_i235[i][0] == '.'){
			k++;
			dict_size+=	mdc.Dict_i235[i].length(); //remove . add some 1 byte delimiter
		}else{
			dict_size+=	mdc.Dict_i235[i].length()+1; //add 1 byte delimiter
		}
	}
	//dict_size/=(1.75); // to simulate compression
	cout <<"dict_size: "<<(dict_size)<<endl;
	cout<<"suffix amount="<<k<<endl;

		mdc.gen_reverse();		// generate the reverse multidelimiter codeword set
		mdc.formT2351();		// preprocess table for the fast decoding method

	cout<<"   "<<"entropy="<<mdc.entropy<<"\n";
	cout<<"R="<<(float)mdc.cur_byte*8/mdc.Nwords<<"  "; //// NWords is not assigned by this time!(cur_byte is )
	
	cout<<"formed!!"<<endl;
	
	mdc.sumi=mdc.sumd=mdc.sums=mdc.sum1=0;
	mdc.S=223;
	mdc.C=256-mdc.S;
	
	mdc.text_to_ranks(mdc.i235_map_sorted,fname,mdc.ranks, true,true);	// generate the array of word indices

	mdc.encodeI235(mdc.Nwords,mdc.ranks);					// generate the R2x code
	///decodeI235_1(ilen+1);
	cout <<"size:"<<size<<"different words:"<<mdc.diff_words<<"\n"<<"I235 bytes: "<<mdc.cur_byte<<", I235 av codeword length: "<<(float)mdc.cur_byte*8/mdc.Nwords<<"; entropy="<<mdc.entropy<<"\n";
	cout<<mdc.diff_words<<", ";
	mdc.create_tables();
	scdc_L=mdc.rpbc_encode(mdc.Nwords,mdc.ranks,mdc.codes_scdc);
	cout<<"S="<<mdc.S<<" scdc_L= "<<scdc_L<<" SCDC av codeword length: "<<(float)scdc_L*8/mdc.Nwords<<"\n";
    
	//for(int iter=0;iter<10;iter++) {
		//u+=mdc.decode_i235_fast();
		u+=mdc.decode_i235_fast();//mdc.cur_byte);
		//sumi+=(float)(tend.QuadPart - tstart.QuadPart)/tfreq.QuadPart;

		//uu+=mdc.rpbc_decode(mdc.codes_scdc,mdc.decoded_scdc,scdc_L);

		//sums+=(float)(tend.QuadPart - tstart.QuadPart)/tfreq.QuadPart;
	
	//}
	/*
	for (int i=0;i<100;i++){
		cout<<mdc.Dict_i235[i]<<endl;
	}*/
	/*cout<<"s1="<<mdc.s1<<"s2="<<mdc.s2<<"r1="<<mdc.r1<<"r2="<<mdc.r2<<"r3="<<mdc.r3<<"r4="<<mdc.r4;
	cout<<"decode_SCDC time: "<<(float)mdc.sums<<" scdc_L="<<scdc_L<<endl;
	cout<<" decode_I_fast time: "<<(float)mdc.sumi<<"\n";*/
    cout<<" compression ratio: "<< ((float)filesize(fname))/(mdc.cur_byte)<<endl;
	cout<<" compression ratio+dict: "<< ((float)filesize(fname))/(mdc.cur_byte+dict_size)<<endl;

	//mdc.i235_test(mdc.Nwords,fname);
	//cout<<"\n uu="<<uu*2<<" u="<< u<<"\n";
	/*
	for(int i=0;i<100;i++){
		cout << *(mdc.outSCDC[i])<<" ";
	}*/
	/*
	char cstr[100];
	for(int i =1;i<100;i++){
		//cstr[i-4] = cstr2[i];
		std::cout <<mdc.Dict_i235[mdc.rand_test[i]]<<" ";
	}*/
	delete &mdc;
	
}
int main() {
    //benchmarkDocument("./datasets/hp1_processed.txt");
	benchmarkDocument("./datasets/bible_processed.txt",0);
	//benchmarkDocument("./datasets/voly_processed.txt",i);
	//benchmarkDocument("./datasets/processed.txt");

	//benchmarkDocument("./datasets/kjv_true_formatted.txt");
}