#include "ticker.h"
#include <assert.h>
#include <string.h>

bool get_ticker(char symbol[TICKER_LEN], ticker *ticker)
{
    assert(ticker != NULL);

    ticker->price = 666.99;
    strncpy(ticker->symbol, symbol, TICKER_LEN);

    return true;
}