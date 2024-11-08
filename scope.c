#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "id_attrs.h"
#include "ast.h"
#include "symtab.h"
#include "scope_check.h"
#include "utilities.h"
#include "id_use.h"

typedef struct Scope {
    SymbolTable *symbol_table;   // Symbol table stack for scope levels
    struct Scope *parent;        // Pointer to the parent scope
} Scope;

Scope *create_scope(SymbolTable *symbol_table, Scope *parent) {
    Scope *new_scope = (Scope *)malloc(sizeof(Scope));
    if (new_scope == NULL) {
        report_error("Failed to allocate memory for new scope.");
        exit(EXIT_FAILURE);
    }
    new_scope->symbol_table = symbol_table;
    new_scope->parent = parent;
    return new_scope;
}

void destroy_scope(Scope *scope) {
    if (scope) {
        free(scope);
    }
}

void add_identifier_to_scope(Scope *scope, const char *name) {
    if (!scope) {
        report_error("Invalid scope provided.");
        return;
    }
    add_symbol(scope->symbol_table, name); // Add to symbol table in this scope
}

bool is_identifier_in_scope(Scope *scope, const char *name) {
    Scope *current_scope = scope;
    while (current_scope != NULL) {
        if (symbol_exists(current_scope->symbol_table, name)) {
            return true;
        }
        current_scope = current_scope->parent;
    }
    return false;
}
