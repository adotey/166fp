#! /usr/bin/env python
import os

#Params
# programs_to_run = ['./Cord/CordAppendDriver', './String/StringAppendDriver', './GapBuffer/GapBufferAppendDriver']
# programs_to_run = ['./String/StringInsertDriver', './GapBuffer/GapBufferInsertDriver', './Cord/CordInsertDriver']
num_words = 200000
initial_word_len = 20
max_word_len = 500
increment = 20

#benchmark script code
from subprocess import call
import time


def runtests1():
    print num_words, initial_word_len, max_word_len, increment

    for program in programs_to_run:
        print '\n' + program

        cur_word_len = initial_word_len
        while cur_word_len <= max_word_len:

            start = time.time()
            os.system("%s %d %d" % (program, num_words, cur_word_len));
            elapsed = (time.time() - start)
            # print program, cur_word_len, str(elapsed)
            print cur_word_len, str(elapsed)

            cur_word_len += increment

def runtests2():
    # print num_words, initial_word_len, max_word_len, increment
    programs_to_run = ['./Cord/CordFetchDriver', './String/StringFetchDriver', 
    './GapBuffer/GapBufferFetchDriver']

    for program in programs_to_run:
        print '\n' + program

        for num_words in range(50, 10001, 50):
            start = time.time()
            os.system("%s %d" % (program, num_words));
            elapsed = (time.time() - start)
            print str(num_words) + '\t' + str(elapsed)



def main():
    # runtests();
    runtests2();

if __name__ == "__main__":
    main();

