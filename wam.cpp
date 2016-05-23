// Prolog Virtual Machine
// based on [hak] Hassan Aït-Kaci
// Warren's Abstract Machine: A Tutorial Reconstruction

#include "wam.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { yyparse(); cout << "=============\n"; heap_dump(); return 0; }

// ============== HEAP ============

vector<Cell*> HEAP;

void heap_dump() {
	for (auto item = HEAP.begin(), last = HEAP.end(); item != last; item++)
		cout << (*item)->dump() << endl;
}

// ========== WAM heap cell =======

Cell::Cell(string T) {
		tag = T;						// tag
		ref = this;						// point to itself
		HEAP.push_back(this);			// save to HEAP
		assert(HEAP.size() < HEAPsz);	// limit total HEAP size
}

string Cell::head() {					// represent as string
		ostringstream os;
		os << this << ":\t" << tag << '\t' << ref << endl;
		return os.str();
}
string Cell::dump() { return head(); }

void Cell::push(Cell*X) {
	nest.push_back(X);
	arity++;
}

// ============== REF =============

Ref::Ref(string V): Cell("REF:"+V) {}// [hak,p.10] <REF,k> k = system heap addr

// ============== STR ==============

Str::Str(Cell*X) : Cell("STR") { ref=X; }

string Str::dump() { return head()+ref->dump(); }

// ============== term/n ===========

Term::Term(string V):Cell(V) {}

string Term::dump() {
		ostringstream os;
		os << this << ":\t" << tag << "/" << arity << endl;
		for (auto it = nest.begin(), e = nest.end(); it != e; it++)
			os << (*it)->dump();
		return os.str();
}

// ================== LIST ==============

List::List(){}
void List::push(Cell*o) { nest.push_back(o); }
