#pragma once

#include<stdint.h>
#include<stdio.h>
#include"psr.hpp"

class iss
{
private:
	uint32_t reg_r0;
	uint32_t reg_r1;
	uint32_t reg_r2;
	uint32_t reg_r3;
	uint32_t reg_r4;
	uint32_t reg_r5;
	uint32_t reg_r6;
	uint32_t reg_r7;
	uint32_t reg_r8;
	uint32_t reg_r9;
	uint32_t reg_r10;
	uint32_t reg_r11;
	uint32_t reg_r12;

	uint32_t reg_r13;
	uint32_t reg_r14;
	uint32_t reg_r15;
	psr reg_cpsr;

	//svc mode
	uint32_t reg_r13_svc;
	uint32_t reg_r14_svc;
	psr reg_spsr_svc;

	//irq mode
	uint32_t reg_r13_irq;
	uint32_t reg_r14_irq;
	psr reg_spsr_irq;

	//fiq mode
	uint32_t reg_r13_fiq;
	uint32_t reg_r14_fiq;
	psr reg_spsr_fiq;

	//abt mode
	uint32_t reg_r13_abt;
	uint32_t reg_r14_abt;
	psr reg_spsr_abt;

	//und mode
	uint32_t reg_r13_und;
	uint32_t reg_r14_und;
	psr reg_spsr_und;

	uint32_t reg_r8_fiq;
	uint32_t reg_r9_fiq;
	uint32_t reg_r10_fiq;
	uint32_t reg_r11_fiq;
	uint32_t reg_r12_fiq;
private:
	uint32_t* reg_array[18]
	{
		&reg_r0,
		&reg_r1,
		&reg_r2,
		&reg_r3,
		&reg_r4,
		&reg_r5,
		&reg_r6,
		&reg_r7,
		&reg_r8,
		&reg_r9,
		&reg_r10,
		&reg_r11,
		&reg_r12,
		&reg_r13,
		&reg_r14,
		&reg_r15,
		(uint32_t*)(&reg_cpsr),
		nullptr
	};
public:
	void relocate_reg_array(void)
	{
		if (reg_cpsr.M == psr::FIQ)
		{
			reg_array[8] = &reg_r8_fiq;
			reg_array[9] = &reg_r9_fiq;
			reg_array[10] = &reg_r10_fiq;
			reg_array[11] = &reg_r11_fiq;
			reg_array[12] = &reg_r12_fiq;
		}
		else
		{
			reg_array[8] = &reg_r8;
			reg_array[9] = &reg_r9;
			reg_array[10] = &reg_r10;
			reg_array[11] = &reg_r11;
			reg_array[12] = &reg_r12;
		}

		switch (reg_cpsr.M)
		{
			case psr::SVC:
			{
				reg_array[13] = &reg_r13_svc;
				reg_array[14] = &reg_r14_svc;
				reg_array[17] = (uint32_t*)(&reg_spsr_svc);
			}; break;
			case psr::ABT:
			{
				reg_array[13] = &reg_r13_abt;
				reg_array[14] = &reg_r14_abt;
				reg_array[17] = (uint32_t*)(&reg_spsr_abt);
			}; break;
			case psr::UND:
			{
				reg_array[13] = &reg_r13_und;
				reg_array[14] = &reg_r14_und;
				reg_array[17] = (uint32_t*)(&reg_spsr_und);
			}; break;
			case psr::IRQ:
			{
				reg_array[13] = &reg_r13_irq;
				reg_array[14] = &reg_r14_irq;
				reg_array[17] = (uint32_t*)(&reg_spsr_irq);
			}; break;
			case psr::FIQ:
			{
				reg_array[13] = &reg_r13_fiq;
				reg_array[14] = &reg_r14_fiq;
				reg_array[17] = (uint32_t*)(&reg_spsr_fiq);
			}; break;
			default:
			{
				reg_array[13] = &reg_r13;
				reg_array[14] = &reg_r14;
				reg_array[17] = nullptr;
			}; break;
		}
	}
	inline uint32_t& index_reg(uint8_t index)
	{
		return *(reg_array[index]);
	}
public:
	iss(void)
	{
		reset();
	}
	void reset(void)
	{
		reg_r0 = 0;
		reg_r1 = 0;
		reg_r2 = 0;
		reg_r3 = 0;
		reg_r4 = 0;
		reg_r5 = 0;
		reg_r6 = 0;
		reg_r7 = 0;
		reg_r8 = 0;
		reg_r9 = 0;
		reg_r10 = 0;
		reg_r11 = 0;
		reg_r12 = 0;
		reg_r13 = 0;
		reg_r14 = 0;
		reg_r15 = 0;

		reg_cpsr.reset();

		reg_r13_svc = 0;
		reg_r14_svc = 0;
		reg_spsr_svc = 0;

		reg_r13_irq = 0;
		reg_r14_irq = 0;
		reg_spsr_irq = 0;

		reg_r8_fiq = 0;
		reg_r9_fiq = 0;
		reg_r10_fiq = 0;
		reg_r11_fiq = 0;
		reg_r12_fiq = 0;
		reg_r13_fiq = 0;
		reg_r14_fiq = 0;
		reg_spsr_fiq = 0;

		reg_r13_abt = 0;
		reg_r14_abt = 0;
		reg_spsr_abt = 0;

		reg_r13_und = 0;
		reg_r14_und = 0;
		reg_spsr_und = 0;
	}
	void print(void)
	{
#define PRINT(X) printf(#X": %08X\n", X());
		PRINT(r0);
		PRINT(r1);
		PRINT(r2);
		PRINT(r3);
		PRINT(r4);
		PRINT(r5);
		PRINT(r6);
		PRINT(r7);
		PRINT(r8);
		PRINT(sb);
		PRINT(sl);
		PRINT(fp);
		PRINT(ip);
		PRINT(sp);
		PRINT(lr);
		PRINT(pc);
		cpsr().print();
		printf("\n\n");
#undef PRINT
	}
public:
	void execute(uint32_t ins);
public:
	inline uint32_t& r0(void) { return *reg_array[0]; }
	inline uint32_t& r1(void) { return *reg_array[1]; }
	inline uint32_t& r2(void) { return *reg_array[2]; }
	inline uint32_t& r3(void) { return *reg_array[3]; }
	inline uint32_t& r4(void) { return *reg_array[4]; }
	inline uint32_t& r5(void) { return *reg_array[5]; }
	inline uint32_t& r6(void) { return *reg_array[6]; }
	inline uint32_t& r7(void) { return *reg_array[7]; }
	inline uint32_t& r8(void) { return *reg_array[8]; }
	inline uint32_t& r9(void) { return *reg_array[9]; }
	inline uint32_t& r10(void) { return *reg_array[10]; }
	inline uint32_t& r11(void) { return *reg_array[11]; }
	inline uint32_t& r12(void) { return *reg_array[12]; }
	inline uint32_t& r13(void) { return *reg_array[13]; }
	inline uint32_t& r14(void) { return *reg_array[14]; }
	inline uint32_t& r15(void) { return *reg_array[15]; }
	inline psr& cpsr(void) { return *((psr*)reg_array[16]); }
	inline psr& spsr(void) { return *((psr*)reg_array[17]); }

	inline uint32_t& sb(void) { return *reg_array[9]; }
	inline uint32_t& sl(void) { return *reg_array[10]; }
	inline uint32_t& fp(void) { return *reg_array[11]; }
	inline uint32_t& ip(void) { return *reg_array[12]; }
	inline uint32_t& sp(void) { return *reg_array[13]; }
	inline uint32_t& lr(void) { return *reg_array[14]; }
	inline uint32_t& pc(void) { return *reg_array[15]; }

	inline uint32_t& a1(void) { return *reg_array[0]; }
	inline uint32_t& a2(void) { return *reg_array[1]; }
	inline uint32_t& a3(void) { return *reg_array[2]; }
	inline uint32_t& a4(void) { return *reg_array[3]; }
	inline uint32_t& v1(void) { return *reg_array[4]; }
	inline uint32_t& v2(void) { return *reg_array[5]; }
	inline uint32_t& v3(void) { return *reg_array[6]; }
	inline uint32_t& v4(void) { return *reg_array[7]; }
	inline uint32_t& v5(void) { return *reg_array[8]; }
	inline uint32_t& v6(void) { return *reg_array[9]; }
	inline uint32_t& v7(void) { return *reg_array[10]; }
	inline uint32_t& v8(void) { return *reg_array[11]; }
};

#include"instructions.hpp"

void iss::execute(uint32_t ins)
{
#define MATCH_AND_EXECUTE(X) if ((ins & X::SIGNATURE_MASK) == X::SIGNATURE_CODE) { static X temp; *((uint32_t*)(&temp)) = ins; temp.execute(*this); } return;

	MATCH_AND_EXECUTE(data_processing);
	MATCH_AND_EXECUTE(branch);
	MATCH_AND_EXECUTE(branch_and_exchange);

	printf("instruction not implement or undefined\n"); return;
}