/**
 * \file array.h
 * \author Wispy (wspvlv@gmail.com)
 * \brief Array manipulation functions
 * \version 0.1
 * \date 2021-06-30
 */
#ifndef WC_ARRAY_H
#define WC_ARRAY_H



#include <wc/core.h>
#include <wc/types.h>
#include <wc/memory.h>

/* ALL FUNCTIONS DECLARED THROUGH "ADECL" ARE DEFINED IN "array.c" */


/*--- Macros --------------------------------------------*/
#undef	NO
#define NO(X)		(X)
#undef	NT
#define NT(X)		(~X)
#undef	AN
#define AN(X,Y)		(X&Y)
#undef	OR
#define OR(X,Y)		(X|Y)
#undef	XR
#define XR(X,Y)		(X^Y)
#undef	NN
#define NN(X,Y)		(~(X&Y))
#undef	NR
#define NR(X,Y)		(~(X|Y))
#undef	NX
#define NX(X,Y)		(~(X^Y))

#undef	EQ
#define	EQ(X,Y)		(X==Y)
#undef	NQ
#define NQ(X,Y)		(X!=Y)
#undef	GT
#define GT(X,Y)		(X>Y)
#undef	LT
#define LT(X,Y)		(X<Y)
#undef	GQ
#define GQ(X,Y)		(X>=Y)
#undef	LQ
#define LQ(X,Y)		(X<=Y)

#undef	NG
#define NG(X)		(-X)
#undef	IC
#define	IC(X)		(X++)
#undef	DC
#define DC(X)		(X--)
#undef	AD
#define	AD(X,Y)		(X+Y)
#undef	SB
#define SB(X,Y)		(X-Y)
#undef	ML
#define ML(X,Y)		(X*Y)
#undef	DV
#define DV(X,Y)		(X/Y)
#undef	MD
#define MD(X,Y)		(X%Y)

/**
 * \brief	Flag for memory search functions to search for the last occurance 
 * \def		SEARCH_REVERSE
 */
#define SEARCH_REVERSE	(wl_U8)0x01
/**
 * \brief	Flag for memory search functions to count amount of occurances
 * \def		SEARCH_COUNT
 */
#define SEARCH_COUNT	(wl_U8)0x02



/*--- Macro functions -----------------------------------*/
#undef	ADECL1
/** 
 * 	\def	Declaration for unioperand functions
 *	\param	NAME	Function name
 *	\brief	Most unioperand functions only require next 
 *			parameters
 *			- `s`	size of the operands in bytes
 *			- `r`	the array where the result is stored
 *			- `a`	the operand
 *
 *			return type is `Vo*`
 */
#define ADECL1(NAME)	\
	wl_vo* NAME(const wl_U8 s, register wl_Vo* r, register const wl_Vo* a)

#undef	ADECL2
/** 
 * 	\def	Declaration for bioperand functions
 *	\param	NAME	Function name
 *	\brief	Most bioperand functions only require next 
 *			parameters
 *			-	`s`	size of the operands in bytes
 *			-	`r`	the array where the result is stored 
 *			-	`a`	the operand A
 *			-	`b`	the operand B
 *				(a user can provide a pointer to an array
 *				and the result will be stored there, if
 *				null pointer is given, the result array
 *				will be automatically allocated)
 *			return type is `VO*`
 */
#define ADECL2(NAME)	\
	wl_vo* NAME(const wl_U8 s, register wl_Vo* r, register const wl_Vo* a, register const wl_Vo* b)

#undef	ADEF1
#if	NO_I64
/** 
 * 	\def	Definition of unioperand logic array operation (32-bit)
 *  \brief	Definition of unioperand logic array operation for systems where
 * 			a 64-bit type is not supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL1
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 4 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 4 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 2 phases
 *				+ First phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Second phase:	if Rsize & 1, then apply FUNC to next 1 bytes
 *	Sorry, I'm not good at explaining things
 */
#define ADEF1(NAME, FUNC) 												\
	ADECL1(NAME) {														\
		if (!r) r = wl_mal(0,s);										\
		register wl_U8 d = s/4;											\
		register wl_U8 m = s%4;											\
		register wl_U16 i = 0;											\
																		\
		for (; i < d; i++)												\
			((wl_U32*)r)[i] = FUNC(((wl_U32*)a)[i]);					\
																		\
		i *= 4;															\
																		\
		if (m&0b01)	{													\
			((wl_U8*)r)[i] = FUNC(((wl_U8*)a)[i]);						\
			i++;														\
		}																\
		if (m&0b10)	{													\
			((wl_U16*)r)[i] = FUNC(((wl_U16*)a)[i]);					\
			i += 2;														\
		}																\
																		\
		return r;														\
	}
#else
/** 
 * 	\def	Definition of unioperand logic array operations (64-bit)
 *  \brief	Definition of unioperand logic array operations for systems where
 * 			a 64-bit type is supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL1
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 8 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 8 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 3 phases
 *				+ First phase:	if Rsize & 4, then apply FUNC to next 4 bytes
 *				+ Second phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Third phase:	if Rsize & 1, then apply FUNC to next 1 byte
 *	Sorry, I'm not good at explaining things
 */
#define ADEF1(NAME, FUNC) 												\
	ADECL1(NAME) {														\
		if (!r) r = wl_mal(0,s);										\
		register wl_U8 d = s/8;											\
		register wl_U8 m = s%8;											\
		register wl_U16 i = 0;											\
																		\
		for (; i < d; i++)												\
			((wl_U64*)r)[i] = FUNC(((wl_U64*)a)[i]);					\
																		\
		i *= 8;															\
																		\
		if (m&0b001)	{												\
			((wl_U8*)r)[i] = FUNC(((wl_U8*)a)[i]);						\
			i++;														\
		}																\
		if (m&0b010)	{												\
			((wl_U16*)r)[i] = FUNC(((wl_U16*)a)[i]);					\
			i += 2;														\
		}																\
		if (m&0b100)	{												\
			((wl_U32*)r)[i] = FUNC(((wl_U32*)a)[i]);					\
			i += 4;														\
		}																\
																		\
		return r;														\
	}
#endif

#undef	ADEF2
#if	NO_I64
/** 
 * 	\def	Definition of bioperand logic array operations (32-bit)
 *  \brief	Definition of bioperand logic array operations for systems where
 * 			a 64-bit type is not supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL2
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 4 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 4 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 2 phases
 *				+ First phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Second phase:	if Rsize & 1, then apply FUNC to next 1 bytes
 *	Sorry, I'm not good at explaining things
 */
#define ADEF2(NAME, FUNC) 												\
	ADECL2(NAME) {														\
		if (!r) r = wl_mal(0,s);										\
		register wl_U8 d = s/4;											\
		register wl_U8 m = s%4;											\
		register wl_U16 i = 0;											\
																		\
		for (; i < d; i++)												\
			((wl_U32*)r)[i] = FUNC(((wl_U32*)a)[i], ((wl_U32*)b)[i]);	\
																		\
		i *= 4;															\
																		\
		if (m&0b01)	{													\
			((wl_U8*)r)[i] = FUNC(((wl_U8*)a)[i], ((wl_U8*)b)[i]);		\
			i++;														\
		}																\
		if (m&0b10)	{													\
			((wl_U16*)r)[i] = FUNC(((wl_U16*)a)[i], ((wl_U16*)b)[i]);	\
			i += 2;														\
		}																\
																		\
		return r;														\
	}
#else
/** 
 * 	\def	Definition of bioperand logic array operation (64-bit)
 *  \brief	Definition of bioperand logic array operation for systems where
 * 			a 64-bit type is supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL2
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 8 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 8 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 3 phases
 *				+ First phase:	if Rsize & 4, then apply FUNC to next 4 bytes
 *				+ Second phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Third phase:	if Rsize & 1, then apply FUNC to next 1 byte
 *	Sorry, I'm not good at explaining things
 */
#define ADEF2(NAME, FUNC) 										\
	ADECL2(NAME) {												\
		if (!r) r = wl_mal(0,s);								\
		register U8 d = s/8;									\
		register U8 m = s%8;									\
		register U16 i = 0;										\
																\
		for (; i < d; i++)										\
			((U64*)r)[i] = FUNC(((U64*)a)[i], ((U64*)b)[i]);	\
																\
		i *= 8;													\
																\
		if (m&0b001)	{										\
			((U8*)r)[i] = FUNC(((U8*)a)[i], ((U8*)b)[i]);		\
			i++;												\
		}														\
		if (m&0b010)	{										\
			((U16*)r)[i] = FUNC(((U16*)a)[i], ((U16*)b)[i]);	\
			i += 2;												\
		}														\
		if (m&0b100)	{										\
			((U32*)r)[i] = FUNC(((U32*)a)[i], ((U32*)b)[i]);	\
			i += 4;												\
		}														\
																\
		return r;												\
	}
#endif

#undef	ADECL1B
/** 
 * 	\def	Declaration for unioperand boolean functions
 *	\param	NAME	Function name
 *	\brief	Most unioperand boolean functions only require next 
 *			parameters
 *			- `s`	size of the operands in bytes
 *			- `a`	the operand
 *			return type is `BL`
 */
#define ADECL1B(NAME)	\
	wl_Bl NAME(const wl_U8 s, register const wl_Vo* a)

#undef	ADECL2B
/** 
 * 	\def	Declaration for bioperand boolean functions
 *	\param	NAME	Function name
 *	\brief	Most bioperand boolean functions only require next 
 *			parameters
 *			-	`s`	size of the operands in bytes
 *			-	`a`	the operand A
 *			-	`b`	the operand B)
 *			return type is `BL`
 */
#define ADECL2B(NAME)	\
	wl_Bl NAME(const wl_U8 s, register const wl_Vo* a, register const wl_Vo* b)

#undef	ADEF1
#if	NO_I64
/** 
 * 	\def	Definition of unioperand logic array operation (32-bit)
 *  \brief	Definition of unioperand logic array operation for systems where
 * 			a 64-bit type is not supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL1
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 4 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 4 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 2 phases
 *				+ First phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Second phase:	if Rsize & 1, then apply FUNC to next 1 bytes
 *	Sorry, I'm not good at explaining things
 */
#define ADEF1(NAME, FUNC) 										\
	ADECL1(NAME) {												\
		if (!r) r = wl_mal(0,s);								\
		register U8 d = s/4;									\
		register U8 m = s%4;									\
		register U16 i = 0;										\
																\
		for (; i < d; i++)										\
			((U32*)r)[i] = FUNC(((U32*)a)[i]);					\
																\
		i *= 4;													\
																\
		if (m&0b01)	{											\
			((U8*)r)[i] = FUNC(((U8*)a)[i]);					\
			i++;												\
		}														\
		if (m&0b10)	{											\
			((U16*)r)[i] = FUNC(((U16*)a)[i]);					\
			i += 2;												\
		}														\
																\
		return r;												\
	}
#else
/** 
 * 	\def	Definition of unioperand logic array operations (64-bit)
 *  \brief	Definition of unioperand logic array operations for systems where
 * 			a 64-bit type is supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL1
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 8 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 8 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 3 phases
 *				+ First phase:	if Rsize & 4, then apply FUNC to next 4 bytes
 *				+ Second phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Third phase:	if Rsize & 1, then apply FUNC to next 1 byte
 *	Sorry, I'm not good at explaining things
 */
#define ADEF1(NAME, FUNC) 										\
	ADECL1(NAME) {												\
		if (!r) r = wl_mal(0,s);								\
		register const U8 d = s/8;								\
		register const U8 m = s%8;								\
		register U16 i = 0;										\
																\
		for (; i < d; i++)										\
			((U64*)r)[i] = FUNC(((U64*)a)[i]);					\
																\
		i *= 8;													\
																\
		if (m&0b001)	{										\
			((U8*)r)[i] = FUNC(((U8*)a)[i]);					\
			i++;												\
		}														\
		if (m&0b010)	{										\
			((U16*)r)[i] = FUNC(((U16*)a)[i]);					\
			i += 2;												\
		}														\
		if (m&0b100)	{										\
			((U32*)r)[i] = FUNC(((U32*)a)[i]);					\
			i += 4;												\
		}														\
																\
		return r;												\
	}
#endif

#undef	ADEF2
#if	NO_I64
/** 
 * 	\def	Definition of bioperand logic array operations (32-bit)
 *  \brief	Definition of bioperand logic array operations for systems where
 * 			a 64-bit type is not supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL2
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 4 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 4 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 2 phases
 *				+ First phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Second phase:	if Rsize & 1, then apply FUNC to next 1 bytes
 *	Sorry, I'm not good at explaining things
 */
#define ADEF2(NAME, FUNC) 										\
	ADECL2(NAME) {												\
		if (!r) r = wl_mal(0,s);								\
		register U8 d = s/4;									\
		register U8 m = s%4;									\
		register U16 i = 0;										\
																\
		for (; i < d; i++)										\
			((U32*)r)[i] = FUNC(((U32*)a)[i], ((U32*)b)[i]);	\
																\
		i *= 4;													\
																\
		if (m&0b01)	{											\
			((U8*)r)[i] = FUNC(((U8*)a)[i], ((U8*)b)[i]);		\
			i++;												\
		}														\
		if (m&0b10)	{											\
			((U16*)r)[i] = FUNC(((U16*)a)[i], ((U16*)b)[i]);	\
			i += 2;												\
		}														\
																\
		return r;												\
	}
#else
/** 
 * 	\def	Definition of bioperand logic array operation (64-bit)
 *  \brief	Definition of bioperand logic array operation for systems where
 * 			a 64-bit type is supported.
 *	\param	NAME	Function name
 *	\param	FUNC	The operation it need to perform
 *	\return	result pointer
 *	\see	ADECL2
 *	
 *	Method:
 *		-#	If user provided a pointer for `r`, the result will be stored 
 *			there, otherwise it will be allocated.
 *		-#	Break up the operand A into chunks of 8 bytes.
 *		-#	Perform FUNC to all chunks of operand A and store the result it in 
 *			`r`
 *		-#	If there's any remaining part of the operand A that happened to be
 *			smaller than 8 bytes, **consider it's size ("Rsize") in binary**. The 
 *			algorithm does the same thing as in the step 3 but in 3 phases
 *				+ First phase:	if Rsize & 4, then apply FUNC to next 4 bytes
 *				+ Second phase:	if Rsize & 2, then apply FUNC to next 2 bytes
 *				+ Third phase:	if Rsize & 1, then apply FUNC to next 1 byte
 *	Sorry, I'm not good at explaining things
 */
#define ADEF2(NAME, FUNC) 										\
	ADECL2(NAME) {												\
		if (!r) r = wl_mal(0,s);								\
		register U8 d = s/8;									\
		register U8 m = s%8;									\
		register U16 i = 0;										\
																\
		for (; i < d; i++)										\
			((U64*)r)[i] = FUNC(((U64*)a)[i], ((U64*)b)[i]);	\
																\
		i *= 8;													\
																\
		if (m&0b001)	{										\
			((U8*)r)[i] = FUNC(((U8*)a)[i], ((U8*)b)[i]);		\
			i++;												\
		}														\
		if (m&0b010)	{										\
			((U16*)r)[i] = FUNC(((U16*)a)[i], ((U16*)b)[i]);	\
			i += 2;												\
		}														\
		if (m&0b100)	{										\
			((U32*)r)[i] = FUNC(((U32*)a)[i], ((U32*)b)[i]);	\
			i += 4;												\
		}														\
																\
		return r;												\
	}
#endif

/**
 */
#undef	ADEFB1
#define	ADEFB1(NAME,FUNC)										\
	ADECL1B(NAME) {												\
		register U8 d = s/8;									\
		register U8 m = s%8;									\
		register U16 i = 0;										\
																\
		for (; i < d; i++)										\
			if ( FUNC((U64*)a)[i] ) return 0;					\
																\
		i *= 8;													\
																\
		if (m&0x1) {											\
			if ( FUNC((U8*)a)[i] ) return 0;					\
			i++;												\
		}														\
		if (m&0x2) {											\
			if ( FUNC((U16*)a)[i] ) return 0;					\
			i += 2;												\
		}														\
		if (m&0x4)	{											\
			if ( FUNC((U32*)a)[i] ) return 0;					\
			i += 4;												\
		}														\
																\
		return 1;												\
	}

/**
 */
#undef	ADEFB2
#define	ADEFB2(NAME,FUNC)										\
	ADECL2B(NAME) {												\
		register U8 d = s/8;									\
		register U8 m = s%8;									\
		register U16 i = 0;										\
																\
		for (; i < d; i++)										\
			if ( FUNC((U64*)a)[i], ((U64*)b)[i]) ) return 0;	\
																\
		i *= 8;													\
																\
		if (m&0x1) {											\
			if ( FUNC((U8*)a)[i], ((U8*)b)[i]) ) return 0;		\
			i++;												\
		}														\
		if (m&0x2) {											\
			if ( FUNC((U16*)a)[i], ((U16*)b)[i]) ) return 0;	\
			i += 2;												\
		}														\
		if (m&0x4)	{											\
			if ( FUNC((U32*)a)[i], ((U32*)b)[i]),  ) return 0;	\
			i += 4;												\
		}														\
																\
		return 1;												\
	}



#ifndef NO_SHORT_NAMES
#define AA0		WL_AA0
#define aas		wl_aas
#define anot	wl_anot
#define aand	wl_aand
#define aor		wl_aor
#define axor	wl_axor
#define anand	wl_anand
#define anor	wl_anor
#define anxor	wl_anxor
#define ano		wl_ano
#define anotl	wl_anotl
#define aandl	wl_aandl
#define aorl	wl_aorl
#define axorl	wl_axorl
#define anandl	wl_anandl
#define anorl	wl_anorl
#define anxorl	wl_anxorl
#endif

/**
 * \brief	Array Allocate and set 0
 * \def		WL_AA0
 * \param	s Size
 * \return	wl_Vo*
 */
#define WL_AA0(s)	(wl_afl(s, NULL, 1, ""))



/*--- Types ---------------------------------------------*/
/**
 * \brief	wl_Vo* or integer
 * \typedef	wl_Vopu
 * \typedef wl_vopu
 * \typedef	wl_Vopi
 * \typedef	wl_vopi
 * A type for functions that return wl_Vo* and an integer
 */
typedef wl_Vo* wl_Vopu, wl_vopu, wl_Vopi, wl_vopi;



/*--- Declarations --------------------------------------*/
EXTERN ADECL1(wl_aas);		/* Array Assignment */
EXTERN ADECL1(wl_anot);		/* Array NOT */
EXTERN ADECL2(wl_aand);		/* Array AND */
EXTERN ADECL2(wl_aor);		/* Array OR */
EXTERN ADECL2(wl_axor);		/* Array XOR */
EXTERN ADECL2(wl_anand);	/* Array NAND */
EXTERN ADECL2(wl_anor);		/* Array NOR */
EXTERN ADECL2(wl_anxor);	/* Array NXOR */

EXTERN ADECL1B(wl_anol);	/* Array Logical No Operation */
EXTERN ADECL1B(wl_anotl);	/* Array Logical NOT */
EXTERN ADECL2B(wl_aandl);	/* Array Logical AND */
EXTERN ADECL2B(wl_aorl);	/* Array Logical OR */
EXTERN ADECL2B(wl_axorl);	/* Array Logical XOR */
EXTERN ADECL2B(wl_anandl);	/* Array Logical NAND */
EXTERN ADECL2B(wl_anorl);	/* Array Logical NOR */
EXTERN ADECL2B(wl_anxorl);	/* Array Logical NXOR */
EXTERN ADECL2B(wl_aeq);		/* Array Equals */
EXTERN ADECL2B(wl_aneq);	/* Array Not Equals */
EXTERN ADECL2B(wl_agt);		/* Array Greater Than */
EXTERN ADECL2B(wl_alt);		/* Array Less Than */
EXTERN ADECL2B(wl_agtq);	/* Array Greater Than Or Equal */
EXTERN ADECL2B(wl_altq);	/* Array Less Than Or Equal */

/**	\fn		VO* afl(register 8 sa, register VO* a, register U8 sb, register VO* b)
 *	\param	sa	size of the array A in bytes
 *	\param	a	the array A
 *	\param	sb	size of the array B in bytes
 *	\param	b	the array B
 *	\brief	Takes two arrays and their sizes. Fills the array A with as many
 *			instances of array B as the size of array A can handle.
 *	\return	The array A
 *	Method:
 *		-#	If /e a = NULL, then the array of size /e sa will be allocated
 *		-#	If /e b = NULL and /e sb = 0, then array will be filled with zeros
 *		-#	If /e sb = 0, the function does nothing and returns NULL
 *		-#	Declares a variable /e i, this is be the pointer offset
 *		-#	Assignes array /e b to array /e a offsetted by /e i, and incriments
 *			/e i by /e sb. This step is repeated until less than sb bytes are
 *			left untreated
 *		-#	Assignes the remaining part of array /e a with whatever piece of 
 *			array /e b fits
 *	\sa	wl_aas
 *	\sa wl_mal
 */
EXTERN wl_Vo*	wl_afl(	register wl_U8	sa, 
						register wl_Vo*	a, 
						register wl_U8	sb, 
						register wl_Vo*	b		);

/**
 * \brief	Find a byte in an array and return it's location relative to \a src address
 * \fn		wl_u8*	wl_asb(register wl_U8* src, register wl_U8 srcSize, register wl_U8 _byte);
 * \param	src		Source array
 * \param	srcSize	Array size
 * \param	_byte	Byte to find
 * \param	flags	Flags
 * \return	wl_u8* 
 * Searches for the occurance of \p _byte in anywhere in \p src .
 * -	If \c SEARCH_COUNT flag was not set, the function returns true, if any
 * 		occurance was found, false otherwise
 * -	If no flags were provided the algorithm searches for the first \p _byte
 * 		and stores in location in \p srcSize
 * -	If \c SEARCH_RESERVE flag is set, the address of last occurance will be
 *		stored in \p srcSize
 * -	If nothing was found (unless \c SEARCH_COUNT flag is set) \p srcSize
 * 		will be a null pointer
 * -	If \c SEARCH_COUNT flag is set, \p srcSize won't change, but the
 * 		function will return the amount of occurances
 * Regardless of flags used, if any occurance was found the function will
 * return a true (>0) value, and false (0) otherwise
 */
EXTERN wl_Vopu	wl_asb(	register wl_Vo*	src,
						register wl_U8	srcSize,
						register wl_U8	_byte,
						register wl_U8	flags	);


EXTERN wl_Vopu	wl_asa(	register wl_Vo*	src,
						register wl_U8	srcSize,
						register wl_Vo*	target,
						register wl_U8	targetSize,
						register wl_U8	flags	);



#endif