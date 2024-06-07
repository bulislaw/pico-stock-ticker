#pragma once

#include <stdbool.h>

#define TICKER_LEN 9 // Stock symbols are usually limited to 5 + 3 for %5E + EOS

typedef struct {
    char symbol[TICKER_LEN];
    char alias[TICKER_LEN]; // Usually alias is %5E which represents ^ for example in ^SPX
    float price;
} ticker;

bool get_ticker(const char *symbol, const char *alias, ticker *ticker);