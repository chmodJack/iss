#pragma once

class branch
{
public:
	uint32_t Offset : 24;
	uint32_t L : 1;
	uint32_t RESERVED0 : 3;
	uint32_t Cond : 4;
public:
	static const uint32_t SIGNATURE_MASK{ NBITS_MAXVALUE(3) << 25 };
	static const uint32_t SIGNATURE_CODE{ 0b101 << 25 };
public:
	void execute(iss& i)
	{
		if (false == i.cpsr().check_cond(Cond))
			return;

		i.pc() += ((int32_t)Offset) * 4;
	}
};