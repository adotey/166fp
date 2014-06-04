#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define NUM_ALPHABETS 52
#define MEDIUM_WORD_SIZE 20
// #define TEST_WORD_LEN 1000

// #define BENCH_DOC_LEN 10000

#define RAND_SEED 5

char alphabets[NUM_ALPHABETS];

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


void setup() {
    init_alphabets();
    srand(RAND_SEED);
}

#define NUM_FETCHES 10000

void benchmark_fetch(int num_words) {
  string res = "";
  for (int i = 0; i < num_words; i++) {
    res += randomWord(MEDIUM_WORD_SIZE);
  }

  for (int i = 0; i < NUM_FETCHES; i++) {
    char c = res[rand() % res.length()];
  }
}

//ARG 1: number of words
//ARG 2: length of each word
int main(int argc, char *argv[]) {
  setup();

  if (argc >= 2) {
    benchmark_fetch(atoi(argv[1]));
  }


  return 0;
}
