/* mars.c optimized C code - copyright(c) 1998 IBM 
 *
 * This code implements both the NIST high level C API (version 5)
 * and an underlying IBM defined low level (WORD32 oriented) C API.
 */

/* Revisions log:
 *
 *   Aug 1999, Shai - the "tweaked" key schedule
 *   Apr 1998, Dave && Shai - new key scheduling, new sbox, NIST API
 *   Mar 1998, Shai Halevi  - adapted to the latest variant of mars
 *   Feb 1998, Dave Safford - created
 */
 
/* Compilation using pcg's version of gcc:
 *    gcc -Wall -pedantic -c -O6 -fomit-frame-pointer -mcpu=pentiumpro 
 *        -DINTEL_GCC tests.c mars-opt.c
 * 
 * Compilation using xlc on AIX:
 *    xlc -c -O3 -DAIX_XLC mars-opt.c
 *
 * Compilation using Borland C++ 5.0 from a DOS command line:
 *    bcc32 -Oi -6 -v -A -a4 -O2 -DKAT tests.c mars-opt.c
 *
 * Useful compilation defines:
 *    NO_MIX     - do not execute the mixing phases (core only)
 *    INTEL_GCC  - optimized for pentiumpro and djgpp/gcc compiler
 *    AIX_XLC    - optimized for powerpc/AIX with xlc compiler
 *    SWAP_BYTES - force endian conversion (eg __BYTE_ORDER not supported)
 *    IVT        - add intermediate values test outputs (this slows
 *                 down encryption and decryption significantly)
 */
  
#include "Mars.h"

/* The low level mars routines are completely WORD32 oriented, and 
 * endian neutral. The high level NIST routines provide BYTE oriented
 * inputs and outputs, thus raising the endian issue when converting
 * between BYTEs and WORDs. For these conversions, mars assumes 
 * little endian order. On a big endian machine, we define BSWAP() 
 * to do the conversions. BSWAP() is about the best you can do in C. 
 * Real implementations will undoubtedly use inline ASM, as most risc 
 * machines can do this in one instruction.
 * 
 * Make a best guess on platform endianness; This works on linux, AIX,
 * and W95. For other platforms, you may have to manually define SWAP_BYTES
 * on a big endian machine if this guessing doesn't work. 
 */
#ifdef _AIX 
#define SWAP_BYTES
#else
#ifdef __linux__
#include <endian.h>
#ifdef __BYTE_ORDER
#if __BYTE_ORDER == __BIG_ENDIAN
#define SWAP_BYTES
#endif
#endif
#endif
#endif
#ifdef SWAP_BYTES
#define BSWAP(x) \
    ( (( x          ) << 24) | \
      (((x)&0xff00  ) << 8 ) | \
      (((x)&0xff0000) >> 8 ) | \
      (( x          ) >> 24)  )        
#else
#define BSWAP(x) (x)
#endif

/* Some compiler optimizers will recognize certain rotation idioms,
 * and reduce them to native rotation instructions. These idioms
 * have been found to work for GCC on Intel, and XLC on RS6000.
 * Nothing seems to work on Borland C++ 5.0, although we can leave
 * out the mask on 'b'.
 */
#ifdef INTEL_GCC
#define LROTATE(a,b) (((a)<<(int)(b)) | ((a)>>(W - (int)(b))))
#define RROTATE(a,b) (((a)>>(int)(b)) | ((a)<<(W - (int)(b))))
#else
#ifdef AIX_XLC
#define LROTATE(a,b) ( ((a)>>(W - (b))) | ((a)<<(b)) )
#define RROTATE(a,b) ( ((a)<<(W - (b))) | ((a)>>(b)) )
#else
#ifdef __BORLANDC__
#define LROTATE(a,b) ( ((a)>>(W - (b))) | ((a)<<(b)) )
#define RROTATE(a,b) ( ((a)<<(W - (b))) | ((a)>>(b)) )
#else
#define LROTATE(a,b) (((a)<<(int)(b&31)) | ((a)>>(W - (int)(b&31))))
#define RROTATE(a,b) (((a)>>(int)(b&31)) | ((a)<<(W - (int)(b&31))))
#endif
#endif
#endif

/* two 8 x 32 sboxes - stored together to save a pointer
 * these sboxes were generated with buf[3] = 0x02917d59, as
 * chosen by sbox.c, which had the following output:
 *   After 54817140, (38023 fail) new min j = 43089241 (0x2917d59)
 *   test 0 eval 0.044922 (single bit correlation)
 *   test 1 eval 0.033203 (single bit bias)
 *   test 2 eval 0.031250 (consecutive bit bias)
 *   test 3 eval 0.007813 (parity bias)
 *   test 4 eval 0.148438 (avalanche)
 */
static WORD32 S[512] = {
  0x09d0c479, 0x28c8ffe0, 0x84aa6c39, 0x9dad7287, 
  0x7dff9be3, 0xd4268361, 0xc96da1d4, 0x7974cc93, 
  0x85d0582e, 0x2a4b5705, 0x1ca16a62, 0xc3bd279d, 
  0x0f1f25e5, 0x5160372f, 0xc695c1fb, 0x4d7ff1e4, 
  0xae5f6bf4, 0x0d72ee46, 0xff23de8a, 0xb1cf8e83, 
  0xf14902e2, 0x3e981e42, 0x8bf53eb6, 0x7f4bf8ac, 
  0x83631f83, 0x25970205, 0x76afe784, 0x3a7931d4, 
  0x4f846450, 0x5c64c3f6, 0x210a5f18, 0xc6986a26, 
  0x28f4e826, 0x3a60a81c, 0xd340a664, 0x7ea820c4, 
  0x526687c5, 0x7eddd12b, 0x32a11d1d, 0x9c9ef086, 
  0x80f6e831, 0xab6f04ad, 0x56fb9b53, 0x8b2e095c, 
  0xb68556ae, 0xd2250b0d, 0x294a7721, 0xe21fb253, 
  0xae136749, 0xe82aae86, 0x93365104, 0x99404a66, 
  0x78a784dc, 0xb69ba84b, 0x04046793, 0x23db5c1e, 
  0x46cae1d6, 0x2fe28134, 0x5a223942, 0x1863cd5b, 
  0xc190c6e3, 0x07dfb846, 0x6eb88816, 0x2d0dcc4a, 
  0xa4ccae59, 0x3798670d, 0xcbfa9493, 0x4f481d45, 
  0xeafc8ca8, 0xdb1129d6, 0xb0449e20, 0x0f5407fb, 
  0x6167d9a8, 0xd1f45763, 0x4daa96c3, 0x3bec5958, 
  0xababa014, 0xb6ccd201, 0x38d6279f, 0x02682215, 
  0x8f376cd5, 0x092c237e, 0xbfc56593, 0x32889d2c, 
  0x854b3e95, 0x05bb9b43, 0x7dcd5dcd, 0xa02e926c, 
  0xfae527e5, 0x36a1c330, 0x3412e1ae, 0xf257f462, 
  0x3c4f1d71, 0x30a2e809, 0x68e5f551, 0x9c61ba44, 
  0x5ded0ab8, 0x75ce09c8, 0x9654f93e, 0x698c0cca, 
  0x243cb3e4, 0x2b062b97, 0x0f3b8d9e, 0x00e050df, 
  0xfc5d6166, 0xe35f9288, 0xc079550d, 0x0591aee8, 
  0x8e531e74, 0x75fe3578, 0x2f6d829a, 0xf60b21ae, 
  0x95e8eb8d, 0x6699486b, 0x901d7d9b, 0xfd6d6e31, 
  0x1090acef, 0xe0670dd8, 0xdab2e692, 0xcd6d4365, 
  0xe5393514, 0x3af345f0, 0x6241fc4d, 0x460da3a3, 
  0x7bcf3729, 0x8bf1d1e0, 0x14aac070, 0x1587ed55, 
  0x3afd7d3e, 0xd2f29e01, 0x29a9d1f6, 0xefb10c53, 
  0xcf3b870f, 0xb414935c, 0x664465ed, 0x024acac7, 
  0x59a744c1, 0x1d2936a7, 0xdc580aa6, 0xcf574ca8, 
  0x040a7a10, 0x6cd81807, 0x8a98be4c, 0xaccea063, 
  0xc33e92b5, 0xd1e0e03d, 0xb322517e, 0x2092bd13, 
  0x386b2c4a, 0x52e8dd58, 0x58656dfb, 0x50820371, 
  0x41811896, 0xe337ef7e, 0xd39fb119, 0xc97f0df6, 
  0x68fea01b, 0xa150a6e5, 0x55258962, 0xeb6ff41b, 
  0xd7c9cd7a, 0xa619cd9e, 0xbcf09576, 0x2672c073, 
  0xf003fb3c, 0x4ab7a50b, 0x1484126a, 0x487ba9b1, 
  0xa64fc9c6, 0xf6957d49, 0x38b06a75, 0xdd805fcd, 
  0x63d094cf, 0xf51c999e, 0x1aa4d343, 0xb8495294, 
  0xce9f8e99, 0xbffcd770, 0xc7c275cc, 0x378453a7, 
  0x7b21be33, 0x397f41bd, 0x4e94d131, 0x92cc1f98, 
  0x5915ea51, 0x99f861b7, 0xc9980a88, 0x1d74fd5f, 
  0xb0a495f8, 0x614deed0, 0xb5778eea, 0x5941792d, 
  0xfa90c1f8, 0x33f824b4, 0xc4965372, 0x3ff6d550, 
  0x4ca5fec0, 0x8630e964, 0x5b3fbbd6, 0x7da26a48, 
  0xb203231a, 0x04297514, 0x2d639306, 0x2eb13149, 
  0x16a45272, 0x532459a0, 0x8e5f4872, 0xf966c7d9, 
  0x07128dc0, 0x0d44db62, 0xafc8d52d, 0x06316131, 
  0xd838e7ce, 0x1bc41d00, 0x3a2e8c0f, 0xea83837e, 
  0xb984737d, 0x13ba4891, 0xc4f8b949, 0xa6d6acb3, 
  0xa215cdce, 0x8359838b, 0x6bd1aa31, 0xf579dd52, 
  0x21b93f93, 0xf5176781, 0x187dfdde, 0xe94aeb76, 
  0x2b38fd54, 0x431de1da, 0xab394825, 0x9ad3048f, 
  0xdfea32aa, 0x659473e3, 0x623f7863, 0xf3346c59, 
  0xab3ab685, 0x3346a90b, 0x6b56443e, 0xc6de01f8, 
  0x8d421fc0, 0x9b0ed10c, 0x88f1a1e9, 0x54c1f029, 
  0x7dead57b, 0x8d7ba426, 0x4cf5178a, 0x551a7cca, 
  0x1a9a5f08, 0xfcd651b9, 0x25605182, 0xe11fc6c3, 
  0xb6fd9676, 0x337b3027, 0xb7c8eb14, 0x9e5fd030, 
  0x6b57e354, 0xad913cf7, 0x7e16688d, 0x58872a69, 
  0x2c2fc7df, 0xe389ccc6, 0x30738df1, 0x0824a734, 
  0xe1797a8b, 0xa4a8d57b, 0x5b5d193b, 0xc8a8309b, 
  0x73f9a978, 0x73398d32, 0x0f59573e, 0xe9df2b03, 
  0xe8a5b6c8, 0x848d0704, 0x98df93c2, 0x720a1dc3, 
  0x684f259a, 0x943ba848, 0xa6370152, 0x863b5ea3, 
  0xd17b978b, 0x6d9b58ef, 0x0a700dd4, 0xa73d36bf, 
  0x8e6a0829, 0x8695bc14, 0xe35b3447, 0x933ac568, 
  0x8894b022, 0x2f511c27, 0xddfbcc3c, 0x006662b6, 
  0x117c83fe, 0x4e12b414, 0xc2bca766, 0x3a2fec10, 
  0xf4562420, 0x55792e2a, 0x46f5d857, 0xceda25ce, 
  0xc3601d3b, 0x6c00ab46, 0xefac9c28, 0xb3c35047, 
  0x611dfee3, 0x257c3207, 0xfdd58482, 0x3b14d84f, 
  0x23becb64, 0xa075f3a3, 0x088f8ead, 0x07adf158, 
  0x7796943c, 0xfacabf3d, 0xc09730cd, 0xf7679969, 
  0xda44e9ed, 0x2c854c12, 0x35935fa3, 0x2f057d9f, 
  0x690624f8, 0x1cb0bafd, 0x7b0dbdc6, 0x810f23bb, 
  0xfa929a1a, 0x6d969a17, 0x6742979b, 0x74ac7d05, 
  0x010e65c4, 0x86a3d963, 0xf907b5a0, 0xd0042bd3, 
  0x158d7d03, 0x287a8255, 0xbba8366f, 0x096edc33, 
  0x21916a7b, 0x77b56b86, 0x951622f9, 0xa6c5e650, 
  0x8cea17d1, 0xcd8c62bc, 0xa3d63433, 0x358a68fd, 
  0x0f9b9d3c, 0xd6aa295b, 0xfe33384a, 0xc000738e, 
  0xcd67eb2f, 0xe2eb6dc2, 0x97338b02, 0x06c9f246, 
  0x419cf1ad, 0x2b83c045, 0x3723f18a, 0xcb5b3089, 
  0x160bead7, 0x5d494656, 0x35f8a74b, 0x1e4e6c9e, 
  0x000399bd, 0x67466880, 0xb4174831, 0xacf423b2, 
  0xca815ab3, 0x5a6395e7, 0x302a67c5, 0x8bdb446b, 
  0x108f8fa4, 0x10223eda, 0x92b8b48b, 0x7f38d0ee, 
  0xab2701d4, 0x0262d415, 0xaf224a30, 0xb3d88aba, 
  0xf8b2c3af, 0xdaf7ef70, 0xcc97d3b7, 0xe9614b6c, 
  0x2baebff4, 0x70f687cf, 0x386c9156, 0xce092ee5, 
  0x01e87da6, 0x6ce91e6a, 0xbb7bcc84, 0xc7922c20, 
  0x9d3b71fd, 0x060e41c6, 0xd7590f15, 0x4e03bb47, 
  0x183c198e, 0x63eeb240, 0x2ddbf49a, 0x6d5cba54, 
  0x923750af, 0xf9e14236, 0x7838162b, 0x59726c72, 
  0x81b66760, 0xbb2926c1, 0x48a0ce0d, 0xa6c0496d, 
  0xad43507b, 0x718d496a, 0x9df057af, 0x44b1bde6, 
  0x054356dc, 0xde7ced35, 0xd51a138b, 0x62088cc9, 
  0x35830311, 0xc96efca2, 0x686f86ec, 0x8e77cb68, 
  0x63e1d6b8, 0xc80f9778, 0x79c491fd, 0x1b4c67f2, 
  0x72698d7d, 0x5e368c31, 0xf7d95e2e, 0xa1d3493f, 
  0xdcd9433e, 0x896f1552, 0x4bc4ca7a, 0xa6d1baf4, 
  0xa5a96dcc, 0x0bef8b46, 0xa169fda7, 0x74df40b7, 
  0x4e208804, 0x9a756607, 0x038e87c8, 0x20211e44, 
  0x8b7ad4bf, 0xc6403f35, 0x1848e36d, 0x80bdb038, 
  0x1e62891c, 0x643d2107, 0xbf04d6f8, 0x21092c8c, 
  0xf644f389, 0x0778404e, 0x7b78adb8, 0xa2c52d53, 
  0x42157abe, 0xa2253e2e, 0x7bf3f4ae, 0x80f594f9, 
  0x953194e7, 0x77eb92ed, 0xb3816930, 0xda8d9336, 
  0xbf447469, 0xf26d9483, 0xee6faed5, 0x71371235, 
  0xde425f73, 0xb4e59f43, 0x7dbe2d4e, 0x2d37b185, 
  0x49dc9a63, 0x98c39d98, 0x1301c9a2, 0x389b1bbf, 
  0x0c18588d, 0xa421c1ba, 0x7aa3865c, 0x71e08558, 
  0x3c5cfcaa, 0x7d239ca4, 0x0297d9dd, 0xd7dc2830, 
  0x4b37802b, 0x7428ab54, 0xaeee0347, 0x4b3fbb85, 
  0x692f2f08, 0x134e578e, 0x36d9e0bf, 0xae8b5fcf, 
  0xedb93ecf, 0x2b27248e, 0x170eb1ef, 0x7dc57fd6, 
  0x1e760f16, 0xb1136601, 0x864e1b9b, 0xd7ea7319, 
  0x3ab871bd, 0xcfa4d76f, 0xe31bd782, 0x0dbeb469, 
  0xabb96061, 0x5370f85d, 0xffb07e37, 0xda30d0fb, 
  0xebc977b6, 0x0b98b40f, 0x3a4d0fe6, 0xdf4fc26b, 
  0x159cf22a, 0xc298d6e2, 0x2b78ef6a, 0x61a94ac0, 
  0xab561187, 0x14eea0f0, 0xdf0d4164, 0x19af70ee 
};

/*
 * The following implements Intermediate Values Tests Macros.
 * Since internal words are always kept little-endian, always
 * swap bytes before displaying.
 */
#ifdef IVT
int ivt_debug = 0;
FILE *ivt_fp;
int ivt_l = 0;
#define IVTSWAP(x) \
    ( (( x          ) << 24) | \
      (((x)&0xff00  ) << 8 ) | \
      (((x)&0xff0000) >> 8 ) | \
      (( x          ) >> 24)  )        
#define IVT_DEBUG(a,b,c,d) \
    if (ivt_debug) \
        fprintf(ivt_fp,"IV%d=%8.8lx %8.8lx %8.8lx %8.8lx\n",ivt_l++,\
        IVTSWAP(a),IVTSWAP(b),IVTSWAP(c),IVTSWAP(d));
#else
#define IVT_DEBUG(a,b,c,d)
#endif

/*************************************************************************
 *
 *   Low Level key setup, block encrypt and decrypt routines.
 *   For efficiency, these are WORD32 oriented. The high level NIST
 *   routines provide BYTE oriented interfaces, with ENDIAN conversion. 
 *
 ************************************************************************/
/* if multiplication subkey k has 10 0's or 10 1's, mask in a fixing value */
static WORD32 fix_subkey(WORD32 k, WORD32 r) 
{
    /* the mask words come from S[265]..S[268], as chosen by index.c */
    WORD32 *B = &S[265]; 
    WORD32 m1, m2;
    int i;

    i = k & 3;            /* store the least two bits of k */
    k |= 3;               /* and then mask them away       */

    /* we look for 9 consequtive 1's in m1 */
    m1 = (~k) ^ (k<<1);   /* for i > 1, m1_i = 1 iff k_i = k_{i-1} */
    m2 = m1 & (m1 << 1);  /* m2_i = AND (m1_i, m1_{i-1})   */
    m2 &= m2 << 2;        /* m2_i = AND (m1_i...m1_{i-3})  */
    m2 &= m2 << 4;        /* m2_i = AND (m1_i...m1_{i-7})  */
    m2 &= m1 << 8;        /* m2_i = AND (m1_i...m1_{i-8})  */
    m2 &= 0xfffffe00;     /* mask out the low 9 bits of m2 */
    /* for i = 9...31, m2_i = 1 iff k_i = ... = k_{i-9} */

    /* if m2 is zero, k was good, so return */ 
    if (!m2)
        return(k);

    /* need to fix k: we copy each 1 in m2 to the nine bits to its right */
    m1 = m2 | (m2 >> 1);  /* m1_i = AND (m2_i, m2_{i+1})   */
    m1 |= m1 >> 2;        /* m1_i = AND (m2_i...m2_{i+3})  */
    m1 |= m2 >> 4;        /* m1_i = AND (m2_i...m2_{i+4})  */
    m1 |= m1 >> 5;        /* m1_i = AND (m2_i...m2_{i+9})  */
    /* m1_i = 1 iff k_i belongs to a sequence of ten 0's or ten 1's */

    /* we turn off the two lowest bits of M, and also every bit 
     * M_i such that k_i is not equal to both k_{i-1} and k_{i+1} 
     */
    m1 &= ((~k)^(k<<1)) & ((~k)^(k>>1)) & 0x7ffffffc; 
    
    /* and finally pick a pattern, rotate it, 
     * and xor it into k under the control of the mask m1
     */
     k ^= LROTATE(B[i], r) & m1;

     return(k);
}


/* setup a mars key schedule 
 *
 * n  (input) is the number of words in the key
 * kp (input) is a pointer to the array of key words
 * ep (output) is a pointer to the array of EKEY_WORDS expanded subkey WORDs 
 */
int mars_setup(int n, WORD32 *kp, WORD32 *ep)
{
    WORD32 T[15] = {0}; 
    int i,j,t;

    /* check key length */
    if ((n<4)||(n>14))
        return(BAD_KEY_MAT);

    /* initialize the T[] array with key data */
    for (i=0; i<n; i++)
        T[i] = kp[i];
    T[n] = n;
    for (i=n+1; i<15; i++)
        T[i] = 0;

    /* Four iterations, each one computing 10 words of the array */
    for (j=0; j<4; j++) {
        WORD32 w;

        /* Linear transformation */
	w = T[8] ^ T[13];	T[0] ^= LROTATE(w,3) ^ j;
	w = T[9] ^ T[14];	T[1] ^= LROTATE(w,3) ^ (4+j);
        for (i=2; i<7; i++) { 
            w = T[i+8] ^ T[i-2]; 
            T[i] ^= LROTATE(w,3) ^ ((i<<2)+j);
        }
        for (i=7; i<15; i++) { 
            w = T[i-7] ^ T[i-2]; 
            T[i] ^= LROTATE(w,3) ^ ((i<<2)+j);
        }

        /* Four stirring rounds */
        for (t=0; t<4; t++){
            /* stir with full type-1 s-box rounds */
	    T[0] += S[ T[14]&511 ];
	    T[0] = LROTATE(T[0],9);
            for (i=1; i<15; i++) {
                T[i] += S[ T[i-1]&511 ]; 
                T[i] = LROTATE(T[i],9);
            }
        }

        /* copy subkeys to mars_ctx, with swapping around */

#define SWAP(i) (ep[(10*j)+i] = T[(i*4)%15])

	SWAP(0); SWAP(1); SWAP(2); SWAP(3); SWAP(4); 
	SWAP(5); SWAP(6); SWAP(7); SWAP(8); SWAP(9); 
    }

    /* check and fix all multiplication subkeys */
    for (i=NUM_DATA+1;i<(EKEY_WORDS-NUM_DATA);i+=2)
        ep[i] = fix_subkey(ep[i], ep[i-1]);

    return(TRUE);
}


#define MixForwardRound(d1,d2,d3,d4) \
    d2 ^= sp[d1&255];      \
    y = RROTATE(d1,8);     \
    z = RROTATE(d1,16);    \
    d1 = RROTATE(d1,24);   \
    d2 += sp[(y&255)+256]; \
    d3 += sp[z&255];       \
    d4 ^= sp[(d1&255)+256];

#define MixBackwardsRound(d1,d2,d3,d4) \
    d2 ^= sp[(d1&255)+256];\
    y = LROTATE(d1,8);     \
    z = LROTATE(d1,16);    \
    d1 = LROTATE(d1,24);   \
    d3 -= sp[y&255];       \
    d4 -= sp[(z&255)+256]; \
    d4 ^= sp[d1&255];      

#define CoreRound(d1,d2,d3,d4,i) \
    y = d1;            \
    d1 += ep[i];       \
    y = LROTATE(y,13); \
    z = d1;            \
    tmp = y;           \
    y *= ep[(i)+1];    \
    z &= 511;          \
    z = sp[z];         \
    y = LROTATE(y,5);  \
    z ^= y;            \
    d1 = LROTATE(d1,y);\
    y = LROTATE(y,5);  \
    d3 += d1;          \
    z ^= y;            \
    z = LROTATE(z,y);  \
    d2 += z;           \
    d4 ^= y;           \
    d1 = tmp;          

#define InvCoreRound(d1, d2, d3, d4, i) \
    y = d1;             \
    d1 = RROTATE(d1,13);\
    y *= ep[(i)+1];     \
    tmp = d1;           \
    d1 += ep[i];        \
    z = d1;             \
    y = LROTATE(y,5);   \
    z &= 511;           \
    z = sp[z];          \
    d1 = LROTATE(d1,y); \
    z ^= y;             \
    y = LROTATE(y,5);   \
    d3 -= d1;           \
    z ^= y;             \
    d1 = tmp;           \
    z = LROTATE(z,y);   \
    d4 ^= y;            \
    d2 -= z;            

/* The basic mars encryption: (ep is the expanded key array) */
void mars_encrypt(WORD32 *in, WORD32 *out, WORD32 *ep)
{
    register WORD32 a,b,c,d,y,z;
    WORD32 tmp;
    WORD32 *sp = S;

    a = in[0];
    b = in[1];
    c = in[2];
    d = in[3];
    IVT_DEBUG(a,b,c,d);

#ifndef NO_MIX
    /* first, add subkeys to all input data words */
    a += ep[0];
    b += ep[1];
    c += ep[2];
    d += ep[3];
    IVT_DEBUG(a,b,c,d);

    /* then do eight mixing rounds */
    MixForwardRound(a,b,c,d);
    a += d;
    IVT_DEBUG(a,b,c,d);
    MixForwardRound(b,c,d,a);
    b += c;
    IVT_DEBUG(a,b,c,d);
    MixForwardRound(c,d,a,b);
    IVT_DEBUG(a,b,c,d);
    MixForwardRound(d,a,b,c);
    IVT_DEBUG(a,b,c,d);

    MixForwardRound(a,b,c,d);
    a += d;
    IVT_DEBUG(a,b,c,d);
    MixForwardRound(b,c,d,a);
    b += c;
    IVT_DEBUG(a,b,c,d);
    MixForwardRound(c,d,a,b);
    IVT_DEBUG(a,b,c,d);
    MixForwardRound(d,a,b,c);
    IVT_DEBUG(a,b,c,d);
#endif

    /* then sixteen mars encrypting rounds             *
     * (eight in forward- and eight in backwards-mode) */

    CoreRound(a,b,c,d,4);
    IVT_DEBUG(a,b,c,d);
    CoreRound(b,c,d,a,6);
    IVT_DEBUG(a,b,c,d);
    CoreRound(c,d,a,b,8);
    IVT_DEBUG(a,b,c,d);
    CoreRound(d,a,b,c,10);
    IVT_DEBUG(a,b,c,d);

    CoreRound(a,b,c,d,12);
    IVT_DEBUG(a,b,c,d);
    CoreRound(b,c,d,a,14);
    IVT_DEBUG(a,b,c,d);
    CoreRound(c,d,a,b,16);
    IVT_DEBUG(a,b,c,d);
    CoreRound(d,a,b,c,18);
    IVT_DEBUG(a,b,c,d);

    CoreRound(a,d,c,b,20);
    IVT_DEBUG(a,b,c,d);
    CoreRound(b,a,d,c,22);
    IVT_DEBUG(a,b,c,d);
    CoreRound(c,b,a,d,24);
    IVT_DEBUG(a,b,c,d);
    CoreRound(d,c,b,a,26);
    IVT_DEBUG(a,b,c,d);

    CoreRound(a,d,c,b,28);
    IVT_DEBUG(a,b,c,d);
    CoreRound(b,a,d,c,30);
    IVT_DEBUG(a,b,c,d);
    CoreRound(c,b,a,d,32);
    IVT_DEBUG(a,b,c,d);
    CoreRound(d,c,b,a,34);
    IVT_DEBUG(a,b,c,d);

#ifndef NO_MIX
    /* then do eight inverse-mixing rounds */
    MixBackwardsRound(a,b,c,d);
    IVT_DEBUG(a,b,c,d);
    MixBackwardsRound(b,c,d,a);
    c -= b;
    IVT_DEBUG(a,b,c,d);
    MixBackwardsRound(c,d,a,b);
    d -= a;
    IVT_DEBUG(a,b,c,d);
    MixBackwardsRound(d,a,b,c);
    IVT_DEBUG(a,b,c,d);

    MixBackwardsRound(a,b,c,d);
    IVT_DEBUG(a,b,c,d);
    MixBackwardsRound(b,c,d,a);
    c -= b;
    IVT_DEBUG(a,b,c,d);
    MixBackwardsRound(c,d,a,b);
    d -= a;
    IVT_DEBUG(a,b,c,d);
    MixBackwardsRound(d,a,b,c);
    IVT_DEBUG(a,b,c,d);

    /* subtract final subkeys */
    a -= ep[2*NUM_ROUNDS+4];
    b -= ep[2*NUM_ROUNDS+5];
    c -= ep[2*NUM_ROUNDS+6];
    d -= ep[2*NUM_ROUNDS+7];
    IVT_DEBUG(a,b,c,d);
#endif

    out[0] = a;
    out[1] = b;
    out[2] = c;
    out[3] = d;
}

/* mars decryption is simply encryption in reverse */
void mars_decrypt(WORD32 *in, WORD32 *out, WORD32 *ep)
{
    register WORD32 a,b,c,d,y,z;
    WORD32 tmp;
    WORD32 *sp = S;

    d = in[0];
    c = in[1];
    b = in[2];
    a = in[3];
    IVT_DEBUG(d,c,b,a);

#ifndef NO_MIX
    /* first, add subkeys to all input data words */
    a += ep[2*NUM_ROUNDS+7];
    b += ep[2*NUM_ROUNDS+6];
    c += ep[2*NUM_ROUNDS+5];
    d += ep[2*NUM_ROUNDS+4];
    IVT_DEBUG(d,c,b,a);

    /* then do eight mixing rounds */
    MixForwardRound(a,b,c,d);
    IVT_DEBUG(d,c,b,a);
    a += d;
    MixForwardRound(b,c,d,a);
    IVT_DEBUG(d,c,b,a);
    b += c;
    MixForwardRound(c,d,a,b);
    IVT_DEBUG(d,c,b,a);
    MixForwardRound(d,a,b,c);
    IVT_DEBUG(d,c,b,a);

    MixForwardRound(a,b,c,d);
    IVT_DEBUG(d,c,b,a);
    a += d;
    MixForwardRound(b,c,d,a);
    IVT_DEBUG(d,c,b,a);
    b += c;
    MixForwardRound(c,d,a,b);
    IVT_DEBUG(d,c,b,a);
    MixForwardRound(d,a,b,c);
    IVT_DEBUG(d,c,b,a);
#endif

    /* then sixteen mars decrypting rounds             *
     * (eight in forward- and eight in backwards-mode) */

    InvCoreRound(a,b,c,d,34);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(b,c,d,a,32);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(c,d,a,b,30);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(d,a,b,c,28);
    IVT_DEBUG(d,c,b,a);

    InvCoreRound(a,b,c,d,26);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(b,c,d,a,24);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(c,d,a,b,22);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(d,a,b,c,20);
    IVT_DEBUG(d,c,b,a);

    InvCoreRound(a,d,c,b,18);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(b,a,d,c,16);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(c,b,a,d,14);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(d,c,b,a,12);
    IVT_DEBUG(d,c,b,a);

    InvCoreRound(a,d,c,b,10);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(b,a,d,c,8);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(c,b,a,d,6);
    IVT_DEBUG(d,c,b,a);
    InvCoreRound(d,c,b,a,4);
    IVT_DEBUG(d,c,b,a);

#ifndef NO_MIX
    /* then do eight inverse-mixing rounds */
    MixBackwardsRound(a,b,c,d);
    IVT_DEBUG(d,c,b,a);
    MixBackwardsRound(b,c,d,a);
    IVT_DEBUG(d,c,b,a);
    c -= b;
    MixBackwardsRound(c,d,a,b);
    IVT_DEBUG(d,c,b,a);
    d -= a;
    MixBackwardsRound(d,a,b,c);
    IVT_DEBUG(d,c,b,a);

    MixBackwardsRound(a,b,c,d);
    IVT_DEBUG(d,c,b,a);
    MixBackwardsRound(b,c,d,a);
    IVT_DEBUG(d,c,b,a);
    c -= b;
    MixBackwardsRound(c,d,a,b);
    IVT_DEBUG(d,c,b,a);
    d -= a;
    MixBackwardsRound(d,a,b,c);
    IVT_DEBUG(d,c,b,a);

    /* subtract final subkeys */
    a -= ep[3];
    b -= ep[2];
    c -= ep[1];
    d -= ep[0];
    IVT_DEBUG(d,c,b,a);
#endif

    out[0] = d;
    out[1] = c;
    out[2] = b;
    out[3] = a;
}

/*************************************************************************
 *
 *   NIST High Level key setup, block encrypt and decrypt routines
 *
 ************************************************************************/

/* table for rapid, case insensitive hex conversion */
BYTE hex[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 
    0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* NIST defined high level key setup */
int makeKeyMars(keyInstanceMars *key, BYTE direction, int keyLen, char *keyMaterial)
{
    WORD32 tmpkey[EKEY_WORDS];
    int i,j;

    /* sanity check pointers */
    if (key == NULL)
        return(BAD_KEY_INSTANCE);
    if (keyMaterial == NULL)
        return(BAD_KEY_MAT);

	for(i=0;i<EKEY_WORDS;i++) tmpkey[i]=0;

    /* save parameters into keyInstance */
    key->direction = direction;
    key->keyLen = keyLen;
    for (i=0;i<keyLen/4;i++)
        key->keyMaterial[i] = keyMaterial[i];
    key->keyMaterial[MAX_KEY_SIZE] = '\0';

    /* convert ascii keyMaterial to BYTEs */
    for(i=0,j=0;i<keyLen/4;i+=2,j++)
        ((BYTE *)tmpkey)[j] = (BYTE)((hex[(int)keyMaterial[i]]<<4) | 
                               hex[(int)keyMaterial[i+1]]); 
#   ifdef SWAP_BYTES
        /* BSWAP the input key words */
        for (i=0;i<keyLen/W;i++)
            tmpkey[i] = BSWAP(tmpkey[i]);
#   endif

    /* call low level mars setup routine */
    return(mars_setup(keyLen/32,tmpkey,key->E)); 
}

int cipherInitMars(cipherInstanceMars *cipher, BYTE mode, char *IV)
{
    int i,j;

    /* sanity check pointers */
    if (cipher == NULL)
        return(BAD_CIPHER_MODE);

    /* save cipher parameters */
    cipher->mode = mode;
        
    /* handle IV */
    if((mode == MODE_CBC)||(mode == MODE_CFB1)) {
        if(IV == NULL)
            return(BAD_CIPHER_MODE);
        /* convert ascii IV to BYTEs */
        for(i=0,j=0;j<MAX_IV_SIZE;i+=2,j++)
            cipher->IV[j] = (BYTE)((hex[(int)IV[i]]<<4) | hex[(int)IV[i+1]]); 
        /* copy BYTE IV to word CIV, with conversion if necessary */
        for(i=0;i<NUM_DATA;i++)
            cipher->CIV[i] = BSWAP(((WORD32 *)&cipher->IV)[i]);
    }
    return(TRUE);
}

/* this assumes the input length is a multiple of 128 bits */
int blockEncryptMars(cipherInstanceMars *cipher, keyInstanceMars *key, BYTE *input, 
                 int inputLen, BYTE *outBuffer)
{
    WORD32 tmp[4];
    int i;

    if (cipher->mode == MODE_ECB) {
        for(i=0;i<inputLen/8;i+=16){
#           ifdef SWAP_BYTES
                tmp[0] = BSWAP(*(WORD32 *)(input+i+0)); 
                tmp[1] = BSWAP(*(WORD32 *)(input+i+4)); 
                tmp[2] = BSWAP(*(WORD32 *)(input+i+8)); 
                tmp[3] = BSWAP(*(WORD32 *)(input+i+12)); 
                mars_encrypt(tmp,(WORD32 *)(outBuffer+i),key->E);
                *(WORD32 *)(outBuffer+i+0) = BSWAP(*(WORD32 *)(outBuffer+i+0)); 
                *(WORD32 *)(outBuffer+i+4) = BSWAP(*(WORD32 *)(outBuffer+i+4)); 
                *(WORD32 *)(outBuffer+i+8) = BSWAP(*(WORD32 *)(outBuffer+i+8)); 
                *(WORD32 *)(outBuffer+i+12) = BSWAP(*(WORD32 *)(outBuffer+i+12)); 
#           else
                mars_encrypt((WORD32 *)(input+i),(WORD32 *)(outBuffer+i),key->E);
#           endif
        }
    }
    else if(cipher->mode == MODE_CBC) {
        for(i=0;i<inputLen/8;i+=16){
#           ifdef SWAP_BYTES
                tmp[0] = BSWAP(*(WORD32 *)(input+i+0)) ^ cipher->CIV[0]; 
                tmp[1] = BSWAP(*(WORD32 *)(input+i+4)) ^ cipher->CIV[1]; 
                tmp[2] = BSWAP(*(WORD32 *)(input+i+8)) ^ cipher->CIV[2]; 
                tmp[3] = BSWAP(*(WORD32 *)(input+i+12)) ^ cipher->CIV[3]; 
                mars_encrypt(tmp,(WORD32 *)(outBuffer+i),key->E);
                cipher->CIV[0] = *(WORD32 *)(outBuffer+i+0);
                cipher->CIV[1] = *(WORD32 *)(outBuffer+i+4);
                cipher->CIV[2] = *(WORD32 *)(outBuffer+i+8);
                cipher->CIV[3] = *(WORD32 *)(outBuffer+i+12);
                *(WORD32 *)(outBuffer+i+0) = BSWAP(*(WORD32 *)(outBuffer+i+0)); 
                *(WORD32 *)(outBuffer+i+4) = BSWAP(*(WORD32 *)(outBuffer+i+4)); 
                *(WORD32 *)(outBuffer+i+8) = BSWAP(*(WORD32 *)(outBuffer+i+8)); 
                *(WORD32 *)(outBuffer+i+12) = BSWAP(*(WORD32 *)(outBuffer+i+12)); 
#           else
                tmp[0] = *(WORD32 *)(input+i+0) ^ cipher->CIV[0]; 
                tmp[1] = *(WORD32 *)(input+i+4) ^ cipher->CIV[1]; 
                tmp[2] = *(WORD32 *)(input+i+8) ^ cipher->CIV[2]; 
                tmp[3] = *(WORD32 *)(input+i+12) ^ cipher->CIV[3]; 
                mars_encrypt(tmp,(WORD32 *)(outBuffer+i),key->E);
                cipher->CIV[0] = *(WORD32 *)(outBuffer+i+0);
                cipher->CIV[1] = *(WORD32 *)(outBuffer+i+4);
                cipher->CIV[2] = *(WORD32 *)(outBuffer+i+8);
                cipher->CIV[3] = *(WORD32 *)(outBuffer+i+12);
#           endif
        }
    }
    else if(cipher->mode == MODE_CFB1) {
        /* Input is one bit (lsb of first byte).
         * Encrypt IV with key, xor input with msb of encrypted IV,
         * and then feed output cipher bit into lsb of IV.
         */
        WORD32 ECIV[4];

        if(inputLen != 1)
            return(BAD_CIPHER_MODE);

        mars_encrypt(cipher->CIV, ECIV, key->E); 
#pragma warning( disable : 4244)
        outBuffer[0] = (input[0] & 1)^(ECIV[0]>>31);
        cipher->CIV[0] = (cipher->CIV[0]<<1)|(cipher->CIV[1] & 0x80000000);
        cipher->CIV[1] = (cipher->CIV[1]<<1)|(cipher->CIV[2] & 0x80000000);
        cipher->CIV[2] = (cipher->CIV[2]<<1)|(cipher->CIV[3] & 0x80000000);
        cipher->CIV[3] = (cipher->CIV[3]<<1)|(WORD32)outBuffer[0];
    }
    else 
        return(BAD_CIPHER_MODE);

    return(inputLen);
}

/* this assumes the input length is a multiple of 128 bits */
int blockDecryptMars(cipherInstanceMars *cipher, keyInstanceMars *key, BYTE *input,
                 int inputLen, BYTE *outBuffer)
{
    int i;

    if (cipher->mode == MODE_ECB) {
        for(i=0;i<inputLen/8;i+=16){
#           ifdef SWAP_BYTES
                WORD32 tmp[4];
                tmp[0] = BSWAP(*(WORD32 *)(input+i+0)); 
                tmp[1] = BSWAP(*(WORD32 *)(input+i+4)); 
                tmp[2] = BSWAP(*(WORD32 *)(input+i+8)); 
                tmp[3] = BSWAP(*(WORD32 *)(input+i+12)); 
                mars_decrypt(tmp,(WORD32 *)(outBuffer+i),key->E);
                *(WORD32 *)(outBuffer+i+0) = BSWAP(*(WORD32 *)(outBuffer+i+0)); 
                *(WORD32 *)(outBuffer+i+4) = BSWAP(*(WORD32 *)(outBuffer+i+4)); 
                *(WORD32 *)(outBuffer+i+8) = BSWAP(*(WORD32 *)(outBuffer+i+8)); 
                *(WORD32 *)(outBuffer+i+12) = BSWAP(*(WORD32 *)(outBuffer+i+12)); 
#           else
                mars_decrypt((WORD32 *)(input+i),(WORD32 *)(outBuffer+i),key->E);
#           endif
        }
    }
    else if(cipher->mode == MODE_CBC) {
        for(i=0;i<inputLen/8;i+=16){
#           ifdef SWAP_BYTES
                WORD32 tmp[4];
                tmp[0] = BSWAP(*(WORD32 *)(input+i+0)); 
                tmp[1] = BSWAP(*(WORD32 *)(input+i+4)); 
                tmp[2] = BSWAP(*(WORD32 *)(input+i+8)); 
                tmp[3] = BSWAP(*(WORD32 *)(input+i+12)); 
                mars_decrypt(tmp,(WORD32 *)(outBuffer+i),key->E);
                *(WORD32 *)(outBuffer+i+0) = BSWAP(*(WORD32 *)(outBuffer+i+0)
                    ^ cipher->CIV[0]); 
                *(WORD32 *)(outBuffer+i+4) = BSWAP(*(WORD32 *)(outBuffer+i+4)
                    ^ cipher->CIV[1]); 
                *(WORD32 *)(outBuffer+i+8) = BSWAP(*(WORD32 *)(outBuffer+i+8)
                    ^ cipher->CIV[2]); 
                *(WORD32 *)(outBuffer+i+12) = BSWAP(*(WORD32 *)(outBuffer+i+12)
                    ^ cipher->CIV[3]); 
                cipher->CIV[0] = tmp[0];
                cipher->CIV[1] = tmp[1];
                cipher->CIV[2] = tmp[2];
                cipher->CIV[3] = tmp[3];
#           else
                mars_decrypt((WORD32 *)(input+i),(WORD32 *)(outBuffer+i),key->E);
                *(WORD32 *)(outBuffer+i+0) ^= cipher->CIV[0];
                *(WORD32 *)(outBuffer+i+4) ^= cipher->CIV[1];
                *(WORD32 *)(outBuffer+i+8) ^= cipher->CIV[2];
                *(WORD32 *)(outBuffer+i+12) ^= cipher->CIV[3];
                cipher->CIV[0] = *(WORD32 *)(input+i+0);
                cipher->CIV[1] = *(WORD32 *)(input+i+4);
                cipher->CIV[2] = *(WORD32 *)(input+i+8);
                cipher->CIV[3] = *(WORD32 *)(input+i+12);
#           endif
        }
    }
    else if(cipher->mode == MODE_CFB1){
        /* Input is one bit (lsb of first byte).
         * Encrypt IV with key, xor input with msb of encrypted IV,
         * and then feed input cipher bit into lsb of IV.
         */
        WORD32 ECIV[4];

        if(inputLen != 1)
            return(BAD_CIPHER_MODE);

        mars_encrypt(cipher->CIV, ECIV, key->E); 
        outBuffer[0] = (input[0] & 1)^(ECIV[0]>>31);
        cipher->CIV[0] = (cipher->CIV[0]<<1)|(cipher->CIV[1] & 0x80000000);
        cipher->CIV[1] = (cipher->CIV[1]<<1)|(cipher->CIV[2] & 0x80000000);
        cipher->CIV[2] = (cipher->CIV[2]<<1)|(cipher->CIV[3] & 0x80000000);
        cipher->CIV[3] = (cipher->CIV[3]<<1)|(WORD32)(input[0]&1);

    } 
    else 
        return(BAD_CIPHER_MODE);

    return(inputLen);
}



