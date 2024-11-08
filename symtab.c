// symtab.c
#include "symtab.h"
#include <string.h>

void init_symbol_table(SymbolTable *table) {
    table->scopes = NULL;
}

void add_scope(SymbolTable *table) {
    Scope *new_scope = create_scope(table, table->scopes);
    table->scopes = new_scope;
}

void remove_scope(SymbolTable *table) {
    if (table->scopes) {
        Scope *to_remove = table->scopes;
        table->scopes = table->scopes->parent;
        destroy_scope(to_remove);
    }
}

void add_symbol(SymbolTable *table, const char *name) {
    if (table->scopes) {
        add_identifier_to_scope(table->scopes, name);
    }
}

bool symbol_exists(SymbolTable *table, const char *name) {
    Scope *current = table->scopes;
    while (current) {
        if (is_identifier_in_scope(current, name)) {
            return true;
        }
        current = current->parent;
    }
    return false;
}
