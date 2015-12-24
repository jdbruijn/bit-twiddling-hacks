/*******************************************************************************
 * Begin of file BitOperations_UnitTest.c
 * Author: jdebruijn
 * Created on December 22, 2015, 10:00 AM
 *
 *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
 *
 * Copyright (c) 2015  Jeroen de Bruijn  <vidavidorra@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~**/
/** @file
 * @brief Unit test for the BitOperations project.
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "greatest.h"                   /* Unit test framework. */
#include "BitOperations_UnitTest.h"
#include "BitOperations.h"              /* Unit under test. */

/*******************************************************************************
 * Test functions
 ******************************************************************************/
/**
 * @testname    bitMask32_masksUpTo32Bit_Generated
 * @testcase    BIT_MASK32(n) creates the correct bit mask for n is 0 to 31.
 * @testvalues
 *  0
 *  1
 *  ...
 *  30
 *  31
 */
TEST
bitMask32_masksUpTo32Bit_Generated()
{
    uint8_t i;
    for (i = 0; i < 32; i++) {
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], BIT_MASK32(i));
    }
    PASS();
}

/**
 * @testname    bitMask32_masksBetween32And64Bit_ShouldFail
 * @testcase    BIT_MASK32(n) fails to create a correct mask for n is 32 to 127.
 * @testvalues
 *  32
 *  33
 *  ...
 *  126
 *  127
 */
TEST
bitMask32_masksBetween32And128Bit_ShouldFail()
{
    uint8_t i;
    for (i = 32; i < 128; i++) {
        GREATEST_ASSERT_FALSE(correctBitMasksUpTo64Bit[i] == BIT_MASK32(i));
    }
    PASS();
}

/**
 * @testname    bitMask64_masksUpTo64Bit_Generated
 * @testcase    BIT_MASK64(n) creates the correct bit mask for n is 0 to 63.
 * @testvalues
 *  0
 *  1
 *  ...
 *  62
 *  63
 */
TEST
bitMask64_masksUpTo64Bit_Generated()
{
    uint8_t i;
    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], BIT_MASK64(i));
    }
    PASS();
}

/**
 * @testname    bitMask32_masksBetween64And128Bit_ShouldFail
 * @testcase    BIT_MASK64(n) fails to create a correct mask for n is 32 to 127.
 * @testvalues
 *  0
 *  1
 *  ...
 *  126
 *  127
 */
TEST
bitMask64_masksBetween64And128Bit_ShouldFail()
{
    uint8_t i;
    for (i = 64; i < 128; i++) {
        GREATEST_ASSERT_FALSE(correctBitMasksUpTo64Bit[i] == BIT_MASK64(i));
    }
    PASS();
}

/**
 * @testname    bitGet_singleSetBitsUpTo64Bit_Generated
 * @testcase    BIT_GET(v, n) correctly returns the set bit for n is 0 to 63.
 * @testvalues
 *  0x0000000000000001, 0
 *  0x0000000000000002, 1
 *  ...
 *  0x4000000000000000, 62
 *  0x8000000000000000, 63
 */
TEST
bitGet_singleSetBitsUpTo64Bit_Generated()
{
    uint8_t i;
    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, bitGet(correctBitMasksUpTo64Bit[i], i));
    }

    PASS();
}

/**
 * @testname    bitGet_singleClearedBitsUpTo64Bit_Generated
 * @testcase    BIT_GET(v, n) correctly returns the cleared bit for n is 0 to
 * 63.
 * @testvalues
 *  0xFFFFFFFFFFFFFFFE, 0
 *  0xFFFFFFFFFFFFFFFD, 1
 *  ...
 *  0xBFFFFFFFFFFFFFFF, 62
 *  0x7FFFFFFFFFFFFFFF, 63
 */
TEST
bitGet_singleClearedBitsUpTo64Bit_Generated()
{
    uint8_t i;
    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(0, bitGet(~correctBitMasksUpTo64Bit[i], i));
    }

    PASS();
}

/**
 * @testname    bitGetm_multipleSetBitsUpTo64Bit_Generated
 * @testcase    BIT_GET(v, n) correctly returns the set bit for n is 0 to 63.
 * @testvalues
 *  0x0000000000000001 | rand64(), 0
 *  0x0000000000000002 | rand64(), 1
 *  ...
 *  0x4000000000000000 | rand64(), 62
 *  0x8000000000000000 | rand64(), 63
 */
TEST
bitGetm_multipleRandomSetBitsUpTo64Bit_Generated()
{
    uint64_t r;
    uint8_t i;
    for (i = 0; i < 64; i++) {
        r = rand64();
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i] | r,
                bitGetm(correctBitMasksUpTo64Bit[i] | r, (1UL << i) | r));
    }

    PASS();
}

/**
 * @testname    bitGet_multipleClearedBitsUpTo64Bit_Generated
 * @testcase    BIT_GET(v, n) correctly returns the cleared bit for n is 0 to
 * 63.
 * @testvalues
 *  0xFFFFFFFFFFFFFFFE, 0
 *  0xFFFFFFFFFFFFFFFD, 1
 *  ...
 *  0xBFFFFFFFFFFFFFFF, 62
 *  0x7FFFFFFFFFFFFFFF, 63
 */
TEST
bitGetm_multipleRandomClearedBitsUpTo64Bit_Generated()
{
    uint64_t r;
    uint8_t i;
    for (i = 0; i < 64; i++) {
        r = rand64();
        GREATEST_ASSERT_EQ(0,
            bitGetm(correctBitMasksUpTo64Bit[i] | r, ~((1UL << i) | r)));
    }

    PASS();
}

/**
 * @testname    test_bitGetm_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_bitGetm_goodWeather(void) {
    SKIPm("Have not checked the implementation of this test.");
    uint8_t i;
    for( i = 0; i < 64; i++ ) {
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], bitGetm(0xFFFFFFFFFFFFFFFF, correctBitMasksUpTo64Bit[i]));
    }
    for( i = 0; i < UINT8_MAX; i++ ) {
        GREATEST_ASSERT_EQ(i, bitGetm(0xFFFFFFFFFFFFFFFF, i));
    }

    PASS();
}

/**
 * @testname    test_bitSet_goodWeather
 * @testcase    Whether ...
 * @testvalues
 *  0, 0
 *  0, 1
 *  ...
 *  0, 62
 *  0, 63
 *
 *  0x8000000000000000, 1
 *  0x8000000000000002, 62
 */
TEST
test_bitSet_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0;
        BIT_SET(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }

    v = 0x8000000000000000;
    BIT_SET(v, 1);
    GREATEST_ASSERT_EQ(0x8000000000000002, v);
    BIT_SET(v, 62);
    GREATEST_ASSERT_EQ(0xC000000000000002, v);

    PASS();
}

/**
 * @testname    test_bitSetm_goodWeather
 * @testcase    Whether ...
 * @testvalues
 *  0, 0
 *  0, 1
 *  ...
 *  0, 62
 *  0, 63
 *
 *  0x8000000000000000, 0x1F00
 *  0x8000000000001F00, 0x123ABC0F000000
 */
TEST
test_bitSetm_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0;
        BIT_SETM(v, i);
        GREATEST_ASSERT_EQ(i, v);
    }

    v = 0x8000000000000000;
    BIT_SETM(v, 0x1F00);
    GREATEST_ASSERT_EQ(0x8000000000001F00, v);
    BIT_SETM(v, 0x123ABC0F000000);
    GREATEST_ASSERT_EQ(0x80123ABC0F001F00, v);

    PASS();
}

/**
 * @testname    test_bitClear_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_bitClear_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_CLEAR(v, i);
        GREATEST_ASSERT_EQ(~correctBitMasksUpTo64Bit[i], v);
    }

    v = 0x80123ABC0F001F00;
    BIT_CLEAR(v, 63);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    BIT_CLEAR(v, 35);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    BIT_CLEAR(v, 8);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    BIT_CLEAR(v, 0);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);

    PASS();
}

/**
 * @testname    test_bitClear_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_bitClearm_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_CLEARM(v, i);
        GREATEST_ASSERT_EQ(~i, v);
    }

    v = 0x80123ABC0F001F00;
    BIT_CLEARM(v, 0x8000000000000000);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    BIT_CLEARM(v, 0x800000000);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    BIT_CLEARM(v, 0x100);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    BIT_CLEARM(v, 1);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);

    PASS();
}

/**
 * @testname    test_bitFlip_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_bitFlip_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_FLIP(v, i);
        GREATEST_ASSERT_EQ(~correctBitMasksUpTo64Bit[i], v);
    }

    v = 0x80123ABC0F001F00;
    BIT_FLIP(v, 63);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    BIT_FLIP(v, 35);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    BIT_FLIP(v, 8);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    BIT_FLIP(v, 0);
    GREATEST_ASSERT_EQ(0x00123AB40F001E01, v);

    PASS();
}

/**
 * @testname    test_bitFlipm_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_bitFlipm_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_FLIPM(v, i);
        GREATEST_ASSERT_EQ(~i, v);
    }

    v = 0x80123ABC0F001F00;
    BIT_FLIPM(v, 0x8000000000000000);
    GREATEST_ASSERT_EQ(0x00123ABC0F001F00, v);
    BIT_FLIPM(v, 0x800000000);
    GREATEST_ASSERT_EQ(0x00123AB40F001F00, v);
    BIT_FLIPM(v, 0x100);
    GREATEST_ASSERT_EQ(0x00123AB40F001E00, v);
    BIT_FLIPM(v, 1);
    GREATEST_ASSERT_EQ(0x00123AB40F001E01, v);

    PASS();
}

/**
 * @testname    test_shiftLeft_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_shiftLeft_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 1;
        SHIFT_LEFT(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }
    v = 0x00000000000FF010;
    SHIFT_LEFT(v, 4);
    GREATEST_ASSERT_EQ(0x0000000000FF0100, v);
    SHIFT_LEFT(v, 12);
    GREATEST_ASSERT_EQ(0x0000000FF0100000, v);
    SHIFT_LEFT(v, 32);
    GREATEST_ASSERT_EQ(0xF010000000000000, v);

    PASS();
}

/**
 * @testname    test_shiftRight_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_shiftRight_goodWeather(void) {
    SKIP();
    uint8_t i;
    uint64_t v;
    for( i = 0; i < 64; i++ ) {
        v = 0x8000000000000000;
        SHIFT_RIGHT(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[63-i], v);
    }
    v = 0x010FF00000000000;
    SHIFT_RIGHT(v, 4);
    GREATEST_ASSERT_EQ(0x0010FF0000000000, v);
    SHIFT_RIGHT(v, 12);
    GREATEST_ASSERT_EQ(0x0000010FF0000000, v);
    SHIFT_RIGHT(v, 32);
    GREATEST_ASSERT_EQ(0x000000000000010F, v);

    PASS();
}

/**
 * @testname    test_isPositive_goodWeather
 * @testcase    Whether the signs of a unit32 minimum, zero and maximum values are correctly determined
 * determined.
 * @testvalues
 *  -2147483648 (INT32_MIN)
 *  0
 *  2147483647 (INT32_MAX)
 */
TEST
test_isPositive_goodWeather(void)
{
    GREATEST_ASSERT_EQ(0, isPositive(INT32_MIN));
    GREATEST_ASSERT_EQ(1, isPositive(0));
    GREATEST_ASSERT_EQ(1, isPositive(INT32_MAX));

    PASS();
}

/**
 * @testname    test_haveOppositeSigns_goodWeather
 * @testcase    Whether difference in signs are correctly determined
 * @testvalues
 *  -   -
 *  -   +
 *  +   -
 *  +   +
 */
TEST
test_haveOppositeSigns_goodWeather(void)
{
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(INT32_MIN, -1));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(-1, 1));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(1, -1));
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(1, INT32_MAX));

    PASS();
}

/**
 * @testname    test_min_goodWeather
 * @testcase    Whether min() returns the right value
 * @testvalues
 *  -2147483648 (INT32_MIN) -1
 *  2147483647 (INT32_MAX)  -2147483648 (INT32_MIN)
 *  0                       0
 *  1                       2147483647 (INT32_MAX)
 */
TEST
test_min_goodWeather(void)
{
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MIN, -1));
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MAX, INT32_MIN));
    GREATEST_ASSERT_EQ(0, min(0, 0));
    GREATEST_ASSERT_EQ(1, min(1, INT32_MAX));

    PASS();
}

/**
 * @testname    test_max_goodWeather
 * @testcase    Whether max() returns the right value
 * @testvalues
 *  -2147483648 (INT32_MIN) -1
 *  2147483647 (INT32_MAX)  -2147483648 (INT32_MIN)
 *  0                       0
 *  1                       2147483647 (INT32_MAX)
 */
TEST
test_max_goodWeather(void)
{
    GREATEST_ASSERT_EQ(-1, max(INT32_MIN, -1));
    GREATEST_ASSERT_EQ(INT32_MAX, max(INT32_MAX, INT32_MIN));
    GREATEST_ASSERT_EQ(0, max(0, 0));
    GREATEST_ASSERT_EQ(INT32_MAX, max(1, INT32_MAX));

    PASS();
}

/**
 * @testname    test_isPowerOf2_goodWeather
 * @testcase    Whether isPowerOf2() returns the right value
 * @testvalues
 *  2^0
 *  2^1
 *  ...
 *  2^62
 *  2^63
 */
TEST
test_isPowerOf2_goodWeather(void)
{
    uint8_t i;
    uint64_t power = 1;

    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, isPowerOf2(power << i));
    }

    PASS();
}

/**
 * @testname    test_isPowerOf2_falsePositive
 * @testcase    Whether isPowerOf2() returns the right value
 * @testvalues
 *  0
 *  1
 *  ...
 *  62
 *  63
 */
TEST
test_isPowerOf2_falsePositive(void)
{
    uint8_t i;

    for (i = 0; i < 64; i++) {
        if (i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32) {
            GREATEST_ASSERT_EQ(1, isPowerOf2(i));
        } else {
            GREATEST_ASSERT_EQ(0, isPowerOf2(i));
        }
    }

    PASS();
}

/**
 * @testname    test_modifyBits_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_modifyBits_goodWeather(void)
{
    uint8_t i;
    uint32_t v;
    for (i = 1; i < UINT8_MAX; i++) {
        v = 0x0F0F0F0F;
        modifyBits(&v, i, 1);
        GREATEST_ASSERT_EQ(0x0F0F0F0F | i, v);
    }
    for (i = 1; i < 32; i++) {
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

TEST
test_mergeBits_goodWeather(void)
{


    SKIP();
}

/**
 * @testname    test_nBitsSet_goodWeather
 * @testcase    Whether ...
 * @testvalues
 *  0x00000000
 *  0x00000001
 *  0x00000003
 *  0x00000007
 *  0x10000008
 *  0xFFFFFFFF
 */
TEST
test_nBitsSet_goodWeather(void)
{
    GREATEST_ASSERT_EQ(0, nBitsSet(0x00000000));
    GREATEST_ASSERT_EQ(1, nBitsSet(0x00000001));
    GREATEST_ASSERT_EQ(2, nBitsSet(0x00000003));
    GREATEST_ASSERT_EQ(3, nBitsSet(0x00000007));
    GREATEST_ASSERT_EQ(2, nBitsSet(0x10000008));
    GREATEST_ASSERT_EQ(32, nBitsSet(0xFFFFFFFF));

    PASS();
}

/**
 * @testname    test_isEven_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_isEven_goodWeather(void)
{
    uint8_t i;
    for (i = 1; i < 32; i++) {
        GREATEST_ASSERT_EQ(1, isEven(correctBitMasksUpTo64Bit[i]));
    }

    for (i = 0; i < UINT8_MAX; i++) {
        if (i % 2)
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
 * @testname    test_isEven_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_isOdd_goodWeather(void)
{
    uint8_t i;
    for (i = 1; i < 32; i++) {
        GREATEST_ASSERT_EQ(0, isOdd(correctBitMasksUpTo64Bit[i]));
    }

    for (i = 0; i < UINT8_MAX; i++) {
        if (i % 2)
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
 * @testname    test_isEvenParity_goodWeather
 * @testcase    Whether ...
 * @testvalues
 *  18446744073709551615 (UINT64_MAX)
 *  0xFFFFFFCFAFFFFFFF
 *  0xFFFFFFCFAFFFFFF1
 *  0
 *  1
 *  7
 *  54
 */
TEST
test_isEvenParity_goodWeather(void)
{
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
 * @testname    test_isOddParity_goodWeather
 * @testcase    Whether ...
 * @testvalues
 *  18446744073709551615 (UINT64_MAX)
 *  0xFFFFFFCFAFFFFFFF
 *  0xFFFFFFCFAFFFFFF1
 *  0
 *  1
 *  7
 *  54
 */
TEST
test_isOddParity_goodWeather(void)
{
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
 * @testname    test_reverseBitOrder_goodWeather
 * @testcase    Whether ...
 * @testvalues
 *  0x0F0F0F0F
 *  0xF0F0F0F0
 *  0x12345678
 *  1
 */
TEST
test_reverseBitOrder_goodWeather(void)
{
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
 * @testname    test_roundUpToPowerOf2_goodWeather
 * @testcase    Whether ...
 * @testvalues
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
TEST
test_roundUpToPowerOf2_goodWeather(void)
{
    uint8_t i;
    for (i = 1; i < 32; i++) {
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i],
                roundUpToPowerOf2(correctBitMasksUpTo64Bit[i]));
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

    for (i = 10; i < 32; i++) {
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i],
                roundUpToPowerOf2(correctBitMasksUpTo64Bit[i] - 200));
    }

    PASS();
}

SUITE(BitOperations)
{
    RUN_TEST(bitMask32_masksUpTo32Bit_Generated);
    RUN_TEST(bitMask32_masksBetween32And128Bit_ShouldFail);
    RUN_TEST(bitMask64_masksUpTo64Bit_Generated);
    RUN_TEST(bitMask64_masksBetween64And128Bit_ShouldFail);
    RUN_TEST(bitGet_singleSetBitsUpTo64Bit_Generated);
    RUN_TEST(bitGet_singleClearedBitsUpTo64Bit_Generated);
    RUN_TEST(bitGetm_multipleRandomSetBitsUpTo64Bit_Generated);
    RUN_TEST(bitGetm_multipleRandomClearedBitsUpTo64Bit_Generated);
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



/*******************************************************************************
 * Main function
 ******************************************************************************/
GREATEST_MAIN_DEFS();

int
main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();

    /* Seed the pseudo random number generator */
    srand(time(NULL));


    RUN_SUITE(BitOperations);

    GREATEST_MAIN_END();

    return EXIT_SUCCESS;
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
uint64_t
rand64() {
    return ((uint64_t)rand() <<32 | rand());
}

void
putBits(const uint64_t _v, const uint8_t _nBits)
{
    uint8_t i;

    for( i = _nBits; i > 0; i-- ) {
        /* Output plus 48, since character '0' is in the 48th place of the
         * ASCII table.
         */
        putchar(((_v >> (i - 1)) & 0x01) + 48);
    }

    return;
}
/* End of file BitOperations.c */
