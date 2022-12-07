#include <stdio.h>
 
char * check(const char * s) {
    switch ( *s ) {
        case '\0' :
        case ')' :
        case '}' :
        case ']' :
            return (char*)s;
        case '(' : {
            char * ret = check(s + 1);
            return ( *ret == ')' ) ? check(ret + 1) : (char*)s;
        }
        case '{' : {
            char * ret = check(s + 1);
            return ( *ret == '}' ) ? check(ret + 1) : (char*)s;
        }
        case '[' : {
            char * ret = check(s + 1);
            return ( *ret == ']' ) ? check(ret + 1) : (char*)s;
        }
        default :
            return check(s + 1);
    }
}
 
int main(void) {
    char buf[BUFSIZ];
    
    while ( printf("Введите скобочную последовательность: ") && fgets(buf, BUFSIZ, stdin) && *buf != '\n' )
        printf("%s\n", ( *check(buf) ) ? "Не верная" : "Верная");
    
    return 0;
}