#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
	BAD_TOKEN,
	NUM,
	ADD,
	SUB,
	MUL,
	DIV,
	EOL
} TokenKind;

#define MAX_TOKEN_SIZE (100)

typedef struct {
	TokenKind kind;
	double value;
	char str[MAX_TOKEN_SIZE];
} Token;

void set_line(char *line);
void get_token(Token *token);

#endif


