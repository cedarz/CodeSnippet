#include <stdio.h>
#include <stdlib.h>
#include "token.h"

#define LINE_BUF_SIZE (1024)

static Token st_look_ahead_token;
static int st_look_ahead_token_exists;

static void my_get_token(Token *token) {
	if(st_look_ahead_token_exists) {
		*token = st_look_ahead_token;
		st_look_ahead_token_exists = 0;
	} else {
		get_token(token);
	}
}

static void unget_token(Token *token) {
    st_look_ahead_token = *token;
    st_look_ahead_token_exists = 1;	
}

static double parse_primary_expression() {
    Token token;
    my_get_token(&token);
    if(token.kind == NUM) return token.value;
    fprintf(stderr, "syntax error: number required.\n");
    exit(1);
}

static double parse_term() {
    double v1, v2;
    Token token;
    v1 = parse_primary_expression();
    for(;;) {
        my_get_token(&token);
        if(token.kind != MUL && token.kind != DIV) {
            unget_token(&token);
            break;
        }
        v2 = parse_primary_expression();
        if(token.kind == MUL) {
            v1 *= v2;
        } else if(token.kind == DIV) {
            v1 /= v2;
        }
    }
    return v1;
}

double parse_expression() {
    double v1, v2;
    Token token;
    v1 = parse_term();
    for(;;) {
        my_get_token(&token);
        if(token.kind != ADD && token.kind != SUB) {
            unget_token(&token);
            break;
        }
        v2 = parse_term();
        if(token.kind == ADD) {
            v1 += v2;
        } else if(token.kind == SUB) {
            v1 -= v2;
        }
    }
    return v1;
}

double parse_line(void) {
    double value;
    Token token;
    st_look_ahead_token_exists = 0;
    my_get_token(&token);
    if(token.kind == EOL) {
    	fprintf(stderr, "expression required. \n");
    	return 0.0;
    } else {
    	unget_token(&token);
    	value = parse_expression();
    	return value;
    }
}

int main() {
    char line[LINE_BUF_SIZE];
    double value;
    
    while(fgets(line, LINE_BUF_SIZE, stdin)) {
        set_line(line);
        value = parse_line();
        printf(">>%lf\n", value);
    }
    return 0;
}
    
    

