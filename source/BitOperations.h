/*******************************************************************************
 * Begin of file BitOperations.h
 * Author: jdebruijn
 * Created on October 5, 2015, 8:59 AM
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
 * @brief Several bit operations and manipulations, also known as 'bit hacks'.
 *
 * @note Most functions below are based on Sean Eron Anderson's Bit Twiddling
 * Hacks.
 * @see https://graphics.stanford.edu/~seander/bithacks.html
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md
 *
 ******************************************************************************/

#ifndef BITOPERATIONS_H
#define	BITOPERATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 ******************************************************************************/
//#include <xc.h>                       /* Include for PIC microcontrollers. */
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define BITOPERATIONS_NCHAR_BITS    8   /**< Number of bits in a byte. */

/*******************************************************************************
 * Function macros
 ******************************************************************************/
/**
 * @brief   Create a bit mask for a 32-bit variable.
 *
 * @param   n Number of the bit to create the mask for (0-31).
 * @return  uint32_t The created bit mask.
 */
#define BIT_MASK32(n) (1U << (n))

/**
 * @brief   Create a bit mask for a 64-bit variable.
 *
 * @param   n Number of the bit to create the mask for (0-63).
 * @return  uint64_t The created bit mask.
 */
#define BIT_MASK64(n) (1ULL << (n))

/**
 * @brief   Set a bit or bits according to a mask.
 *
 * @param   v Variable to set the bit(s) in.
 * @param   mask Mask for setting the bit(s).
 */
#define BIT_SETM(v, mask) ((v) |= (mask))

/**
 * @brief   Set a single bit.
 *
 * @param   v Variable to set a bit in.
 * @param   n Number of the bit to set where 0 is the rightmost bit.
 */
#define BIT_SET(v, n) BIT_SETM((v), (1ULL << (n)))

/**
 * @brief   Clear a bit or bits according to a mask.
 *
 * @param   v Variable to clear the bit(s) in.
 * @param   mask Mask for clearing the bit(s).
 */
#define BIT_CLEARM(v, mask) ((v) &= (~(mask)))

/**
 * @brief   Clear a single bit.
 *
 * @param   v Variable to clear a bit in.
 * @param   n Number of the bit to clear where 0 is the rightmost bit.
 */
#define BIT_CLEAR(v, n) BIT_CLEARM((v), (1ULL << (n)))

/**
 * @brief   Flip/toggle a bit or bits according to a mask.
 *
 * @param   v Variable to flip the bit(s) in.
 * @param   mask Mask for flipping the bit(s).
 */
#define BIT_FLIPM(v, mask) ((v) ^= (mask))

/**
 * @brief   Flip/toggle a single bit.
 *
 * @param   v Variable to flip a bit in.
 * @param   n Number of the bit to flip where 0 is the rightmost bit.
 */
#define BIT_FLIP(v, n) BIT_FLIPM((v), (1ULL << (n)))

/**
 * @brief   Shift a variable n places left.
 *
 * @param   v Variable to shift n places left.
 * @param   n Number of positions to shift the variable left.
 */
#define SHIFT_LEFT(v, n) ((v) <<= (n))

/**
 * @brief   Shift a variable n places right.
 *
 * @param   v Variable to shift n places right.
 * @param   n Number of positions to shift the variable right.
 */
#define SHIFT_RIGHT(v, n) ((v) >>= (n))

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
/**
 * @brief   Get the value of a bit or bits according to a mask.
 *
 * @note    This will for example return 7 when all bits in a byte were set and
 * the mask for getting the bits was 7.
 * @param   _v The variable to get the bit(s) from.
 * @param   _mask Mask for getting the bit(s).
 * @return  uint64_t Value of the bits of v that where set according to the
 * mask.
 */
uint64_t
bitGetm(uint64_t _v, uint64_t _mask);

/**
 * @brief   Get the value of a single bit.
 *
 * @param   _var Variable to get a from.
 * @param   _n Number of the bit to get where 0 is the rightmost bit
 * @return  bool True if the selected bit was set, false else.
 */
bool
bitGet(uint64_t _var, uint8_t _n);

/**
 * @brief   Compute the sign of an integer.
 *
 * @param   _var Variable of which to compute the sign
 * @return  boolean value of 1 (true) if the variable is positive, 0 else.
 */
bool
isPositive(int32_t const _var);

/**
 * @brief   Compute parity of a variable to see if it is odd.
 *
 * @param   _var Variable of which to compute the parity.
 * @return  bool True if the variable is odd, false else.
 */
bool
isOdd(int64_t const _v);

/**
 * @brief   Compute parity of a variable to see if it is even.
 *
 * @param   _var Variable of which to compute the parity
 * @return  bool True if the variable is even, false else.
 */
bool
isEven(int64_t const _v);

/**
 * @brief   Detect if two integers have opposite signs.
 *
 * @param   _x First variable of which the signs need to be compared.
 * @param   _y Second variable of which the signs need to be compared.
 * @return  bool True if the variables have opposite signs, false else.
 */
bool
haveOppositeSigns(int32_t const _x, int32_t const _y);

/**
 * @brief   Compute the minimum of two integers without branching.
 *
 * @param   _x First variable of which the minimum needs to be found.
 * @param   _y Second variable of which the minimum needs to be found.
 * @return  int32_t The minimum value _x or _y.
 */
int32_t
min(int32_t const _x, int32_t const _y);

/**
 * @brief   Compute the maximum of two integers without branching.
 *
 * @param   _x First variable of which the maximum needs to be found.
 * @param   _y Second variable of which the maximum needs to be found.
 * @return  int32_t The maximum value _x or _y.
 */
int32_t
max(int32_t const _x, int32_t const _y);

/**
 * @brief   Determining if an integer is a power of 2.
 *
 * @param   _var Variable of which to check if it is a power of two.
 * @return  bool True if _v is a power of to, false else.
 */
bool
isPowerOf2(uint64_t const _var);

/**
 * @brief   Conditionally set or clear bits without branching.
 *
 * @param   _var Pointer to the variable of which to set or clear bits.
 * @param   _mask Bit mask for setting or clearing bits.
 * @param   _f Flag whether the flag needs to be set or cleared (1 or 0).
 */
void
modifyBits(uint32_t *const _var, uint32_t const _mask, bool const _f);

/**
 * @brief   Merge bits from two values according to a mask.
 *
 * @note    This does not change the variable!
 * @param   _x Variable to merge in non-masked bits.
 * @param   _y Variable to merge in masked bits.
 * @param   _mask Bit mask for setting or clearing bits.
 * @return  uint32_t Result of the merged variables _x and _y.
 */
uint32_t
mergeBits(uint32_t const _x, uint32_t const _y, uint32_t const _mask);

/**
 * @brief   Counting bits set.
 *
 * @param   _var Variable of which to check how much bits are set.
 * @return  uint8_t Number of bits set in _var.
 */
uint8_t
nBitsSet(uint32_t const _var);

/**
 * @brief   Compute parity of word with a multiply.
 *
 * @param   _var Variable of which to compute the parity.
 * @return  bool True if the nuber of bits set in _v is odd, false else.
 */
bool
isOddParity(uint64_t const _var);

/**
 * @brief   Compute parity of word with a multiply.
 *
 * @param   _var Variable of which to compute the parity.
 * @return  bool True if the nuber of bits set in _var is even, false else.
 */
bool
isEvenParity(uint64_t const _var);

/**
 * @brief Reverse the order of bits in a byte.
 *
 * @param   _pByte Pointer to the byte which needs to be reversed.
 */
void
reverseBitOrderByte(uint8_t *const _pByte);

/**
 * @brief   Reverse an N-bit quantity in parallel in 5 * lg(N) operations.
 *
 * @note    Now set to reverse the bit order of an 32 bit unsigned integer.
 * @param   _pVar Pointer to the variable of which the bit order needs to be
 * reversed.
 */
void
reverseBitOrder(uint32_t *const _pVar);

/**
 * @brief   Round up to the next highest power of 2 by float casting.
 *
 * @note    This does not change the variable!
 * @param   _var Variable of which needs to be rounded up to the next highest
 * power of 2.
 * @return  uint32_t The next highest power of 2.
 */
uint32_t
roundUpToPowerOf2(uint32_t const _var);

#ifdef	__cplusplus
}
#endif

#endif	/* BITOPERATIONS_H */
/* End of file BitOperations.h */
