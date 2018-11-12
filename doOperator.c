#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

struct lexToken *token;

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_diff(struct tokenStack *stack); 
static int op_product(struct tokenStack *stack);
static int op_quotient(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack); 
static int op_ge(struct tokenStack *stack); 
static int op_le(struct tokenStack *stack); 
static int op_eq(struct tokenStack *stack); 
static int op_swap(struct tokenStack *stack);
static int op_rem(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_diff},
  {"*", op_product},
  {"/", op_quotient},
  {"GT", op_gt},
  {"LT", op_lt},
  {"GE", op_ge},
  {"LE", op_le},
  {"EQ", op_eq},
  {"SWAP", op_swap},
  {"MOD", op_rem},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  int i = 0;
  if(s->top == 0) {
    fprintf(stderr,"popTokenStack: popping an empty stack, aborting\n");
    exit(1);
  }
  else{
    i =atoi(popTokenStack(s)->symbol);
  }
  return i;
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
  token = allocToken();
  token->kind = LEX_TOKEN_NUMBER;
  
  sprintf(token->symbol, "%d", v);
  pushTokenStack(s,token);  
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_diff(struct tokenStack *stack)
{
  int v1, v2;

  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1);
  return(0);
}

static int op_product(struct tokenStack *stack)
{
  int v1, v2;

  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2);
  return(0);
}

static int op_quotient(struct tokenStack *stack)
{
  int v1, v2;

  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2/v1);
  return(0);
}

static int op_gt(struct tokenStack *stack)
{
  int v1, v2,result;

  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v2 > v1)
  {
	  result = 1;
  }
  else
  {
	  result = 0;
  }
  pushInt(stack, result);
  return(0);
}

static int op_lt(struct tokenStack *stack)
{
  int v1, v2,result;

  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v2 < v1)
  {
	  result = 1;
  }
  else
  {
	  result = 0;
  }
  pushInt(stack, result);
  return(0);
}

static int op_ge(struct tokenStack *stack)
{
  int v1, v2,result;

  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v2 >= v1)
  {
	  result = 1;
  }
  else
  {
	  result = 0;
  }
  pushInt(stack, result);
  return(0);
}


static int op_le(struct tokenStack *stack)
{
  int v1, v2,result;

  v1 = popInt(stack);
  v2 = popInt(stack);
  
  if (v2 <= v1)
  {
	  result = 1;
  }
  else
  {
	  result = 0;
  }
  pushInt(stack, result);
  return(0);
}

static int op_eq(struct tokenStack *stack)
{
  int v1, v2,result;

  v1 = popInt(stack);
  v2 = popInt(stack);

  if (v1 == v2)
  {
	  result = 1;
  }
  else
  {
	  result = 0;
  }
  pushInt(stack, result);
  return(0);
}


static int op_swap(struct tokenStack *stack)
{
  int v1, v2,temp;

  v1 = popInt(stack);
  temp = v1; 
  v2 = popInt(stack);
  v1 = v2;
  v2 = temp;
 
  pushInt(stack, v2);
  pushInt(stack, v1);

  return(0);
}

static int op_rem(struct tokenStack *stack)
{
  int v1;

  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v1);
  return(0);
}

