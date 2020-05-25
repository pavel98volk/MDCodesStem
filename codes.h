
#ifndef multi_delimiter_codes_header
#define multi_delimiter_codes_header
#include <vector>
#include <map>
using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef vector<int> vi;
typedef map<int, string> um;

//============== i235 ===================
struct tabsi235 {
	int p1,p2,p3,p4;
	struct tabsi235* al;
};

struct tabsi2351 {
	int p1,p2,p3,p4,n;
	struct tabsi2351* al;
};
struct ai_state {
	int st,L,p,res;
};

//===================================
struct tabs {
	uint f,w1,w2,w3,w4,r,s;
};

struct FibT {
	uchar pl,pv,s,sl,sv,p;
};

class bn{
  public:
	uint x;
	int last_bit;
	bn(const char*);
	bn(uint a):x(a),last_bit(8){}; // right-shifted byte value constructor
	bn():x(0),last_bit(0){}; //right-shifted value constructor
	void set(uint a) {x=a;last_bit=8;};
	void set1(){x=1;last_bit=1;};
	void init(){x=0;last_bit=0;};
	void add(const char*,int);
	void prepend(const char*);
	void print();
	void form_nevr(bn);
	uint toint();
	uint get_len();
	uint transform_to_nevr_value();
};

struct entry {
    short PL, PV, SL, SV, p;
    vector<int> S;
};

// class kinda can't be used in stack, use new ;)
class MultiDelimiterCodes{
    public:
    //============== i235 ===================
    unsigned int experT[256][256];
    //tabsi235 T235[1000000]; changed to heap (below)
    tabsi235 *T235 = new tabsi235[1000000];
    // tabsi2351 T235_1[1000000]; changed to heap (below)
    tabsi2351 *T235_1 = new tabsi2351[1000000];
    static const int Lmax=30,max_i235=30000;
    int nlk[Lmax+8][40],clen,ilen,s1,s2,r1,r2,r3,r4;
    int nl[Lmax];
    
    //============= rpbc ====================
    const int R=256,R2=256*256,R3=256*256*256;
    //int suffix[500000],first[500000]; changed to heap (below)
    int*suffix = new int[500000],*first = new int[500000];
    int v1,v2,v3,v4;
    //=======================================

    //LARGE_INTEGER tstart, tend, tfreq;
    static const int N=610000,L=30000000,globL=3600000;
    uint rank_after0=0,ranks[L],ranks_scdc[L],_0ranks[N],S=145,C=256-S,base[100],sumd,sum1;
    //i235 and rand_test changed to heap allocation (below)
    uint *i235 = new uint[300000],*rand_test= new uint[1000000];
    unsigned char codes[L*4],codes_d235[L*4],codes_scdc[L*4];
    uint decoded[1],decoded_fib[1],decoded_scdc[1],rz_esi,rz_esp,decoded_c[1];

    //string *out235[20000000],*out_i235[20000000],Dict_i235[1000000],*outSCDC[20000000]; changed to heap(below);
    string **out235= new string*[20000000],**out_i235=new string*[20000000],*Dict_i235 = new string[1000000],**outSCDC=new string*[20000000];
    //string out_i235s[20000000]; changed to heap(below);
    string *out_i235s = new string[20000000];
    float sumi,sums;

    char* glob_res;
    //dictionary
    string Dict[N*2],DictSCDC[N*2];
    map<string,int> dic_map,i235_map,i235_map_sorted,d235_map_sorted;
    map<string,int> dic_map_scdc;
    map<int,string> dic_map1;
    map<int,pair<int,int>> d235_map;
    int dic_size,dic_size_scdc;
    //text
    int Nwords,diff_words;
    string out_text,out_text_scdc;

    double points[N+1],maxpoi,entropy;
    int t=sizeof(unsigned int)*8,cur_byte = 0,cur_bit=7;
    bool w3_output;

    static const int sw=256,sr=10;
    uint f[sr][sw],w1[sr][sw],w2[sr][sw],w3[sr][sw],w4[sr][sw],r[sr][sw],s[sr][sw];

    tabs* TARR[10][256];
    uint TAB[10*256];
    FibT Ftab[255][3];
    uint Fib3[150][28],Start[32];

    uint decode_d235_base();
    //--------------- stemming related ---------------
    map<string,int> i235_map_endings,i235_map_stems;
    // --------------------
    void decodeFib();

    int get_size(unsigned int x);

    void insert_1(unsigned int& x,int pos);

    int d235_length(uint x);

    //==================== Encode ===================
    //obtain code shifted to left boundary of 32-bit word
    unsigned int get_code(unsigned int x);

    void flush_to_byte(unsigned int x);

    void flush_to_byte_i235(unsigned int x);

    uint invert_d235(uint x);

    uint inverted_d235[150000];

    void make_inverted_d235(); // not implemented (empty)

    void encodeC235(int max_rank,uint* ranks);

    void encodeI235(int max_rank,uint* ranks);
    //========================================================


    int cmp_bit(bn x,const char u);

    //cmp part of string from current position
    int cmp_(bn x,const char* str);

    bool cmp_rest(bn x,const char* str);

    //return: 2 - end of byte; 1 - end with vnevr; 0 - end of codeword
    int fw(bn& x,bn& res,bool fin_flag);


    // 0 - stopped with vnevr
    // -1 - simply finish previous w, don't append anything
    // -2 - codeword succesfully extracted
    int get_w1(uint nevr,bn& x,bn& y); // x - input byte, y - output w1	




    void print_bin_char(uchar c);

    int write_table0(bn w1,bn nv);

    int write_table1(bn w1,bn w2,bn nv);

    int write_table2(bn w1,bn w2,bn w3,bn nv);

    int write_table01(bn w1,bn nv,tabs* v);

    int write_table11(bn w1,bn w2,bn nv,tabs* v) ;

    int write_table21(bn w1,bn w2,bn w3,bn nv,tabs* v);



    void initTAB1();

    void initTAB();

    const int block_size = 8;
    const int M = 148;
    const int wcount = 5*1e6;
    const int numShifts = 20;
    int cur_dec;

    vector<int> fib3, start;
    um dictionary;

    // here struct entry was defined

    int getIndex(int n, int l);

    int f2(int n,int l);

    entry** build_partial_decoding_table();

    int** build_Fib3();

    void dict();

    void full_Fib3_decode();

    void dic_to_file();

    int scdc_encode(int L,uint* numbers,uchar* outp);

    int rpbc_encode(int L,uint* numbers,uchar* outp);

    int scdc_decode(uchar* code, uint* out,int L_coded);

    void set_v1_v4();
    void create_tables();

    int rpbc_decode(uchar* code, uint* out,int L_coded);

    void print_codeword(uint x);

    void obtain_codes235();

    //f=0 - w1 not output, f=1 - output w1, not w2, f=2 - output w3, no w4
    int decode_C();

    void dict_from_file();

    void dict_from_file_scdc();

    void text_to_ranks(map<string,int> dic_map,const char* file_name,unsigned int* ranks);

    bool d235_in_i235(uint x) ;

    void d235_codeword_map(int L);

    int state_max=7;
    ai_state a_step(ai_state prev,int bit);

    // new automaton modelling
    ai_state a_step1(ai_state prev,int bit);

    void decodeI235(int N);

    // new decoding method - slow; for testing
    void decodeI235_1(int N);

    int nf[100000];
    int nf1[100000];
    int nf2[100000];
    int nf3[100000];
    int nf4[100000];

    void formT235_inner(int L,ai_state state);

    uint pack(tabsi2351 v, ai_state s);

    int mx=0;

    void formT235_inner1(int L,ai_state state);

    void formT2351();

    void formT235();

    //====================================== test function pointer
    int glob_=0;

    void f1();

    void f2();

    //void (*actions[2])()={this->f1,this->f2}; //not used
    //============================================================

    int decode_i235_fast_orig();

    int decode_i235_fast();

    int k[20]={0,1,21}; //numbers which are not delimiters, the last = biggest delimiter+1
    int kmax=3,Lmin=3; //number of elements in the array k; length of the shortest codeword

    void gen_reverse() ;

    //NOTE: here the library is created. Taking a word from document and checking against hash map
    int word_frequences(const char* s);

    void write_to_file_i235(int N,string** indices,char* fname);

    void i235_test(int N,char* fname);

    void write_to_file_binary(uchar* code,const char* filename,int N);

};

#endif