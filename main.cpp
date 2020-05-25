#include "codes.h"
#include <iostream>
#include <fstream>
using namespace std;

ifstream::pos_type filesize(const char* filename)
{
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg(); 
}
void benchmarkDocument(const char* fname){
    cout <<"hello";

	MultiDelimiterCodes& mdc = *new MultiDelimiterCodes();
	int scdc_L=0;
	mdc.ilen=1000;
	double harm=0,u=0,su=100;
	unsigned int i,j,maxi4=100000,iter=100,uu=0,size,t,v,min_i,min_j,min_x,min_z,min_y;
		//QueryPerformanceFrequency(&tfreq);
		size=mdc.word_frequences(fname);		// get the word frequences in the text
		cout<<"Nwords(size): "<<size<<endl;
		mdc.gen_reverse();		// generate the reverse multidelimiter codeword set
		mdc.formT2351();		// preprocess table for the fast decoding method
	
	cout<<"   "<<"entropy="<<mdc.entropy<<"\n";
	cout<<"R="<<(float)mdc.cur_byte*8/mdc.Nwords<<"  "; //// NWords is not assigned by this time!(cur_byte is )
	
	cout<<"formed!!!!!!!!!!!!!!!!!!!!!!!!";
	
	mdc.sumi=mdc.sumd=mdc.sums=mdc.sum1=0;
	mdc.S=223;
	mdc.C=256-mdc.S;
	
	mdc.text_to_ranks(mdc.i235_map_sorted,fname,mdc.ranks);	// generate the array of word indices

	mdc.encodeI235(mdc.Nwords,mdc.ranks);					// generate the R2x code
	//decodeI235_1(ilen+1);
	cout <<"size:"<<size<<"different words:"<<mdc.diff_words<<"\n"<<"I235 bytes: "<<mdc.cur_byte<<", I235 av codeword length: "<<(float)mdc.cur_byte*8/mdc.Nwords<<"; entropy="<<mdc.entropy<<"\n";
	mdc.create_tables();
	scdc_L=mdc.rpbc_encode(mdc.Nwords,mdc.ranks,mdc.codes_scdc);
	cout<<"S="<<mdc.S<<" scdc_L= "<<scdc_L<<" SCDC av codeword length: "<<(float)scdc_L*8/mdc.Nwords<<"\n";
	for(int iter=0;iter<10;iter++) {
		u+=mdc.decode_i235_fast();
		//sumi+=(float)(tend.QuadPart - tstart.QuadPart)/tfreq.QuadPart;

		uu+=mdc.rpbc_decode(mdc.codes_scdc,mdc.decoded_scdc,scdc_L);

		//sums+=(float)(tend.QuadPart - tstart.QuadPart)/tfreq.QuadPart;
	

	}	
	cout<<"s1="<<mdc.s1<<"s2="<<mdc.s2<<"r1="<<mdc.r1<<"r2="<<mdc.r2<<"r3="<<mdc.r3<<"r4="<<mdc.r4;
	cout<<"decode_SCDC time: "<<(float)mdc.sums<<" scdc_L="<<scdc_L<<endl;
	cout<<" decode_I_fast time: "<<(float)mdc.sumi<<"\n";
    cout<<" compression ratio: "<< ((float)filesize(fname))/mdc.cur_byte<<endl;
	//i235_test(Nwords,fname);
	cout<<"\n uu="<<uu*2<<u<<"\n";
	//getch();//remove
}
int main() {
    cout<<"hello";
    benchmarkDocument("./datasets/hp1_processed.txt");
    benchmarkDocument("./datasets/bible_processed.txt");
}