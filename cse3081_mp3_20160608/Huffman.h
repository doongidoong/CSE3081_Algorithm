#ifndef KIBBOMI_Data
#define KIBBOMI_Data
#define MAX_WORD 2478	//최대 글자개수
#include <queue>	//for priority queue
#include <list>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

class tree
{
public :
	tree(){}
	tree(unsigned char n, int f) { name = n;freq = f;  left_child = list<tree>(); right_child = list<tree>(); }
	unsigned char name;	
	int freq;	
	//child
	tree* left;
	tree* right;
	list<tree>  left_child, right_child;
};

class code{
public:
	//data
	unsigned char name;
	string huffcode;
	code(){}
	code(unsigned char n, string h)	{name =n ;huffcode =h;}
};
struct code_compare {
	bool operator()(const code& l, const code& r) {
		return l.huffcode > r.huffcode;	
	}
};
struct tree_compare {
	bool operator()(const tree& l, const tree& r) {
		return l.freq > r.freq;	
	}
};

bool huffman_encode(string , const string , priority_queue<code, vector<code>, code_compare> &);
bool huffman_decode(string);
bool search_code(vector<code> &, string &, char *);
bool huff_compare(const code &,const code &);
#endif