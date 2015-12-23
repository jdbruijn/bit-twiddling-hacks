/*******************************************************************************
 * Begin of file BitOperations.c
 * Author: jdebruijn
 * Created on October 5, 2015, 9:00 AM
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
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BitOperations.h"

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#CopyIntegerSign
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#compute-the-sign-of-an-integer
 *
 */
bool
isPositive(int32_t const _v)
{
    return (1 ^ ((unsigned int)_v >>
            (sizeof(int) * BITOPERATIONS_NCHAR_BITS - 1)));
}

/**
 * Use one AND-operation to check whether the LSB (zeroth bit) is set.
 *
 */
bool
isOdd(int64_t const _v)
{
    return (_v & 1ULL);
}

/**
 * Use the isOdd function and inverse the outcome.
 *
 */
bool
isEven(int64_t const _v)
{
    return (!isOdd(_v));
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#DetectOppositeSigns
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#detect-if-two-integers-have-opposite-signs
 *
 */
bool
haveOppositeSigns( int32_t const _x, int32_t const _y ) {
    return( (_x ^ _y) < 0 );
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#compute-the-minimum-min-or-maximum-max-of-two-integers-without-branching
 *
 */
int32_t
min( int32_t const _x, int32_t const _y ) {
    return( _y ^ ((_x ^ _y) & -(_x < _y)) );
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#compute-the-minimum-min-or-maximum-max-of-two-integers-without-branching
 *
 */
int32_t
max( int32_t const _x, int32_t const _y ) {
    return( _x ^ ((_x ^ _y) & -(_x < _y)) );
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#determining-if-an-integer-is-a-power-of-2
 *
 */
bool
isPowerOf2( uint64_t const _v ) {
    return( _v && !(_v & (_v - 1)) );
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#ConditionalSetOrClearBitsWithoutBranching
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#conditionally-set-or-clear-bits-without-branching
 *
 */
void
modifyBits( uint32_t *_v, uint32_t const _mask, bool const _f ) {
    *_v ^= (-_f ^*_v) & _mask;

    return;
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#merge-bits-from-two-values-according-to-a-mask
 *
 */
//uint32_t
//mergeBits( uint32_t const _x, uint32_t const _y, uint32_t const _mask ) {
//    return( _x ^((_x ^_y) & _mask) );
//}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSet64
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#counting-bits-set-in-14-24-or-32-bit-words-using-64-bit-instructions
 *
 */
uint8_t
nBitsSet( uint32_t const _v ) {
    uint8_t result;
    result =  ((_v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1F;
    result += (((_v & 0xfff000) >> 12) * 0x1001001001001ULL & \
            0x84210842108421ULL) % 0x1f;
    result += ((_v >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1F;

    return( result );
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#ParityMultiply
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#compute-parity-of-word-with-a-multiply
 *
 */
bool
isOddParity( uint64_t const _v ) {
    uint64_t v = _v;

    v ^= v >> 1;
    v ^= v >> 2;
    v = (v & 0x1111111111111111UL) * 0x1111111111111111UL;
    return (v >> 60) & 1;
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#ParityMultiply
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#compute-parity-of-word-with-a-multiply
 *
 */
bool
isEvenParity( uint64_t const _v ) {
    return( !isOddParity(_v) );
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#reverse-the-bits-in-a-byte-with-3-operations-64-bit-multiply-and-modulus-division
 *
 */
//void
//ByteReverseBits( uint8_t *_pByte ) {
//    *_pByte = ((*_pByte * 0x0202020202ULL & 0x010884422010ULL) % 1023) & 0xFF;
//
//    return;
//}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#ReverseParallel
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#reverse-an-n-bit-quantity-in-parallel-in-5--lgn-operations
 *
 */
void
reverseBitOrder( uint32_t *_v ) {
    // swap odd and even bits
    *_v = ((*_v >> 1) & 0x55555555) | ((*_v & 0x55555555) << 1);
    // swap consecutive pairs
    *_v = ((*_v >> 2) & 0x33333333) | ((*_v & 0x33333333) << 2);
    // swap nibbles ...
    *_v = ((*_v >> 4) & 0x0F0F0F0F) | ((*_v & 0x0F0F0F0F) << 4);
    // swap bytes
    *_v = ((*_v >> 8) & 0x00FF00FF) | ((*_v & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    *_v = ( *_v >> 16             ) | ( *_v               << 16);

    return;
}

/**
 * Based on Sean Eron Anderson's Bit Twiddling Hacks.
 *
 * @see https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2Float
 * @see https://github.com/gibsjose/BitHacks/blob/master/BitHacks.md#round-up-to-the-next-highest-power-of-2-by-float-casting
 *
 */
uint32_t
roundUpToPowerOf2( uint32_t const _v ) {
    if( _v > 1 ) {
        float f = (float)_v;
        uint32_t const t = 1U << ((*(uint32_t *)&f >> 23) - 0x7F);
        return( t << (t < _v) );
    }
    else {
        return( 1 );
    }
}
/* End of file BitOperations.c */
