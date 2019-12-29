#pragma once

#include<stdint.h>
#include<stdio.h>

class psr
{
public:
	uint32_t M : 5;
	uint32_t T : 1;
	uint32_t F : 1;
	uint32_t I : 1;
	uint32_t A : 1;
	uint32_t E : 1;
	uint32_t RESERVED0 : 6;
	uint32_t GE : 4;
	uint32_t RESERVED1 : 4;
	uint32_t J : 1;
	uint32_t RESERVED2 : 2;
	uint32_t Q : 1;
	uint32_t V : 1;
	uint32_t C : 1;
	uint32_t Z : 1;
	uint32_t N : 1;
public:
	static const uint8_t USR = 0b10000;
	static const uint8_t FIQ = 0b10001;
	static const uint8_t IRQ = 0b10010;
	static const uint8_t SVC = 0b10011;
	static const uint8_t ABT = 0b10111;
	static const uint8_t UND = 0b11011;
	static const uint8_t SYS = 0b11111;
public:
	psr(void)
	{
		reset();
	}
	inline operator uint32_t()
	{
		return *((uint32_t*)this);
	}
	inline uint32_t operator=(uint32_t value)
	{
		*((uint32_t*)this) = value;
		return value;
	}
	inline void reset(void)
	{
		N = 0;
		Z = 0;
		C = 0;
		V = 0;
		Q = 0;
		J = 0;
		GE = 0;
		E = 0;
		A = 0;

		I = 1;
		F = 1;

		T = 0;
		M = SYS;
	}
	inline bool check_cond(uint8_t cond)
	{
		switch (cond)
		{
			case  0:return check_EQ();
			case  1:return check_NE();
			case  2:return check_CS();
			case  3:return check_CC();
			case  4:return check_MI();
			case  5:return check_PL();
			case  6:return check_VS();
			case  7:return check_VC();
			case  8:return check_HI();
			case  9:return check_LS();
			case 10:return check_GE();
			case 11:return check_LT();
			case 12:return check_GT();
			case 13:return check_LE();
			case 14:return check_AL();
			default:return false;
		};
	}
	inline void print(void)
	{
		const char* mode_string[32] = { 0 };

#define SET_MODE_STRING(X) mode_string[X] = #X;
		SET_MODE_STRING(USR);
		SET_MODE_STRING(FIQ);
		SET_MODE_STRING(IRQ);
		SET_MODE_STRING(SVC);
		SET_MODE_STRING(ABT);
		SET_MODE_STRING(UND);
		SET_MODE_STRING(SYS);

		printf("N Z C V Q J E A I F T M\n");
		printf("%01u %01u %01u %01u %01u %01u %01u %01u %01u %01u %01u %s\n", N, Z, C, V, Q, J, E, A, I, F, T, mode_string[M]);
	}
private:
#define Z_SET	  (Z == 1)
#define Z_CLEAR	  (Z == 0)
#define C_SET	  (C == 1)
#define C_CLEAR	  (C == 0)
#define N_SET	  (N == 1)
#define N_CLEAR	  (N == 0)
#define V_SET	  (V == 1)
#define V_CLEAR   (V == 0)
#define EQUAL_NV  (N == V)
#define NEQUAL_NV (N != V)

	inline bool check_EQ(void) { return Z_SET; }
	inline bool check_NE(void) { return Z_CLEAR; }
	inline bool check_CS(void) { return C_SET; }
	inline bool check_CC(void) { return C_CLEAR; }
	inline bool check_MI(void) { return N_SET; }
	inline bool check_PL(void) { return N_CLEAR; }
	inline bool check_VS(void) { return V_SET; }
	inline bool check_VC(void) { return V_CLEAR; }
	inline bool check_HI(void) { return C_SET and Z_CLEAR; }
	inline bool check_LS(void) { return C_CLEAR or Z_SET; }
	inline bool check_GE(void) { return EQUAL_NV; }
	inline bool check_LT(void) { return NEQUAL_NV; }
	inline bool check_GT(void) { return Z_CLEAR and EQUAL_NV; }
	inline bool check_LE(void) { return Z_SET or NEQUAL_NV; }
	inline bool check_AL(void) { return true; }
};
