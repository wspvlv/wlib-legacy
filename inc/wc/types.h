#ifndef WC_TYPES_H
#define WC_TYPES_H



#include <wc/sys/lang.h>
#include <wc/sys/damo.h>
#if (defined(USE_STDINT) || defined(USE_STDLIB)) && LG_C >= VR_C99
#	include <stdint.h>
#	include <limit.h>
#endif



/***
 *    ##     ##    ###     ######  ########   #######   ######  
 *    ###   ###   ## ##   ##    ## ##     ## ##     ## ##    ## 
 *    #### ####  ##   ##  ##       ##     ## ##     ## ##       
 *    ## ### ## ##     ## ##       ########  ##     ##  ######  
 *    ##     ## ######### ##       ##   ##   ##     ##       ## 
 *    ##     ## ##     ## ##    ## ##    ##  ##     ## ##    ## 
 *    ##     ## ##     ##  ######  ##     ##  #######   ######  
 */
/**
 * \brief	Floating-point type support 
 * \def		WL_TYPE_FLOAT
 * If set to 0, floating-point arithmetic not supported
 * If set to 1, otherwise
 */
/**
 * \brief	IMaginary type specifier
 * \def		wl_im
 * \def		wl_Im
 */
#if !defined(WL_TYPE_FLOAT) 
#	if && defined(__GCC_IEC_559) && !__GCC_IEC_559
#		define WL_TYPE_FLOAT	0
#		define wl_im
#		define wl_Im
#	else
#		define WL_TYPE_FLOAT	1
#		define wl_im	_Imaginary
#		define wl_Im	_Imaginary
#	endif
#endif
/**
 * \brief	Complex Floating-point type support 
 * \def		WL_TYPE_COMPLEX
 * If set to 0, floating-point complex arithmetic not supported
 * If set to 1, otherwise
 */
/**
 * \brief	CompleX type specifier
 * \def		wl_cx
 * \def		wl_Cx
 */
#if !defined(WL_TYPE_COMPLEX) 
#	if defined(__GCC_IEC_559_COMPLEX) && !__GCC_IEC_559_COMPLEX
#		define WL_TYPE_COMPLEX	0
#		define wl_cx
#		define wl_Cx
#	else
#		define WL_TYPE_FLOAT	1
#		define wl_cx	_Complex
#		define wl_Cx	_Complex
#	endif
#endif
/**
 * \brief	Long long type support 
 * \def		WL_TYPE_LONG_LONG
 * If set to 0, floating-point arithmetic not supported
 * If set to 1, otherwise
 */
#if !defined(WL_TYPE_LONG_LONG)
#	if ((defined(LG_C) && LG_C >= VR_C99) || (defined(LG_CPP) && LG_CPP >= VR_CPP11))
#		define WL_TYPE_LONG_LONG	1
#	else
#		define WL_TYPE_LONG_LONG	0
#	endif
#endif

/**
 * \brief	maXimal value of `unsigned char`
 * \def		WL_UCHX
 */
/**
 * \brief	maXimal value of `unsigned short`
 * \def		WL_UCHX
 */
/**
 * \brief	maXimal value of `unsigned int`
 * \def		WL_UINX
 */
/**
 * \brief	maXimal value of `unsigned long`
 * \def		WL_ULOX
 */
/**
 * \brief	maXimal value of `unsigned long long`
 * \def		WL_ULLX
 */
/**
 * \brief	miNimal value of `unsigned char`
 * \def		WL_UCHN
 */
/**
 * \brief	miNimal value of `unsigned short`
 * \def		WL_UCHN
 */
/**
 * \brief	miNimal value of `unsigned int`
 * \def		WL_UINN
 */
/**
 * \brief	miNimal value of `unsigned long`
 * \def		WL_LON
 */
/**
 * \brief	miNimal value of `unsigned long long`
 * \def		WL_LLN
 */
/**
 * \brief	miNimal value of `signed char`
 * \def		WL_UCHN
 */
/**
 * \brief	miNimal value of `short`
 * \def		WL_UCHN
 */
/**
 * \brief	miNimal value of `nt`
 * \def		WL_UINN
 */
/**
 * \brief	miNimal value of `long`
 * \def		WL_LON
 */
/**
 * \brief	miNimal value of `long long`
 * \def		WL_LLN
 */

#if (defined(USE_STDINT) || defined(USE_STDLIB)) && LG_C >= VR_C99

/* --- Sizes ------------------------------------------- */
/**
 * \brief	Bit-width of `char` or `wl_Ch`
 * \def		WL_CHB
 */
#	ifndef WL_CHB
#		ifdef CHAR_WIDTH
#			define WL_CHB	CHAR_WIDTH
#		else
#			define WL_CHB	CHAR_BIT
#		endif
#	endif

/**
 * \brief	Bit-width of `short`
 * \def		WL_SHB
 */
#	ifndef WL_SHB
#		ifdef SHRT_WIDTH
#			define WL_SHB	SHRT_WIDTH
#		else
#			define WL_SHB	(sizeof(short)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `int`
 * \def		WL_INB
 */
#	ifndef WL_INB
#		ifdef INT_WIDTH
#			define WL_INB	INT_WIDTH
#		else
#			define WL_INB	(sizeof(int)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `long`
 * \def		WL_INB
 */
#	ifndef WL_LOB
#		ifdef LONG_WIDTH
#			define WL_LOB	LONG_WIDTH
#		else
#			define WL_LOB	(sizeof(long)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `long long`
 * \def		WL_INB
 */
#	ifndef WL_LLB
#		ifdef LLONG_WIDTH
#			define WL_LLB	LLONG_WIDTH
#		else
#			define WL_LLB	(sizeof(long long)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `_Bool` or `wl_Bl`
 * \def		WL_BLB
 */
#	ifndef WL_BLB
#		ifdef BOOL_WIDTH
#			define WL_BLB	BOOL_WIDTH
#		else
#			define WL_BLB	CHAR_BIT
#		endif
#	endif

/**
 * \brief	Bit-width of `wl_I8`
 * \def		WL_I8B
 */
#	ifdef UINT8_WIDTH
#		define WL_I8B	UINT8_WIDTH
#	elif defined(__UINT8_WIDTH__)
#		define WL_I8B	__UINT8_WIDTH__
#	else
#		define WL_I8B	CHAR_BIT
#	endif

/**
 * \brief	Bit-width of `wl_I16`
 * \def		WL_I16B
 */
#	ifndef WL_I16B
#		ifdef UINT16_WIDTH
#			define WL_I16B	UINT16_WIDTH
#		elif defined(__UINT16_WIDTH__)
#			define WL_I16B	__UINT16_WIDTH__
#		else
#			define WL_I16B	(sizeof(wl_I16)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `wl_I32`
 * \def		WL_I32B
 */
#	ifndef WL_I32B
#		ifdef UINT32_WIDTH
#			define WL_I32B	UINT32_WIDTH
#		elif defined(__UINT32_WIDTH__)
#			define WL_I32B	__UINT32_WIDTH__
#		else
#			define WL_I32B	(sizeof(wl_I32)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `wl_I64`
 * \def		WL_I64B
 */
#	ifndef WL_I64B
#		ifdef UINT64_WIDTH
#			define WL_I64B	UINT64_WIDTH
#		elif defined(__UINT64_WIDTH__)
#			define WL_I64B	__UINT64_WIDTH__
#		else
#			define WL_I64B	(sizeof(wl_I64)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `wl_Pt`
 * \def		WL_PTB
 */
#	ifndef WL_PTB
#		ifdef UINTPTR_WIDTH
#			define WL_PTB	UINTPTR_WIDTH
#		else
#			define WL_PTB	(sizeof(wl_Pt)*CHAR_BIT)
#		endif
#	endif

/**
 * \brief	Bit-width of `wl_IMax` and `wl_UMax`
 * \def		WL_MXB
 */
#	ifndef WL_MXB
#		ifdef UINTMAX_WIDTH
#			define WL_MXB	UINTMAX_WIDTH
#		else
#			define WL_MXB	(sizeof(wl_UMax)*CHAR_BIT)
#		endif
#	endif


/* --- Limits ------------------------------------------ */

#	if !defined(WL_UCHX) && defined(UCHAR_MAX)
#		define WL_UCHX	UCHAR_MAX
#	endif
#	if !defined(WL_USHX) && defined(USHRT_MAX)
#		define WL_USHX	USHRT_MAX
#	endif
#	if !defined(WL_UINX) && defined(UINT_MAX)
#		define WL_UINX	UINT_MAX
#	endif
#	if !defined(WL_ULOX) && defined(ULONG_MAX)
#		define WL_ULOX	ULONG_MAX
#	endif
#	if !defined(WL_ULLX) && defined(ULLONG_MAX)
#		define WL_ULLX	ULLONG_MAX
#	endif
#	if !defined(WL_SCHN) && defined(SCHAR_MIN)
#		define WL_SCHN	SCHAR_MIN
#	endif
#	if !defined(WL_SHN) && defined(SHRT_MIN)
#		define WL_SHN	SHRT_MIN
#	endif
#	if !defined(WL_INN) && defined(INT_MIN)
#		define WL_INN	INT_MIN
#	endif
#	if !defined(WL_LON) && defined(LONG_MIN)
#		define WL_LON	LONG_MIN
#	endif
#	if !defined(WL_LLN) && defined(LLONG_MIN)
#		define WL_LLN	LLONG_MIN
#	endif



/**
 * \brief	maXimal value of `unsigned int`
 * \def		WL_UINN
 */
/* #	ifdef UINT_MAX
#		define WL_UINX	UINT_MAX
#	elif DATA_MODEL >= DM_ILP64
#		define WL_UINX	(unsigned int)0xFFFFFFFFFFFFFFFF
#	elif DATA_MODEL == DM_LP32
#		define WL_UINX	(unsigned int)0xFFFF
#	endif */

#endif

/* Always */

/**
 * \brief	miNimal value of `unsigned char`
 * \def		WL_UCHN
 */
#define WL_UCHN		(unsigned char)0
/**
 * \brief	miNimal value of `unsigned short`
 * \def		WL_UCHN
 */
#define WL_USHN		(unsigned short)0
/**
 * \brief	miNimal value of `unsigned int`
 * \def		WL_UINN
 */
#define WL_UINN		(unsigned int)0
/**
 * \brief	miNimal value of `unsigned long`
 * \def		WL_ULON
 */
#define WL_ULON		(unsigned long)0
/**
 * \brief	miNimal value of `unsigned long long`
 * \def		WL_ULLN
 */
#define WL_ULLN		(unsigned long long)0
/**
 * \brief	miNimal value of `unsigned long long`
 * \def		WL_ULLN
 */
#define WL_BLN		(wl_Bl)0
/**
 * \brief	miNimal value of `wl_I8`
 * \def		WL_U8N
 */
#define WL_U8N		(wl_I8)0
/**
 * \brief	miNimal value of `wl_I16`
 * \def		WL_U16N
 */
#define WL_U16N		(wl_I16)0
/**
 * \brief	miNimal value of `wl_I32`
 * \def		WL_U32N
 */
#define WL_U32N		(wl_I32)0
/**
 * \brief	miNimal value of `wl_I64`
 * \def		WL_U64N
 */
#define WL_U64N		(wl_I64)0
/**
 * \brief	miNimal value of `wl_Pt`
 * \def		WL_PTN
 */
#define WL_PTN		(wl_Pt)0
/**
 * \brief	miNimal value of `wl_UMax`
 * \def		WL_UMXN
 */
#define WL_UMXN		(wl_UMax)0

/* Guess the minimal and maximal values */
#if DATA_MODEL == NULL
#	ifndef WL_USHX		


#if	DATA_MODEL == DM_SILP64
#	ifndef WL_USHX
#		define	WL_USHX	(unsigned short)0xFFFFFFFFFFFFFFFF
#	endif
#	ifndef WL_SHX
#		define	WL_SHX	(short)0x7FFFFFFFFFFFFFFF
#	endif
#	ifndef WL_SHN
#		define	WL_SHN	(short)-0x7FFFFFFFFFFFFFFF
#	endif
#endif
#if	DATA_MODEL >= DM_ILP64
#	ifndef WL_UINX
#		define	WL_UINX (unsigned int)0xFFFFFFFFFFFFFFFF
#	endif
#	ifndef WL_INX
#		define	WL_INX	(int)0x7FFFFFFFFFFFFFFF
#	endif
#	ifndef WL_INN
#		define	WL_INN	(int)-0x7FFFFFFFFFFFFFFF
#	endif
#endif
#if	DATA_MODEL >= DM_LP64
#	ifndef WL_ULOX
#		define	WL_ULOX (unsigned long)0xFFFFFFFFFFFFFFFF
#	endif
#	ifndef WL_LOX
#		define	WL_LOX	(int)0x7FFFFFFFFFFFFFFF
#	endif
#	ifndef WL_LON
#		define	WL_LON	(int)-0x7FFFFFFFFFFFFFFF
#	endif
#endif
#if	DATA_MODEL >= DM_ILP32
#	ifndef WL_UINX
#		define	WL_UINX (unsigned int)0xFFFFFFFF
#	endif
#endif
#if	DATA_MODEL >= DM_LP32
#	ifndef WL_UINX
#		define	WL_UINX (unsigned int)0xFFFF
#	endif
#ifndef WL_USHX
#	define	WL_USHX (unsigned short)0xFFFF
#endif
#ifndef WL_ULOX
#	define	WL_ULOX (unsigned long)0xFFFFFFFF
#endif
#ifndef WL_UCHX
#	define	WL_UCHX (unsigned char)0xFF
#endif
#	ifndef WL_UINX
#		define	WL_UINX (unsigned int)0xFFFFFFFF
#	endif



/***
 *    ######## ##    ## ########  ########  ######  
 *       ##     ##  ##  ##     ## ##       ##    ## 
 *       ##      ####   ##     ## ##       ##       
 *       ##       ##    ########  ######    ######  
 *       ##       ##    ##        ##             ## 
 *       ##       ##    ##        ##       ##    ## 
 *       ##       ##    ##        ########  ######  
 */
#if (defined(USE_STDINT) || defined(USE_STDLIB)) && LG_C >= VR_C99

	/* --- Signed integer ------------------------------ */
	/**
	 * \brief	8-bit signed Integer type
	 * \typedef	wl_i8
	 * \typedef	wl_I8
	 */
	typedef int8_t			wl_i8,		wl_I8;
	/**
	 * \brief	16-bit signed Integer type
	 * \typedef	wl_i16
	 * \typedef	wl_I16
	 */
	typedef int16_t			wl_i16,		wl_I16;
	/**
	 * \brief	32-bit signed Integer type
	 * \typedef	wl_i32
	 * \typedef	wl_I32
	 */
	typedef int32_t			wl_i32,		wl_I32;
	/**
	 * \brief	64-bit signed Integer type
	 * \typedef	wl_i64
	 * \typedef	wl_I64
	 */
	typedef int64_t			wl_i64,		wl_I64;
	/**
	 * \brief	Signed Integer type of MAXimal size
	 * \typedef	wl_imax
	 * \typedef	wl_IMax
	 */
	typedef intmax_t		wl_imax,	wl_IMax;

	/* --- Unsigned integer ---------------------------- */
	/**
	 * \brief	8-bit Unsigned integer type
	 * \typedef	wl_i8
	 * \typedef	wl_I8
	 */
	typedef uint8_t			wl_u8,		wl_U8;
	/**
	 * \brief	16-bit Unsigned integer type
	 * \typedef	wl_i16
	 * \typedef	wl_I16
	 */
	typedef uint16_t		wl_u16,		wl_U16;
	/**
	 * \brief	32-bit Unsigned integer type
	 * \typedef	wl_i32
	 * \typedef	wl_I32
	 */
	typedef uint32_t		wl_u32,		wl_U32;
	/**
	 * \brief	64-bit Unsigned integer type
	 * \typedef	wl_i64
	 * \typedef	wl_I64
	 */
	typedef uint64_t		wl_u64,		wl_U64;
	/**
	 * \brief	Unsigned integer type of MAXimal size
	 * \typedef	wl_imax
	 * \typedef	wl_IMax
	 */
	typedef uintmax_t		wl_umax,	wl_UMax;

	/**
	 * \brief	PoinTer type
	 * \typedef wl_pt
	 * \typedef	wl_Pt
	 * \typedef	wl__Ptr
	 */
	typedef uintptr_t		wl_pt,	wl_Pt, 
							wl__Ptr;	/* Depricated */

#else
#endif

/* --- Other ------------------------------------------- */
/**
 * \brief	BooLean type
 * \def		wl_bl
 * \def		wl_Bl
 */
typedef _Bool			wl_bl,		wl_Bl;
/**
 * \brief	CHaracter/byte type
 * \def		wl_ch
 * \def		wl_Ch
 */
typedef char			wl_ch,		wl_Ch;

#if WL_TYPE_FLOAT
	/**
	 * \brief	32-bit Floating-point type
	 * \def		wl_f32
	 * \def		wl_F32
	 */
	typedef float			wl_f32,		wl_F32;
	/**
	 * \brief	64-bit Floating-point type
	 * \def		wl_f64
	 * \def		wl_F64
	 */
	typedef double			wl_f64,		wl_F64;
#else
	/**
	 * \brief	32-bit Floating-point type
	 * \def		wl_f32
	 * \def		wl_F32
	 */
	typedef wl_U32			wl_f32,		wl_F32;
	/**
	 * \brief	64-bit Floating-point type
	 * \def		wl_f64
	 * \def		wl_F64
	 */
	typedef wl_U64			wl_f64,		wl_F64;
#endif



#endif