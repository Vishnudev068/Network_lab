#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expression[50];
int count = 0, flag = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void E() {
    T();
    Eprime();
}

void Eprime() {
    if (expression[count] == '+') {
        count++;
        T();
        Eprime();
    }
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (expression[count] == '*') {
        count++;
        F();
        Tprime();
    }
}

void F() {
    if (isalnum(expression[count])) {
        count++;
    } else if (expression[count] == '(') {
        count++;
        E();
        if (expression[count] == ')')
            count++;
        else
            flag = 1;
    } else {
        flag = 1;
    }
}

int main() {
    printf("\nEnter an Algebraic Expression:\t");
    scanf("%s", expression);

    E();

    if ((strlen(expression) == count) && (flag == 0))
        printf("\nThe Expression %s is Valid\n", expression);
    else
        printf("\nThe Expression %s is Invalid\n", expression);

    return 0;
}
