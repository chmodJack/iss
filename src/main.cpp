#include<stdio.h>
#include<stdint.h>

#include"iss.hpp"

int main(int argc, char* argv[])
{
	iss i;

	i.execute(0xe3a000e9); i.print();
	i.execute(0xe3a010fe); i.print();
	i.execute(0xe1a02001); i.print();

	return 0;
}
