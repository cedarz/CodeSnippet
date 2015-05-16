#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <iostream>
#include "token.h"

using namespace std;

static char *st_line;
static int st_line_pos;

typedef enum {
    INITIAL,
    IN_INT_PART,
    DOT,
    IN_FRAC_PART
} LexStatus;

void get_token(Token *token) {
    int out_pos = 0;
    LexStatus status = INITIAL;
    char current_char;
    token->kind = BAD_TOKEN;
    token->value = 0;
    while(st_line[st_line_pos] != '\0') {
    	//std::cout<<st_line_pos<<"=="<<endl;
    	//while(1);
        current_char = st_line[st_line_pos]; 
		//std::cout<<"char: "<<current_char<<std::endl;
        if((status == IN_INT_PART || status == IN_FRAC_PART)
                && !(isdigit(current_char)) && current_char != '.') {
            token->kind = NUM;
            sscanf(token->str, "%lf", &token->value);
            //std::cout<<"value: "<<token->value<<std::endl;
            return;
        }
        if(isspace(current_char)) {
            if(current_char == '\n') {
                token->kind =  EOL;
                return;
            }
            st_line_pos++;
            continue;
        } 
        if(out_pos >= MAX_TOKEN_SIZE - 1) {
            fprintf(stderr, "token too long!\n");
            exit(1);
        }
        token->str[out_pos] = st_line[st_line_pos];
        st_line_pos++;
        out_pos++;
        token->str[out_pos] = '\0';
        if(current_char == '+') {
            token->kind = ADD;
            return;
        } else if(current_char == '-') {
            token->kind = SUB;
            return;
        } else if(current_char == '*') {
            token->kind = MUL;
            return;
        } else if(current_char == '/') {
            token->kind = DIV;
            return;
        } else if(isdigit(current_char)) {
            if(status == INITIAL) {
                status = IN_INT_PART;
            } else if(status == DOT) {
                status = IN_FRAC_PART;
            } 
            //std::cout<<"value: "<<token->value<<std::endl;
        } else if(current_char == '.') {
            if(status == IN_INT_PART) {
                status = IN_FRAC_PART;
            } else {
                fprintf(stderr, "Syntax error!\n");
                exit(1);
            }
        } else {
        	fprintf(stderr, "input error !\n");
        }
    }
}

void set_line(char *line) {
    st_line = line;
    st_line_pos = 0;
}


void _parse_line(char *buf) {
    Token token;
    set_line(buf);
    for(;;) {
        get_token(&token);
        if(token.kind == EOL) {
            break;
        } else {
            printf("kind: %d, str: %s\n", token.kind, token.str);
        }
    }
}

int _main() {
    char buf[1024];
    while(fgets(buf, 1024, stdin)) {
        _parse_line(buf);
    }
    return 0;
}


