#include "TEMPLATE.h"
#include "Cord.h"

#define SMALL_WORD_SIZE 5
#define MEDIUM_WORD_SIZE 20

#define NUM_CONCATS 100
#define MAX_RANDOM_CONCATS 1000
#define NUM_ALPHABETS 52

#define RAND_SEED 5

char alphabets[NUM_ALPHABETS];

string to_str(const char *x) {
    stringstream s;
    s << x;
    return s.str();
}

void init_alphabets() {
    for (int i = 0; i < 26; i++) {
        alphabets[i] = 'a' + i;
    }

    for (int i = 0; i < 26; i++) {
        alphabets[i + 26] = 'A' + i;
    }
}

char randomAlpha() {
    return alphabets[rand() % NUM_ALPHABETS];
}


const char *randomWord(int word_size) {
    char *s = (char *)malloc(word_size + 1);
    for (int i = 0; i < word_size; i++) {
        s[i] = randomAlpha();
    }

    s[word_size] = '\0';
    return s;
}

void benchmark_insert(int num_words, int word_len) {

    Cord::Ptr res = NULL;
    res = Cord::cord_from_char_star(randomWord(word_len));
  
    for (int i = 1; i < num_words; i++) {
        const char *rand_string = randomWord(word_len);
        int insertion_pos = rand() % (res->length());
        res = Cord::insert(res, rand_string, insertion_pos);
    }
}

void setup() {
    init_alphabets();
    srand(RAND_SEED);
}

//ARG 1: number of words
//ARG 2: length of each word
int main(int argc, char *argv[]) {

    setup();

    if (argc >= 3) {
        benchmark_insert(atoi(argv[1]), atoi(argv[2]));
    }
    
    return 0;
}




