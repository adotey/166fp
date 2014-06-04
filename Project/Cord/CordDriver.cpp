#include "TEMPLATE.h"
#include "Cord.h"

#define SMALL_WORD_SIZE 5
#define MEDIUM_WORD_SIZE 20

#define NUM_CONCATS 100
#define MAX_RANDOM_CONCATS 1000
#define NUM_ALPHABETS 52

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

void runSmallCorrectnessTests1() {

    string original = "";

    const char *word = randomWord(SMALL_WORD_SIZE);

    string t = to_str(word);
    Cord::Ptr res = NULL;
    for (int i = 0; i < NUM_CONCATS; i++) {
        original = original + t;
        char *temp = (char *)malloc(sizeof(char) * SMALL_WORD_SIZE);
        strcpy(temp, word);

        res = Cord::cat(res, Cord::cord_from_char_star(temp));
    }

    assert (res != NULL && "Res is still NULL");

    // res->log();
    // db((res->length()));
    // db((original.length()));

    assert(res->length() == original.length() && "Lengths don't match");

    for (int i = 0; i < res->length(); i++) {
        assert(res->fetch(i) == original[i]);
    }

}

void runSmallCorrectnessTests2 () {

    std::pair<Cord::Ptr, std::string> random_cord_string = randomCordAndString(13);
    Cord::Ptr rand_cord = random_cord_string.first;
    std::string rand_string = random_cord_string.second;
    assert(rand_cord->length() == rand_string.length());

    assert(rand_cord->to_str() == rand_string);

    // rand_cord->log();

    // cout << endl;
    // cout << endl;

    // cout << rand_string << endl;


}

void concatTests1 () {
    std::pair<Cord::Ptr, std::string> random_cord_string1 = randomCordAndString(13);
    Cord::Ptr rand_cord1 = random_cord_string1.first;
    std::string rand_string1 = random_cord_string1.second;
    assert(rand_cord1->to_str() == rand_string1 && "rand_string1 != rand_cord1");


    std::pair<Cord::Ptr, std::string> random_cord_string2 = randomCordAndString(109);
    Cord::Ptr rand_cord2 = random_cord_string2.first;
    std::string rand_string2 = random_cord_string2.second;
    assert(rand_cord2->to_str() == rand_string2 && "rand_string2 != rand_cord2");

    Cord::Ptr cat_cord = Cord::cat(rand_cord1, rand_cord2);
    std::string cat_string = rand_string1 + rand_string2;



    string t = cat_cord->to_str();
    assert (cat_string.length() == t.length() && "lengths do not match");
    assert(cat_string == cat_cord->to_str() && "cat_string != cat_cord");
}


void substrTests1 () {
    std::pair<Cord::Ptr, std::string> random_cord_string1 = randomCordAndString(MEDIUM_WORD_SIZE);
    Cord::Ptr rand_cord1 = random_cord_string1.first;
    std::string rand_string1 = random_cord_string1.second;
    assert(rand_cord1->to_str() == rand_string1 && "rand_string1 != rand_cord1");


    for (int i = 0; i < 100; i++) {
        int pos = rand() % rand_string1.length();
        int len = rand() % rand_string1.length();


        Cord::Ptr subCord = Cord::substr(rand_cord1, pos, len);
        string subCord_str = subCord->to_str();
        string substring = rand_string1.substr(pos, len);

        assert(subCord_str == substring && "Substring and subCord don't match");
    }
}

void simpleSubstrTests1() {

    const char *word = randomWord(SMALL_WORD_SIZE);
    string t = to_str(word);

    Cord::Ptr res = NULL;
    std::string original = "";

    for (int i = 0; i < NUM_CONCATS; i++) {
        original = original + t;
        char *temp = (char *)malloc(sizeof(char) * (SMALL_WORD_SIZE + 1));
        strcpy(temp, word);
        temp[SMALL_WORD_SIZE] = '\0';

        res = Cord::cat(res, Cord::cord_from_char_star(temp));
    }
    db (res->to_str());

    Cord::Ptr subres = Cord::substr(res, 5, 60);
    db(subres->to_str());
}

void simpleInsertTests1() {
    std::pair<Cord::Ptr, std::string> random_cord_string1 = randomCordAndString(MEDIUM_WORD_SIZE);

    Cord::Ptr rand_cord1 = random_cord_string1.first;
    std::string rand_string1 = random_cord_string1.second;

    for (int i = 0; i < 100; i++) {
        const char *word = randomWord(SMALL_WORD_SIZE);
        int pos = rand() % rand_string1.length();

        rand_cord1 = Cord::insert(rand_cord1, word, pos);
        // db(rand_cord1->to_str());
        rand_string1 = rand_string1.insert(pos, word);

        assert(rand_cord1->to_str() == rand_string1 && "rand_string1 != rand_cord1");
    }

}

void simpleInsertTests2 () {
    const char *word = randomWord(SMALL_WORD_SIZE);
    string t = to_str(word);

    Cord::Ptr res = Cord::cord_from_char_star(word);
    std::string original = t;

    const char *insert_word = randomWord(SMALL_WORD_SIZE);
    original.insert(2, insert_word);
    res = Cord::insert(res, insert_word, 2);

    db(res->to_str());
    db(original);
}

void setup() {
    init_alphabets();
}

int main() {
    setup();
    // runSmallCorrectnessTests1();
    // runSmallCorrectnessTests2();

    // substrTests1();
    // simpleSubstrTests1();

    // concatTests1();

    simpleInsertTests1();
    simpleInsertTests2();
    return 0;
}




