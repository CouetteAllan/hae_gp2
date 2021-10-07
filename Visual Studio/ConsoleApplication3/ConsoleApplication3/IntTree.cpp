#include "IntTree.hpp"

int count(IntTree* head)
{
    int nbr = 0;

    if (!head)
        return 0;
    //int nbg = count(head->leftSon);
    //int nbr = count(head->rightSon);
    return 1 + count(head->leftSon) + count(head->rightSon);
   
}

IntTree* create(int value)
{
    IntTree* node = (IntTree*)malloc(sizeof(IntTree));
    node->value = value;
    node->leftSon = node->rightSon = nullptr;
    return node;
}

IntTree* insert(IntTree* head, int value)
{
    if (!head)
        return create(value);

    else {
        if (head->value > value) {
            if (head->leftSon)
                insert(head->leftSon, value);
            else
                head->leftSon = create(value);
        }
        else
        {
            if (head->rightSon)
                insert(head->rightSon, value);
            else
                head->rightSon = create(value);
        }
    }
    
    return head;
}

IntTree* remove(IntTree* head, int value)
{
    if (!head) {
        return head;
    }

    if (head->value == value) {
        IntTree* merged = merge(head->leftSon, head->rightSon);
        free(head);

        head = merged;
    }
    else {
        head->rightSon = remove(head->rightSon, value);
        head->leftSon = remove(head->leftSon, value);

    }
        return head;
}

IntTree* merge(IntTree* a, IntTree* b)
{
    if (!a)
        return b;
    if (!b)
        return a;

    IntTree* fg = a->leftSon;
    IntTree* fd = a->rightSon;
    int value = a->value;
    free(a);

    b = insert(b, value);

    b = merge(fg, b);
    b = merge(fd, b);

    return b;
}
