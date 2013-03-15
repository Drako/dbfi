#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct dbfi_lexer
{
    FILE * source_;
    uint32_t row_;
    uint32_t column_;
    char const * filename_;
};

struct dbfi_lexer * dbfi_lexer_init(char const * filename)
{
    struct dbfi_lexer * lexer = malloc(sizeof(struct dbfi_lexer));
    if (!lexer)
        return NULL;
    
    lexer->source_ = fopen(filename, "rt");
    if (!(lexer->source_))
    {
        free(lexer);
        return NULL;
    }
    
    lexer->row_ = lexer->column_ = 0;
    lexer->filename_ = filename;
    
    return lexer;
}

void dbfi_lexer_release(struct dbfi_lexer * this)
{
    if (this)
    {
        fclose(this->source_);
        free(this);
    }
}

dbfi_token_info_t * dbfi_lexer_next_token(struct dbfi_lexer * this)
{
    static dbfi_token_info_t tok;
    
    assert(this);
    assert(this->source_);
    assert(this->filename_);
    
    tok.filename_ = this->filename_;
    
    for (; !feof(this->source_);)
    {
        int c; /* current character */
        
        tok.row_ = this->row_;
        tok.column_ = this->column_;
        
        c = fgetc(this->source_);
        ++(this->column_);
        
        switch (c)
        {
        case '+':
            {
                tok.type_ = DBFI_TOKEN_PLUS;
                return &tok;
            } break;
        case '-':
            {
                tok.type_ = DBFI_TOKEN_MINUS;
                return &tok;
            } break;
        case '>':
            {
                tok.type_ = DBFI_TOKEN_GT;
                return &tok;
            } break;
        case '<':
            {
                tok.type_ = DBFI_TOKEN_LT;
                return &tok;
            } break;
        case '[':
            {
                tok.type_ = DBFI_TOKEN_BLEFT;
                return &tok;
            } break;
        case ']':
            {
                tok.type_ = DBFI_TOKEN_BRIGHT;
                return &tok;
            } break;
        case '.':
            {
                tok.type_ = DBFI_TOKEN_DOT;
                return &tok;
            } break;
        case ',':
            {
                tok.type_ = DBFI_TOKEN_COMMAND;
                return &tok;
            } break;
            
        case '\n':
        case '\r':
            {
                ++(this->row_);
                this->column_ = 0;
            } break;
        }
    }
    
    tok.type_ = DBFI_TOKEN_EOF;
    return &tok;
}
