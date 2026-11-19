#include "lab01.hpp"

bool insertAt(int a[], int& size, int cap, int pos, int x) {
    if (cap <= 0 || size < 0 || size >= cap) {
        return false;
    }
    if (pos < 0 || pos > size) {
        return false;
    }

    for (int i = size; i > pos; --i) {
        a[i] = a[i - 1];
    }

    a[pos] = x;
    ++size;
    return true;
}

bool deleteAt(int a[], int& size, int pos) {
    if (size <= 0 || pos < 0 || pos >= size) {
        return false;
    }

    for (int i = pos; i < size - 1; ++i) {
        a[i] = a[i + 1];
    }

    --size;
    return true;
}
