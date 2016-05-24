// Prolog Virtual Machine
// based on [hak] Hassan Aït-Kaci
// Warren's Abstract Machine: A Tutorial Reconstruction

#include "wam.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { yyparse(); heap_dump(); X_dump(); return 0; }

// ============== HEAP ============

vector<Cell*> HEAP;

void heap_dump() {
	cout << "================= HEAP =================\n";
	for (auto item = HEAP.begin(), last = HEAP.end(); item != last; item++)
		cout << (*item)->head() << endl;
}

map<string,Cell*> heap_index;

// ========== X registers =========

Cell* X[Xsz];

void X_dump() {
	cout << "================= X regs =================\n";
	for (auto i=0;i<Xsz;i++) {
		cout << i << '\t';
		if (X[i]) cout << X[i]->head();
		cout << endl;
	}
}

Xref::Xref(int X) : Cell("X","") { Xn=X; }
string Xref::head() {
	ostringstream os;
	os << this << ":\t" << tag << ":" << Xn << endl;
	return os.str();
}

Xvar::Xvar(string V) : Cell("X",V) {}
Xvar::Xvar(int N) : Cell("X","") {
	Xn=N; ostringstream os; os<<N; name=os.str();
}

void Xvar::push(Cell*o) { X[Xn]=o; Cell::push(o); }

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
	os << this << ":\t" << pad(tag+":"+name) << '\t' << ref;
	return os.str();
}
string Cell::dump(int depth) {
	string S = "\n" + tab(depth) + head();
	for (auto it = nest.begin(), e = nest.end(); it != e; it++)
		S += (*it)->dump(depth+1);
	return S;
}
string Cell::tab(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }

void Cell::push(Cell*X) { nest.push_back(X); }

// ============== REF =============

Ref::Ref(string V) : Cell("REF",V) {// [hak,p.10] <REF,k> k = system heap addr
	to_heap();
	if (heap_index[name]) {			// heap index lookup
		ref = heap_index[name];
		push(ref);
		name = "";					// zero name: points to other named REF
	}
	else heap_index[name] = this;	// save to index
}

// ============== STR ==============

Str::Str(Cell*X) : Cell("STR","") { ref = X; to_heap(); }

string Str::dump(int depth) { return Cell::dump(depth)+ref->dump(depth+1); }

// ============== term/n ===========

Term::Term(string V) : Cell("TERM",V) { to_heap(); }

string Term::head() {					// special for term/x
	ostringstream os;
	os << this << ":\t" << name << '/' << nest.size();
	return os.str();
}

// ================== LIST ==============

List::List() : Cell("","[]") { /* no to_heap() */}
