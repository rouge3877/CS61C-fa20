#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    /*get bit*/
    uint16_t _0th_bit_ = ((*reg) & (1 << 0)) >> 0;
    uint16_t _2th_bit_ = ((*reg) & (1 << 2)) >> 2;
    uint16_t _3th_bit_ = ((*reg) & (1 << 3)) >> 3;
    uint16_t _5th_bit_ = ((*reg) & (1 << 5)) >> 5;
    /*calculate bit*/
    uint16_t _15th_bit_ = ((_0th_bit_ ^ _2th_bit_) ^ _3th_bit_) ^ _5th_bit_;
    /*write current bit and shift   */   
    uint16_t _writen_15th_bit_ = _15th_bit_ << 15;
    uint16_t _15th_bit_eq0_ = 0b0111111111111111;
    (*reg) = (*reg) >> 1;
    (*reg) = ((*reg) & _15th_bit_eq0_) | _writen_15th_bit_;
    return;
}

