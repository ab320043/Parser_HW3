#include <stdio.h>
#include <stdlib.h>
#include "id_attrs.h"
#include "ast.h"
#include "symtab.h"
#include "scope_check.h"
#include "utilities.h"
#include "id_use.h"


// Function to check scopes within a block AST node
void scope_check_block(block_t *block, Scope *current_scope) {
    Scope *block_scope = create_scope(current_scope->symbol_table, current_scope);
    
    // Check constant declarations
    const_decl_t *const_decl = block->const_decls.start;
    while (const_decl) {
        add_identifier_to_scope(block_scope, const_decl->const_def_list.start->ident.name);
        const_decl = const_decl->next;
    }

    // Check variable declarations
    var_decl_t *var_decl = block->var_decls.var_decls;
    while (var_decl) {
        ident_t *ident = var_decl->ident_list.start;
        while (ident) {
            add_identifier_to_scope(block_scope, ident->name);
            ident = ident->next;
        }
        var_decl = var_decl->next;
    }

    // Check statements
    stmt_t *stmt = block->stmts.stmt_list.start;
    while (stmt) {
        scope_check_stmt(stmt, block_scope);
        stmt = stmt->next;
    }

    destroy_scope(block_scope);
}

void scope_check_stmt(stmt_t *stmt, Scope *current_scope) {
    switch (stmt->stmt_kind) {
        case assign_stmt:
            if (!is_identifier_in_scope(current_scope, stmt->data.assign_stmt.name)) {
                report_error("Undeclared identifier in assignment");
            }
            break;
        case call_stmt:
            if (!is_identifier_in_scope(current_scope, stmt->data.call_stmt.name)) {
                report_error("Undeclared function called");
            }
            break;
        case if_stmt:
        case while_stmt:
            scope_check_condition(&stmt->data.if_stmt.condition, current_scope);
            scope_check_block(stmt->data.if_stmt.then_stmts->stmt_list.start, current_scope);
            if (stmt->data.if_stmt.else_stmts) {
                scope_check_block(stmt->data.if_stmt.else_stmts->stmt_list.start, current_scope);
            }
            break;
        default:
            break;
    }
}

void scope_check_program(block_t program_AST) {
    SymbolTable symbol_table;
    init_symbol_table(&symbol_table);
    Scope *global_scope = create_scope(&symbol_table, NULL);
    scope_check_block(&program_AST, global_scope);
    destroy_scope(global_scope);
}