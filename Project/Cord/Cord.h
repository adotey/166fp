#ifndef CORD_H
#define CORD_H

#include "TEMPLATE.h"

#define MAX_DEPTH 48

class Cord {

public:
    typedef Cord * Ptr;
    Cord::Ptr left() {
        return left_;
    }

    void leftIs(Cord::Ptr _left) {
        left_ = _left;
    }

    Cord::Ptr right() {
        return right_;
    }

    void rightIs(Cord::Ptr _right) {
        right_ = _right;
    }

    bool isLeaf() {
        if (this->right() == NULL) {
            return true;
        }
        return false;
    }

    bool isString() {
        return isLeaf();
    }

    size_t length() {
        return length_;
    }

    void lengthIs(size_t _length) {
        length_ = _length;
    }

    size_t depth() {
        return depth_;
    }

    void depthIs(size_t _depth) {
        depth_ = _depth;
    }

    void update() {
        assert(this->left() != NULL && "left is NULL");
        assert(this->right() != NULL && "right is NULL");

        this->lengthIs(this->left()->length() + this->right()->length());
        this->depthIs(max(this->left()->depth(), this->right()->depth()) + 1);
    }



    const char * char_star() {
        if (isLeaf()) {
            return (const char *)left_;
        }
        return NULL;
    }

    bool isEmpty() {
        return this->length() == 0;
    }

    static Cord::Ptr cat(Cord::Ptr x, Cord::Ptr y);
    static Cord::Ptr balance(Cord::Ptr x);

    char fetch(int i);
    void log();

    static Cord::Ptr cord_from_char_star(const char *x) {

        int lenx = strlen(x);

        if (lenx <= 0) {
            return NULL;
        }

        Cord::Ptr res = new Cord();
        assert (res != NULL && "res is NULL in cord_from_char_star");

        res->leftIs((Cord::Ptr)x);
        res->rightIs(NULL);

        res->lengthIs(lenx);
        res->depthIs(0);

        return res;
    }

    Cord () {
        this->depthIs(0);
        this->lengthIs(0);
        this->leftIs(NULL);
        this->rightIs(NULL);
    }

    std::string to_str();

    static Cord::Ptr substr (Cord::Ptr x, int start, int len);

    static Cord::Ptr insert (Cord::Ptr x, const char *s, int pos);



private:

    void to_str_helper(std::string &res);
    static Cord::Ptr substr_helper(Cord::Ptr x, int pos, size_t len);



    size_t depth_;
    size_t length_;

    Cord::Ptr left_;
    Cord::Ptr right_;
};

#endif /* CORD_H */







