
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Interpreter state
struct BFState {
    // The array and the size of the array.
    size_t array_len;
    uint8_t* array;

    // Pointer to the current position, points into array..array+array_len.
    uint8_t* cur;
};

// Return 0 on success, and -1 in case of an error (e.g., an out-of-bounds access).
int brainfuck(struct BFState* state, const char* program) {
  
  if(state->cur < state->array || state->cur >= state->array + state->array_len){
      	return -1;
  }
  
  for(size_t i = 0;; ++i){
    
	  switch(program[i]){
		  case '>':
          		if(state->cur == state->array + state->array_len - 1){
					return -1;
				}
				++(state->cur);
				break;
		  case '<':
				if(state->cur == state->array){
					return -1;
				}
				--(state->cur);
				break;
		  case '+':
          		{
                    size_t acc = i;
                    while(program[++i] == '+');
                    (*(state->cur)) += i-acc;
                }
          		--i;
          		break;
		  case '-': 
          		{
                    size_t acc = i;
                    while(program[++i] == '-');
                    (*(state->cur)) -= i-acc;
                }
          		--i;
          		break;
		  case '[': 
          		if(program[i+1] == '-' && program[i+2] == ']'){
                    (*(state->cur)) = 0;
                    i +=2;
                } else if((*(state->cur)) == 0){
					for(int pCounter = 1; pCounter != 0;){
						++i;
						if(program[i] == '\0'){
							return -1;
						} else if(program[i] == ']'){
							--pCounter;
						} else if(program[i] == '['){
							++pCounter;
						}
					}
					--i;
				}
				break;
		  case ']': 
				if((*(state->cur)) != 0){
					for(int pCounter = -1; pCounter != 0;){
						if(i == 0){
							return -1;
						}
                        --i;
						if(program[i] == ']'){
							--pCounter;
						} else if(program[i] == '['){
							++pCounter;
						}
					}
					--i;
				}
				break;
		  case '\0': return 0;
		  case '.': putchar(*(state->cur)); break;
		  case ',': (*(state->cur)) = getchar(); break;
		  default: break;
	  }
  }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <bfprog>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t array_len = 3000;
    uint8_t* array = calloc(array_len, sizeof(uint8_t));
    if (!array) {
        fprintf(stderr, "could not allocate memory\n");
        return EXIT_FAILURE;
    }

    struct BFState state = {
        .array_len = array_len,
        .array = array,
        .cur = array,
    };
    int res = brainfuck(&state, argv[1]);
    if (res) {
        puts("an error occured");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
