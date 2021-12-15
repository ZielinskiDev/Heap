#include "heap.h"

TYPE_VALUE defaultCompare(TYPE_VALUE a, TYPE_VALUE b){
    return a>b ? 1 : 0;
}
TYPE_VALUE (*compareFunction)(TYPE_VALUE,TYPE_VALUE) = &defaultCompare;

bool init(heapPtr *head)
{
    if ((*head = (heapPtr)malloc(sizeof(struct Heap))) == NULL)
        return false;
    else
        (*head)->leftChild=(*head)->rightChild=(*head)->parent=NULL;
    return true;
}

void setCompareFunction(TYPE_VALUE(*compareFunctionArg)(TYPE_VALUE,TYPE_VALUE)){
    compareFunction = compareFunctionArg;
}

TYPE_VALUE getValue(heapPtr head)
{
    return head->value;
}

TYPE_VALUE getKey(heapPtr head)
{
    return head->key;
}

bool push(heapPtr head, TYPE_VALUE key, TYPE_VALUE value, lld length)
{
    heapPtr p;
    if ((p = (heapPtr)malloc(sizeof(struct Heap))) == NULL)
    {
        return false;
    }
    else
    {
        if(length == 1){
            head->value = value;
            head->key = key;
            return true;
        }
        heapPtr tmp = head;
        lld binaryRepLength = (lld)log2(length)+1;
        lld binaryRep[binaryRepLength];

        for(lld k = 0; k < binaryRepLength; k++)
            binaryRep[k] = 0;
        
        lld i = 0;
        while(length > 0){
            binaryRep[i] = length % 2;
            length /= 2;
            i++;
        }
        
        for(lld j = i-2; j > 0; j--){
            if(binaryRep[j] == 0)
                tmp=tmp->leftChild;
            else if(binaryRep[j] == 1)
                tmp=tmp->rightChild;
        }

        p->value = value;
        p->key = key;
        p->parent = tmp;
        p->leftChild = p->rightChild = NULL;

        if(binaryRep[0] == 0)
            tmp->leftChild = p;
        else if(binaryRep[0] == 1)
            tmp->rightChild = p;

        while(p->parent != NULL && compareFunction(value, p->parent->value)){
            p->value = p->parent->value;
            p->key = p->parent->key;
            p->parent->value = value;
            p->parent->key = key;
            p = p->parent;
        }
        
    }
    return true;
}

bool pop(heapPtr *head, lld length){
    heapPtr tmp = *head;
    lld binaryRepLength = (lld)log2(length)+1;
    lld binaryRep[binaryRepLength];
    for(lld k = 0; k < binaryRepLength; k++)
        binaryRep[k] = 0;
    
    lld i = 0;
    while(length > 0){
        binaryRep[i] = length % 2;
        length /= 2;
        i++;
    }
    
    for(lld j = i-2; j >= 0; j--){
        if(binaryRep[j] == 0)
            tmp=tmp->leftChild;
        else if(binaryRep[j] == 1)
            tmp=tmp->rightChild;
    }
    (*head)->value = tmp->value;
    (*head)->key = tmp->key;

    if(binaryRep[0] == 0 && tmp->parent != NULL)
        (tmp->parent)->leftChild = NULL;
    if(binaryRep[0] == 1 && tmp->parent != NULL)
        (tmp->parent)->rightChild = NULL;

    tmp = NULL;
    free(tmp);
    tmp = *head;
    TYPE_VALUE tmp_val = tmp->value;
    TYPE_VALUE tmp_key = tmp->key;
    while(tmp->leftChild != NULL){
        if(tmp->rightChild == NULL){
            if(compareFunction(tmp->leftChild->value, tmp_val)){
                tmp->value = tmp->leftChild->value;
                tmp->key = tmp->leftChild->key;
                tmp->leftChild->value = tmp_val;
                tmp->leftChild->key = tmp_key;
                tmp = tmp->leftChild;
            }else{
                break;
            }
        }else{
            if(compareFunction(tmp->leftChild->value, tmp->rightChild->value) && compareFunction( tmp->leftChild->value, tmp_val)){
                tmp->value = tmp->leftChild->value;
                tmp->key = tmp->leftChild->key;
                tmp->leftChild->value = tmp_val;
                tmp->leftChild->key = tmp_key;
                tmp = tmp->leftChild;
            }else if(compareFunction(tmp->rightChild->value, tmp->leftChild->value) && compareFunction( tmp->rightChild->value, tmp_val)){
                tmp->value = tmp->rightChild->value;
                tmp->key = tmp->rightChild->key;
                tmp->rightChild->value = tmp_val;
                tmp->rightChild->key = tmp_key;
                tmp = tmp->rightChild;
            }else if(compareFunction(tmp->leftChild->value, tmp->rightChild->value) == 0 && compareFunction(tmp->leftChild->value, tmp_val)){
                tmp->value = tmp->leftChild->value;
                tmp->key = tmp->leftChild->key;
                tmp->leftChild->value = tmp_val;
                tmp->leftChild->key = tmp_key;
                tmp = tmp->leftChild;
            }else{
                break;
            }
        }
    }
    return true;
}