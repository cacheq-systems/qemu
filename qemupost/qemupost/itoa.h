//
//  itoa.h
//  qemupost
//
//  Created by mnelson1 on 1/31/21.
//  Copyright © 2021 none. All rights reserved.
//

#ifndef itoa_h
#define itoa_h

#ifdef __cplusplus
extern "C" {
#endif

int
itoa( int    val,
      char * buf,
      int   width,
      int   radix );

#ifdef __cplusplus
}
#endif

#endif /* itoa_h */
