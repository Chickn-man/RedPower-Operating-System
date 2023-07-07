#include "table.h"
#include <stdlib.h>

unsigned long chstolba(chs *input) {
    if (input->head >= 255 || input->sector >= 63) return 1UL << 24; // return 2^24 (an impossible chs value)
    
    return (255 * 63 * input->cylinder) + (255 * input->head) + input->sector - 1;
}

chs *lbatochs(unsigned long input) {
    chs ret;

    ret.cylinder = (unsigned short)(input / (255 * 63));
    ret.head = (unsigned char)((ret.cylinder * (255 * 63)) / 63);
    ret.sector = ret.cylinder * (255 * 63) - ret.head * 63 + 1;

    return &ret;
}