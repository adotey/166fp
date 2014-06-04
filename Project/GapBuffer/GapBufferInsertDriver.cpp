#include <iostream>
#include <string.h>
#include "GapBuffer.h"
#include <stdlib.h>
using namespace std;

#define NUM_ALPHABETS 52
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



void benchmark_insert(int num_words, int word_len) {

  GapBuffer gap = GapBuffer();
  gap.insert_string((char *)randomWord(word_len));

  for (int i = 1; i < num_words; i++) {
    const char *rand_string = randomWord(word_len);
    int insertion_pos = rand() % gap.length();
    gap.insert_string_at (insertion_pos, (char *)rand_string);
  }
  // cout << gap.to_str() << endl;
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