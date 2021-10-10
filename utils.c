//
// Created by mitza on 05-Mar-21.
//

#include "utils.h"

void InitRandom(void) {
    srand((int) time(NULL));
}

double RandomReal(double low, double high) {
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    return (low + d * (high - low));
}

int RandomInteger(int low, int high) {
    int k;
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    k = (int) (d * (high - low + 1));
    return (low + k);
}
