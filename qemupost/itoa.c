//
//  itoa.c
//  qemupost
//
//  Created by mnelson1 on 1/31/21.
//  Copyright © 2021 none. All rights reserved.
//

#include "itoa.h"

// Make sure this code is always compiled as C
// maximum speed.
#ifdef __cplusplus
extern "C" {
#endif

// Easy lookup table to convert values in values characters.
const int val_to_char_offset[ 16 ] =
    { '0', '0', '0', '0',
      '0', '0', '0', '0',
      '0', '0', '7', '7',
      '7', '7', '7', '7'
    };

int
itoa( int    val,
      char * buf,
      int   width,
      int   radix )
    {

    char *       p;
    unsigned int a;        // Every digit.
    int          len;
    char *       b;        // Start of the digit char.
    char         temp;
    unsigned int u;

    p = buf;

    if( val < 0 ) 
        {
        *p++ = '-';
        val = 0 - val;
        }
    
    u = (unsigned int)val;

    b = p;

    do
        {
        a = u % radix;
        u /= radix;
        
        *p++ = a + val_to_char_offset[ a ];
        
        --width;
        }
    while( ( u > 0 ) || ( width > 0 ) );

    len = (int)( p - buf );

    *p-- = 0;

    // Swap.
    do
        {
        temp = *p;
        *p = *b;
        *b = temp;
        --p;
        ++b;
        }
    while( b < p );

    return len;
    }

#ifdef __cplusplus
}
#endif
