// Prolog Virtual Machine
// based on [hak] Hassan Aït-Kaci
// Warren's Abstract Machine: A Tutorial Reconstruction

#include "wam.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { yyparse(); heap_dump(); return 0; }

// ============== HEAP ============

vector<Cell*> HEAP;

void heap_dump() {
	cout << "================= HEAP =================\n";
	for (auto item = HEAP.begin(), last = HEAP.end(); item != last; item++)
		cout << (*item)->head();// << endl;
}

map<string,Cell*> heap_index;

// ========== WAM heap cell =======

Cell::Cell(string T, string N) {
	tag = T;
	name = N;
	ref = this;						// point to itself
}

void Cell::to_heap() {
	HEAP.push_back(this);			// save to HEAP
	assert(HEAP.size() < HEAPsz);	// limit total HEAP size
}

string Cell::pad(string X) {
	string S = X;
	for (int i = 0; i < 0x10 - X.length(); i++) S += ' ';
	return S;
}
string Cell::head() {					// represent as string
	ostringstream os;
	os << this << ":\t" << pad(tag+":"+name) << '\t' << ref << endl;
	return os.str();
}
string Cell::dump() { return head(); }

void Cell::push(Cell*X) { nest.push_back(X); }

// ============== REF =============

Ref::Ref(string V) : Cell("REF",V) {// [hak,p.10] <REF,k> k = system heap addr
	to_heap();
	if (heap_index[name]) {			// heap index lookup
		ref = heap_index[name];
		name = "";					// zero name: points to other named REF
	}
	else heap_index[name] = this;	// save to index
}

// ============== STR ==============

Str::Str(Cell*X) : Cell("STR","") { ref = X; to_heap(); }

string Str::dump() { return head()+ref->dump(); }

// ============== term/n ===========

Term::Term(string V) : Cell("TERM",V) { to_heap(); }

string Term::dump() {
		string S = head();
		for (auto it = nest.begin(), e = nest.end(); it != e; it++)
			S += (*it)->dump();
		return S;
}

string Term::head() {					// special for term/x
	ostringstream os;
	os << this << ":\t" << name << '/' << nest.size() << endl;
	return os.str();
}

// ================== LIST ==============

List::List() : Cell("","[]") { /* no to_heap() */}
