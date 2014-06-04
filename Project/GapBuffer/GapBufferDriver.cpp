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




void test_simple_insert_move() {
  GapBuffer gap = GapBuffer();

  //insert, forward/back, delete
  gap.insert_char('a');
  gap.step_cursor_backward();
  gap.insert_char('b');
  gap.insert_char('i');
  gap.insert_char('k');
  gap.insert_char('e');
  gap.insert_char('s');
  gap.step_cursor_forward();
  gap.delete_char();
  gap.insert_char(' ');
  gap.print_buffer();
}

void test_complex_insert_move() {
  GapBuffer gap = GapBuffer();

  //insert, forward/back, delete
  gap.insert_char('a');
  gap.step_cursor_backward();
  gap.insert_char('b');
  gap.insert_char('i');
  gap.insert_char('k');
  gap.insert_char('e');
  gap.insert_char('s');
  gap.step_cursor_forward();
  gap.delete_char();
  gap.insert_char(' ');
  gap.print_buffer();

  //insert string
  gap.insert_string((char *)"are cool");
  gap.print_buffer();

  //move_cursor_to with insert/delete of char/string
  // gap.move_cursor_to(0);
  // gap.print_buffer();
  // gap.insert_string((char *)"sometimes, ");
  // gap.print_buffer();
  // gap.move_cursor_to(25);
  // gap.print_buffer();
  // gap.insert_char('!');
  // gap.print_buffer();
  // gap.move_cursor_to(16);
  // gap.print_buffer();
  // gap.insert_string((char *)"AAA");
  // gap.print_buffer();

  //insert_at (confirm same result as above)
  gap.insert_string_at(0, (char *)"sometimes, ");
  // gap.insert_char_at(25, '!');
  // gap.insert_string_at(16, (char *)"AAA");
  gap.print_buffer();
}

void test_fetch() {
  GapBuffer gap = GapBuffer();

  //insert, forward/back, delete
  gap.insert_char('a');
  gap.step_cursor_backward();
  gap.insert_char('b');
  gap.insert_char('i');
  gap.insert_char('k');
  gap.insert_char('e');
  gap.insert_char('s');
  gap.step_cursor_forward();
  gap.delete_char();
  gap.insert_char(' ');
  gap.print_buffer();

  //insert string
  gap.insert_string((char *)"are cool");
  gap.print_buffer();

  //insert_at (confirm same result as above)
  gap.insert_string_at(0, (char *)"sometimes, ");
  // gap.insert_char_at(25, '!');
  // gap.insert_string_at(16, (char *)"AAA");
  gap.print_buffer();

  //fetch (tested)
  cout << gap.fetch_char_at(0) << endl;
  cout << gap.fetch_char_at(9) << endl;
  cout << gap.fetch_char_at(11) << endl;
  cout << gap.fetch_char_at(21) << endl;
  cout << gap.fetch_char_at(24) << endl;

  cout << "string test:" << endl;
  cout << gap.fetch_string_at(0, 25) << endl;
  cout << gap.fetch_string_at(0, 24) << endl;
  cout << gap.fetch_string_at(9, 10) << endl;
  cout << gap.fetch_string_at(9, 1) << endl;
  cout << gap.fetch_string_at(21, 2) << endl;
}


void test_various() {
  cout << "test" << endl;
  GapBuffer gap = GapBuffer();

  //insert, forward/back, delete
  gap.insert_char('a');
  gap.step_cursor_backward();
  gap.insert_char('b');
  gap.insert_char('i');
  gap.insert_char('k');
  gap.insert_char('e');
  gap.insert_char('s');
  gap.step_cursor_forward();
  gap.delete_char();
  gap.insert_char(' ');
  gap.print_buffer();

  //insert string
  gap.insert_string((char *)"are cool");
  gap.print_buffer();

  //move_cursor_to with insert/delete of char/string
  // gap.move_cursor_to(0);
  // gap.print_buffer();
  // gap.insert_string((char *)"sometimes, ");
  // gap.print_buffer();
  // gap.move_cursor_to(25);
  // gap.print_buffer();
  // gap.insert_char('!');
  // gap.print_buffer();
  // gap.move_cursor_to(16);
  // gap.print_buffer();
  // gap.insert_string((char *)"AAA");
  // gap.print_buffer();

  //insert_at (confirm same result as above)
  gap.insert_string_at(0, (char *)"sometimes, ");
  // gap.insert_char_at(25, '!');
  // gap.insert_string_at(16, (char *)"AAA");
  gap.print_buffer();

  //fetch (tested)
  cout << gap.fetch_char_at(0) << endl;
  cout << gap.fetch_char_at(9) << endl;
  cout << gap.fetch_char_at(11) << endl;
  cout << gap.fetch_char_at(21) << endl;
  cout << gap.fetch_char_at(24) << endl;

  cout << "string test:" << endl;
  cout << gap.fetch_string_at(0, 25) << endl;
  cout << gap.fetch_string_at(0, 24) << endl;
  cout << gap.fetch_string_at(9, 10) << endl;
  cout << gap.fetch_string_at(9, 1) << endl;
  cout << gap.fetch_string_at(21, 2) << endl;

  // gap.append((char *)"Hi");
  // gap.print_buffer();
}

void setup() {
    init_alphabets();
}





void benchmark_append(int num_words, int word_len) {
  GapBuffer gap = GapBuffer();

  for (int i = 0; i < num_words; i++) {
    const char *rand_string = randomWord(word_len);
    gap.append((char *)rand_string);
  }

  // gap.print_buffer();
}


void benchmark_insert(int num_words, int word_len) {
  GapBuffer gap = GapBuffer();

  int bench_doc_len = word_len * num_words;
  for (int i = 0; i < num_words; i++) {
    const char *rand_string = randomWord(word_len);
    int insertion_pos = rand() % bench_doc_len;
    gap.insert_string_at(insertion_pos, (char *)rand_string);
  }
}

//ARG 1: number of words
//ARG 2: length of each word
int main(int argc, char *argv[]) {
  setup();

  srand(RAND_SEED);
  // test_simple_insert_move();
  // test_complex_insert_move();
  // test_fetch();
  // test_various();

  //second argument is number of words to generate
  if (argc >= 3) {
    // cout << "running benchmark" << endl;
    // benchmark_insert(atoi(argv[1]), atoi(argv[2]));
    benchmark_append(atoi(argv[1]), atoi(argv[2]));
  }


  return 0;
}