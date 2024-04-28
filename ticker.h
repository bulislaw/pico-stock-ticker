#pragma once

#include <stdbool.h>

#define TICKER_LEN 6 // Stock symbols are usually limited to 5 (+ EOS)

typedef struct {
    char symbol[TICKER_LEN];
    float price;
} ticker;

bool get_ticker(char symbol[TICKER_LEN], ticker *ticker);