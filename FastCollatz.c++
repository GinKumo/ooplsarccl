#include <cassert>
#include <stdint.h>

// USE int for fast but overflows on 32-bit and int64_t for always correct
#ifndef TINT
#define TINT int64_t
#endif /* TINT */


#ifdef __GNUC__
#define ctz __builtin_ctz
#else /* if we don't have GNUC then use this pretty quick implementation */
/* https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup */
static int ctz(int v) {  // find the number of trailing zeros in 32-bit v 
    int r;            // result goes here
    static const int MultiplyDeBruijnBitPosition[32] = 
    {
      0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
      31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
   return MultiplyDeBruijnBitPosition[((uint32_t)((v & -v) * 0x077CB531U)) >> 27];
}
#endif /* __GNUC__ */

int collatz_plen (int i) {
    TINT  p = i;
    TINT  c = 1;
    TINT cp;

    // 32 entry LUT for first 32 odd solutions
    static TINT lut[32] = {
                1,    8,   6,   17,
               20,   15,  10,   18,
               13,   21,   8,   16,
               24,  112,  19,  107,
               27,   14,  22,   35,
              110,   30,  17,  105,
               25,   25,  12,  113,
               33,   33,  20,  108 };

        if (p > 1) { cp = ctz(p); if (cp) {
            p >>= cp;
            c += cp;
        }

        while (p > 1) {
            assert (p != 1); // a should never be 1 here
            // multipy odd by 3
            p *= 3;
            // Since p is odd if we add 1 here we would just ripple carry
            // up from the lsb until the point where we have a zero bit.
            // instead of doing the add, we'll invert and use the optimized
            // ctz. then shift out all the ones.
            cp = ctz(~p);
            p >>= cp;
            // Set the bit that an add would have carried to
            p |= 1;
            // increment number of solutions found
            c += cp+1;
            assert ((p & 1) == 1); // p should always be odd

            // 32 entry lookup for first 32 odd solutions
            if (p < (int)(2*sizeof(lut)/sizeof(lut[0]))) {
                return c + lut[p/2] - 1;
            }
        }
    }

    return c;
}
