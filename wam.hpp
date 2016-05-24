#ifndef _H_WAM
#define _H_WAM

// ============ headers ===========

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
using namespace std;


struct Cell {				// [hak,p.10] heap cell
							// (base class must have 1+ virtual fn)
	string tag;				// cell type tag
	string name;			// item name (used for heap lookups)
	Cell* ref;				// pointer to other cell (or itself) see [hak,L0]
	Cell(string,string);
	virtual void to_heap();	// HEAP allocator
	virtual string dump(int=0);	// represent as string
	virtual string head();
	string pad(string); string tab(int);
	vector <Cell*> nest;
	virtual void push(Cell*);
};

extern vector<Cell*> HEAP;	// uses C++ vector storage in system memory
extern void heap_dump();
extern map<string,Cell*> heap_index;	// index table for term & vars

extern Cell* X[Xsz];		// X-registers vector [hak,p.11]
extern void X_dump();		// dump X array

struct Xref : Cell {		// reference to X register
	int Xn;					// index in X array;
	Xref(int);
	string head();
};
struct Xvar: Cell {
	int Xn;
	Xvar(string);
	Xvar(int);
	void push(Cell*);
};

struct Ref: Cell {			// [hak,p.10] <REF,k> k = system heap addr
	Ref(string);
};

struct Str: Cell {			// [hak,p.10] pointer to [str]ucture
	Str(Cell*);
	string dump(int);
};

struct Term : Cell {
	Term(string);
//	string dump(int);
	string head();
};

struct List : Cell {
	List();
	void to_heap(){}		// drop HEAP allocation
};

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "wam.tab.hpp"

#endif // _H_WAM
