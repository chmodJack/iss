#pragma once

class branch_and_exchange
{
public:
	uint32_t Rn : 4;
	uint32_t RESERVED0 : 24;
	uint32_t Cond : 4;
public:
	static const uint32_t SIGNATURE_MASK{ NBITS_MAXVALUE(24) << 4 };
	static const uint32_t SIGNATURE_CODE{ 0b100101111111111110001 << 4 };
public:
	void execute(iss& i)
	{
		if (false == i.cpsr().check_cond(Cond))
			return;
	}
};
