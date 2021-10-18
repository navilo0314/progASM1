#include <stdio.h>
int main (void) {
    int hh = 3, mm = 1, ss = 4, dd = 159;
    printf ("Time is %02d:%02d:%02d.%06d\n", hh, mm, ss, dd);
    return 0;
}