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

std::pair<Cord::Ptr, std::string> randomCordAndString(int word_size) {

    Cord::Ptr res = NULL;
    string original = "";
    int num_concats = rand() % MAX_RANDOM_CONCATS;

    for (int i = 0; i <num_concats; i++) {

        const char *random_word = randomWord(word_size);

        res = Cord::cat(res, Cord::cord_from_char_star(random_word));

        original += to_str(random_word);
    }

    assert (res != NULL && "res is still NULL");
    return make_pair(res, original);
}

void benchmark_append(int num_words, int word_len) {
  Cord::Ptr res = NULL;

  for (int i = 0; i < num_words; i++) {
    const char *rand_string = randomWord(word_len);
    res = Cord::cat(res, Cord::cord_from_char_star(rand_string));
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
        benchmark_append(atoi(argv[1]), atoi(argv[2]));
    }
    
    return 0;
}




