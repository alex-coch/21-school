#include "parser.h"

float pars(char *line) {
    float ret = 0;
    int *pointer;
    double result;
    error = No;
    expr = line;
    pointer = getToken(expr);
    fSum(&result);
    *pointer = 0;

    switch (error) {
     case No:
        sprintf(expr, "%f", result);
        ret = result;
        break;
     case Syntax:
        strcpy(expr, "Syntax error!");
        break;
     case Zero:
        strcpy(expr, "Divide by zero!");
        break;
    }
    return ret;
}

int* getToken(char *expr) {
    static int i = 0;
    type = Empty;

    if (expr[i] == '\0') {  // Если конец выражения
        i = 0;
        return 0;
        }
    // while (isspace(expr[i])) i++;  // Пропустить разделительные символы
    while (expr[i] == ' ') i++;

    if (strchr("+-sctgl*/%^=()", expr[i])) {
        *token = expr[i];
        *(token+1) = '\0';
        if (((expr[i] == 's') && (expr[i+1] == 'i') && (expr[i+2] == 'n')) ||  \
            ((expr[i] == 'c') && (expr[i+1] == 'o') && (expr[i+2] == 's')) ||  \
            ((expr[i] == 't') && (expr[i+1] == 'a') && (expr[i+2] == 'n')) ||  \
            ((expr[i] == 'c') && (expr[i+1] == 't') && (expr[i+2] == 'g'))) {
            if ((expr[i] == 'c') && (expr[i+1] == 't') && (expr[i+2] == 'g')) {
            expr[i] = 'G';
            }
            i += 2;
            }
        if ((expr[i] == 's') && (expr[i+1] == 'q') && (expr[i+2] == 'r') && (expr[i+3] == 't'))  {
            expr[i] = 'S';
            i += 3;
            }
        if ((expr[i] == 'l') && (expr[i+1] == 'n'))  {
            i += 1;
            }
        type = Operator;
    } else if (isalpha(expr[i])) {
//    } else if ((expr[i] >= 'a') && (expr[i] <= 'z')) {
//    } else if (((expr[i] >= 97) && (expr[i] <= 122)) || ((expr[i] >= 65) && (expr[i] <= 90)))  {
        *token = expr[i];
        *(token+1) = '\0';
        type = Variable;
    } else if (isdigit(expr[i])) {
//    } else if ((expr[i] >= '0') && (expr[i] <= '9'))  {
//    } else if ((expr[i] >= 48) && (expr[i] <= 57))  {
        int j = 0;
        token[j] = expr[i];
        while (isdigit(expr[i+1]) || expr[i+1] == '.')
//        while (((expr[i] >= '0') && (expr[i] <= '9'))  || expr[i+1] == '.')
/*        while ((((expr[i] >= 97) && (expr[i] <= 122)) || ((expr[i] >= 65) && (expr[i] <= 90))) || \
            expr[i+1] == '.') */
            token[++j] = expr[++i];
        token[j+1] = '\0';
        type = Number;
    }
    i++;
    return &i;
}

int fSum(double *anw) {
    char op;
    double temp;
    if (fMulti(anw)) return 1;

    while ((op = *token) == '+' || op == '-' || op == 's' || op == 'c'  \
           || op == 't'|| op == 'g' || op == 'G' || op == 'S' || op == 'l') {
        getToken(expr);
        fMulti(&temp);
        switch (op) {
         case '+':
            *anw += temp;
            break;
         case '-':
            *anw -= temp;
            break;
        }
    }

return 0;
}

int fMulti(double *anw) {
    char op;
    double temp;
    if (fExp(anw)) return 1;  // Ошибка

    while ((op = *token) == '*' || op == '/' || op == '%') {
        getToken(expr);
        if (fExp(&temp)) return 1;  // Ошибка
        switch (op) {
         case '*':
            *anw *= temp;
            break;
         case '/':
            if (temp == 0.0) {
                error = Zero;
                return 1;
                }
            *anw /= temp;
            break;
         case '%':
            *anw = (int)*anw % (int)temp;
            break;
        }
    }

return 0;
}

int fExp(double *anw) {
    double temp;
    if (fUnary(anw)) return 1;  // Ошибка

    while (*token  == '^') {
        getToken(expr);
        if (fUnary(&temp)) return 1;  // Ошибка
        *anw = pow(*anw, temp);
        }

return 0;
}

int fUnary(double *anw) {
    char op = 0;
    if (*token == '+' || *token == '-' || *token == 's' || *token == 'c' || \
        *token == 't' || *token == 'g' || *token == 'G' || *token == 'S' || \
        *token == 'l') {
        op = *token;
        getToken(expr);
        }
    if (fBrack(anw)) return 1;  // Ошибка
    if (op == '-') *anw = -(*anw);
    if (op == 's') *anw = sin(*anw);
    if (op == 'c') *anw = cos(*anw);
    if (op == 't') *anw = tan(*anw);
    if (expr[0] == 'G') *anw = 1/tan(*anw);
    if ((op == 's') && (expr[0] == 'S')) *anw = sqrt(*anw);
    if (op == 'l') *anw = log(*anw);

return 0;
}

int fBrack(double *anw) {
    if (*token == '(') {
        getToken(expr);
        fSum(anw);

        if (*token != ')') {
            error = Syntax;
            return 1;
            }
        getToken(expr);
    } else {
        if (fAtom(anw)) return 1;  // Ошибка
    }
return 0;
}

int fAtom(double *anw) {
    if (type == Number) {
        *anw = atof(token);
        getToken(expr);
    } else {
        error = Syntax;
        return 1;
    }

return 0;
}


