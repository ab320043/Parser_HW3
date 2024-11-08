#ifndef SCOPE_H
#define SCOPE_H

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "id_attrs.h"
#include "ast.h"
#include "symtab.h"
#include "scope_check.h"
#include "utilities.h"
#include "id_use.h"

typedef struct Scope Scope;

Scope *create_scope(SymbolTable *symbol_table, Scope *parent);
void destroy_scope(Scope *scope);
void add_identifier_to_scope(Scope *scope, const char *name);
bool is_identifier_in_scope(Scope *scope, const char *name);

#endif
