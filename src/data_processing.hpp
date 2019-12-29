#pragma once

class data_processing
{
public:
	uint32_t Operand2 : 12;
	uint32_t Rd : 4;
	uint32_t Rn : 4;
	uint32_t S : 1;
	uint32_t OpCode : 4;
	uint32_t I : 1;
	uint32_t RESERVED0 : 2;
	uint32_t Cond : 4;
public:
	static const uint32_t SIGNATURE_MASK{ NBITS_MAXVALUE(2) << 26 };
	static const uint32_t SIGNATURE_CODE{ 0b0 << 26 };
	void execute(iss& i)
	{
		print();

		if (i.cpsr().check_cond(Cond))
		{
			printf("[TRUE]\n");
			(this->*execute_funcs[OpCode])(i);
		}
		else
		{
			printf("[FALSE]\n");
			return;
		}
	}
private:
	void execute_AND(iss& i) {}
	void execute_EOR(iss& i) {}
	void execute_SUB(iss& i) {}
	void execute_RSB(iss& i) {}
	void execute_ADD(iss& i) {}
	void execute_ADC(iss& i) {}
	void execute_SBC(iss& i) {}
	void execute_RSC(iss& i) {}
	void execute_TST(iss& i) {}
	void execute_TEQ(iss& i) {}
	void execute_CMP(iss& i) {}
	void execute_CMN(iss& i) {}
	void execute_ORR(iss& i) {}
	void execute_MOV(iss& i) 
	{
		if (I)
			i.index_reg(Rd) = Operand2;
		else
			i.index_reg(Rd) = i.index_reg(Operand2);
	}
	void execute_BIC(iss& i) {}
	void execute_MVN(iss& i) {}
private:
	void (data_processing::* execute_funcs[16])(iss&) =
	{
		&data_processing::execute_AND,
		&data_processing::execute_EOR,
		&data_processing::execute_SUB,
		&data_processing::execute_RSB,
		&data_processing::execute_ADD,
		&data_processing::execute_ADC,
		&data_processing::execute_SBC,
		&data_processing::execute_RSC,
		&data_processing::execute_TST,
		&data_processing::execute_TEQ,
		&data_processing::execute_CMP,
		&data_processing::execute_CMN,
		&data_processing::execute_ORR,
		&data_processing::execute_MOV,
		&data_processing::execute_BIC,
		&data_processing::execute_MVN
	};
private:
	const char* opcode_string[16] =
	{
		"AND",
		"EOR",
		"SUB",
		"RSB",
		"ADD",
		"ADC",
		"SBC",
		"RSC",
		"TST",
		"TEQ",
		"CMP",
		"CMN",
		"ORR",
		"MOV",
		"BIC",
		"MVN"
	};
	void print(void)
	{
		printf("[%08x] <data_processing>(Cond:%s I:%u OpCode:%s S:%u Rn:%u Rd:%u Operand2:%u)\n", *((uint32_t*)(this)), cond_code_string[Cond], I, opcode_string[OpCode], S, Rn, Rd, Operand2);
	}
};

