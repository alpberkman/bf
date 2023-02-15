#include <stdio.h>


int brainfuck(char *input);
int bf_brace_checker(char *input);


int main(int argc, char** argv) {

    if(argc != 2) {
        printf("No input!\n");
        return 1;
    }

    return brainfuck(argv[1]);
}


int bf_brace_checker(char *input) {

    int brace_ctr = 0;
    for(; *input != '\0'; ++input) {
        if(*input == '[')
            ++brace_ctr;
        else if(*input == ']')
            --brace_ctr;

        if(brace_ctr < 0)
            return -1;
    }

    if(brace_ctr != 0)
        return -1;
    else
        return 0;
}

int brainfuck(char *input) {

    if(bf_brace_checker(input))
        return -1;

    char arr[30000] = {0};
    char *ptr = arr;

    for(; *input; ++input) {

        switch(*input) {
        case '>':
            ++ptr;
            break;
        case '<':
            --ptr;
            break;
        case '+':
            ++*ptr;
            break;
        case '-':
            --*ptr;
            break;
        case '[':
            if(*ptr == 0) {
                for(int num_braces = 1; num_braces != 0;) {
                    ++input;
                    if(*input == '[')
                        ++num_braces;
                    else if(*input == ']')
                        --num_braces;
                }
            }
            break;
        case ']':
            for(int num_braces = -1; num_braces != 0;) {
                --input;
                if(*input == '[')
                    ++num_braces;
                else if(*input == ']')
                    --num_braces;
            }
            --input;
            break;
        case '.':
            putchar(*ptr);
            break;
        case ',':
            *ptr = getchar();
            break;
        default:
            break;
        }

        if(ptr < arr || ptr >= arr + 30000)
            return -1;
    }

    return 0;
}







