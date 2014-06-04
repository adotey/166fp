#ifndef GAPBUFFER_H
#define GAPBUFFER_H

//GapBuffer class
#include <iostream>
#include <string.h>
using namespace std;

#define INIT_SIZE 5

class GapBuffer {
    char *buf;
    int size;
    int pre_size;
    int post_size;

    void expand();
    void move_cursor(int dist);

  public:
    // char fetch();
    // void concat();
    // void substring();
    // void iter();

    GapBuffer();

    void insert_char(char c);
    void delete_char();

    bool step_cursor_forward();
    bool step_cursor_backward();

    void move_cursor_to(int pos);
    void insert_string(char *str);

    void insert_char_at(int pos, char c);
    void insert_string_at(int pos, char *str);
    void append(char *str);

    char fetch_char_at(int pos);
    char *fetch_string_at(int pos, int len);

    void print_buffer();
    std::string to_str();
    size_t length() {
        return pre_size + post_size;
    }
};

#endif /* GAPBUFFER_H */