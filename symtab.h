#ifndef SYMTAB_H
#define SYMTAB_H


#include <stdio.h>
#include <stdlib.h>
#include "id_attrs.h"
#include "ast.h"
#include "symtab.h"
#include "scope_check.h"
#include "utilities.h"
#include "id_use.h"
#include <stdbool.h>

typedef struct SymbolTable {
    Scope *scopes; // Stack of scopes
} SymbolTable;

void init_symbol_table(SymbolTable *table);
void add_scope(SymbolTable *table);
void remove_scope(SymbolTable *table);
void add_symbol(SymbolTable *table, const char *name);
bool symbol_exists(SymbolTable *table, const char *name);

#endif
