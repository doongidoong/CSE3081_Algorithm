#include <iostream>
#include "Huffman.h"
#include <ctime>
#include <cstring>
using namespace std;



int main(int argc, char* argv[]) {
	priority_queue<code, vector<code>, code_compare> huffcode;
	FILE * openFile = fopen(argv[2], "rt");
	if(openFile==NULL) {
		printf("input error\n");
		return 1;
	}
	char c;
    string input="";
	while (fscanf(openFile, "%c", &c) != EOF) input+=c;
	fclose(openFile);
	if(strcmp(argv[1],"-c")==0) huffman_encode(argv[2], input, huffcode);
	else if(strcmp(argv[1],"-d")==0) huffman_decode(argv[2]);
	else{
		printf("input error\n");
		return 0;
	}
	return 0;
}