//GapBuffer class implementation
//Ideas from http://scienceblogs.com/goodmath/2009/02/18/gap-buffers-or-why-bother-with-1/
#include "GapBuffer.h"
#include <iostream>
#include <string.h>
using namespace std;

GapBuffer::GapBuffer() {
  buf = new char[INIT_SIZE];
  size = INIT_SIZE;
  pre_size = 0;
  post_size = 0;
}

void GapBuffer::insert_char(char c) {
  if (pre_size + post_size == size) {
    expand();
  }

  buf[pre_size] = c;
  pre_size++;
}

void GapBuffer::insert_string(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    insert_char(str[i]);
  }
}

void GapBuffer::delete_char() {
  if (pre_size > 0) {
    pre_size--;
  }
}

bool GapBuffer::step_cursor_forward() {
  if (post_size > 0) {
    buf[pre_size] = buf[size - post_size];

    pre_size++;
    post_size--;
    return true;
  } else {
    return false;
  }
}

bool GapBuffer::step_cursor_backward() {
  if (pre_size > 0) {
    char char_to_copy = buf[pre_size - 1];
    buf[size - post_size - 1] = char_to_copy;

    pre_size--;
    post_size++;
    return true;
  } else {
    return false;
  }
}

// Moves cursor from current position by the amount in 'dist'
// 'dist' can be positive or negative
void GapBuffer::move_cursor(int dist) {
  if (dist > 0) {
    for (int i = 0; i < dist; i++) {
      if (!step_cursor_forward()) {
        return;
      }
    }
  } else if (dist < 0) {
    dist *= -1;
    for (int i = 0; i < dist; i++) {
      if (!step_cursor_backward()) {
        return;
      }
    }
  }
}

void GapBuffer::move_cursor_to(int pos) {
  // while (pos > size) {
  //   expand();
  // }

  move_cursor(pos - pre_size);  
}

void GapBuffer::insert_char_at(int pos, char c) {
  move_cursor_to(pos);
  insert_char(c);
}

void GapBuffer::insert_string_at(int pos, char *str) {
  move_cursor_to(pos);
  insert_string(str);
}

void GapBuffer::append(char *str) {
  insert_string_at(size, str);
}

// Calculates where the given position is in the gap buffer, then returns
// the character at that position. 
// O(1). Note it assumes the position is valid.
char GapBuffer::fetch_char_at(int pos) {
  if (pos < pre_size) {
    //position is before gap, so just return it
    return buf[pos];
  } else {
    // position is after gap, so look at (pos + gap_size)
    int gap_size = size - pre_size - post_size;
    return buf[pos + gap_size];
  }
}

// Returns a copy of the string in the buffer at the given position.
char *GapBuffer::fetch_string_at(int pos, int len) {
  char *new_str = new char[len];
  for (int i = 0; i < len; i++) {
    new_str[i] = fetch_char_at(pos + i);
  }

  return new_str;
}

void GapBuffer::expand() {
  int new_size = size * 2;
  char *new_buf = new char[new_size];

  memcpy(new_buf, buf, pre_size);
  memcpy(new_buf + (new_size - post_size), buf + (size - post_size), post_size);

  delete buf;
  buf = new_buf;
  size = new_size;
}

void GapBuffer::print_buffer() {
  for (int i = 0; i < size; i++) {
    if (buf[i] == '\0') {
      cout << "_";
    }
    cout << buf[i] << "|";
  }
  cout << endl;
  // cout << buf << endl;
  cout << size << endl;
  cout << "pre: " << pre_size << ", post: " << post_size << endl;
}

std::string GapBuffer::to_str() {
  std::string res = "";
  for (int i = 0; i < pre_size; i++) {
    res += buf[i];
  }

  for (int i = size - post_size; i < size; i++) {
    res += buf[i];
  }
  return res;
}








