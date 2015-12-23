/*
 ============================================================================
 Name        : BitTwiddlingHacksTest.c
 Author      : jdebruijn
 Version     :
 Copyright   : � jdebruijn 2015
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "BitOperations.h"
#include "greatest.h"

void
putBits( const uint64_t _v, const uint8_t _nBits );

const uint64_t bitMaskNNResult[] = {
        0b0000000000000000000000000000000000000000000000000000000000000001,
        0b0000000000000000000000000000000000000000000000000000000000000010,
        0b0000000000000000000000000000000000000000000000000000000000000100,
        0b0000000000000000000000000000000000000000000000000000000000001000,
        0b0000000000000000000000000000000000000000000000000000000000010000,
        0b0000000000000000000000000000000000000000000000000000000000100000,
        0b0000000000000000000000000000000000000000000000000000000001000000,
        0b0000000000000000000000000000000000000000000000000000000010000000,
        0b0000000000000000000000000000000000000000000000000000000100000000,
        0b0000000000000000000000000000000000000000000000000000001000000000,
        0b0000000000000000000000000000000000000000000000000000010000000000,
        0b0000000000000000000000000000000000000000000000000000100000000000,
        0b0000000000000000000000000000000000000000000000000001000000000000,
        0b0000000000000000000000000000000000000000000000000010000000000000,
        0b0000000000000000000000000000000000000000000000000100000000000000,
        0b0000000000000000000000000000000000000000000000001000000000000000,
        0b0000000000000000000000000000000000000000000000010000000000000000,
        0b0000000000000000000000000000000000000000000000100000000000000000,
        0b0000000000000000000000000000000000000000000001000000000000000000,
        0b0000000000000000000000000000000000000000000010000000000000000000,
        0b0000000000000000000000000000000000000000000100000000000000000000,
        0b0000000000000000000000000000000000000000001000000000000000000000,
        0b0000000000000000000000000000000000000000010000000000000000000000,
        0b0000000000000000000000000000000000000000100000000000000000000000,
        0b0000000000000000000000000000000000000001000000000000000000000000,
        0b0000000000000000000000000000000000000010000000000000000000000000,
        0b0000000000000000000000000000000000000100000000000000000000000000,
        0b0000000000000000000000000000000000001000000000000000000000000000,
        0b0000000000000000000000000000000000010000000000000000000000000000,
        0b0000000000000000000000000000000000100000000000000000000000000000,
        0b0000000000000000000000000000000001000000000000000000000000000000,
        0b0000000000000000000000000000000010000000000000000000000000000000,
        0b0000000000000000000000000000000100000000000000000000000000000000,
        0b0000000000000000000000000000001000000000000000000000000000000000,
        0b0000000000000000000000000000010000000000000000000000000000000000,
        0b0000000000000000000000000000100000000000000000000000000000000000,
        0b0000000000000000000000000001000000000000000000000000000000000000,
        0b0000000000000000000000000010000000000000000000000000000000000000,
        0b0000000000000000000000000100000000000000000000000000000000000000,
        0b0000000000000000000000001000000000000000000000000000000000000000,
        0b0000000000000000000000010000000000000000000000000000000000000000,
        0b0000000000000000000000100000000000000000000000000000000000000000,
        0b0000000000000000000001000000000000000000000000000000000000000000,
        0b0000000000000000000010000000000000000000000000000000000000000000,
        0b0000000000000000000100000000000000000000000000000000000000000000,
        0b0000000000000000001000000000000000000000000000000000000000000000,
        0b0000000000000000010000000000000000000000000000000000000000000000,
        0b0000000000000000100000000000000000000000000000000000000000000000,
        0b0000000000000001000000000000000000000000000000000000000000000000,
        0b0000000000000010000000000000000000000000000000000000000000000000,
        0b0000000000000100000000000000000000000000000000000000000000000000,
        0b0000000000001000000000000000000000000000000000000000000000000000,
        0b0000000000010000000000000000000000000000000000000000000000000000,
        0b0000000000100000000000000000000000000000000000000000000000000000,
        0b0000000001000000000000000000000000000000000000000000000000000000,
        0b0000000010000000000000000000000000000000000000000000000000000000,
        0b0000000100000000000000000000000000000000000000000000000000000000,
        0b0000001000000000000000000000000000000000000000000000000000000000,
        0b0000010000000000000000000000000000000000000000000000000000000000,
        0b0000100000000000000000000000000000000000000000000000000000000000,
        0b0001000000000000000000000000000000000000000000000000000000000000,
        0b0010000000000000000000000000000000000000000000000000000000000000,
        0b0100000000000000000000000000000000000000000000000000000000000000,
        0b1000000000000000000000000000000000000000000000000000000000000000
};

/**
 * Test name:   test_bitMask32_goodWeather
 * Test case:   Whether bitMaks32(n) gives the right bit mask for n is 0 to 32.
 * Test values:
 *  0
 *  1
 *  ...
 *  30
 *  31
 */
TEST test_bitMask32_goodWeather(void) {
    uint8_t i;
    for( i = 0; i<32; i++ ) {
        GREATEST_ASSERT_EQ(bitMaskNNResult[i], bitMask32(i));
    }
    PASS();
}

/**
 * Test name:   test_bitMask32_falsePositive
 * Test case:   Whether bitMaks32(n) fails for bit mask n is 32 to 64.
 * Test values:
 *  32
 *  33
 *  ...
 *  62
 *  63
 */
TEST test_bitMask32_falsePositive(void) {
    uint8_t i;
    for( i = 32; i<64; i++ ) {
        GREATEST_ASSERT_FALSE(bitMaskNNResult[i] == bitMask32(i));
    }
    PASS();
}

/**
 * Test name:   test_bitMask64_goodWeather
 * Test case:   Whether bitMaks64(n) gives the right bit mask for n is 0 to 64.
 * Test values:
 *  0
 *  1
 *  ...
 *  62
 *  63
 */
TEST test_bitMask64_goodWeather(void) {
    uint8_t i;
    for( i = 0; i<64; i++ ) {
        GREATEST_ASSERT_EQ(bitMaskNNResult[i], bitMask64(i));
    }
    PASS();
}

/**
 * Test name:   test_bitGet_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0xFFFFFFFFFFFFFFFF, 0
 *  0xFFFFFFFFFFFFFFFF, 1
 *  ...
 *  0xFFFFFFFFFFFFFFFF, 62
 *  0xFFFFFFFFFFFFFFFF, 63
 */
TEST test_bitGet_goodWeather(void) {
    uint8_t i;
    for( i = 0; i < 64; i++ ) {
        GREATEST_ASSERT_EQ(1, bitGet(0xFFFFFFFFFFFFFFFF, i));
    }

    PASS();
}

/**
 * Test name:   test_bitGetm_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0xFFFFFFFFFFFFFFFF, 2^0
 *  0xFFFFFFFFFFFFFFFF, 2^1
 *  ...
 *  0xFFFFFFFFFFFFFFFF, 2^62
 *  0xFFFFFFFFFFFFFFFF, 2^63
 *
 *  0xFFFFFFFFFFFFFFFF, 0
 *  0xFFFFFFFFFFFFFFFF, 1
 *  ...
 *  0xFFFFFFFFFFFFFFFF, 253
 *  0xFFFFFFFFFFFFFFFF, 254
 */
TEST test_bitGetm_goodWeather(void) {
    uint8_t i;
    for( i = 0; i < 64; i++ ) {
        GREATEST_ASSERT_EQ(bitMaskNNResult[i], bitGetm(0xFFFFFFFFFFFFFFFF, bitMaskNNResult[i]));
    }
    for( i = 0; i < UINT8_MAX; i++ ) {
        GREATEST_ASSERT_EQ(i, bitGetm(0xFFFFFFFFFFFFFFFF, i));
    }

    PASS();
}

/**
 * Test name:   test_bitSet_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0, 0
 *  0, 1
 *  ...
 *  0, 62
 *  0, 63
 *
 *  0x8000000000000000, 1
 *  0x8000000000000002, 62
 */
TEST test_bitSet_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0;
        bitSet(v, i);
        GREATEST_ASSERT_EQ(bitMaskNNResult[i], v);
    }

    v = 0x8000000000000000;
    bitSet(v, 1);
    GREATEST_ASSERT_EQ(0x8000000000000002, v);
    bitSet(v, 62);
    GREATEST_ASSERT_EQ(0xC000000000000002, v);

    PASS();
}

/**
 * Test name:   test_bitSetm_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0, 0
 *  0, 1
 *  ...
 *  0, 62
 *  0, 63
 *
 *  0x8000000000000000, 0x1F00
 *  0x8000000000001F00, 0x123ABC0F000000
 */
TEST test_bitSetm_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0;
        bitSetm(v, i);
        GREATEST_ASSERT_EQ(i, v);
    }

    v = 0x8000000000000000;
    bitSetm(v, 0x1F00);
    GREATEST_ASSERT_EQ(0x8000000000001F00, v);
    bitSetm(v, 0x123ABC0F000000);
    GREATEST_ASSERT_EQ(0x80123ABC0F001F00, v);

    PASS();
}

/**
 * Test name:   test_bitClear_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0xFFFFFFFFFFFFFFFF, 0
 *  0xFFFFFFFFFFFFFFFF, 1
 *  ...
 *  0xFFFFFFFFFFFFFFFF, 62
 *  0xFFFFFFFFFFFFFFFF, 63
 *
 *  0x80123ABC0F001F00, 63
 *  0x00123ABC0F001F00, 35
 *  0x00123AB40F001F00, 8
 *  0x00123AB40F001E00, 0
 */
TEST test_bitClear_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        bitClear(v, i);
        GREATEST_ASSERT_EQ(~bitMaskNNResult[i], v);
    }

    v = 0x80123ABC0F001F00;
    bitClear(v, 63);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    bitClear(v, 35);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    bitClear(v, 8);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    bitClear(v, 0);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);

    PASS();
}

/**
 * Test name:   test_bitClear_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0xFFFFFFFFFFFFFFFF, 0
 *  0xFFFFFFFFFFFFFFFF, 1
 *  ...
 *  0xFFFFFFFFFFFFFFFF, 62
 *  0xFFFFFFFFFFFFFFFF, 63
 *
 *  0x80123ABC0F001F00, 0x8000000000000000
 *  0x00123ABC0F001F00, 0x800000000
 *  0x00123AB40F001F00, 0x100
 *  0x00123AB40F001E00, 1
 */
TEST test_bitClearm_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        bitClearm(v, i);
        GREATEST_ASSERT_EQ(~i, v);
    }

    v = 0x80123ABC0F001F00;
    bitClearm(v, 0x8000000000000000);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    bitClearm(v, 0x800000000);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    bitClearm(v, 0x100);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    bitClearm(v, 1);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);

    PASS();
}

/**
 * Test name:   test_bitFlip_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0xFFFFFFFFFFFFFFFF, 0
 *  0xFFFFFFFFFFFFFFFF, 1
 *  ...
 *  0xFFFFFFFFFFFFFFFF, 62
 *  0xFFFFFFFFFFFFFFFF, 63
 *
 *  0x80123ABC0F001F00, 63
 *  0x00123ABC0F001F00, 35
 *  0x00123AB40F001F00, 8
 *  0x00123AB40F001E00, 0
 */
TEST test_bitFlip_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        bitFlip(v, i);
        GREATEST_ASSERT_EQ(~bitMaskNNResult[i], v);
    }

    v = 0x80123ABC0F001F00;
    bitFlip(v, 63);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    bitFlip(v, 35);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    bitFlip(v, 8);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    bitFlip(v, 0);
    GREATEST_ASSERT_EQ(0x00123AB40F001E01, v);

    PASS();
}

/**
 * Test name:   test_bitFlipm_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0xFFFFFFFFFFFFFFFF, 0
 *  0xFFFFFFFFFFFFFFFF, 1
 *  ...
 *  0xFFFFFFFFFFFFFFFF, 62
 *  0xFFFFFFFFFFFFFFFF, 63
 *
 *  0x80123ABC0F001F00, 0x8000000000000000
 *  0x00123ABC0F001F00, 0x800000000
 *  0x00123AB40F001F00, 0x100
 *  0x00123AB40F001E00, 1
 */
TEST test_bitFlipm_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        bitFlipm(v, i);
        GREATEST_ASSERT_EQ(~i, v);
    }

    v = 0x80123ABC0F001F00;
    bitFlipm(v, 0x8000000000000000);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    bitFlipm(v, 0x800000000);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    bitFlipm(v, 0x100);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    bitFlipm(v, 1);
    GREATEST_ASSERT_EQ(0x00123AB40F001E01, v);

    PASS();
}

/**
 * Test name:   test_shiftLeft_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  1, 0
 *  1, 1
 *  ...
 *  1, 62
 *  1, 63
 *
 *  0x00000000000FF010, 4
 *  0x0000000000FF0100, 12
 *  0x0000000FF0100000, 32
 */
TEST test_shiftLeft_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 1;
        shiftLeft(v, i);
        GREATEST_ASSERT_EQ(bitMaskNNResult[i], v);
    }
    v = 0x00000000000FF010;
    shiftLeft(v, 4);
    GREATEST_ASSERT_EQ(0x0000000000FF0100, v);
    shiftLeft(v, 12);
    GREATEST_ASSERT_EQ(0x0000000FF0100000, v);
    shiftLeft(v, 32);
    GREATEST_ASSERT_EQ(0xF010000000000000, v);

    PASS();
}

/**
 * Test name:   test_shiftRight_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  1, 0
 *  1, 1
 *  ...
 *  1, 62
 *  1, 63
 *
 *  0x010FF00000000000, 4
 *  0x0010FF0000000000, 12
 *  0x0000010FF0000000, 32
 */
TEST test_shiftRight_goodWeather(void) {
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0x8000000000000000;
        shiftRight(v, i);
        GREATEST_ASSERT_EQ(bitMaskNNResult[63-i], v);
    }
    v = 0x010FF00000000000;
    shiftRight(v, 4);
    GREATEST_ASSERT_EQ(0x0010FF0000000000, v);
    shiftRight(v, 12);
    GREATEST_ASSERT_EQ(0x0000010FF0000000, v);
    shiftRight(v, 32);
    GREATEST_ASSERT_EQ(0x000000000000010F, v);

    PASS();
}

/**
 * Test name:   test_isPositive_goodWeather
 * Test case:   Whether the signs of a unit32 minimum, zero and maximum values are correctly determined
 * determined.
 * Test values:
 *  -2147483648 (INT32_MIN)
 *  0
 *  2147483647 (INT32_MAX)
 */
TEST test_isPositive_goodWeather(void) {
    GREATEST_ASSERT_EQ(0 , isPositive(INT32_MIN));
    GREATEST_ASSERT_EQ(1 , isPositive(0));
    GREATEST_ASSERT_EQ(1 , isPositive(INT32_MAX));

    PASS();
}

/**
 * Test name:   test_haveOppositeSigns_goodWeather
 * Test case:   Whether difference in signs are correctly determined
 * Test values:
 *  -   -
 *  -   +
 *  +   -
 *  +   +
 */
TEST test_haveOppositeSigns_goodWeather(void) {
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(INT32_MIN, -1));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(-1, 1));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(1, -1));
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(1, INT32_MAX));

    PASS();
}

/**
 * Test name:   test_min_goodWeather
 * Test case:   Whether min() returns the right value
 * Test values:
 *  -2147483648 (INT32_MIN) -1
 *  2147483647 (INT32_MAX)  -2147483648 (INT32_MIN)
 *  0                       0
 *  1                       2147483647 (INT32_MAX)
 */
TEST test_min_goodWeather(void) {
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MIN, -1));
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MAX, INT32_MIN));
    GREATEST_ASSERT_EQ(0, min(0, 0));
    GREATEST_ASSERT_EQ(1, min(1, INT32_MAX));

    PASS();
}

/**
 * Test name:   test_max_goodWeather
 * Test case:   Whether max() returns the right value
 * Test values:
 *  -2147483648 (INT32_MIN) -1
 *  2147483647 (INT32_MAX)  -2147483648 (INT32_MIN)
 *  0                       0
 *  1                       2147483647 (INT32_MAX)
 */
TEST test_max_goodWeather(void) {
    GREATEST_ASSERT_EQ(-1, max(INT32_MIN, -1));
    GREATEST_ASSERT_EQ(INT32_MAX, max(INT32_MAX, INT32_MIN));
    GREATEST_ASSERT_EQ(0, max(0, 0));
    GREATEST_ASSERT_EQ(INT32_MAX, max(1, INT32_MAX));

    PASS();
}

/**
 * Test name:   test_isPowerOf2_goodWeather
 * Test case:   Whether isPowerOf2() returns the right value
 * Test values:
 *  2^0
 *  2^1
 *  ...
 *  2^62
 *  2^63
 */
TEST test_isPowerOf2_goodWeather(void) {
    uint8_t i;
    uint64_t power = 1;

    for(i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, isPowerOf2(power << i));
    }

    PASS();
}

/**
 * Test name:   test_isPowerOf2_falsePositive
 * Test case:   Whether isPowerOf2() returns the right value
 * Test values:
 *  0
 *  1
 *  ...
 *  62
 *  63
 */
TEST test_isPowerOf2_falsePositive(void) {
    uint8_t i;

    for(i = 0; i < 64; i++) {
        if(i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32) {
            GREATEST_ASSERT_EQ(1, isPowerOf2(i));
        }
        else {
            GREATEST_ASSERT_EQ(0, isPowerOf2(i));
        }
    }

    PASS();
}

/**
 * Test name:   test_modifyBits_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  &0x0F0F0F0F, 0,   1
 *  &0x0F0F0F0F, 1,   1
 *  ...
 *  &0x0F0F0F0F, 253, 1
 *  &0x0F0F0F0F, 254, 1
 *
 *  &0x0F0F0F0F, 0,   0
 *  &0x0F0F0F0F, 1,   0
 *  ...
 *  &0x0F0F0F0F, 253, 0
 *  &0x0F0F0F0F, 254, 0
 *
 *  &0x0F0F0F0F, 0xF01,     0
 *  &0x0F0F000E, 0x11001202, 1
 */
TEST test_modifyBits_goodWeather(void) {
    uint8_t i;
    uint32_t v;
    for( i = 1; i < UINT8_MAX; i++ ) {
        v = 0x0F0F0F0F;
        modifyBits(&v, i, 1);
        GREATEST_ASSERT_EQ(0x0F0F0F0F | i, v);
    }
    for( i = 1; i < 32; i++ ) {
        v = 0x0F0F0F0F;
        modifyBits(&v, i, 0);
        GREATEST_ASSERT_EQ(0x0F0F0F0F & ~i, v);
    }

    v = 0x0F0F0F0F;
    modifyBits(&v, 0xF01, 0);
    GREATEST_ASSERT_EQ(0x0F0F000E, v);
    modifyBits(&v, 0x11001202, 1);
    GREATEST_ASSERT_EQ(0x1F0F120E, v);

    PASS();
}

TEST test_mergeBits_goodWeather(void) {


    SKIP();
}

/**
 * Test name:   test_nBitsSet_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0x00000000
 *  0x00000001
 *  0x00000003
 *  0x00000007
 *  0x10000008
 *  0xFFFFFFFF
 */
TEST test_nBitsSet_goodWeather(void) {
    GREATEST_ASSERT_EQ(0, nBitsSet(0x00000000));
    GREATEST_ASSERT_EQ(1, nBitsSet(0x00000001));
    GREATEST_ASSERT_EQ(2, nBitsSet(0x00000003));
    GREATEST_ASSERT_EQ(3, nBitsSet(0x00000007));
    GREATEST_ASSERT_EQ(2, nBitsSet(0x10000008));
    GREATEST_ASSERT_EQ(32, nBitsSet(0xFFFFFFFF));

    PASS();
}

/**
 * Test name:   test_isEven_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  2^0
 *  2^1
 *  ...
 *  2^62
 *  2^63
 *
 *  0
 *  1
 *  ...
 *  253
 *  254
 *
 *  0x00123AB40F001E00
 *  0x00123AB40F001E01
 *  18446744073709551615 (UINT_MAX)
 */
TEST test_isEven_goodWeather(void) {
    uint8_t i;
    for( i = 1; i < 32; i++ ) {
        GREATEST_ASSERT_EQ(1, isEven(bitMaskNNResult[i]));
    }

    for( i = 0; i < UINT8_MAX; i++ ) {
        if( i % 2 )
          GREATEST_ASSERT_EQ(0, isEven(i));
        else
          GREATEST_ASSERT_EQ(1, isEven(i));
    }

    GREATEST_ASSERT_EQ(1, isEven(0x00123AB40F001E00));
    GREATEST_ASSERT_EQ(0, isEven(0x00123AB40F001E01));
    GREATEST_ASSERT_EQ(0, isEven(UINT64_MAX));


    PASS();
}

/**
 * Test name:   test_isEven_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  2^0
 *  2^1
 *  ...
 *  2^62
 *  2^63
 *
 *  0
 *  1
 *  ...
 *  253
 *  254
 *
 *  0x00123AB40F001E00
 *  0x00123AB40F001E01
 *  18446744073709551615 (UINT64_MAX)
 */
TEST test_isOdd_goodWeather(void) {
    uint8_t i;
    for( i = 1; i < 32; i++ ) {
        GREATEST_ASSERT_EQ(0, isOdd(bitMaskNNResult[i]));
    }

    for( i = 0; i < UINT8_MAX; i++ ) {
        if( i % 2 )
          GREATEST_ASSERT_EQ(1, isOdd(i));
        else
          GREATEST_ASSERT_EQ(0, isOdd(i));
    }

    GREATEST_ASSERT_EQ(0, isOdd(0x00123AB40F001E00));
    GREATEST_ASSERT_EQ(1, isOdd(0x00123AB40F001E01));
    GREATEST_ASSERT_EQ(1, isOdd(UINT64_MAX));


    PASS();
}

/**
 * Test name:   test_isEvenParity_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  18446744073709551615 (UINT64_MAX)
 *  0xFFFFFFCFAFFFFFFF
 *  0xFFFFFFCFAFFFFFF1
 *  0
 *  1
 *  7
 *  54
 */
TEST test_isEvenParity_goodWeather(void) {
    GREATEST_ASSERT_EQ(1, isEvenParity(UINT64_MAX));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xFFFFFFCFAFFFFFFF));
    GREATEST_ASSERT_EQ(0, isEvenParity(0xFFFFFFCFAFFFFFF1));
    GREATEST_ASSERT_EQ(1, isEvenParity(0));
    GREATEST_ASSERT_EQ(0, isEvenParity(1));
    GREATEST_ASSERT_EQ(0, isEvenParity(7));
    GREATEST_ASSERT_EQ(1, isEvenParity(54));

    PASS();
}

/**
 * Test name:   test_isOddParity_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  18446744073709551615 (UINT64_MAX)
 *  0xFFFFFFCFAFFFFFFF
 *  0xFFFFFFCFAFFFFFF1
 *  0
 *  1
 *  7
 *  54
 */
TEST test_isOddParity_goodWeather(void) {
    GREATEST_ASSERT_EQ(0, isOddParity(UINT64_MAX));
    GREATEST_ASSERT_EQ(0, isOddParity(0xFFFFFFCFAFFFFFFF));
    GREATEST_ASSERT_EQ(1, isOddParity(0xFFFFFFCFAFFFFFF1));
    GREATEST_ASSERT_EQ(0, isOddParity(0));
    GREATEST_ASSERT_EQ(1, isOddParity(1));
    GREATEST_ASSERT_EQ(1, isOddParity(7));
    GREATEST_ASSERT_EQ(0, isOddParity(54));

    PASS();
}

/**
 * Test name:   test_reverseBitOrder_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  0x0F0F0F0F
 *  0xF0F0F0F0
 *  0x12345678
 *  1
 */
TEST test_reverseBitOrder_goodWeather(void) {
    uint32_t v = 0x0F0F0F0F;
    reverseBitOrder(&v);
    GREATEST_ASSERT_EQ(0xF0F0F0F0, v);
    reverseBitOrder(&v);
    GREATEST_ASSERT_EQ(0x0F0F0F0F, v);
    v = 0x12345678;
    reverseBitOrder(&v);
    GREATEST_ASSERT_EQ(0x1E6A2C48, v);
    v = 1;
    reverseBitOrder(&v);
    GREATEST_ASSERT_EQ(0x80000000, v);

    PASS();
}

/**
 * Test name:   test_roundUpToPowerOf2_goodWeather
 * Test case:   Whether ...
 * Test values:
 *  2^0
 *  2^1
 *  ...
 *  2^62
 *  2^63
 *
 *  0
 *  1
 *  3
 *  5
 *  9
 *  17
 *  33
 *  65
 *  127
 *  129
 *  200
 *  500
 *
 *  2^10 - 200
 *  2^11 - 200
 *  ...
 *  2^62 - 200
 *  2^63 - 200
 */
TEST test_roundUpToPowerOf2_goodWeather(void) {
    uint8_t i;
    for( i = 1; i < 32; i++ ) {
        GREATEST_ASSERT_EQ(bitMaskNNResult[i], roundUpToPowerOf2(bitMaskNNResult[i]));
    }

    GREATEST_ASSERT_EQ(1, roundUpToPowerOf2(0));
    GREATEST_ASSERT_EQ(1, roundUpToPowerOf2(1));
    GREATEST_ASSERT_EQ(4, roundUpToPowerOf2(3));
    GREATEST_ASSERT_EQ(8, roundUpToPowerOf2(5));
    GREATEST_ASSERT_EQ(16, roundUpToPowerOf2(9));
    GREATEST_ASSERT_EQ(32, roundUpToPowerOf2(17));
    GREATEST_ASSERT_EQ(64, roundUpToPowerOf2(33));
    GREATEST_ASSERT_EQ(128, roundUpToPowerOf2(65));
    GREATEST_ASSERT_EQ(128, roundUpToPowerOf2(127));
    GREATEST_ASSERT_EQ(256, roundUpToPowerOf2(129));
    GREATEST_ASSERT_EQ(256, roundUpToPowerOf2(200));
    GREATEST_ASSERT_EQ(512, roundUpToPowerOf2(500));

    for( i = 10; i < 32; i++ ) {
        GREATEST_ASSERT_EQ(bitMaskNNResult[i], roundUpToPowerOf2(bitMaskNNResult[i] - 200));
    }

    PASS();
}

SUITE(BitOperations) {
    RUN_TEST(test_bitMask32_goodWeather);
    RUN_TEST(test_bitMask32_falsePositive);
    RUN_TEST(test_bitMask64_goodWeather);
    RUN_TEST(test_bitGet_goodWeather);
    RUN_TEST(test_bitGetm_goodWeather);
    RUN_TEST(test_bitSet_goodWeather);
    RUN_TEST(test_bitSetm_goodWeather);
    RUN_TEST(test_bitClear_goodWeather);
    RUN_TEST(test_bitClearm_goodWeather);
    RUN_TEST(test_bitFlip_goodWeather);
    RUN_TEST(test_bitFlipm_goodWeather);
    RUN_TEST(test_shiftLeft_goodWeather);
    RUN_TEST(test_shiftRight_goodWeather);

    RUN_TEST(test_isPositive_goodWeather);
    RUN_TEST(test_haveOppositeSigns_goodWeather);
    RUN_TEST(test_min_goodWeather);
    RUN_TEST(test_max_goodWeather);
    RUN_TEST(test_isPowerOf2_goodWeather);
    RUN_TEST(test_isPowerOf2_falsePositive);
    RUN_TEST(test_modifyBits_goodWeather);
    RUN_TEST(test_mergeBits_goodWeather);
    RUN_TEST(test_nBitsSet_goodWeather);
    RUN_TEST(test_isEven_goodWeather);
    RUN_TEST(test_isOdd_goodWeather);
    RUN_TEST(test_isEvenParity_goodWeather);
    RUN_TEST(test_isOddParity_goodWeather);
    RUN_TEST(test_reverseBitOrder_goodWeather);
    RUN_TEST(test_roundUpToPowerOf2_goodWeather);

}




GREATEST_MAIN_DEFS();

///* Set up, run suite(s) of tests, report pass/fail/skip stats. */
//int run_tests(void) {
//    GREATEST_INIT();            /* init. greatest internals */
//    /* List of suites to run (if any). */
//    RUN_SUITE(BitOperations);
//
//    /* Tests can also be run directly, without using test suites. */
//
//    GREATEST_PRINT_REPORT();          /* display results */
//    return greatest_all_passed();
//}

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(BitOperations);

    GREATEST_MAIN_END();

	return EXIT_SUCCESS;
}

void
putBits( const uint64_t _v, const uint8_t _nBits ) {
    uint8_t i;

    for( i = _nBits; i > 0; i-- ) {
        /**
         * Output plus 48, since character '0' is in the 48th place of the
         * ASCII table.
         */
        putchar( ( (_v >>(i-1)) & 0x01) + 48 );
    }

    return;
}
