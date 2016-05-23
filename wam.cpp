// Prolog Virtual Machine
// based on [hak] Hassan Aït-Kaci
// Warren's Abstract Machine: A Tutorial Reconstruction

// ============ headers ===========

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

// ============== HEAP ============

struct CELL;				// \ HEAP uses C++ vector storage in system memory
vector<CELL*> HEAP;			// /

// ========== WAM heap cell =======

struct CELL {				// [hak,p.10] heap cell
							// (base class must have 1+ virtual fn)

	string tag;				// cell type tag
	CELL* ref;				// pointer to other cell (or itself) see [hak,L0]

	CELL() {
		ref = this;						// point to itself
		tag = "(cell)";					// static tag not works (?)
		HEAP.push_back(this);			// save to HEAP
		assert(HEAP.size() < HEAPsz);	// limit total HEAP size
	}

	virtual string dump() {	// represent as string
		ostringstream os;
		os << this << ":\t" << tag << '\t' << ref << endl;
		return os.str();
	}
};

// ============== REF =============

struct REF: CELL {			// [hak,p.10] <REF,k> k = system heap addr
	REF();
};

REF::REF() : CELL() {
	tag = "REF";
}

// ============== STR ==============

struct STR: CELL {			// [hak,p.10]
	STR(CELL*);
};

STR::STR(CELL*FNC) : CELL() {
	tag = "STR"; ref = FNC;
}

// ============== term/n ===========

struct TERM : CELL {
	CELL* str;
	TERM(string);
	int arity=0;
	vector<CELL*> nest; void push(CELL*);	// nested terms
	string dump();
};

TERM::TERM(string Name) : CELL() {
	str = new STR(this);
	tag = Name;
}

void TERM::push(CELL* X) { nest.push_back(X); arity++; }

string TERM::dump() {
	ostringstream os;
	os << this << ":\t" << tag << "/" << arity << endl;
	for (auto it = nest.begin(), e = nest.end(); it != e; it++)
		os << (*it)->dump();
	return os.str();
}

// ================== heap dump ==============

void dump_heap() {
	for (auto item = HEAP.begin(), last = HEAP.end(); item != last; item++)
		cout << (*item)->dump() << endl;
}

// ============== static defined items ===========

REF X,Y;
TERM B("bb"),C("cCc");

// ===================== main() ============

int main() {
	B.push(new REF()); B.push(new STR(&C));
	dump_heap();
	return 0;
}
