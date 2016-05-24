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
	virtual string dump();	// represent as string
	virtual string head();
	string pad(string);
	vector <Cell*> nest;
	void push(Cell*);
};

extern vector<Cell*> HEAP;				// HEAP
extern void heap_dump();
extern map<string,Cell*> heap_index;	// index table for term & vars

extern vector<Cell*> HEAP;	// uses C++ vector storage in system memory
extern void heap_dump();

struct Ref: Cell {			// [hak,p.10] <REF,k> k = system heap addr
	Ref(string);
};

struct Str: Cell {			// [hak,p.10] pointer to [str]ucture
	Str(Cell*);
	string dump();
};

struct Term : Cell {
	Term(string);
	string dump();
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
