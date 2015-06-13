/*
 * generalDef.h
 *
 *  Created on: Aug 24, 2013
 *      Author: TV
 */

#ifndef GENERALDEF_H_
#define GENERALDEF_H_
//#include "integer.h"


typedef unsigned char           uint8;
typedef signed char             sint8;
typedef unsigned short          uint16;
typedef signed short            sint16;
typedef unsigned int            uint32;
typedef signed int              sint32;
typedef uint8 const             ucint8;
//
//typedef union {
//	unsigned char value;
//	struct {
//		unsigned char _0 :1;
//		unsigned char _1 :1;
//		unsigned char _2 :1;
//		unsigned char _3 :1;
//		unsigned char _4 :1;
//		unsigned char _5 :1;
//		unsigned char _6 :1;
//		unsigned char _7 :1;
//	} bits;
//} _UBYTE;
//
//typedef union {
//	char value;
//	struct {
//		char _0 :1;
//		char _1 :1;
//		char _2 :1;
//		char _3 :1;
//		char _4 :1;
//		char _5 :1;
//		char _6 :1;
//		char _7 :1;
//	} bits;
//} _BYTE;
//
//typedef union {
//	unsigned short value;
//	struct {
//		unsigned char _0;
//		unsigned char _1;
//	} bytes;
//	struct {
//		unsigned short _0 :1;
//		unsigned short _1 :1;
//		unsigned short _2 :1;
//		unsigned short _3 :1;
//		unsigned short _4 :1;
//		unsigned short _5 :1;
//		unsigned short _6 :1;
//		unsigned short _7 :1;
//		unsigned short _8 :1;
//		unsigned short _9 :1;
//		unsigned short _10 :1;
//		unsigned short _11 :1;
//		unsigned short _12 :1;
//		unsigned short _13 :1;
//		unsigned short _14 :1;
//		unsigned short _15 :1;
//	} bits;
//} _UWORD;
//typedef union {
//	short value;
//	struct {
//		unsigned char _0;
//		unsigned char _1;
//	} bytes;
//	struct {
//		short _0 :1;
//		short _1 :1;
//		short _2 :1;
//		short _3 :1;
//		short _4 :1;
//		short _5 :1;
//		short _6 :1;
//		short _7 :1;
//		short _8 :1;
//		short _9 :1;
//		short _10 :1;
//		short _11 :1;
//		short _12 :1;
//		short _13 :1;
//		short _14 :1;
//		short _15 :1;
//	} bits;
//} _SWORD;
//typedef union {
//	unsigned long int value;
//	struct {
//		unsigned char _0;
//		unsigned char _1;
//		unsigned char _2;
//		unsigned char _3;
//	} bytes;
//	struct {
//		unsigned long int _0 :1;
//		unsigned long int _1 :1;
//		unsigned long int _2 :1;
//		unsigned long int _3 :1;
//		unsigned long int _4 :1;
//		unsigned long int _5 :1;
//		unsigned long int _6 :1;
//		unsigned long int _7 :1;
//		unsigned long int _8 :1;
//		unsigned long int _9 :1;
//		unsigned long int _10 :1;
//		unsigned long int _11 :1;
//		unsigned long int _12 :1;
//		unsigned long int _13 :1;
//		unsigned long int _14 :1;
//		unsigned long int _15 :1;
//		unsigned long int _16 :1;
//		unsigned long int _17 :1;
//		unsigned long int _18 :1;
//		unsigned long int _19 :1;
//		unsigned long int _20 :1;
//		unsigned long int _21 :1;
//		unsigned long int _22 :1;
//		unsigned long int _23 :1;
//		unsigned long int _24 :1;
//		unsigned long int _25 :1;
//		unsigned long int _26 :1;
//		unsigned long int _27 :1;
//		unsigned long int _28 :1;
//		unsigned long int _29 :1;
//		unsigned long int _30 :1;
//		unsigned long int _31 :1;
//	} bits;
//} _ULONG;
//typedef union {
//	long int value;
//	struct {
//		unsigned char _0;
//		unsigned char _1;
//		unsigned char _2;
//		unsigned char _3;
//	} bytes;
//	struct {
//		long int _0 :1;
//		long int _1 :1;
//		long int _2 :1;
//		long int _3 :1;
//		long int _4 :1;
//		long int _5 :1;
//		long int _6 :1;
//		long int _7 :1;
//		long int _8 :1;
//		long int _9 :1;
//		long int _10 :1;
//		long int _11 :1;
//		long int _12 :1;
//		long int _13 :1;
//		long int _14 :1;
//		long int _15 :1;
//		long int _16 :1;
//		long int _17 :1;
//		long int _18 :1;
//		long int _19 :1;
//		long int _20 :1;
//		long int _21 :1;
//		long int _22 :1;
//		long int _23 :1;
//		long int _24 :1;
//		long int _25 :1;
//		long int _26 :1;
//		long int _27 :1;
//		long int _28 :1;
//		long int _29 :1;
//		long int _30 :1;
//		long int _31 :1;
//	} bits;
//} _SLONG;
//typedef union {
//	long long int value;
//	struct {
//		unsigned char _0;
//		unsigned char _1;
//		unsigned char _2;
//		unsigned char _3;
//		unsigned char _4;
//		unsigned char _5;
//		unsigned char _6;
//		unsigned char _7;
//	} bytes;
//	struct {
//		long long int _0 :1;
//		long long int _1 :1;
//		long long int _2 :1;
//		long long int _3 :1;
//		long long int _4 :1;
//		long long int _5 :1;
//		long long int _6 :1;
//		long long int _7 :1;
//		long long int _8 :1;
//		long long int _9 :1;
//		long long int _10 :1;
//		long long int _11 :1;
//		long long int _12 :1;
//		long long int _13 :1;
//		long long int _14 :1;
//		long long int _15 :1;
//		long long int _16 :1;
//		long long int _17 :1;
//		long long int _18 :1;
//		long long int _19 :1;
//		long long int _20 :1;
//		long long int _21 :1;
//		long long int _22 :1;
//		long long int _23 :1;
//		long long int _24 :1;
//		long long int _25 :1;
//		long long int _26 :1;
//		long long int _27 :1;
//		long long int _28 :1;
//		long long int _29 :1;
//		long long int _30 :1;
//		long long int _31 :1;
//		long long int _32 :1;
//		long long int _33 :1;
//		long long int _34 :1;
//		long long int _35 :1;
//		long long int _36 :1;
//		long long int _37 :1;
//		long long int _38 :1;
//		long long int _39 :1;
//		long long int _40 :1;
//		long long int _41 :1;
//		long long int _42 :1;
//		long long int _43 :1;
//		long long int _44 :1;
//		long long int _45 :1;
//		long long int _46 :1;
//		long long int _47 :1;
//		long long int _48 :1;
//		long long int _49 :1;
//		long long int _50 :1;
//		long long int _51 :1;
//		long long int _52 :1;
//		long long int _53 :1;
//		long long int _54 :1;
//		long long int _55 :1;
//		long long int _56 :1;
//		long long int _57 :1;
//		long long int _58 :1;
//		long long int _59 :1;
//		long long int _60 :1;
//		long long int _61 :1;
//		long long int _62 :1;
//		long long int _63 :1;
//	} bits;
//} _DSLONG;

typedef void VOID;
typedef unsigned char UBYTE;
typedef char SBYTE;
typedef unsigned short UWORD;
typedef short SWORD;
typedef unsigned long int ULONG;
typedef long int SLONG;
typedef long long int	DSLONG;
typedef unsigned long long int	DULONG;

#define UB	UBYTE
#define SB	SBYTE
#define UW	UWORD
#define SW	SWORD
#define UL	ULONG
#define SL	SLONG
#define DSL	DSLONG


#ifndef FALSE
#define FALSE 0
#define TRUE !FALSE

#define BOOL UBYTE
#endif

#define NULL_UB		(UB)0
#define NULL_SB		(SB)0

#define NULL_UW		(UW)0
#define NULL_SW		(SW)0
#define NULL_UL		(UL)0
#define NULL_SL		(SL)0

#define UWORD_MAX	(UWORD)0xFFFF

#endif /* GENERALDEF_H_ */
