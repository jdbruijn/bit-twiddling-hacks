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
 * @see https://graphics.stanford.edu/~seander/bithacks.html#CopyIntegerSign
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
 * Create a bit mask. E.g. 0b00010000
 *
 * @param   b, number of the bit to create the mask for (0-32)
 * @return  the created bit mask
 * @Example <code>uint8_t mask3 = bitMask32(3); // Create bit mask 0b00001000</code>
 */
#define bitMask32(b) (1U << (b))

/**
 * Create a bit mask. E.g. 0b00010000
 *
 * @param   b, number of the bit to create the mask for (0-64)
 * @return  the created bit mask
 * @Example <code>uint8_t mask3 = bitMask64(3); // Create bit mask 0b00001000</code>
 */
#define bitMask64(b) (1ULL << (b))

/**
 * Get the value of a bit or bits according to a mask.
 *
 * @param   v, the variable to get the bit(s) from
 * @param   mask, mask for getting the bit(s)
 * @return  the value of the bits of v that where 1 according to mask
 * @Example <code>uint8_t x = 0b00001000;\n
 * bitGetm(x, 3); // Get the value of bit 3 (0b00001000) of
 * variable x, returns 8\n
 * bitGetm(x, bitMask(5)); // Get the value of bit 5 (0b00100000) of variable x
 * , returns 0 since x = 0b00001000</code>
 */
#define bitGetm(v, mask) ((v) & (mask))

/**
 * Get the value of a single bit.
 *
 * @param   v, variable to get the bit from
 * @param   n, number of the bit to get where 0 is the rightmost bit
 * @return  0 or 1, depending whether the selected bit was set or not
 * @Example <code>uint8_t x = 0b10000000;\n
 * bitGet(x, 3); // Get the value of bit 3 (00001000) of
 * variable x, returns 0\n
 * bitGet(x, 7); // Get the value of bit 7 (10000000) of variable x, returns 1
 * </code>
 */
#define bitGet(v, n) bitGetm(((v) >> (n)), 1U)

/**
 * Set a bit or bits according to a mask.
 *
 * @Note    This changes the variable!
 * @param   v, variable to set the bit(s) in
 * @param   mask, mask for setting the bit(s)
 * @Example <code>uint8_t x = 0b00001000;\n
 * bitSetm(x, 4); // Set bit 2 (00000100) in variable x, x is now 0b00001100\n
 * bitSetm(x, 0x3F); // Set bits 0-5 (00111111) in variable x, x is now 0b0011111\n
 * bitSetm(x, bitMask(7)); // Set bit 7 (10000000) in variable x, x is now 0b10111111
 * </code>
 */
#define bitSetm(v, mask) ((v) |= (mask))

/**
 * Set a single bit.
 *
 * @Note    This changes the variable!
 * @param   v, variable to set a bit in
 * @param   n, number of the bit to set where 0 is the rightmost bit
 * @Example <code>uint8_t x = 0b00001000;\n
 * bitSet(x, 1); // Set bit 1 (00000010) in variable x, x is now 0b00001010\n
 * bitSet(x, 7); // Set bit 7 (10000000) in variable x, x is now 0b10001010
 * </code>
 */
#define bitSet(v, n) bitSetm((v), (1ULL << (n)))

/**
 * Clear a bit or bits according to a mask.
 *
 * @Note    This changes the variable!
 * @param   v, variable to clear the bit(s) in
 * @param   mask, mask for clearing the bit(s)
 * @Example <code>uint8_t x = 0b11001011;\n
 * bitClearm(x, 8); // Clear bit 3 (00001000) of variable x, x is now 0b11000011\n
 * bitClearm(x, 7); // Clear bits 0-2 (00000111) of variable x, x is now 0b11000000\n
 * bitClearm(x, bitMask(7)); // Clear bit 7(10000000) of variable x, x is now 0b01000000
 * </code>
 */
#define bitClearm(v, mask) ((v) &= (~(mask)))

/**
 * Clear a single bit.
 *
 * @Note    This changes the variable!
 * @param   v, variable to clear a bit in
 * @param   n, number of the bit to clear where 0 is the rightmost bit
 * @Example <code>uint8_t x = 0b11001011;\n
 * bitClear(x, 1); // Clear bit 1 (00000010) in variable x, x is now 0b11001001\n
 * bitClear(x, 7); // Clear bit 7 (10000000) in variable x, x is now 0b01001001
 * </code>
 */
#define bitClear(v, n) bitClearm((v), (1ULL << (n)))

/**
 * Flip/toggle a bit or bits according to a mask.
 *
 * @Note    This changes the variable!
 * @param   v, variable to toggle the bit(s) in
 * @param   mask, mask for flipping the bit(s)
 * @Example <code>uint8_t x = 0b01001011;\n
 * bitFlipm(x, 2); // Flip bit 1 (00000010) of variable x, x is now 0b01001001\n
 * bitFlipm(x, 7); // Flip bits 0-2 (00000111) of variable x, x is now 0b01001110\n
 * bitFlipm(x, bitMask(7)); // Flip bit 7(10000000) of variable x, x is now 0b11001110
 * </code>
 */
#define bitFlipm(b, mask) ((b) ^= (mask))

/**
 * Flip/toggle a single bit.
 *
 * @Note    This changes the variable!
 * @param   v, variable to flip a bit in
 * @param   n, number of the bit to flip where 0 is the rightmost bit
 * @Example <code>uint8_t x = 0b01001011;\n
 * bitFlip(x, 1); // Flip bit 1 (00000010) in variable x, x is now 0b01001001\n
 * bitFlip(x, 7); // Flip bit 7 (10000000) in variable x, x is now 0b11001001
 * </code>
 */
#define bitFlip(v, n) bitFlipm((v), (1ULL << (n)))

/**
 * Shift a variable left.
 *
 * @Note    This changes the variable!
 * @param   v The variable to shift left
 * @param   p Number of positions to shift the variable left
 * @Example <code>shiftLeft(x, 2); // Shift variable x 2 places left</code>
 */
#define shiftLeft(v, p) ((v) <<= (p))

/**
 * Shift a variable right.
 *
 * @Note    This changes the variable!
 * @param   v The variable to shift right
 * @param   p Number of positions to shift the variable right
 * @Example <code>shiftRight(x, 2); // Shift variable x 2 places right</code>
 */
#define shiftRight(v, p) ((v) >>= (p))

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
/**
 * Compute the sign of an integer.
 *
 * @param   _v, variable of which to compute the sign
 * @return  boolean value of 1 (true) if the variable is positive, 0 else.
 */
bool
isPositive( int32_t const _v ) ;

 /**
  * Compute parity of a variable.
  *
  * @param   _v, variable of which to compute the parity
  * @return  boolean value of 1 (true) if the variable is odd, 0 else.
  */
 bool
 isOdd( int64_t const _v );

 /**
  * Compute parity of a variable.
  *
  * @param   _v, variable of which to compute the parity
  * @return  boolean value of 1 (true) if the variable is even, 0 else.
  */
 bool
 isEven( int64_t const _v );

/**
 * Detect if two integers have opposite signs.
 *
 * @param   _x, first variable of which the signs need to be compared
 * @param   _y, second variable of which the signs need to be compared
 * @return  bool, true if the variables have opposite signs, false else
 */
bool
haveOppositeSigns( int32_t const _x, int32_t const _y );

/**
 * Compute the minimum of two integers without branching.
 *
 * @param   _x, first variable of which the minimum needs to be found
 * @param   _y, second variable of which the minimum needs to be found
 * @return  int32_t, the minimum value _x or _y
 */
int32_t
min( int32_t const _x, int32_t const _y );

/**
 * Compute the maximum of two integers without branching.
 *
 * @param   _x, first variable of which the maximum needs to be found
 * @param   _y, second variable of which the maximum needs to be found
 * @return  int32_t, the maximum value _x or _y
 */
int32_t
max( int32_t const _x, int32_t const _y );

/**
 * Determining if an integer is a power of 2
 *
 * @param   _v, variable of which to check if it is a power of two
 * @return  bool, true if _v is a power of to, false else
 */
bool
isPowerOf2( uint64_t const _v );

/**
 * Conditionally set or clear bits without branching.
 *
 * @param   _v, pointer to the variable of which to set or clear bits
 * @param   _mask, bit mask for setting or clearing bits
 * @param   _f, flag whether the flag needs to be set or cleared (1 or 0)
 * @return  void
 */
void
modifyBits( uint32_t *_v, uint32_t const _mask, bool const _f );

/**
 * Merge bits from two values according to a mask.
 *
 * @param   _x, variable to merge in non-masked bits
 * @param   _y, variable to merge in masked bits
 * @param   _mask, bit mask for setting or clearing bits
 * @return  uint32_t, result of the merged variables _x and _y
 */
//uint32_t
//mergeBits( uint32_t const _x, uint32_t const _y, uint32_t const _mask );

/**
 * Counting bits set.
 *
 * @param   _v, variable of which to check how much bits are set
 * @return  uint8_t, number of bits set in _v
 */
uint8_t
nBitsSet( uint32_t const _v );

/**
 * Compute parity of word with a multiply.
 *
 * @param   _v, variable of which to compute the parity
 * @return  bool, true if the nuber of bits set in _v is odd, false else
 */
bool
isOddParity( uint64_t const _v );

/**
 * Compute parity of word with a multiply.
 *
 * @param   _v, variable of which to compute the parity
 * @return  bool, true if the nuber of bits set in _v is even, false else
 */
bool
isEvenParity( uint64_t const _v );

/**@todo change this function and description
 * Reverse the order of bits in a byte.
 * @Note
 *  Old: 8  7  6  5  4  3  2  1
 *       |  |  |  |  |  |  |  |
 *  New: 1  2  3  4  5  6  7  8
 *
 * @param   _pByte, byte pointer to the byte which needs to be reversed
 * @return  void
 */
//void
//ByteReverseBits( uint8_t *_pByte );

/**
 * Reverse an N-bit quantity in parallel in 5 * lg(N) operations. Now set to
 * reverse the bit order of an 32 bit unsigned integer.
 *
 * @param   _v, pointer to the variable of which the bit order needs to be
 * reversed
 * @return  void
 */
void
reverseBitOrder( uint32_t *_v );

/**
 * Round up to the next highest power of 2 by float casting.
 *
 * @param   _v, pointer to the variable of which needs to be round up to the
 * next power of 2
 * @return  uint16_t, the next power of 2
 */
uint32_t
roundUpToPowerOf2( uint32_t const _v );

#ifdef	__cplusplus
}
#endif

#endif	/* BITOPERATIONS_H */
/* End of file BitOperations.h */
