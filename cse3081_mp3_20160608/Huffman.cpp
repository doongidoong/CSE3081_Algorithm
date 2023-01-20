#include "Huffman.h"

using namespace std;

//encoding
bool huffman_encode(string file, const string input, priority_queue<code,vector<code>,code_compare> &huffcode){
	map<char, int> m;
	priority_queue<tree, vector<tree>, tree_compare>  pq;
	for (auto& c : input) m[c]++;
	for (auto iter = m.begin(); iter != m.end(); ++iter){
		tree item(iter->first, iter->second);
		pq.push(item);
    }
	while (pq.size() > 1){
		tree left = pq.top();
		pq.pop();
		tree right = pq.top();
		pq.pop();
		tree parent(0,left.freq + right.freq);
		parent.left_child.push_back(left);
		parent.right_child.push_back(right);
		pq.push(parent);
	}
	stack<pair<tree, string>> st;
	st.push({ pq.top(), "" });
	while (!st.empty()) {
        tree cur = st.top().first;
        string cur_code = st.top().second;
        st.pop();
		if(!cur.left_child.empty()){
            st.push({ cur.left_child.front(), cur_code + "0" });
        }
        if(!cur.right_child.empty()){
            st.push({ cur.right_child.front(), cur_code + "1" });
        }
		if (cur.left_child.empty() && cur.right_child.empty()) {
			code item(cur.name ,cur_code);
			huffcode.push(item);
        }
    }
	string filename = file;
	FILE *readFile = fopen(filename.c_str(), "rt");
	string savefilename = filename + ".zz";
	FILE *writeFile = fopen(savefilename.c_str(), "wb");
	int dummy = 0;
	fprintf(writeFile, "%c", dummy);
	fprintf(writeFile, "%d", (int)huffcode.size());
	int idx = 0;
	char word;
	char buffer = 0;
	int msb = -1;
	vector<code> v(huffcode.size());
	while (!huffcode.empty()){
		code item = huffcode.top(); huffcode.pop();
		buffer = 0;
		msb = -1;
		v[idx++] = item;
		fprintf(writeFile, "%c", item.name);
		fprintf(writeFile, "%c",(char)item.huffcode.length());
		for (int i = 0; i < item.huffcode.length(); ++i){
			if (msb == 7) {
				fprintf(writeFile, "%c", buffer);
				buffer = 0;
				msb = -1;
			}
			buffer = buffer << 1;
			buffer = buffer | item.huffcode[i] - '0';
			++msb;}
		if (msb != -1) {
			while (msb != 7) {
				buffer = buffer << 1;
				msb++;
			}
			fprintf(writeFile, "%c", buffer);
		}
	}

	buffer = 0;
	msb = -1;
	int flag = 0;
	while (fscanf(readFile, "%c", &word) != EOF) {
		string writeCode;
		flag = 0;
		for (code tempItem : v) {
			if (tempItem.name == word){
				writeCode = tempItem.huffcode;
				flag = 1;
			}
		}
		if(flag==0) writeCode = string("NULL");
		for (int i = 0; i < writeCode.length(); ++i){
			if (msb == 7) {
				fprintf(writeFile, "%c", buffer);
				buffer = 0;
				msb = -1;
			}
			buffer = buffer << 1;
			buffer = buffer | writeCode[i] - '0';
			++msb;
		}
	}
	int lastbit = msb;
	while (lastbit != 7) {
		buffer = buffer << 1;
		lastbit++;
	}
	fprintf(writeFile, "%c", buffer);
	fseek(writeFile, 0, SEEK_SET);
	fprintf(writeFile, "%c", (char)msb);
	fclose(readFile);
	fclose(writeFile);
	return true;
}

//decoding
bool huff_compare(const code &l, const code &r){
	return l.huffcode < r.huffcode;	
}

bool binary_search(vector<code> &v, string &s, char* word){
	int left = 0;
	int right = v.size() - 1;
	while (left <= right){
		int mid = (left + right) / 2;
		if (v[mid].huffcode < s) left = mid + 1;
		else if (s < v[mid].huffcode)
			right = mid - 1;
		else{
			*word = v[mid].name;
			return true;
		}
	}
	return false;
}

bool huffman_decode(string filename){
	vector<code> v;
	FILE *file = fopen(filename.c_str(), "rb");
	if (file == NULL){
		return false;
	}
	string outfilename = filename;
	outfilename += ".yy";
	FILE *decoded = fopen(outfilename.c_str(), "wt");
	char msb;
	int codenum;
	char validbit;
	fscanf(file, "%c", &msb);
	fscanf(file, "%d", &codenum);
	for (int i = 0; i < codenum; ++i){
		code item;
		fscanf(file,"%c", &item.name);
		fscanf(file, "%c", &validbit);
		char buffer = 0;
		while (validbit > 0){
			fscanf(file, "%c", &buffer);
			for (int j = 7; j >= 0; --j){
				if (validbit <= 0)
					break;
				char bitdata = (buffer >> j) & 1;
				item.huffcode.push_back(bitdata + '0');
				--validbit;
			}
		}
		v.push_back(item);
	}
	sort(v.begin(), v.end(), huff_compare);
	char buffer, EOFcheck;
	bool founded_code;
	string huffcode;
	while (fscanf(file, "%c", &buffer) != EOF){
		if (fscanf(file, "%c", &EOFcheck) == EOF){
			for (int i = 7; i >= 7 - msb; --i)	{
				char bitdata = (buffer >> i) & 1;
				huffcode.push_back(bitdata + '0');
				char write_word = 0 ;
				founded_code = binary_search(v, huffcode, &write_word);
				if (founded_code){
					fprintf(decoded, "%c", write_word);
					huffcode.clear();
					break;
				}
			}
		}
		else{
			fseek(file, -1, SEEK_CUR);
			for (int i = 7; i >= 0; --i){
				char bitdata = (buffer >> i) & 1;
				char write_word =  0 ;
				huffcode.push_back(bitdata + '0');
				founded_code = binary_search(v, huffcode, &write_word);
				if (founded_code){
					fprintf(decoded, "%c", write_word);
					huffcode.clear();
				}
			}
		}
	}
	fclose(file);
	fclose(decoded);
	return true;
}