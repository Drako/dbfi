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

dbfi_lexer_t dbfi_lexer_init(char const * filename)
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

void dbfi_lexer_release(dbfi_lexer_t _this)
{
    if (_this)
    {
        fclose(_this->source_);
        free(_this);
    }
}

dbfi_token_info_t * dbfi_lexer_next_token(dbfi_lexer_t _this)
{
    static dbfi_token_info_t tok;
    
    assert(_this);
    assert(_this->source_);
    assert(_this->filename_);
    
    tok.filename_ = _this->filename_;
    
    for (; !feof(_this->source_);)
    {
        int c; /* current character */
        
        tok.row_ = _this->row_;
        tok.column_ = _this->column_;
        
        c = fgetc(_this->source_);
        ++(_this->column_);
        
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
                tok.type_ = DBFI_TOKEN_COMMA;
                return &tok;
            } break;
            
        case '\n':
        case '\r':
            {
                ++(_this->row_);
                _this->column_ = 0;
            } break;
        }
    }
    
    tok.type_ = DBFI_TOKEN_EOF;
    return &tok;
}
