#include <stdio.h>
#include <string.h>
#include <ctype.h>

char tempvariables[] = {'z','y','x','w','v','u','t'};
int length, top = -1, count = 0, tvar = 0;
char input[20], prearray[20], stack[20], threeaddress[10][10];

char *strrev(char *str) {
    if (!str || !*str) return str;
    int i = strlen(str) - 1, j = 0;
    char ch;
    while (i > j) {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--; j++;
    }
    return str;
}

int prec(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

int isoperator(char sym) {
    return (sym == '+' || sym == '-' || sym == '*' || sym == '/');
}

void push(char sym) {
    stack[++top] = sym;
}

char pop() {
    return stack[top--];
}

void prefix() {
    int k = 0;
    for (int i = 0; i < length; i++) {
        if (isalnum(input[i])) {
            prearray[k++] = input[i];
        } else {
            while (top != -1 && prec(stack[top]) >= prec(input[i])) {
                prearray[k++] = pop();
            }
            push(input[i]);
        }
    }
    while (top != -1) {
        prearray[k++] = pop();
    }
    prearray[k] = '\0';
}

void generator(char op, char sym1, char sym2) {
    char line[10];
    sprintf(line, "%c=%c%c%c", tempvariables[tvar++], sym1, op, sym2);
    strcpy(threeaddress[count++], line);
}

int main() {
    printf("\nEnter the input expression: ");
    scanf("%s", input);

    length = strlen(input);
    strrev(input);
    prefix();
    strrev(prearray);

    for (int i = 0; i < length; i++) {
        if (isoperator(prearray[i])) {
            if (isalnum(prearray[i + 1]) && isalnum(prearray[i + 2])) {
                generator(prearray[i], prearray[i + 1], prearray[i + 2]);
            }
        }
    }

    printf("\nThree Address Code for the expression:\n\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", threeaddress[i]);
    }
    return 0;
}
