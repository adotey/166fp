#include "Cord.h"

#define MAX_FLAT_LEN 50
static size_t min_len [ MAX_DEPTH ];

static bool min_len_initialized = 0;

typedef struct {
    Cord::Ptr c;
} ForestElement;

typedef ForestElement Forest [ MAX_DEPTH ];

void init_min_len() {

    min_len_initialized = 1;

    int first = 1, second = 2;
    min_len[0] = first;
    min_len[1] = second;


    for (int i = 2; i < MAX_DEPTH; i++) {
        int current = first + second;
        if (current < second) {
            current = second;
        }

        first = second;
        second = current;

        min_len[i] = current;
    }
}

void init_forest(ForestElement * forest, size_t max_len)
{
    register int i;

    for (i = 0; i < MAX_DEPTH; i++) {
        forest[i].c = 0;
        if (min_len[i] > max_len)
            return;
    }
    assert(false && "Cord too long");
}

void add_forest(ForestElement *forest, Cord::Ptr x) {
    Cord::Ptr res = NULL;

    // find the spot to be occupied by x
    // concat the other cords to the left
    int chosen_spot = -1;
    for (int i = 0; i < MAX_DEPTH; i++) {

        if (min_len[i] > x->length()) {
            chosen_spot = i - 1;
            break;
        }

        if (forest[i].c != NULL) {
            res = Cord::cat(forest[i].c, res);
            forest[i].c = NULL;
        }
    }

    res = Cord::cat(res, x);
    register int sum_len = res->length();

    int i = chosen_spot;
    while (sum_len >= min_len[i]) {
        if (forest[i].c != NULL) {
            res = Cord::cat(forest[i].c, res);
            sum_len = res->length();
        }
        i++;
    }

    i--;
    forest[i].c = res;
}

Cord::Ptr concat_forest (ForestElement *forest, size_t expected_len) {

    Cord::Ptr res = NULL;
    for (int i = 0; i < MAX_DEPTH; i++) {
        if (expected_len < min_len[i]) {
            break;
        }

        if (res && res->length() == expected_len) {
            break;
        }

        if (forest[i].c != NULL) {
            res = Cord::cat(forest[i].c, res);
        }
    }
    return res;
}

void balance_insert(Cord::Ptr x, ForestElement *forest) {

    if (x->isLeaf()) {
        fflush(stdout);
        add_forest(forest, x);
    } else if (min_len[x->depth()] > x->length()) {

        // x is not balanced
        balance_insert(x->left(), forest);
        balance_insert(x->right(), forest);
    } else {
        // x is not a leaf, but it is balanced
        fflush(stdout);
        add_forest(forest, x);
    }
}

Cord::Ptr Cord::balance (Cord::Ptr x) {
    Forest forest;

    if (x == NULL) {
        return x;
    }

    if (!min_len_initialized) {
        init_min_len();
    }

    if (min_len[x->depth()] >= x->length()) {
        return x;
    }

    init_forest(forest, x->length());
    balance_insert(x, forest);
    return concat_forest(forest, x->length());
}


char Cord::fetch(int pos) {
    if (pos < 0) {
        return 0;
    }

    if (pos >= this->length()) {
        return 0;
    }

    if (this->isLeaf()) {
        const char *string_ = this->char_star();
        return string_[pos];
    }

    if (pos < this->left()->length()) {
        return this->left()->fetch(pos);
    } else {
        return this->right()->fetch(pos - this->left()->length());
    }
}

void Cord::log() {
    if (this->isLeaf()) {
        printf("%s", this->char_star());
        return;
    }

    this->left()->log();
    this->right()->log();
}

void Cord::to_str_helper(std::string &res) {
    if (this->isLeaf()) {
        stringstream s;
        s << this->char_star();
        res += s.str();
        return;
    }

    this->left()->to_str_helper(res);
    this->right()->to_str_helper(res);
}

std::string Cord::to_str() {
    std::string res = "";
    this->to_str_helper(res);
    return res;
}

Cord::Ptr cat_char_star(Cord::Ptr x, const char *y, size_t leny) {
    if (x == NULL) {
        return Cord::cord_from_char_star(y);
    }

    if (leny == 0) {
        return x;
    }

    if (x->isLeaf()) {
        const char *x_str = x->char_star();
        const char *y_str = y;
        int lenx = x->length();

        if ( (lenx + leny) <= MAX_FLAT_LEN) {
            char *res = (char *)malloc(sizeof(char) * (lenx + leny + 1));
            memcpy(res, x_str, lenx);
            memcpy(res + lenx, y_str, leny);
            res[lenx + leny] =  '\0';
            return Cord::cord_from_char_star(res);
        } else {
            Cord::Ptr res = new Cord();
            res->leftIs(x);
            res->rightIs(Cord::cord_from_char_star(y));
            res->update();
            return res;
        }
    } else {
        if (x->right()->isLeaf() && (x->right()->length() + leny <= MAX_FLAT_LEN)) {
            const char *x_right_str = x->right()->char_star();
            int len_x_right = x->right()->length();
            // db(len_x_right);
            char *res = (char *)malloc(sizeof (char) * (len_x_right + leny + 1));

            if (!res) {
                assert(false && "Malloc failed");
            }

            memcpy(res, x_right_str, len_x_right);
            memcpy(res + len_x_right, y, leny);
            res[len_x_right + leny] = '\0';

            x->rightIs(Cord::cord_from_char_star(res));
            x->update();
            return x;
        } else {
            Cord::Ptr res = new Cord();
            res->leftIs(x);
            res->rightIs(Cord::cord_from_char_star(y));
            res->update();

            if (min_len[res->depth()] > res->length()) {
                // db ("balance called");
                res = Cord::balance(res);
            }
            return res;
        }
    }
}

Cord::Ptr Cord::cat (Cord::Ptr x, Cord::Ptr y) {
    if (x == NULL || x->isEmpty()) {
        return y;
    }

    if (y == NULL || y->isEmpty()) {
        return x;
    }

    if (y->isLeaf()) {
        return cat_char_star(x, y->char_star(), y->length());
    }

    register int _depth = max(x->depth(), y->depth()) + 1;

    Cord::Ptr res = new Cord();
    res->leftIs(x);
    res->rightIs(y);
    res->depthIs(_depth);
    res->lengthIs(x->length() + y->length());

    if (res->depth() > MAX_DEPTH) {
        res = Cord::balance(res);
    }
    // db ("here 4");
    return res;
}

Cord::Ptr Cord::substr_helper(Cord::Ptr x, int pos, size_t len) {

    assert (len != 0 && "len cannot be 0");
    assert ((pos + len <= x->length()) && "(pos + len <= x->length()) failed");

    if (x->isLeaf()) {
        char *newcopy = (char *)malloc(len + 1);
        strncpy(newcopy, x->char_star() + pos, len);
        newcopy[len] = '\0';
        return Cord::cord_from_char_star(newcopy);
    } else {
        if (pos >= x->left()->length()) {
            if (len >= x->right()->length()) {
                return x->right();
            } else {
                return Cord::substr_helper(x->right(), pos - x->left()->length(), len);
            }
        } else if (pos + len <= x->left()->length()) {
            if (len == x->left()->length()) {
                return x->left();
            } else  {
                return Cord::substr_helper(x->left(), pos, len);
            }
        } else {

            int leftlen = x->left()->length() - pos;
            int rightlen = len - leftlen;

            Cord::Ptr left = Cord::substr_helper(x->left(), pos, leftlen);
            Cord::Ptr right = Cord::substr_helper(x->right(), 0, rightlen);

            return Cord::cat(left, right);
        }
    }
}


Cord::Ptr Cord::substr(Cord::Ptr x, int pos, int len) {
    if (x == NULL) {
        return NULL;
    }

    if (pos >= x->length() || len <= 0) {
        return NULL;
    }

    if (pos + len > x->length()) {
        len = x->length() - pos;
    }

    return Cord::substr_helper(x, pos, len);
}


// does not modify x
Cord::Ptr Cord::insert(Cord::Ptr x, const char *s, int pos) {

    if (x == NULL) {
        return Cord::cord_from_char_star(s);
    }

    Cord::Ptr partA = Cord::substr(x, 0, pos);
    Cord::Ptr partB = Cord::substr(x, pos, x->length());

    Cord::Ptr res = NULL;
    res = Cord::cat(partA, Cord::cord_from_char_star(s));
    res = Cord::cat(res, partB);

    return res;
}











