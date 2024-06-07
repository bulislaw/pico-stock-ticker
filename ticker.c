#include "ticker.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"

#include "ticker_https.h"

#define YF_SERVER "query1.finance.yahoo.com"
#define YF_PATH "/v8/finance/chart/%s?interval=1d&range=1d"

char buffer[1200]; // This is measured and needs to be updated if the API or call changes
char path_buffer[50];

bool get_ticker(const char *symbol, const char *alias, ticker *ticker)
{
    assert(ticker != NULL);

    strncpy(ticker->symbol, symbol, TICKER_LEN);
    strncpy(ticker->alias, alias, TICKER_LEN);

    int ret = snprintf(path_buffer, sizeof(path_buffer), YF_PATH, symbol);
    if (ret < 0 || ret >= sizeof(path_buffer))
    {
        return false;
    }

    ret = https_get(YF_SERVER, path_buffer, NULL, 0, buffer, 1200);
    if (ret < 0)
    {
        return false;
    }

    char *ptr = strstr(buffer, "\"regularMarketPrice\":");
    if (ptr == NULL)
    {
        return false;
    }

    ret = sscanf(ptr, "\"regularMarketPrice\":%f", &ticker->price);
    if (ret < 1)
    {
        return false;
    }

    return true;
}