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
 * The purpose of this unit test is not to verify that the arithmetic is
 * correct, because Sean Eron Anderson already tested that thoroughly. The
 * purpose of this unit test is to verify that the implementation of the code
 * is correct.
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
 * | Argument |
 * | -------- |
 * | 0        |
 * | 1        |
 * | ...      |
 * | 30       |
 * | 31       |
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
 * @testcase    BIT_MASK32(n) fails to create a correct mask for n is 32 to 63.
 * @testvalues
 * | Argument |
 * | -------- |
 * | 32       |
 * | 33       |
 * | ...      |
 * | 62       |
 * | 63       |
 */
TEST
bitMask32_masksBetween32And64Bit_ShouldFail()
{
    uint8_t i;
    for (i = 32; i < 64; i++) {
        GREATEST_ASSERT_FALSE(correctBitMasksUpTo64Bit[i] == BIT_MASK32(i));
    }

    PASS();
}

/**
 * @testname    bitMask64_masksUpTo64Bit_Generated
 * @testcase    BIT_MASK64(n) creates the correct bit mask for n is 0 to 63.
 * @testvalues
 * | Argument |
 * | -------- |
 * | 0        |
 * | 1        |
 * | ...      |
 * | 62       |
 * | 36       |
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
 * @testname    bitSetm_singleBitsUpTo64Bit_Set
 * @testcase    BIT_SETM sets the correct bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0x0000000000000000 | 0x0000000000000001 |
 * | 0x0000000000000000 | 0x0000000000000002 |
 * | ...                |                    |
 * | 0x0000000000000000 | 0x4000000000000000 |
 * | 0x0000000000000000 | 0x8000000000000000 |
 */
TEST
bitSetm_singleBitsUpTo64Bit_Set()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0;
        BIT_SETM(v, (1ULL << i));
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    bitSetm_multipleBitsUpTo64Bit_Set
 * @testcase    BIT_SETM sets the correct bits in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0x0000000000000000 | 0x5555555555555555 |
 * | 0x5555555555555555 | 0xAAAAAAAAAAAAAAAA |
 */
TEST
bitSetm_multipleBitsUpTo64Bit_Set()
{
    uint64_t v = 0;

    BIT_SETM(v, 0x5555555555555555);
    GREATEST_ASSERT_EQ(0x5555555555555555, v);
    BIT_SETM(v, 0xAAAAAAAAAAAAAAAA);
    GREATEST_ASSERT_EQ(0xFFFFFFFFFFFFFFFF, v);

    PASS();
}

/**
 * @testname    bitSet_singleBitsUpTo64Bit_Set
 * @testcase    BIT_SET sets the correct bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0x0000000000000000 | 0          |
 * | 0x0000000000000000 | 1          |
 * | ...                |            |
 * | 0x0000000000000000 | 62         |
 * | 0x0000000000000000 | 63         |
 */
TEST
bitSet_singleBitsUpTo64Bit_Set()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0;
        BIT_SET(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    bitClearm_singleBitsUpTo64Bit_Cleared
 * @testcase    BIT_CLEARM clears the correct bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0xFFFFFFFFFFFFFFFF | 0xFFFFFFFFFFFFFFFE |
 * | 0xFFFFFFFFFFFFFFFF | 0xFFFFFFFFFFFFFFFD |
 * | ...                |                    |
 * | 0xFFFFFFFFFFFFFFFF | 0xBFFFFFFFFFFFFFFF |
 * | 0xFFFFFFFFFFFFFFFF | 0x7FFFFFFFFFFFFFFF |
 */
TEST
bitClearm_singleBitsUpTo64Bit_Cleared()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_CLEARM(v, (1ULL << i));
        GREATEST_ASSERT_EQ(~correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    bitClearm_multipleBitsUpTo64Bit_Cleared
 * @testcase    BIT_CLEARM clears the correct bits in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0xFFFFFFFFFFFFFFFF | 0x5555555555555555 |
 * | 0xAAAAAAAAAAAAAAAA | 0x0000000000000000 |
 */
TEST
bitClearm_multipleBitsUpTo64Bit_Cleared()
{
    uint64_t v = 0xFFFFFFFFFFFFFFFF;

    BIT_CLEARM(v, 0x5555555555555555);
    GREATEST_ASSERT_EQ(0xAAAAAAAAAAAAAAAA, v);
    BIT_CLEARM(v, 0xAAAAAAAAAAAAAAAA);
    GREATEST_ASSERT_EQ(0x0000000000000000, v);

    PASS();
}

/**
 * @testname    bitClear_singleBitsUpTo64Bit_Cleared
 * @testcase    BIT_CLEAR clears the correct bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0xFFFFFFFFFFFFFFFF | 0          |
 * | 0xFFFFFFFFFFFFFFFF | 1          |
 * | ...                |            |
 * | 0xFFFFFFFFFFFFFFFF | 62         |
 * | 0xFFFFFFFFFFFFFFFF | 63         |
 */
TEST
bitClear_singleBitsUpTo64Bit_Cleared()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_CLEAR(v, i);
        GREATEST_ASSERT_EQ(~correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    bitFlipm_singleSetBitsUpTo64Bit_Flipped
 * @testcase    BIT_FLIPM flips the correct set bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0xFFFFFFFFFFFFFFFF | 0x0000000000000001 |
 * | 0xFFFFFFFFFFFFFFFF | 0x0000000000000002 |
 * | ...                |                    |
 * | 0xFFFFFFFFFFFFFFFF | 0x4000000000000000 |
 * | 0xFFFFFFFFFFFFFFFF | 0x8000000000000000 |
 */
TEST
bitFlipm_singleSetBitsUpTo64Bit_Flipped()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_FLIPM(v, (1ULL << i));
        GREATEST_ASSERT_EQ(~correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    bitFlipm_singleClearedBitsUpTo64Bit_Flipped
 * @testcase    BIT_FLIPM flips the correct cleared bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0x0000000000000000 | 0x0000000000000001 |
 * | 0x0000000000000000 | 0x0000000000000002 |
 * | ...                |                    |
 * | 0x0000000000000000 | 0x4000000000000000 |
 * | 0x0000000000000000 | 0x8000000000000000 |
 */
TEST
bitFlipm_singleClearedBitsUpTo64Bit_Flipped()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0;
        BIT_FLIPM(v, (1ULL << i));
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    bitFlipm_multipleSetBitsUpTo64Bit_Flipped
 * @testcase    BIT_FLIPM flips the correct bits in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0xFFFFFFFFFFFFFFFF | 0x5555555555555555 |
 * | 0xAAAAAAAAAAAAAAAA | 0x0000000000000000 |
 */
TEST
bitFlipm_multipleSetBitsUpTo64Bit_Flipped()
{
    uint64_t v = 0xFFFFFFFFFFFFFFFF;

    BIT_FLIPM(v, 0x5555555555555555);
    GREATEST_ASSERT_EQ(0xAAAAAAAAAAAAAAAA, v);
    BIT_FLIPM(v, 0xAAAAAAAAAAAAAAAA);
    GREATEST_ASSERT_EQ(0x0000000000000000, v);

    PASS();
}

/**
 * @testname    bitFlipm_multipleClearedBitsUpTo64Bit_Flipped
 * @testcase    BIT_FLIPM flips the correct bits in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2         |
 * | ------------------ | ------------------ |
 * | 0x0000000000000000 | 0xAAAAAAAAAAAAAAAA |
 * | 0x5555555555555555 | 0xFFFFFFFFFFFFFFFF |
 */
TEST
bitFlipm_multipleClearedBitsUpTo64Bit_Flipped()
{
    uint64_t v = 0x0000000000000000;

    BIT_FLIPM(v, 0xAAAAAAAAAAAAAAAA);
    GREATEST_ASSERT_EQ(0xAAAAAAAAAAAAAAAA, v);
    BIT_FLIPM(v, 0x5555555555555555);
    GREATEST_ASSERT_EQ(0xFFFFFFFFFFFFFFFF, v);

    PASS();
}

/**
 * @testname    bitFlip_singleSetBitsUpTo64Bit_Flipped
 * @testcase    BIT_FLIPM flips the correct set bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0xFFFFFFFFFFFFFFFF | 0          |
 * | 0xFFFFFFFFFFFFFFFF | 1          |
 * | ...                |            |
 * | 0xFFFFFFFFFFFFFFFF | 62         |
 * | 0xFFFFFFFFFFFFFFFF | 63         |
 */
TEST
bitFlip_singleSetBitsUpTo64Bit_Flipped()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0xFFFFFFFFFFFFFFFF;
        BIT_FLIP(v, i);
        GREATEST_ASSERT_EQ(~correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    bitFlip_singleClearedBitsUpTo64Bit_Flipped
 * @testcase    BIT_FLIP flips the correct cleared bit in a 64-bit variable.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0x0000000000000000 | 0          |
 * | 0x0000000000000000 | 1          |
 * | ...                |            |
 * | 0x0000000000000000 | 62         |
 * | 0x0000000000000000 | 63         |
 */
TEST
bitFlip_singleClearedBitsUpTo64Bit_Flipped()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0;
        BIT_FLIP(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    shiftLeft_singleSetBitUpTo64_Shifted
 * @testcase    SHIFT_LEFT shifts the 64-bit variable with a single bit set to
 * the correct position.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0x0000000000000001 | 0          |
 * | 0x0000000000000001 | 1          |
 * | ...                |            |
 * | 0x0000000000000001 | 62         |
 * | 0x0000000000000001 | 63         |
 */
TEST
shiftLeft_singleSetBitUpTo64_Shifted()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0x0000000000000001;
        SHIFT_LEFT(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    shiftLeft_multipleSetBitsUpTo64_Shifted
 * @testcase    SHIFT_LEFT shifts the 64-bit variable with multiple bits set to
 * the correct position.
 * @testvalues
 * <table class="doxtable">
 * <tr><th>Argument 1                   </th><th>Argument 2 </th></tr>
 * <tr><td>0x0000000000000001 | 0x0000000000007070</td><td>0          </td></tr>
 * <tr><td>0x0000000000000001 | 0x0000000000007070</td><td>1          </td></tr>
 * <tr><td>...                          </td><td>           </td></tr>
 * <tr><td>0x0000000000000001 | 0x0000000000007070</td><td>62         </td></tr>
 * <tr><td>0x0000000000000001 | 0x0000000000007070</td><td>63         </td></tr>
 * </table>
 */
TEST
shiftLeft_multipleSetBitsUpTo64_Shifted()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0x0000000000000001 | 0x0000000000007070;
        SHIFT_LEFT(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i]                         |
                           (0x0000000000007070UL << i), v);
    }

    PASS();
}

/**
 * @testname    shiftRight_singleSetBitUpTo64_Shifted
 * @testcase    SHIFT_RIGHT shifts the 64-bit variable with a single bit set to
 * the correct position.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0x8000000000000000 | 0          |
 * | 0x8000000000000000 | 1          |
 * | ...                |            |
 * | 0x8000000000000000 | 62         |
 * | 0x8000000000000000 | 63         |
 */
TEST
shiftRight_singleSetBitUpTo64_Shifted()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0x8000000000000000;
        SHIFT_RIGHT(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[63-i], v);
    }

    PASS();
}

/**
 * @testname    shiftRight_multipleSetBitsUpTo64_Shifted
 * @testcase    SHIFT_RIGHT shifts the 64-bit variable with multiple bits set to
 * the correct position.
 * @testvalues
 * <table class="doxtable">
 * <tr><th>Argument 1                             </th><th>Argument 2 </th></tr>
 * <tr><td>0x8000000000000000 | 0x7070000000000000</td><td>0          </td></tr>
 * <tr><td>0x8000000000000000 | 0x7070000000000000</td><td>1          </td></tr>
 * <tr><td>...                                    </td><td>           </td></tr>
 * <tr><td>0x8000000000000000 | 0x7070000000000000</td><td>62         </td></tr>
 * <tr><td>0x8000000000000000 | 0x7070000000000000</td><td>63         </td></tr>
 * </table>
 */
TEST
shiftRight_multipleSetBitsUpTo64_Shifted()
{
    uint8_t i;
    uint64_t v;
    for (i = 0; i < 64; i++) {
        v = 0x8000000000000000 | 0x7070000000000000;
        SHIFT_RIGHT(v, i);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[63-i]                      |
                           (0x7070000000000000 >> i), v);
    }

    PASS();
}

/**
 * @testname    bitGetm_multipleSetBitsUpTo64Bit_Generated
 * @testcase    BIT_GET(v, n) correctly returns the set bit for n is 0 to 63.
 * @testvalues
 * <table class="doxtable">
 * <tr><th>Argument 1         </th><th>Argument 2             </th></tr>
 * <tr><td>0x0000000000000001 </td><td>(1UL << 0)  | rand64() </td></tr>
 * <tr><td>0x0000000000000002 </td><td>(1UL << 1)  | rand64() </td></tr>
 * <tr><td>...                </td><td>                       </td></tr>
 * <tr><td>0x4000000000000000 </td><td>(1UL << 62) | rand64() </td></tr>
 * <tr><td>0x8000000000000000 </td><td>(1UL << 63) | rand64() </td></tr>
 * </table>
 */
TEST
bitGetm_multipleRandomSetBitsUpTo64Bit_Generated()
{
    uint64_t r;
    uint8_t i;
    for (i = 0; i < 64; i++) {
        r = rand64();
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i] | r                     ,
                           bitGetm(correctBitMasksUpTo64Bit[i] | r             ,
                                   (1UL << i) | r));
    }

    PASS();
}

/**
 * @testname    bitGet_multipleClearedBitsUpTo64Bit_Generated
 * @testcase    BIT_GET(v, n) correctly returns the cleared bit for n is 0 to
 * 63.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0xFFFFFFFFFFFFFFFE | 0          |
 * | 0xFFFFFFFFFFFFFFFD | 1          |
 * | ...                |            |
 * | 0xBFFFFFFFFFFFFFFF | 62         |
 * | 0x7FFFFFFFFFFFFFFF | 63         |
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
 * @testname    bitGet_singleSetBitsUpTo64Bit_Generated
 * @testcase    BIT_GET(v, n) correctly returns the set bit for n is 0 to 63.
 * @testvalues
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0x0000000000000001 | 0          |
 * | 0x0000000000000002 | 1          |
 * | ...                |            |
 * | 0x4000000000000000 | 62         |
 * | 0x8000000000000000 | 63         |
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
 * | Argument 1         | Argument 2 |
 * | ------------------ | ---------- |
 * | 0xFFFFFFFFFFFFFFFE | 0          |
 * | 0xFFFFFFFFFFFFFFFD | 1          |
 * | ...                |            |
 * | 0xBFFFFFFFFFFFFFFF | 62         |
 * | 0x7FFFFFFFFFFFFFFF | 63         |
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
 * @testname    isPositive_maximumPoitiveAndNegativeNumber_SignGenerated
 * @testcase    isPositive returns the correct sign of maximum positive and
 * negative values.
 * @testvalues
 * | Argument                     |
 * | ---------------------------- |
 * | -2147483648 (@ref INT32_MIN) |
 * | 0                            |
 * | 2147483647 (@ref INT32_MAX)  |
 */
TEST
isPositive_maximumPoitiveAndNegativeNumber_SignGenerated()
{
    GREATEST_ASSERT_EQ(0, isPositive(INT32_MIN));
    GREATEST_ASSERT_EQ(1, isPositive(0));
    GREATEST_ASSERT_EQ(1, isPositive(INT32_MAX));

    PASS();
}

/**
 * @testname    isPositive_minimumPoitiveAndNegativeNumber_SignGenerated
 * @testcase    isPositive returns the correct sign of minimum positive and
 * negative values.
 * @testvalues
 * | Argument |
 * | -------- |
 * | -1       |
 * | 1        |
 */
TEST
isPositive_minimumPoitiveAndNegativeNumber_SignGenerated()
{
    GREATEST_ASSERT_EQ(0, isPositive(-1));
    GREATEST_ASSERT_EQ(1, isPositive(1));

    PASS();
}

/**
 * @testname    isOdd_positivePowersOfTwoUpTo64Bit_ParityGenerated
 * @testcase    isOdd returns the correct parity for positive even integers
 * 2^n from n is 1 to 62.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0x0000000000000002 |
 * | 0x0000000000000004 |
 * | ...                |
 * | 0x2000000000000000 |
 * | 0x4000000000000000 |
 */
TEST
isOdd_positivePowersOfTwoUpTo64Bit_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 63; i++) {
        GREATEST_ASSERT_EQ(0, isOdd((int64_t)correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    isOdd_positiveMaximum64Bit_ParityGenerated
 * @testcase    isOdd returns the correct parity for the maximum positive even
 * integer.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0x7FFFFFFFFFFFFFFE |
 */
TEST
isOdd_positiveMaximum64Bit_ParityGenerated()
{
    GREATEST_ASSERT_EQ(0, isOdd(0x7FFFFFFFFFFFFFFE));

    PASS();
}

/**
 * @testname    isOdd_negativePowersOfTwoUpTo64Bit_ParityGenerated
 * @testcase    isOdd returns the correct parity for negative even integers
 * -2^n from n is 1 to 63.
 * @testvalues
 * | Argument            |
 * | ------------------- |
 * | -0x0000000000000002 |
 * | -0x0000000000000004 |
 * | ...                 |
 * | -0x4000000000000000 |
 * | -0x8000000000000000 |
 */
TEST
isOdd_negativePowersOfTwoUpTo64Bit_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 64; i++) {
        GREATEST_ASSERT_EQ(0, isOdd(-(int64_t)correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    isOdd_positivePowersOfTwoUpTo64BitMinusOne_ParityGenerated
 * @testcase    isOdd returns the correct parity for positive odd integers
 * 2^n - 1 from n is 1 to 63.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0x0000000000000001 |
 * | 0x0000000000000003 |
 * | ...                |
 * | 0x3FFFFFFFFFFFFFFF |
 * | 0x7FFFFFFFFFFFFFFF |
 */
TEST
isOdd_positivePowersOfTwoUpTo64BitMinusOne_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, isOdd((int64_t)correctBitMasksUpTo64Bit[i] - 1));
    }

    PASS();
}

/**
 * @testname    isOdd_negativePowersOfTwoUpTo64BitPlusOne_ParityGenerated
 * @testcase    isOdd returns the correct parity for negative odd integers
 * -2^n + 1 from n is 1 to 63.
 * @testvalues
 * | Argument            |
 * | ------------------- |
 * | -0x0000000000000001 |
 * | -0x0000000000000003 |
 * | ...                 |
 * | -0x3FFFFFFFFFFFFFFF |
 * | -0x7FFFFFFFFFFFFFFF |
 */
TEST
isOdd_negativePowersOfTwoUpTo64BitPlusOne_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, isOdd(-(int64_t)correctBitMasksUpTo64Bit[i] + 1));
    }

    PASS();
}

/**
 * @testname    isEven_positivePowersOfTwoUpTo64Bit_ParityGenerated
 * @testcase    isEven returns the correct parity for positive even integers
 * 2^n from n is 1 to 62.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0x0000000000000002 |
 * | 0x0000000000000004 |
 * | ...                |
 * | 0x2000000000000000 |
 * | 0x4000000000000000 |
 */
TEST
isEven_positivePowersOfTwoUpTo64Bit_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 63; i++) {
        GREATEST_ASSERT_EQ(1, isEven((int64_t)correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    isEven_positiveMaximum64Bit_ParityGenerated
 * @testcase    isEven returns the correct parity for the maximum positive even
 * integer.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0x7FFFFFFFFFFFFFFE |
 */
TEST
isEven_positiveMaximum64Bit_ParityGenerated()
{
    GREATEST_ASSERT_EQ(1, isEven(0x7FFFFFFFFFFFFFFE));

    PASS();
}

/**
 * @testname    isEven_negativePowersOfTwoUpTo64Bit_ParityGenerated
 * @testcase    isEven returns the correct parity for negative even integers
 * -2^n from n is 1 to 63.
 * @testvalues
 * | Argument            |
 * | ------------------- |
 * | -0x0000000000000002 |
 * | -0x0000000000000004 |
 * | ...                 |
 * | -0x4000000000000000 |
 * | -0x8000000000000000 |
 */
TEST
isEven_negativePowersOfTwoUpTo64Bit_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, isEven(-(int64_t)correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    isEven_positivePowersOfTwoUpTo64BitMinusOne_ParityGenerated
 * @testcase    isEven returns the correct parity for positive odd integers
 * 2^n - 1 from n is 1 to 63.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0x0000000000000001 |
 * | 0x0000000000000003 |
 * | ...                |
 * | 0x3FFFFFFFFFFFFFFF |
 * | 0x7FFFFFFFFFFFFFFF |
 */
TEST
isEven_positivePowersOfTwoUpTo64BitMinusOne_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 64; i++) {
        GREATEST_ASSERT_EQ(0, isEven((int64_t)correctBitMasksUpTo64Bit[i] - 1));
    }

    PASS();
}

/**
 * @testname    isEven_negativePowersOfTwoUpTo64BitPlusOne_ParityGenerated
 * @testcase    isEven returns the correct parity for negative odd integers
 * -2^n + 1 from n is 1 to 63.
 * @testvalues
 * | Argument            |
 * | ------------------- |
 * | -0x0000000000000001 |
 * | -0x0000000000000003 |
 * | ...                 |
 * | -0x3FFFFFFFFFFFFFFF |
 * | -0x7FFFFFFFFFFFFFFF |
 */
TEST
isEven_negativePowersOfTwoUpTo64BitPlusOne_ParityGenerated()
{
    uint8_t i;
    for (i = 1; i < 64; i++) {
        GREATEST_ASSERT_EQ(0, isEven(-(int64_t)correctBitMasksUpTo64Bit[i] + 1));
    }

    PASS();
}

/**
 * @testname    haveOppositeSigns_maximumPoitiveAndNegativeValues_Generated
 * @testcase    haveOppositeSigns returns the correct difference in signs of
 * maximum positive and negative values.
 * @testvalues
 * | Argument 1                   | Argument 2                   |
 * | ---------------------------- | ---------------------------- |
 * | -2147483648 (@ref INT32_MIN) | -2147483648 (@ref INT32_MIN) |
 * | -2147483648 (@ref INT32_MIN) | 2147483647 (@ref INT32_MAX)  |
 * | 2147483647 (@ref INT32_MAX)  | -2147483648 (@ref INT32_MIN) |
 * | 2147483647 (@ref INT32_MAX)  | 2147483647 (@ref INT32_MAX)  |
 */
TEST
haveOppositeSigns_maximumPoitiveAndNegativeValues_Generated()
{
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(INT32_MIN, INT32_MIN));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(INT32_MIN, INT32_MAX));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(INT32_MAX, INT32_MIN));
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(INT32_MAX, INT32_MAX));

    PASS();
}

/**
 * @testname    haveOppositeSigns_minimumPoitiveAndNegativeValues_Generated
 * @testcase    haveOppositeSigns returns the correct difference in signs of
 * minimum positive and negative values.
 * @testvalues
 * | Argument 1 | Argument 2 |
 * | ---------- | ---------- |
 * | -1         | -1         |
 * | -1         | 1          |
 * | 1          | -1         |
 * | 1          | 1          |
 */
TEST
haveOppositeSigns_minimumPoitiveAndNegativeValues_Generated()
{
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(-1, -1));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(-1, 1));
    GREATEST_ASSERT_EQ(1, haveOppositeSigns(1, -1));
    GREATEST_ASSERT_EQ(0, haveOppositeSigns(1, 1));

    PASS();
}

/**
 * @testname    min_maximum32BitPositiveAndNegativeNumber_MinFound
 * @testcase    min returns the correct minimum value of maximum positive and
 * negative values.
 * @testvalues
 * | Argument 1                   | Argument 2                   |
 * | ---------------------------- | ---------------------------- |
 * | -2147483648 (@ref INT32_MIN) | 2147483647 (@ref INT32_MAX)  |
 * | 2147483647 (@ref INT32_MAX)  | -2147483648 (@ref INT32_MIN) |
 */
TEST
min_maximum32BitPositiveAndNegativeNumber_MinFound()
{
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MIN, INT32_MAX));
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MAX, INT32_MIN));

    PASS();
}

/**
 * @testname    min_minimum32BitPositiveAndNegativeNumber_MinFound
 * @testcase    min returns the correct minimum value of minimum positive and
 * negative values.
 * @testvalues
 * | Argument 1 | Argument 2 |
 * | ---------- | ---------- |
 * | -1         | 1          |
 * | 1          | -1         |
 */
TEST
min_minimum32BitPositiveAndNegativeNumber_MinFound()
{
    GREATEST_ASSERT_EQ(-1, min(-1, 1));
    GREATEST_ASSERT_EQ(-1, min(1, -1));

    PASS();
}

/**
 * @testname    min_maximum32BitPositiveAndNegativeToZeroNumber_MinFound
 * @testcase    min returns the correct minimum value of maximum positive and
 * negative values to zero.
 * @testvalues
 * | Argument 1                   | Argument 2                   |
 * | ---------------------------- | ---------------------------- |
 * | -2147483648 (@ref INT32_MIN) | 0                            |
 * | 0                            | -2147483648 (@ref INT32_MIN) |
 * | 2147483647 (@ref INT32_MAX)  | 0                            |
 * | 0                            | 2147483647 (@ref INT32_MAX)  |
 */
TEST
min_maximum32BitPositiveAndNegativeToZeroNumber_MinFound()
{
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MIN, 0));
    GREATEST_ASSERT_EQ(INT32_MIN, min(0, INT32_MIN));
    GREATEST_ASSERT_EQ(0, min(INT32_MAX, 0));
    GREATEST_ASSERT_EQ(0, min(0, INT32_MAX));

    PASS();
}

/**
 * @testname    min_minimum32BitPositiveAndNegativeToZeroNumber_MinFound
 * @testcase    min returns the correct minimum value of maximum positive and
 * negative values to zero.
 * @testvalues
 * | Argument 1 | Argument 2 |
 * | ---------- | ---------- |
 * | -1         | 0          |
 * | 0          | -1         |
 * | 1          | 0          |
 * | 0          | 1          |
 */
TEST
min_minimum32BitPositiveAndNegativeToZeroNumber_MinFound()
{
    GREATEST_ASSERT_EQ(-1, min(-1, 0));
    GREATEST_ASSERT_EQ(-1, min(0, -1));
    GREATEST_ASSERT_EQ(0, min(1, 0));
    GREATEST_ASSERT_EQ(0, min(0, 1));

    PASS();
}

/**
 * @testname    min_maximumEqual32BitPositiveAndNegativeNumber_MinFound
 * @testcase    min returns one of the entered values since they are both the
 * same.
 * @testvalues
 * | Argument 1                   | Argument 2                   |
 * | ---------------------------- | ---------------------------- |
 * | 2147483648 (@ref INT32_MAX)  | 2147483647 (@ref INT32_MAX)  |
 * | -2147483647 (@ref INT32_MIN)  | -2147483648 (@ref INT32_MIN) |
 */
TEST
min_maximumEqual32BitPositiveAndNegativeNumber_MinFound()
{
    GREATEST_ASSERT_EQ(INT32_MAX, min(INT32_MAX, INT32_MAX));
    GREATEST_ASSERT_EQ(INT32_MIN, min(INT32_MIN, INT32_MIN));

    PASS();
}

/**
 * @testname    min_minimumEqual32BitPositiveAndNegativeNumber_MinFound
 * @testcase    min returns one of the entered values since they are both the
 * same.
 * @testvalues
 * | Argument 1 | Argument 2 |
 * | ---------- | ---------- |
 * | 1          | 1          |
 * | -1         | -1         |
 */
TEST
min_minimumEqual32BitPositiveAndNegativeNumber_MinFound()
{
    GREATEST_ASSERT_EQ(1, min(1, 1));
    GREATEST_ASSERT_EQ(-1, min(-1, -1));

    PASS();
}

/**
 * @testname    max_maximum32BitPositiveAndNegativeNumber_MaxFound
 * @testcase    min returns the correct maximum value of maximum positive and
 * negative values.
 * @testvalues
 * | Argument 1                   | Argument 2                   |
 * | ---------------------------- | ---------------------------- |
 * | -2147483648 (@ref INT32_MIN) | 2147483647 (@ref INT32_MAX)  |
 * | 2147483647 (@ref INT32_MAX)  | -2147483648 (@ref INT32_MIN) |
 */
TEST
max_maximum32BitPositiveAndNegativeNumber_MaxFound()
{
    GREATEST_ASSERT_EQ(INT32_MAX, max(INT32_MIN, INT32_MAX));
    GREATEST_ASSERT_EQ(INT32_MAX, max(INT32_MAX, INT32_MIN));

    PASS();
}

/**
 * @testname    max_minimum32BitPositiveAndNegativeNumber_MaxFound
 * @testcase    min returns the correct maximum value of minimum positive and
 * negative values.
 * @testvalues
 * | Argument 1 | Argument 2 |
 * | ---------- | ---------- |
 * | -1         | 1          |
 * | 1          | -1         |
 */
TEST
max_minimum32BitPositiveAndNegativeNumber_MaxFound()
{
    GREATEST_ASSERT_EQ(1, max(-1, 1));
    GREATEST_ASSERT_EQ(1, max(1, -1));

    PASS();
}

/**
 * @testname    max_maximum32BitPositiveAndNegativeToZeroNumber_MaxFound
 * @testcase    min returns the correct maximum value of maximum positive and
 * negative values to zero.
 * @testvalues
 * | Argument 1                   | Argument 2                   |
 * | ---------------------------- | ---------------------------- |
 * | -2147483648 (@ref INT32_MIN) | 0                            |
 * | 0                            | -2147483648 (@ref INT32_MIN) |
 * | 2147483647 (@ref INT32_MAX)  | 0                            |
 * | 0                            | 2147483647 (@ref INT32_MAX)  |
 */
TEST
max_maximum32BitPositiveAndNegativeToZeroNumber_MaxFound()
{
    GREATEST_ASSERT_EQ(0, max(INT32_MIN, 0));
    GREATEST_ASSERT_EQ(0, max(0, INT32_MIN));
    GREATEST_ASSERT_EQ(INT32_MAX, max(INT32_MAX, 0));
    GREATEST_ASSERT_EQ(INT32_MAX, max(0, INT32_MAX));

    PASS();
}

/**
 * @testname    max_minimum32BitPositiveAndNegativeToZeroNumber_MaxFound
 * @testcase    min returns the correct maximum value of maximum positive and
 * negative values to zero.
 * @testvalues
 * | Argument 1 | Argument 2 |
 * | ---------- | ---------- |
 * | -1         | 0          |
 * | 0          | -1         |
 * | 1          | 0          |
 * | 0          | 1          |
 */
TEST
max_minimum32BitPositiveAndNegativeToZeroNumber_MaxFound()
{
    GREATEST_ASSERT_EQ(0, max(-1, 0));
    GREATEST_ASSERT_EQ(0, max(0, -1));
    GREATEST_ASSERT_EQ(1, max(1, 0));
    GREATEST_ASSERT_EQ(1, max(0, 1));

    PASS();
}

/**
 * @testname    max_maximumEqual32BitPositiveAndNegativeNumber_MaxFound
 * @testcase    min returns one of the entered values since they are both the
 * same.
 * @testvalues
 * | Argument 1                   | Argument 2                   |
 * | ---------------------------- | ---------------------------- |
 * | 2147483648 (@ref INT32_MAX)  | 2147483647 (@ref INT32_MAX)  |
 * | -2147483647 (@ref INT32_MIN)  | -2147483648 (@ref INT32_MIN) |
 */
TEST
max_maximumEqual32BitPositiveAndNegativeNumber_MaxFound()
{
    GREATEST_ASSERT_EQ(INT32_MAX, max(INT32_MAX, INT32_MAX));
    GREATEST_ASSERT_EQ(INT32_MIN, max(INT32_MIN, INT32_MIN));

    PASS();
}

/**
 * @testname    max_minimumEqual32BitPositiveAndNegativeNumber_MaxFound
 * @testcase    min returns one of the entered values since they are both the
 * same.
 * @testvalues
 * | Argument 1 | Argument 2 |
 * | ---------- | ---------- |
 * | 1          | 1          |
 * | -1         | -1         |
 */
TEST
max_minimumEqual32BitPositiveAndNegativeNumber_MaxFound()
{
    GREATEST_ASSERT_EQ(1, max(1, 1));
    GREATEST_ASSERT_EQ(-1, max(-1, -1));

    PASS();
}

/**
 * @testname    isPowerOf2_powersUpTo64Bit_ArePowers
 * @testcase    isPowerOf2 returns the right value for integers 2^n from n is 0
 * to 64.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0x0000000000000001 |
 * | 0x0000000000000002 |
 * | ...                |
 * | 0x4000000000000000 |
 * | 0x8000000000000000 |
 */
TEST
isPowerOf2_powersUpTo64Bit_ArePowers()
{
    uint8_t i;
    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, isPowerOf2(correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    isPowerOf2_zero_isNotAPower
 * @testcase    isPowerOf2 returns the right value for 0.
 * @testvalues
 * | Argument |
 * | -------- |
 * | 0        |
 */
TEST
isPowerOf2_zero_isNotAPower()
{
    uint8_t i;
    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(0, isPowerOf2(0));
    }

    PASS();
}

/**
 * @testname    isPowerOf2_powersUpTo64BitMinusAndPlusOne_AreNotPowers
 * @testcase    isPowerOf2 returns the right value for integers 2^n -/+ 1 from
 * n is 2 to 64.
 * @testvalues
 * | Argument                 |
 * | ------------------------ |
 * | 0x0000000000000004 -/+ 1 |
 * | 0x0000000000000008 -/+ 1 |
 * | ...                      |
 * | 0x4000000000000000 -/+ 1 |
 * | 0x8000000000000000 -/+ 1 |
 */
TEST
isPowerOf2_powersUpTo64BitMinusAndPlusOne_AreNotPowers()
{
    uint8_t i;
    for (i = 2; i < 64; i++) {
        GREATEST_ASSERT_EQ(0, isPowerOf2(correctBitMasksUpTo64Bit[i] - 1));
        GREATEST_ASSERT_EQ(0, isPowerOf2(correctBitMasksUpTo64Bit[i] + 1));
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

/**
 * @todo add info...
 */
TEST
test_mergeBits_goodWeather(void)
{
//    uint32_t x = 0x10101010, y = 0x0A0A0A0A;
//    mergeBits(x,y,0xABABABAB);

//    uint8_t q = 0x10;
//    reverseBitOrderByte(&q);

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

/**
 * Unit test suite for the BitOperations unit tests. */
SUITE(BitOperations)
{
    /********** Function macro tests ******************************************/
    RUN_TEST(bitMask32_masksUpTo32Bit_Generated);
    RUN_TEST(bitMask32_masksBetween32And64Bit_ShouldFail);
    RUN_TEST(bitMask64_masksUpTo64Bit_Generated);
    RUN_TEST(bitSetm_singleBitsUpTo64Bit_Set);
    RUN_TEST(bitSetm_multipleBitsUpTo64Bit_Set);
    RUN_TEST(bitSet_singleBitsUpTo64Bit_Set);
    RUN_TEST(bitClearm_singleBitsUpTo64Bit_Cleared);
    RUN_TEST(bitClearm_multipleBitsUpTo64Bit_Cleared);
    RUN_TEST(bitClear_singleBitsUpTo64Bit_Cleared);
    RUN_TEST(bitFlipm_singleSetBitsUpTo64Bit_Flipped);
    RUN_TEST(bitFlipm_singleClearedBitsUpTo64Bit_Flipped);
    RUN_TEST(bitFlipm_multipleSetBitsUpTo64Bit_Flipped);
    RUN_TEST(bitFlipm_multipleClearedBitsUpTo64Bit_Flipped);
    RUN_TEST(bitFlip_singleSetBitsUpTo64Bit_Flipped);
    RUN_TEST(bitFlip_singleClearedBitsUpTo64Bit_Flipped);
    RUN_TEST(shiftLeft_singleSetBitUpTo64_Shifted);
    RUN_TEST(shiftLeft_multipleSetBitsUpTo64_Shifted);
    RUN_TEST(shiftRight_singleSetBitUpTo64_Shifted);
    RUN_TEST(shiftRight_multipleSetBitsUpTo64_Shifted);
    /********** Function tests ************************************************/
    RUN_TEST(bitGetm_multipleRandomSetBitsUpTo64Bit_Generated);
    RUN_TEST(bitGetm_multipleRandomClearedBitsUpTo64Bit_Generated);
    RUN_TEST(bitGet_singleSetBitsUpTo64Bit_Generated);
    RUN_TEST(bitGet_singleClearedBitsUpTo64Bit_Generated);
    RUN_TEST(isPositive_maximumPoitiveAndNegativeNumber_SignGenerated);
    RUN_TEST(isPositive_minimumPoitiveAndNegativeNumber_SignGenerated);
    RUN_TEST(isOdd_positivePowersOfTwoUpTo64Bit_ParityGenerated);
    RUN_TEST(isOdd_positiveMaximum64Bit_ParityGenerated);
    RUN_TEST(isOdd_negativePowersOfTwoUpTo64Bit_ParityGenerated);
    RUN_TEST(isOdd_positivePowersOfTwoUpTo64BitMinusOne_ParityGenerated);
    RUN_TEST(isOdd_negativePowersOfTwoUpTo64BitPlusOne_ParityGenerated);
    RUN_TEST(isEven_positivePowersOfTwoUpTo64Bit_ParityGenerated);
    RUN_TEST(isEven_positiveMaximum64Bit_ParityGenerated);
    RUN_TEST(isEven_negativePowersOfTwoUpTo64Bit_ParityGenerated);
    RUN_TEST(isEven_positivePowersOfTwoUpTo64BitMinusOne_ParityGenerated);
    RUN_TEST(isEven_negativePowersOfTwoUpTo64BitPlusOne_ParityGenerated);
    RUN_TEST(haveOppositeSigns_maximumPoitiveAndNegativeValues_Generated);
    RUN_TEST(haveOppositeSigns_minimumPoitiveAndNegativeValues_Generated);
    RUN_TEST(min_maximum32BitPositiveAndNegativeNumber_MinFound);
    RUN_TEST(min_minimum32BitPositiveAndNegativeNumber_MinFound);
    RUN_TEST(min_maximum32BitPositiveAndNegativeToZeroNumber_MinFound);
    RUN_TEST(min_minimum32BitPositiveAndNegativeToZeroNumber_MinFound);
    RUN_TEST(min_maximumEqual32BitPositiveAndNegativeNumber_MinFound);
    RUN_TEST(min_minimumEqual32BitPositiveAndNegativeNumber_MinFound);
    RUN_TEST(max_maximum32BitPositiveAndNegativeNumber_MaxFound);
    RUN_TEST(max_minimum32BitPositiveAndNegativeNumber_MaxFound);
    RUN_TEST(max_maximum32BitPositiveAndNegativeToZeroNumber_MaxFound);
    RUN_TEST(max_minimum32BitPositiveAndNegativeToZeroNumber_MaxFound);
    RUN_TEST(max_maximumEqual32BitPositiveAndNegativeNumber_MaxFound);
    RUN_TEST(max_minimumEqual32BitPositiveAndNegativeNumber_MaxFound);
    RUN_TEST(isPowerOf2_powersUpTo64Bit_ArePowers);
    RUN_TEST(isPowerOf2_zero_isNotAPower);
    RUN_TEST(isPowerOf2_powersUpTo64BitMinusAndPlusOne_AreNotPowers);






    RUN_TEST(test_modifyBits_goodWeather);
    RUN_TEST(test_mergeBits_goodWeather);
    RUN_TEST(test_nBitsSet_goodWeather);
    RUN_TEST(test_isEvenParity_goodWeather);
    RUN_TEST(test_isOddParity_goodWeather);
    RUN_TEST(test_reverseBitOrder_goodWeather);
    RUN_TEST(test_roundUpToPowerOf2_goodWeather);
}



/*******************************************************************************
 * Main function
 ******************************************************************************/
/** Main definitions for the unit test framework greatest. */
GREATEST_MAIN_DEFS();

/**
 * @brief Initializes and controls all other functions (indirectly).
 *
 * @param   argc Argument counter.
 * @param   argv Array of different function arguments.
 * @return  int Error code.
 */
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
putBits(uint64_t const _num, uint8_t const _nBits)
{
    uint8_t i;

    for( i = _nBits; i > 0; i-- ) {
        /* Output plus 48, since character '0' is in the 48th place of the
         * ASCII table.
         */
        putchar(((_num >> (i - 1)) & 0x01) + 48);
    }

    return;
}
/* End of file BitOperations.c */
