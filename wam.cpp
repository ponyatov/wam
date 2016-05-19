// Prolog Virtual Machine
// based on [hak] Hassan Aït-Kaci
// Warren's Abstract Machine: A Tutorial Reconstruction

#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

struct CELL {				// [hak,p.10] heap cell and HEAP array
	string* tag;
	int ref;
} HEAP[HEAPsz];
int HEAP_ALLOC = 0;

struct WAM {				// basic class for heap cell
	WAM();
	static string tag;		// type tag
	int hptr;				// pointer to cell in HEAP
};
string WAM::tag("(undef)");

WAM::WAM() {
	hptr = HEAP_ALLOC++; assert(HEAP_ALLOC < HEAPsz);	// alloc cell
	HEAP[hptr].tag = &tag;								// mark tag
	HEAP[hptr].ref = hptr;								// point to self
}

struct REF: WAM {
	REF();
	static string tag;
};
string REF::tag("REF");
REF::REF() : WAM() { HEAP[hptr].tag = &tag; }

void dump_heap() {
	for (int i = 0; i < HEAP_ALLOC; i++)
		printf("%.4X:\t%s\t%i\n", i, HEAP[i].tag->c_str(), HEAP[i].ref);
}

REF X,Y,Z;

int main() {
	dump_heap();
	return 0;
}
