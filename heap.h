#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define TYPE_VALUE int
#define lld int

typedef struct Heap{
    TYPE_VALUE key;
    TYPE_VALUE value;
    struct Heap *parent;
    struct Heap *leftChild;
    struct Heap *rightChild;
} * heapPtr;

TYPE_VALUE defaultCompare(TYPE_VALUE a, TYPE_VALUE b);
void setCompareFunction(TYPE_VALUE(*compareFunctionArg)(TYPE_VALUE,TYPE_VALUE));
bool init(heapPtr *head);
bool push(heapPtr head, TYPE_VALUE key, TYPE_VALUE value,  lld length);
bool pop(heapPtr *head, lld length);
TYPE_VALUE getValue(heapPtr head);
TYPE_VALUE getKey(heapPtr head);
