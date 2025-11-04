//**************************************************************************************************
//
//	ASTIdef 	���ʒ萔�t�@�C��
//
//	Coding		K.Wada
//
//	History		01	2008.07.31		K.Wada	NEW
//				02	2009.06.26-01	K.Wada	�r�b�g�t�B�[���h�p�̌^�錾��ǉ�
//					2009.06.26-02	K.Wada	�f�[�^�̈ꕔ���Q�Ƃł��鋤�p�̌^�錾���폜
//				03	2010.12.08		K.Wada	���p�̌^�錾���폜
//				04	2014.02.11		Y.Takayanagi	U2,U4,S2,S4�^�ɐڔ���ǉ�
//
//**************************************************************************************************
#ifndef ASTIDEF
#define ASTIDEF

//------------------------------------------------------------------------------
//	�ʖ��錾
//------------------------------------------------------------------------------
typedef	unsigned char			U1 ;
typedef unsigned short			U2 ;
typedef unsigned long			U4 ;

typedef	signed char				S1 ;
typedef signed short			S2 ;
typedef signed long				S4 ;

typedef volatile unsigned char 	VU1 ;
typedef volatile unsigned short VU2 ;
typedef volatile unsigned long	VU4 ;

typedef volatile signed char	VS1 ;
typedef volatile signed short	VS2 ;
typedef volatile signed long	VS4 ;

typedef unsigned int			UINT ;		// �r�b�g�t�B�[���h�̂ݎg�p�\ (2009.06.26-01 �ǉ�)
typedef signed int				SINT ;		// �r�b�g�t�B�[���h�̂ݎg�p�\ (2009.06.26-01 �ǉ�)

//------------------------------------------------------------------------------
//	��{�萔�錾
//------------------------------------------------------------------------------
#define		U1TRUE			((U1)1)
#define		U1FALSE			((U1)0)
#define		U1ON			((U1)1)
#define		U1OFF			((U1)0)
#define		U1HI			((U1)1)
#define		U1LO			((U1)0)
#define		U1UP			((U1)1)
#define		U1DOWN			((U1)0)
#define		U1OK			((U1)1)
#define		U1NG			((U1)0)

#define		BIT0			((U1)0x01)
#define		BIT1			((U1)0x02)
#define		BIT2			((U1)0x04)
#define		BIT3			((U1)0x08)
#define		BIT4			((U1)0x10)
#define		BIT5			((U1)0x20)
#define		BIT6			((U1)0x40)
#define		BIT7			((U1)0x80)
#define		BIT_OFF			((U1)0x00)
#define		BIT_ON			((U1)0x01)

#define		U1MAX			((U1)0xff)
#define		U2MAX			((U2)0xffffUL)
#define		U4MAX			((U4)0xffffffffUL)

#define		U1MIN			((U1)0x00)
#define		U2MIN			((U2)0x0000UL)
#define		U4MIN			((U4)0x00000000UL)

#define		S1MAX			((S1)0x7f)
#define		S2MAX			((S2)0x7fffL)
#define		S4MAX			((S4)0x7fffffffL)

#define		S1MIN			((S1)0x80)
#define		S2MIN			((S2)0x8000L)
#define		S4MIN			((S4)0x80000000L)

#define		S1ZERO			((S1)0x00)
#define		S2ZERO			((S2)0x0000L)
#define		S4ZERO			((S4)0x00000000L)

#define 	U1_HI_NBL	 	((U1)0xf0)
#define 	U1_LO_NBL	 	((U1)0x0f)

// ���p�̂̌^�錾(�t���O) (2010.12.08)
// ���p�̂̌^�錾 �폜 (2009.06.26-02)

#endif
/*====================================== End of File =============================================*/
