#include "DEV_Config.h"
#include "EPD_2in13_V4.h"
#include "GUI_Paint.h"

#include "ticker_display.h"

#define FB_SIZE (((EPD_2in13_V4_WIDTH / 8) + 1) * EPD_2in13_V4_HEIGHT)
#define BUF_LEN 10

UBYTE fb[FB_SIZE];

bool display_init()
{
    if(DEV_Module_Init()!=0){
        return false;
    }

    EPD_2in13_V4_Init();
    EPD_2in13_V4_Clear();
    DEV_Delay_ms(500);

    return true;
}

void display_tickers(ticker *ticker1, ticker *ticker2, int battery)
{
    char buf[BUF_LEN + 1];
    Paint_NewImage(fb, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 270, WHITE);
    Paint_SelectImage(fb);
    // Paint_SetMirroring(MIRROR_HORIZONTAL);
    Paint_Clear(WHITE);

    // Split screen in two horizontally
    Paint_DrawLine(EPD_2in13_V4_HEIGHT / 2, 0, EPD_2in13_V4_HEIGHT / 2, EPD_2in13_V4_WIDTH, BLACK,
            DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    // Draw left ticker
    snprintf(buf, BUF_LEN, "%.2f", ticker1->price);
    Paint_DrawString_EN(0, 0, ticker1->alias, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(0, 25, buf, &Font24, WHITE, BLACK);

    // Draw right ticker
    snprintf(buf, BUF_LEN, "%.2f", ticker2->price);
    Paint_DrawString_EN(EPD_2in13_V4_HEIGHT / 2, 0, ticker2->alias, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(EPD_2in13_V4_HEIGHT / 2, 25, buf, &Font24, WHITE, BLACK);

    // Draw a battery indicator in the bottom right corner, with one dot per 20% of the battery
    // < 20% -> 0 dots; >80% -> 4 dots
    Paint_DrawRectangle(EPD_2in13_V4_HEIGHT - 5, EPD_2in13_V4_WIDTH - 2, EPD_2in13_V4_HEIGHT,
            EPD_2in13_V4_WIDTH, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    int dots = battery / 20;
    dots = dots > 4 ? 4 : dots;
    // Draw the dots, but start with one pixel to the left of the battery indicator square. It makes it look more
    // like a battery indicator with the plus terminal sticking out.
    Paint_DrawLine(EPD_2in13_V4_HEIGHT - 6, EPD_2in13_V4_WIDTH - 1, EPD_2in13_V4_HEIGHT - 6 + dots + 2,
            EPD_2in13_V4_WIDTH - 1, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    EPD_2in13_V4_Display(fb);
}