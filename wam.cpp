// Prolog Virtual Machine
// based on [hak] Hassan Aït-Kaci
// Warren's Abstract Machine: A Tutorial Reconstruction

#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

struct CELL {				// [hak,p.10] heap cell and HEAP array
	string* tag;			// type tag
	int ref;				// reference to other heap cell see [hak,L0]

	static int alloc;				// some hints using C++:
	static int allocate(string&);	// allocation encapsulated
} HEAP[HEAPsz];
int CELL::alloc = 0;

int CELL::allocate(string &tag) {
	assert(alloc<HEAPsz);			// check free heap
	HEAP[alloc].tag=&tag;			// set tag marker
	HEAP[alloc].ref=alloc;			// point unbounded var to itself
	return alloc++;
}

struct WAM {				// basic class for heap cell
	WAM();
	static string tag;		// type tag
	int hptr;				// pointer to cell in HEAP
};
string WAM::tag("(undef)");

WAM::WAM() { hptr = CELL::allocate(tag); }

struct REF: WAM {
	REF();
	static string tag;
};
string REF::tag("REF");
REF::REF() : WAM() { HEAP[hptr].tag = &tag; }

void dump_heap() {
	for (int i = 0; i < CELL::alloc; i++)
		printf("%.4X:\t%s\t%i\n", i, HEAP[i].tag->c_str(), HEAP[i].ref);
}

REF X,Y,Z;

int main() {
	dump_heap();
	return 0;
}
