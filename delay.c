#include "delay.h"

void delayMs(int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 16000; j++) {} // Adjust if your clock is not 16 MHz
}
