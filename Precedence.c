#include <stdio.h>
#include <string.h>
#include <strings.h>

void main() {
    char stack[20], ip[20], opt[10][10][1], ter[10];
    int i, j, k, n, top = 0, row, col;

    // Initialize
    for (i = 0; i < 10; i++) {
        stack[i] = 0;
        ip[i] = 0;
        for (j = 0; j < 10; j++) {
            opt[i][j][1] = 0;
        }
    }

    // Input number of terminals and terminals
    printf("Enter the no. of terminals: ");
    scanf("%d", &n);

    printf("\nEnter the terminals: ");
    scanf("%s", ter);

    // Input operator precedence table
    printf("Enter the table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    // Display operator precedence table
    printf("\nOPERATOR PRECEDENCE TABLE:\n\t");
    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
    }

    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++) {
            printf("%c\t", opt[i][j][0]);
        }
        printf("\n");
    }

    // Input string and simulate parsing
    stack[top] = '$';
    printf("\nEnter the input string (append with $): ");
    scanf("%s", ip);

    i = 0;
    printf("\nSTACK\t\tINPUT STRING\t\tACTION\n");

    while (i < strlen(ip)) {
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k])
                row = k;
            if (ip[i] == ter[k])
                col = k;
        }

        if (stack[top] == '$' && ip[i] == '$') {
            printf("String is ACCEPTED\n");
            break;
        } else if (opt[row][col][0] == '<' || opt[row][col][0] == '=') {
            stack[++top] = opt[row][col][0];
            stack[++top] = ip[i];
            ip[i] = ' ';
            printf("Shift %c\n", stack[top]);
            i++;
        } else if (opt[row][col][0] == '>') {
            while (stack[top] != '<') {
                top--;
            }
            top = top - 1;
            printf("Reduce\n");
        } else {
            printf("\nString is not accepted\n");
            break;
        }

        for (k = 0; k <= top; k++)
            printf("%c", stack[k]);
        printf("\t\t");

        for (k = 0; k < strlen(ip); k++)
            printf("%c", ip[k]);
        printf("\t\t\n");
    }
}
