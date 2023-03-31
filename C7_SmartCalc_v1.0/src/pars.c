#include "pars.h"

/** @brief Parsers tokens.
 *
 *  @param str a input string.
 *  @param retlex a returned token.
 *  @param retlen a returned number.
 *  @param unarop a feature of an unary operation.
 *
 *  @return a flag of parsing.
 */
bool pars_lexeme(char* str, lex* retlex, int* retLen, bool unarop) {
  bool parsed = false;
  int parsChr = FAILD;
  if (retlex != NULL) {
    retlex->num = 0;
    retlex->chr = '\0';
    retlex->type = UNDEFINED;

    if ((parsChr = parse_funx(str, retLen)) != FAILD) {
      retlex->type = FUNCTION;
      retlex->chr = parsChr;
      parsed = true;
    } else if ((parsChr = parse_bracket(str)) != FAILD) {
      *retLen = 1;
      retlex->type = BRACKET;
      retlex->chr = parsChr;
      parsed = true;
    } else {
      double num;
      char chr;
      int opLen;
      parsChr = parse_op(str, &opLen);
      parse_num(str, retLen, &num, &chr);
      if (parsChr != FAILD) {
        if (strchr("+-", parsChr) != NULL && unarop && *retLen > 0) {
          retlex->type = NUMBER;
          retlex->num = num;
          retlex->chr = parsChr;
          parsed = true;
        } else {
          retlex->type = OPERATOR;
          retlex->chr = parsChr;
          *retLen = opLen;
          parsed = true;
        }
      }
    }

    if (parsed == false) {
      double num;
      char chr;
      parse_num(str, retLen, &num, &chr);
      if (*retLen > 0) {
        retlex->type = NUMBER;
        retlex->num = num;
        retlex->chr = chr;
        parsed = true;
      }
    }
  }
  return parsed;
}

/** @brief Checks for functions.
 *
 *  @param str a input string.
 *  @param len a length of a token.
 *
 *  @return a function.
 */
char parse_funx(char* str, int* len) {
  char ret = FAILD;

  if (strstr(str, "cos") == str || strstr(str, "sin") == str ||
      strstr(str, "tan") == str || strstr(str, "ln") == str) {
    *len = 3;
    ret = str[0];
    if (ret == 'l') *len = 2;
  }
  if ((ret == FAILD) &&
      (strstr(str, "acos") == str || strstr(str, "asin") == str ||
       strstr(str, "atan") == str || strstr(str, "sqrt") == str)) {
    *len = 4;
    ret = str[1];
    if (str[1] != 'q') ret -= 32;
  }
  if ((ret == FAILD) && strstr(str, "log") == str) {
    *len = 3;
    ret = 'L';
  }
  return ret;
}

/** @brief Checks for brackets.
 *
 *  @param curl a input string.
 *
 *  @return a bracket.
 */
char parse_bracket(char* str) {
  char ret = FAILD;
  if (strstr(str, "(") == str)
    ret = '(';
  else if (strstr(str, ")") == str)
    ret = ')';
  return ret;
}

/** @brief Checks for operands.
 *
 *  @param str a input string.
 *  @param len a length of a operand.
 *
 *  @return a operand.
 */
char parse_op(char* str, int* len) {
  char ret = FAILD;
  if (strstr(str, "+") == str)
    ret = '+';
  else if (strstr(str, "-") == str)
    ret = '-';
  else if (strstr(str, "*") == str)
    ret = '*';
  else if (strstr(str, "/") == str)
    ret = '/';
  else if (strstr(str, "^") == str)
    ret = '^';
  else if (strstr(str, "mod") == str)
    ret = 'm';

  if (ret != FAILD) *len = 1;
  if (str[0] == 'm') *len = 3;
  return ret;
}

/** @brief Checks for numbers.
 *
 *  @param str a input string.
 *  @param ret_len a length of number.
 *  @param ret_num a returned number.
 *  @param ret_chr a returned char 'x'.
 *
 *  @return void.
 */
void parse_num(char* str, int* ret_len, double* ret_num, char* ret_chr) {
  *ret_len = 0;
  if (sscanf(str, "%lf %n", ret_num, ret_len) <= 0) {
    if (*str == 'x') {
      *ret_chr = 'x';
      *ret_num = 1;
      *ret_len = 1;
    } else if (*str == '+' && *(str + 1) == 'x') {
      *ret_chr = 'x';
      *ret_num = 1;
      *ret_len = 2;
    } else if (*str == '-' && *(str + 1) == 'x') {
      *ret_chr = 'x';
      *ret_num = -1;
      *ret_len = 2;
    }
  } else {
    *ret_chr = '\0';
  }
}

/** @brief Moves from a string to polish notation.
 *
 *  @param string a input string.
 *  @param retque a returned queue.
 *
 *  @return a flag of transition.
 */
bool str_to_polish(char* string, que** retque) {
  int status = true;
  mstack* stack = stack_init();
  *retque = queue_init();
  char* str = NULL;
  char* origstr = NULL;
  if ((status = (string != NULL))) {
    int len = strlen(string);
    str = (char*)calloc(sizeof(char), len + 10);
    origstr = str;
    snprintf(str, len + 9, "%s", string);
    rm_spaces(str);
    // printf("\nexp: = %s\n", str);
    // printf("strlen = %ld\n", strlen(str));
    if (strlen(str) <= 0) status = false;
    // printf("status %d\n", status);
  }

  bool unary = true;
  lex prevlex;
  prevlex.type = UNDEFINED;
  lex curlex;

  // SORT STATION START
  while (*str != '\0' && status) {
    int currWid;
    if (pars_lexeme(str, &curlex, &currWid, unary) &&
        validate(curlex, prevlex)) {
      unary = (curlex.type == OPERATOR || curlex.chr == '(');
      str += currWid;
      // 1. if current char is number -> add lexeme to output queue
      if (curlex.type == NUMBER) queue_add_new_lex(*retque, curlex);
      // 2. if current char is function -> add lexeme to stack
      if (curlex.type == FUNCTION || curlex.chr == '(')
        stack_add_new_lex(stack, curlex);
      // 3. if current char is operator
      if (curlex.type == OPERATOR) {
        while (stack->size > 0 &&
               (stack->head->lexi->type == OPERATOR ||
                stack->head->lexi->type == FUNCTION) &&
               (op_prior_cmp(curlex.chr, stack->head->lexi->chr)))
          queue_push(*retque, stack_pop(stack));

        stack_add_new_lex(stack, curlex);
      }
      // 4. if current cher is closed bracket -> find a pair in stack
      if (curlex.chr == ')') {
        if (stack->size <= 0) {
          printf("\n!SORT STATION ERROR!\n");
          status = false;
          break;
        } else {
          while (stack->head->lexi->chr != '(') {
            queue_push(*retque, stack_pop(stack));
            if (stack->size <= 0) {
              status = false;
              break;
            }
          }
          if (status) {
            free(stack_pop(stack));
            if (stack->size > 0 && stack->head->lexi->type == FUNCTION)
              queue_push(*retque, stack_pop(stack));
          }
        }
      }

      prevlex.type = curlex.type;
      prevlex.chr = curlex.chr;
      prevlex.num = curlex.num;
    } else {
      printf("\n!SORT STATION ERROR!\n");
      status = false;
      break;
    }
  }
  if (!(curlex.type == NUMBER || curlex.chr == ')')) status = false;
  while (stack->size > 0) queue_push(*retque, stack_pop(stack));
  // END OF SORT STATION

  if (origstr != NULL) free(origstr);

  stack_free(stack);
  return status;
}

/** @brief Validates consistent tokens.
 *
 *  @param curl a current token.
 *  @param prevl a prior token.
 *
 *  @return a flag of consistency of tokens.
 */
bool validate(lex curl, lex prevl) {
  bool retval = true;
  switch (prevl.type) {
    case NUMBER:
      if (curl.type != OPERATOR && curl.chr != ')') retval = false;
      break;
    case OPERATOR:
      if (curl.type != NUMBER && curl.type != FUNCTION && curl.chr != '(')
        retval = false;
      break;
    case FUNCTION:
      if (curl.chr != '(') retval = false;
      break;
    case BRACKET:
      if (prevl.chr == '(' && curl.type != NUMBER && curl.type != FUNCTION)
        retval = false;
      if (prevl.chr == ')' && curl.type != OPERATOR && curl.chr != ')')
        retval = false;
      break;
    case UNDEFINED:
      if (curl.type != NUMBER && curl.type != FUNCTION && curl.chr != '(')
        retval = false;
      break;

    default:
      break;
  }
  // printf("\n validate %d \n", retval);
  return retval;
}

/** @brief Removes spaces from a string.
 *
 *  @param str a string.
 *
 *  @return void.
 */
void rm_spaces(char* str) {
  char* d = str;
  do {
    while (*d == ' ') {
      ++d;
    }
  } while ((*str++ = *d++));
}

/** @brief Compares priorities between operations.
 *
 *  @param op1 a first token.
 *  @param op1 a second token.
 *
 *  @return a result of comparision.
 */
bool op_prior_cmp(char op1, char op2) {
  int retval = false;
  int prOp1 = op_prior(op1);
  int prOp2 = op_prior(op2);

  if (prOp1 <= prOp2) {
    retval = true;
    if (op1 == '^') retval = false;  // right-accociative operator
  }
  return retval;
}

/** @brief Determines a priority of an operation.
 *
 *  @param op a token.
 *
 *  @return a priority of an operation.
 */
int op_prior(char op) {
  int prior = 0;
  if (op == '+' || op == '-') prior = 1;
  if (op == '*' || op == '/' || op == 'm' || strchr("cstCSTqlL", op) != NULL)
    prior = 2;
  if (op == '^') prior = 3;
  // if (op < 1) printf("\n! Prior op error ! %d\n", prior);
  return prior;
}
