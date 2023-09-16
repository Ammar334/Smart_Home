#ifndef BIT_MATH
#define BIT_MATH

#define SET_BIT(X,BIT_POS)     			(X |= (1 << BIT_POS))
#define CLEAR_BIT(X,BIT_POS)   			(X &= ~(1 << BIT_POS))
#define TOGGLE_BIT(X,BIT_POS)  			(X ^= (1 << BIT_POS))
#define READ_BIT(REG,BIT_POS)   		((REG >> BIT_POS) & 1)
#define	CLEAR_BITS_IN_REG(REG,MASK)		(REG &= ~(MASK))
#define SET_BITS_IN_REG(REG,MASK)		(REG |= (MASK))
#endif
