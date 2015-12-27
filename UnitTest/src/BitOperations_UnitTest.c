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
 * Unit test functions
 ******************************************************************************/
/**
 * @testname    bitMask32_masksUpTo32Bit_Generated
 * @testcase    @ref @ref BIT_MASK32(n) creates the correct bit mask for n is 0
 * to 31.
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
 * @testcase    @ref BIT_MASK32(n) fails to create a correct mask for n is 32
 * to 63.
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
 * @testcase    @ref BIT_MASK64(n) creates the correct bit mask for n is 0 to
 * 63.
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
 * @testcase    @ref BIT_SETM sets the correct bit in a 64-bit variable.
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
 * @testcase    @ref BIT_SETM sets the correct bits in a 64-bit variable.
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
 * @testcase    @ref BIT_SET sets the correct bit in a 64-bit variable.
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
 * @testcase    @ref BIT_CLEARM clears the correct bit in a 64-bit variable.
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
 * @testcase    @ref BIT_CLEARM clears the correct bits in a 64-bit variable.
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
 * @testcase    @ref BIT_CLEAR clears the correct bit in a 64-bit variable.
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
 * @testcase    @ref BIT_FLIPM flips the correct set bit in a 64-bit variable.
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
 * @testcase    @ref BIT_FLIPM flips the correct cleared bit in a 64-bit
 * variable.
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
 * @testcase    @ref BIT_FLIPM flips the correct bits in a 64-bit variable.
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
 * @testcase    @ref BIT_FLIPM flips the correct bits in a 64-bit variable.
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
 * @testcase    @ref BIT_FLIP flips the correct set bit in a 64-bit variable.
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
 * @testcase    @ref BIT_FLIP flips the correct cleared bit in a 64-bit variable.
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
 * @testcase    @ref SHIFT_LEFT shifts the 64-bit variable with a single bit
 * set to the correct position.
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
 * @testcase    @ref SHIFT_LEFT shifts the 64-bit variable with multiple bits
 * set to the correct position.
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
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i] |
                           (0x0000000000007070ULL << i), v);
    }

    PASS();
}

/**
 * @testname    shiftRight_singleSetBitUpTo64_Shifted
 * @testcase    @ref SHIFT_RIGHT shifts the 64-bit variable with a single bit
 * set to the correct position.
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
 * @testcase    @ref SHIFT_RIGHT shifts the 64-bit variable with multiple bits
 * set to the correct position.
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
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[63-i] |
                           (0x7070000000000000 >> i), v);
    }

    PASS();
}

/**
 * @testname    bitGetm_multipleSetBitsUpTo64Bit_Generated
 * @testcase    @ref bitGetm (v, n) correctly returns the set bit for n is 0 to
 * 63.
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
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i] | r,
                           bitGetm(correctBitMasksUpTo64Bit[i] | r,
                                   (1ULL << i) | r));
    }

    PASS();
}

/**
 * @testname    bitGet_multipleClearedBitsUpTo64Bit_Generated
 * @testcase    @ref bitGetm (v, n) correctly returns the cleared bit for n is
 * 0 to 63.
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
            bitGetm(correctBitMasksUpTo64Bit[i] | r, ~((1ULL << i) | r)));
    }

    PASS();
}

/**
 * @testname    bitGet_singleSetBitsUpTo64Bit_Generated
 * @testcase    @ref bitGet (v, n) correctly returns the set bit for n is 0 to
 * 63.
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
 * @testcase    @ref bitGet (v, n) correctly returns the cleared bit for n is 0
 * to 63.
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
 * @testcase    @ref isPositive returns the correct sign of maximum positive and
 * negative values.
 * @testvalues
 * | Argument                     |
 * | ---------------------------- |
 * | -2147483648 (@ref INT32_MIN) |
 * | 0                            |
 * | 2147483647 (@ref INT32_MAX)  |
 */
TEST
isPositive_maximumPositiveAndNegativeNumber_SignGenerated()
{
    GREATEST_ASSERT_EQ(0, isPositive(INT32_MIN));
    GREATEST_ASSERT_EQ(1, isPositive(0));
    GREATEST_ASSERT_EQ(1, isPositive(INT32_MAX));

    PASS();
}

/**
 * @testname    isPositive_minimumPoitiveAndNegativeNumber_SignGenerated
 * @testcase    @ref isPositive returns the correct sign of minimum positive and
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
 * @testcase    @ref isOdd returns the correct parity for positive even integers
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
 * @testcase    @ref isOdd returns the correct parity for the maximum positive
 * even integer.
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
 * @testcase    @ref isOdd returns the correct parity for negative even integers
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
 * @testcase    @ref isOdd returns the correct parity for positive odd integers
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
 * @testcase    @ref isOdd returns the correct parity for negative odd integers
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
 * @testcase    @ref isEven returns the correct parity for positive even
 * integers 2^n from n is 1 to 62.
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
 * @testcase    @ref isEven returns the correct parity for the maximum positive
 * even integer.
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
 * @testcase    @ref isEven returns the correct parity for negative even
 * integers -2^n from n is 1 to 63.
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
 * @testcase    @ref isEven returns the correct parity for positive odd integers
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
 * @testcase    @ref isEven returns the correct parity for negative odd integers
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
        GREATEST_ASSERT_EQ(0,
                           isEven(-(int64_t)correctBitMasksUpTo64Bit[i] + 1));
    }

    PASS();
}

/**
 * @testname    haveOppositeSigns_maximumPoitiveAndNegativeValues_Generated
 * @testcase    @ref haveOppositeSigns returns the correct difference in signs
 * of maximum positive and negative values.
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
 * @testcase    @ref haveOppositeSigns returns the correct difference in signs
 * of minimum positive and negative values.
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
 * @testcase    @ref min returns the correct minimum value of maximum positive
 * and negative values.
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
 * @testcase    @ref min returns the correct minimum value of minimum positive
 * and negative values.
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
 * @testcase    @ref min returns the correct minimum value of maximum positive
 * and negative values to zero.
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
 * @testcase    @ref min returns the correct minimum value of maximum positive
 * and negative values to zero.
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
 * @testcase    @ref min returns one of the entered values since they are both
 * the same.
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
 * @testcase    @ref min returns one of the entered values since they are both
 * the same.
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
 * @testcase    @ref max returns the correct maximum value of maximum positive
 * and negative values.
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
 * @testcase    @ref max returns the correct maximum value of minimum positive
 * and negative values.
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
 * @testcase    @ref max returns the correct maximum value of maximum positive
 * and negative values to zero.
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
 * @testcase    @ref max returns the correct maximum value of maximum positive
 * and negative values to zero.
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
 * @testcase    @ref max returns one of the entered values since they are both
 * the same.
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
 * @testcase    @ref max returns one of the entered values since they are both
 * the same.
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
 * @testcase    @ref isPowerOf2 returns the right value for integers 2^n from n
 * is 0 to 64.
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
 * @testcase    @ref isPowerOf2 returns the right value for 0.
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
 * @testcase    @ref isPowerOf2 returns the right value for integers 2^n -/+ 1
 * from n is 2 to 64.
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
 * @testname    modifyBits_setBitsUpTo32Bit_SingleBitCleared
 * @testcase    @ref modifyBits modifies the correct bit to the correct value
 * in a 32-bit variable.
 * @testvalues
 * | Argument 1 | Argument 2 | Argument 3 |
 * | ---------- | ---------- | ---------- |
 * | 0xFFFFFFFF | 0x00000001 | 0          |
 * | 0xFFFFFFFF | 0x00000002 | 0          |
 * | ...        |            | 0          |
 * | 0xFFFFFFFF | 0x40000000 | 0          |
 * | 0xFFFFFFFF | 0x80000000 | 0          |
 */
TEST
modifyBits_setBitsUpTo32Bit_SingleBitCleared()
{
    uint8_t i;
    uint32_t v;
    for (i = 0; i < 32; i++) {
        v = 0xFFFFFFFF;
        modifyBits(&v, (1UL << i), 0);
        GREATEST_ASSERT_EQ(~(uint32_t)correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    modifyBits_clearedBitsUpTo32Bit_SingleBitSet
 * @testcase    @ref modifyBits modifies the correct bit to the correct value
 * in a 32-bit variable.
 * @testvalues
 * | Argument 1 | Argument 2 | Argument 3 |
 * | ---------- | ---------- | ---------- |
 * | 0x00000000 | 0x00000001 | 1          |
 * | 0x00000000 | 0x00000002 | 1          |
 * | ...        |            | 1          |
 * | 0x00000000 | 0x40000000 | 1          |
 * | 0x00000000 | 0x80000000 | 1          |
 */
TEST
modifyBits_clearedBitsUpTo32Bit_SingleBitSet()
{
    uint8_t i;
    uint32_t v;
    for (i = 0; i < 32; i++) {
        v = 0;
        modifyBits(&v, (1UL << i), 1);
        GREATEST_ASSERT_EQ(correctBitMasksUpTo64Bit[i], v);
    }

    PASS();
}

/**
 * @testname    modifyBits_setBitsUpTo32Bit_MultipleBitsCleared
 * @testcase    @ref modifyBits modifies the correct bits to the correct value
 * in a 32-bit variable.
 * @testvalues
 * | Argument 1 | Argument 2 | Argument 3 |
 * | ---------- | ---------- | ---------- |
 * | 0xFFFFFFFF | 0x55555555 | 0          |
 * | 0xAAAAAAAA | 0xAAAAAAAA | 0          |
 */
TEST
modifyBits_setBitsUpTo32Bit_MultipleBitsCleared()
{
    uint32_t v = 0xFFFFFFFF;

    modifyBits(&v, 0x55555555, 0);
    GREATEST_ASSERT_EQ(0xAAAAAAAA, v);
    modifyBits(&v, 0xAAAAAAAA, 0);
    GREATEST_ASSERT_EQ(0x00000000, v);

    PASS();
}

/**
 * @testname    modifyBits_setBitsUpTo32Bit_MultipleBitsSet
 * @testcase    @ref modifyBits modifies the correct bits to the correct value
 * in a 32-bit variable.
 * @testvalues
 * | Argument 1 | Argument 2 | Argument 3 |
 * | ---------- | ---------- | ---------- |
 * | 0x00000000 | 0xAAAAAAAA | 1          |
 * | 0xAAAAAAAA | 0x55555555 | 1          |
 */
TEST
modifyBits_setBitsUpTo32Bit_MultipleBitsSet()
{
    uint32_t v = 0x00000000;

    modifyBits(&v, 0xAAAAAAAA, 1);
    GREATEST_ASSERT_EQ(0xAAAAAAAA, v);
    modifyBits(&v, 0x55555555, 1);
    GREATEST_ASSERT_EQ(0xFFFFFFFF, v);

    PASS();
}

/**
 * @testname    mergeBits_magic32BitNumbers_Merged
 * @testcase    @ref mergeBits merges the correct bits in the correct part of
 * the mask to a correct 32-bit variable.
 * @testvalues
 * | Argument 1 | Argument 2 | Argument 3 |
 * | ---------- | ---------- | ---------- |
 * | 0x55555555 | 0xAAAAAAAA | 0xAAAAAAAA |
 * | 0xAAAAAAAA | 0x55555555 | 0xAAAAAAAA |
 * | 0x55555555 | 0xAAAAAAAA | 0x55555555 |
 * | 0xAAAAAAAA | 0x55555555 | 0x55555555 |
 * | 0x55555555 | 0xAAAAAAAA | 0x33333333 |
 * | 0xAAAAAAAA | 0x55555555 | 0x33333333 |
 */
TEST
mergeBits_magic32BitNumbers_Merged()
{
    GREATEST_ASSERT_EQ(0xFFFFFFFF,
                       mergeBits(0x55555555, 0xAAAAAAAA, 0xAAAAAAAA));
    GREATEST_ASSERT_EQ(0x00000000,
                       mergeBits(0xAAAAAAAA, 0x55555555, 0xAAAAAAAA));
    GREATEST_ASSERT_EQ(0x00000000,
                       mergeBits(0x55555555, 0xAAAAAAAA, 0x55555555));
    GREATEST_ASSERT_EQ(0xFFFFFFFF,
                       mergeBits(0xAAAAAAAA, 0x55555555, 0x55555555));
    GREATEST_ASSERT_EQ(0x66666666,
                       mergeBits(0x55555555, 0xAAAAAAAA, 0x33333333));
    GREATEST_ASSERT_EQ(0x99999999,
                       mergeBits(0xAAAAAAAA, 0x55555555, 0x33333333));

    PASS();
}

/**
 * @testname    nBitsSet_magic32BitNumbers_Generated
 * @testcase    @ref nBitsSet determines the correct amount of bits that are set
 * in a 32-bit variable.
 * @testvalues
 * | Argument   |
 * | ---------- |
 * | 0xFFFFFFFF |
 * | 0xEEEEEEEE |
 * | 0xDDDDDDDD |
 * | 0xCCCCCCCC |
 * | 0xBBBBBBBB |
 * | 0xAAAAAAAA |
 * | 0x99999999 |
 * | 0x88888888 |
 * | 0x77777777 |
 * | 0x66666666 |
 * | 0x55555555 |
 * | 0x44444444 |
 * | 0x33333333 |
 * | 0x22222222 |
 * | 0x11111111 |
 * | 0x00000000 |
 */
TEST
nBitsSet_magic32BitNumbers_Generated()
{
    GREATEST_ASSERT_EQ(32, nBitsSet(0xFFFFFFFF));
    GREATEST_ASSERT_EQ(24, nBitsSet(0xEEEEEEEE));
    GREATEST_ASSERT_EQ(24, nBitsSet(0xDDDDDDDD));
    GREATEST_ASSERT_EQ(16, nBitsSet(0xCCCCCCCC));
    GREATEST_ASSERT_EQ(24, nBitsSet(0xBBBBBBBB));
    GREATEST_ASSERT_EQ(16, nBitsSet(0xAAAAAAAA));
    GREATEST_ASSERT_EQ(16, nBitsSet(0x99999999));
    GREATEST_ASSERT_EQ(8, nBitsSet(0x88888888));
    GREATEST_ASSERT_EQ(24, nBitsSet(0x77777777));
    GREATEST_ASSERT_EQ(16, nBitsSet(0x66666666));
    GREATEST_ASSERT_EQ(16, nBitsSet(0x55555555));
    GREATEST_ASSERT_EQ(8, nBitsSet(0x44444444));
    GREATEST_ASSERT_EQ(16, nBitsSet(0x33333333));
    GREATEST_ASSERT_EQ(8, nBitsSet(0x22222222));
    GREATEST_ASSERT_EQ(8, nBitsSet(0x11111111));
    GREATEST_ASSERT_EQ(0, nBitsSet(0x00000000));

    PASS();
}

/**
 * @testname    isOddParity_powersOfTwoUpTo64Bit_ParityGenerated
 * @testcase    @ref isOddParity determines the correct parity of a 64-bit
 * variable.
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
isOddParity_powersOfTwoUpTo64Bit_ParityGenerated()
{
    uint8_t i;
    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(1, isOddParity(correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    isOddParity_magig64BitNumbers_ParityGenerated
 * @testcase    @ref isOddParity determines the correct parity of a 64-bit
 * variable.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0xFFFFFFFFFFFFFFFF |
 * | 0xEEEEEEEEEEEEEEEE |
 * | 0xDDDDDDDDDDDDDDDD |
 * | 0xCCCCCCCCCCCCCCCC |
 * | 0xBBBBBBBBBBBBBBBB |
 * | 0xAAAAAAAAAAAAAAAA |
 * | 0x9999999999999999 |
 * | 0x8888888888888888 |
 * | 0x7777777777777777 |
 * | 0x6666666666666666 |
 * | 0x5555555555555555 |
 * | 0x4444444444444444 |
 * | 0x3333333333333333 |
 * | 0x2222222222222222 |
 * | 0x1111111111111111 |
 * | 0x0000000000000000 |
 */
TEST
isOddParity_magig64BitNumbers_ParityGenerated()
{
    GREATEST_ASSERT_EQ(0, isOddParity(0xFFFFFFFFFFFFFFFF));
    GREATEST_ASSERT_EQ(0, isOddParity(0xEEEEEEEEEEEEEEEE));
    GREATEST_ASSERT_EQ(0, isOddParity(0xDDDDDDDDDDDDDDDD));
    GREATEST_ASSERT_EQ(0, isOddParity(0xCCCCCCCCCCCCCCCC));
    GREATEST_ASSERT_EQ(0, isOddParity(0xBBBBBBBBBBBBBBBB));
    GREATEST_ASSERT_EQ(0, isOddParity(0xAAAAAAAAAAAAAAAA));
    GREATEST_ASSERT_EQ(0, isOddParity(0x9999999999999999));
    GREATEST_ASSERT_EQ(0, isOddParity(0x8888888888888888));
    GREATEST_ASSERT_EQ(0, isOddParity(0x7777777777777777));
    GREATEST_ASSERT_EQ(0, isOddParity(0x6666666666666666));
    GREATEST_ASSERT_EQ(0, isOddParity(0x5555555555555555));
    GREATEST_ASSERT_EQ(0, isOddParity(0x4444444444444444));
    GREATEST_ASSERT_EQ(0, isOddParity(0x3333333333333333));
    GREATEST_ASSERT_EQ(0, isOddParity(0x2222222222222222));
    GREATEST_ASSERT_EQ(0, isOddParity(0x1111111111111111));
    GREATEST_ASSERT_EQ(0, isOddParity(0x0000000000000000));

    PASS();
}

/**
 * @testname    isOddParity_magig64BitNumbersMinusOne_ParityGenerated
 * @testcase    @ref isOddParity determines the correct parity of a 64-bit
 * variable.
 * @testvalues
 * | Argument               |
 * | ---------------------- |
 * | 0xFFFFFFFFFFFFFFFF - 1 |
 * | 0xEEEEEEEEEEEEEEEE - 1 |
 * | 0xDDDDDDDDDDDDDDDD - 1 |
 * | 0xCCCCCCCCCCCCCCCC - 1 |
 * | 0xBBBBBBBBBBBBBBBB - 1 |
 * | 0xAAAAAAAAAAAAAAAA - 1 |
 * | 0x9999999999999999 - 1 |
 * | 0x8888888888888888 - 1 |
 * | 0x7777777777777777 - 1 |
 * | 0x6666666666666666 - 1 |
 * | 0x5555555555555555 - 1 |
 * | 0x4444444444444444 - 1 |
 * | 0x3333333333333333 - 1 |
 * | 0x2222222222222222 - 1 |
 * | 0x1111111111111111 - 1 |
 */
TEST
isOddParity_magig64BitNumbersMinusOne_ParityGenerated()
{
    GREATEST_ASSERT_EQ(1, isOddParity(0xFFFFFFFFFFFFFFFF - 1));
    GREATEST_ASSERT_EQ(0, isOddParity(0xEEEEEEEEEEEEEEEE - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0xDDDDDDDDDDDDDDDD - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0xCCCCCCCCCCCCCCCC - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0xBBBBBBBBBBBBBBBB - 1));
    GREATEST_ASSERT_EQ(0, isOddParity(0xAAAAAAAAAAAAAAAA - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0x9999999999999999 - 1));
    GREATEST_ASSERT_EQ(0, isOddParity(0x8888888888888888 - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0x7777777777777777 - 1));
    GREATEST_ASSERT_EQ(0, isOddParity(0x6666666666666666 - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0x5555555555555555 - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0x4444444444444444 - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0x3333333333333333 - 1));
    GREATEST_ASSERT_EQ(0, isOddParity(0x2222222222222222 - 1));
    GREATEST_ASSERT_EQ(1, isOddParity(0x1111111111111111 - 1));

    PASS();
}

/**
 * @testname    isEvenParity_powersOfTwoUpTo64Bit_ParityGenerated
 * @testcase    @ref isEvenParity determines the correct parity of a 64-bit
 * variable.
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
isEvenParity_powersOfTwoUpTo64Bit_ParityGenerated()
{
    uint8_t i;
    for (i = 0; i < 64; i++) {
        GREATEST_ASSERT_EQ(0, isEvenParity(correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    isEvenParity_magig64BitNumbers_ParityGenerated
 * @testcase    @ref isEvenParity determines the correct parity of a 64-bit
 * variable.
 * @testvalues
 * | Argument           |
 * | ------------------ |
 * | 0xFFFFFFFFFFFFFFFF |
 * | 0xEEEEEEEEEEEEEEEE |
 * | 0xDDDDDDDDDDDDDDDD |
 * | 0xCCCCCCCCCCCCCCCC |
 * | 0xBBBBBBBBBBBBBBBB |
 * | 0xAAAAAAAAAAAAAAAA |
 * | 0x9999999999999999 |
 * | 0x8888888888888888 |
 * | 0x7777777777777777 |
 * | 0x6666666666666666 |
 * | 0x5555555555555555 |
 * | 0x4444444444444444 |
 * | 0x3333333333333333 |
 * | 0x2222222222222222 |
 * | 0x1111111111111111 |
 * | 0x0000000000000000 |
 */
TEST
isEvenParity_magig64BitNumbers_ParityGenerated()
{
    GREATEST_ASSERT_EQ(1, isEvenParity(0xFFFFFFFFFFFFFFFF));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xEEEEEEEEEEEEEEEE));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xDDDDDDDDDDDDDDDD));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xCCCCCCCCCCCCCCCC));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xBBBBBBBBBBBBBBBB));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xAAAAAAAAAAAAAAAA));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x9999999999999999));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x8888888888888888));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x7777777777777777));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x6666666666666666));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x5555555555555555));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x4444444444444444));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x3333333333333333));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x2222222222222222));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x1111111111111111));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x0000000000000000));

    PASS();
}

/**
 * @testname    isEvenParity_magig64BitNumbersMinusOne_ParityGenerated
 * @testcase    @ref isEvenParity determines the correct parity of a 64-bit
 * variable.
 * @testvalues
 * | Argument               |
 * | ---------------------- |
 * | 0xFFFFFFFFFFFFFFFF - 1 |
 * | 0xEEEEEEEEEEEEEEEE - 1 |
 * | 0xDDDDDDDDDDDDDDDD - 1 |
 * | 0xCCCCCCCCCCCCCCCC - 1 |
 * | 0xBBBBBBBBBBBBBBBB - 1 |
 * | 0xAAAAAAAAAAAAAAAA - 1 |
 * | 0x9999999999999999 - 1 |
 * | 0x8888888888888888 - 1 |
 * | 0x7777777777777777 - 1 |
 * | 0x6666666666666666 - 1 |
 * | 0x5555555555555555 - 1 |
 * | 0x4444444444444444 - 1 |
 * | 0x3333333333333333 - 1 |
 * | 0x2222222222222222 - 1 |
 * | 0x1111111111111111 - 1 |
 */
TEST
isEvenParity_magig64BitNumbersMinusOne_ParityGenerated()
{
    GREATEST_ASSERT_EQ(0, isEvenParity(0xFFFFFFFFFFFFFFFF - 1));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xEEEEEEEEEEEEEEEE - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0xDDDDDDDDDDDDDDDD - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0xCCCCCCCCCCCCCCCC - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0xBBBBBBBBBBBBBBBB - 1));
    GREATEST_ASSERT_EQ(1, isEvenParity(0xAAAAAAAAAAAAAAAA - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0x9999999999999999 - 1));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x8888888888888888 - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0x7777777777777777 - 1));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x6666666666666666 - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0x5555555555555555 - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0x4444444444444444 - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0x3333333333333333 - 1));
    GREATEST_ASSERT_EQ(1, isEvenParity(0x2222222222222222 - 1));
    GREATEST_ASSERT_EQ(0, isEvenParity(0x1111111111111111 - 1));

    PASS();
}

/**
 * @testname    reverseBitOrderByte_macic8BitNumbers_Reversed
 * @testcase    @ref reverseBitOrderByte correctly reverses a 8-bit variable.
 * @testvalues
 * | Argument |
 * | -------- |
 * | 0xFF     |
 * | 0xEE     |
 * | 0xDD     |
 * | 0xCC     |
 * | 0xBB     |
 * | 0xAA     |
 * | 0x99     |
 * | 0x88     |
 * | 0x77     |
 * | 0x66     |
 * | 0x55     |
 * | 0x44     |
 * | 0x33     |
 * | 0x22     |
 * | 0x11     |
 * | 0x00     |
 */
TEST
reverseBitOrderByte_macic8BitNumbers_Reversed()
{
    GREATEST_ASSERT_EQ(0xFF, reverseBitOrderByte(0xFF));
    GREATEST_ASSERT_EQ(0x77, reverseBitOrderByte(0xEE));
    GREATEST_ASSERT_EQ(0xBB, reverseBitOrderByte(0xDD));
    GREATEST_ASSERT_EQ(0x33, reverseBitOrderByte(0xCC));
    GREATEST_ASSERT_EQ(0xDD, reverseBitOrderByte(0xBB));
    GREATEST_ASSERT_EQ(0x55, reverseBitOrderByte(0xAA));
    GREATEST_ASSERT_EQ(0x99, reverseBitOrderByte(0x99));
    GREATEST_ASSERT_EQ(0x11, reverseBitOrderByte(0x88));
    GREATEST_ASSERT_EQ(0xEE, reverseBitOrderByte(0x77));
    GREATEST_ASSERT_EQ(0x66, reverseBitOrderByte(0x66));
    GREATEST_ASSERT_EQ(0xAA, reverseBitOrderByte(0x55));
    GREATEST_ASSERT_EQ(0x22, reverseBitOrderByte(0x44));
    GREATEST_ASSERT_EQ(0xCC, reverseBitOrderByte(0x33));
    GREATEST_ASSERT_EQ(0x44, reverseBitOrderByte(0x22));
    GREATEST_ASSERT_EQ(0x88, reverseBitOrderByte(0x11));
    GREATEST_ASSERT_EQ(0x00, reverseBitOrderByte(0x00));

    PASS();
}

/**
 * @testname    reverseBitOrder_macic32BitNumbers_Reversed
 * @testcase    @ref reverseBitOrderByte correctly reverses a 32-bit variable.
 * @testvalues
 * | Argument   |
 * | ---------- |
 * | 0xFFFFFFFF |
 * | 0xEEEEEEEE |
 * | 0xDDDDDDDD |
 * | 0xCCCCCCCC |
 * | 0xBBBBBBBB |
 * | 0xAAAAAAAA |
 * | 0x99999999 |
 * | 0x88888888 |
 * | 0x77777777 |
 * | 0x66666666 |
 * | 0x55555555 |
 * | 0x44444444 |
 * | 0x33333333 |
 * | 0x22222222 |
 * | 0x11111111 |
 * | 0x00000000 |
 */
TEST
reverseBitOrder_macic32BitNumbers_Reversed()
{
    GREATEST_ASSERT_EQ(0xFFFFFFFF, reverseBitOrder(0xFFFFFFFF));
    GREATEST_ASSERT_EQ(0x77777777, reverseBitOrder(0xEEEEEEEE));
    GREATEST_ASSERT_EQ(0xBBBBBBBB, reverseBitOrder(0xDDDDDDDD));
    GREATEST_ASSERT_EQ(0x33333333, reverseBitOrder(0xCCCCCCCC));
    GREATEST_ASSERT_EQ(0xDDDDDDDD, reverseBitOrder(0xBBBBBBBB));
    GREATEST_ASSERT_EQ(0x55555555, reverseBitOrder(0xAAAAAAAA));
    GREATEST_ASSERT_EQ(0x99999999, reverseBitOrder(0x99999999));
    GREATEST_ASSERT_EQ(0x11111111, reverseBitOrder(0x88888888));
    GREATEST_ASSERT_EQ(0xEEEEEEEE, reverseBitOrder(0x77777777));
    GREATEST_ASSERT_EQ(0x66666666, reverseBitOrder(0x66666666));
    GREATEST_ASSERT_EQ(0xAAAAAAAA, reverseBitOrder(0x55555555));
    GREATEST_ASSERT_EQ(0x22222222, reverseBitOrder(0x44444444));
    GREATEST_ASSERT_EQ(0xCCCCCCCC, reverseBitOrder(0x33333333));
    GREATEST_ASSERT_EQ(0x44444444, reverseBitOrder(0x22222222));
    GREATEST_ASSERT_EQ(0x88888888, reverseBitOrder(0x11111111));
    GREATEST_ASSERT_EQ(0x00000000, reverseBitOrder(0x00000000));

    PASS();
}

/**
 * @testname    roundUpToPowerOf2_powersOfTwoUpTo32Bit_ShouldReturnTheSamePower
 * @testcase    @ref roundUpToPowerOf2 returns the same 32-bit variable for
 * variables that are powers of two.
 * @testvalues
 * | Argument   |
 * | ---------- |
 * | 0x00000001 |
 * | 0x00000002 |
 * | ...        |
 * | 0x40000000 |
 * | 0x80000000 |
 */
TEST
roundUpToPowerOf2_powersOfTwoUpTo32Bit_ShouldReturnTheSamePower()
{
    uint8_t i;
    for (i = 1; i < 32; i++) {
        GREATEST_ASSERT_EQ((uint32_t)correctBitMasksUpTo64Bit[i],
            roundUpToPowerOf2((uint32_t)correctBitMasksUpTo64Bit[i]));
    }

    PASS();
}

/**
 * @testname    roundUpToPowerOf2_powersOfTwoUpTo32BitMinusOne_GeneratePower
 * @testcase    @ref roundUpToPowerOf2 returns the correct next power of two for
 * variables 2^n - 1 for n is 2 to 32.
 * that are powers of two.
 * @testvalues
 * | Argument       |
 * | -------------- |
 * | 0x00000004 - 1 |
 * | 0x00000008 - 1 |
 * | ...            |
 * | 0x40000000 - 1 |
 * | 0x80000000 - 1 |
 */
TEST
roundUpToPowerOf2_powersOfTwoUpTo32BitMinusOne_GeneratePower()
{
    uint8_t i;
    for (i = 2; i < 32; i++) {
        GREATEST_ASSERT_EQ((uint32_t)correctBitMasksUpTo64Bit[i],
            roundUpToPowerOf2((uint32_t)correctBitMasksUpTo64Bit[i] - 1));
    }

    PASS();
}

/**
 * @testname    roundUpToPowerOf2_powersOfTwoUpTo32BitPlusOne_GeneratePower
 * @testcase    @ref roundUpToPowerOf2 returns the correct next power of two for
 * variables 2^n + 1 for n is 1 to 31.
 * that are powers of two.
 * @testvalues
 * | Argument       |
 * | -------------- |
 * | 0x00000002 + 1 |
 * | 0x00000004 + 1 |
 * | ...            |
 * | 0x20000000 + 1 |
 * | 0x40000000 + 1 |
 */
TEST
roundUpToPowerOf2_powersOfTwoUpTo32BitPlusOne_GeneratePower()
{
    uint8_t i;
    for (i = 1; i < 32; i++) {
        GREATEST_ASSERT_EQ((uint32_t)correctBitMasksUpTo64Bit[i+1],
            roundUpToPowerOf2((uint32_t)correctBitMasksUpTo64Bit[i] + 1));
    }

    PASS();
}

/**
 * @testname    roundUpToPowerOf2_zero_GeneratePower
 * @testcase    @ref roundUpToPowerOf2 returns the next power of two for zero.
 * @testvalues
 * | Argument   |
 * | ---------- |
 * | 0x00000000 |
 */
TEST
roundUpToPowerOf2_zero_GeneratePower()
{
    uint8_t i;
    for (i = 1; i < 32; i++) {
        GREATEST_ASSERT_EQ(0x00000001, roundUpToPowerOf2(0x00000000));
    }

    PASS();
}

/*******************************************************************************
 * Unit test suite
 ******************************************************************************/
/** Unit test suite for the BitOperations unit tests. */
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
    RUN_TEST(isPositive_maximumPositiveAndNegativeNumber_SignGenerated);
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
    RUN_TEST(modifyBits_setBitsUpTo32Bit_SingleBitCleared);
    RUN_TEST(modifyBits_clearedBitsUpTo32Bit_SingleBitSet);
    RUN_TEST(modifyBits_setBitsUpTo32Bit_MultipleBitsCleared);
    RUN_TEST(modifyBits_setBitsUpTo32Bit_MultipleBitsSet);
    RUN_TEST(mergeBits_magic32BitNumbers_Merged);
    RUN_TEST(nBitsSet_magic32BitNumbers_Generated);
    RUN_TEST(isOddParity_powersOfTwoUpTo64Bit_ParityGenerated);
    RUN_TEST(isOddParity_magig64BitNumbers_ParityGenerated);
    RUN_TEST(isOddParity_magig64BitNumbersMinusOne_ParityGenerated);
    RUN_TEST(isEvenParity_powersOfTwoUpTo64Bit_ParityGenerated);
    RUN_TEST(isEvenParity_magig64BitNumbers_ParityGenerated);
    RUN_TEST(isEvenParity_magig64BitNumbersMinusOne_ParityGenerated);
    RUN_TEST(reverseBitOrderByte_macic8BitNumbers_Reversed);
    RUN_TEST(reverseBitOrder_macic32BitNumbers_Reversed);
    RUN_TEST(roundUpToPowerOf2_powersOfTwoUpTo32Bit_ShouldReturnTheSamePower);
    RUN_TEST(roundUpToPowerOf2_powersOfTwoUpTo32BitMinusOne_GeneratePower);
    RUN_TEST(roundUpToPowerOf2_powersOfTwoUpTo32BitPlusOne_GeneratePower);
    RUN_TEST(roundUpToPowerOf2_zero_GeneratePower);
}

/*******************************************************************************
 * Main function
 ******************************************************************************/
/** Main definitions for the unit test framework greatest. */
GREATEST_MAIN_DEFS();

/**
 * @brief Initialize and run the unit tests.
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
