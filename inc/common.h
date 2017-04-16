/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 14th Apr 2017
 *
 * */

#ifndef COMMON_H
#define COMMON_H

#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif
#endif

enum Color { White, Yellow, Orange, Red, Green, Blue, C_UNDEFINED = -1 };
enum FaceSide { Front, Back, Up, Down, Left, Right, F_UNDEFINED = -1 };
enum PositionType { Center, Edge, Corner, P_UNDEFINED = -1 };

#define X(a, b) b
//#include "Color.def"

#define MIN(a,b) a<b?a:b

#endif
