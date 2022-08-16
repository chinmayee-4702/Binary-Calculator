
#define OPERAND 10 
#define OPERATOR 20
#define END	30
#define ERROR	40

typedef struct token {
	char op;
	int dec;
	int type; /* type takes values OPERAND/OPERATOR/END/*/	
	list *l; 
	int flag;
	char var;
	
}token;
token *getnext(char *, int *);
enum states { SPC, DIG, OPR, STOP, ERR };



