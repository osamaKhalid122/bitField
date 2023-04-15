#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef union GpioPort
{
	struct PortBit {
		volatile unsigned int Bit0 : 1;
		volatile unsigned int Bit1 : 1;
		volatile unsigned int Bit2 : 1;
		volatile unsigned int Bit3 : 1;
		volatile unsigned int Bit4 : 1;
		volatile unsigned int Bit5 : 1;
		volatile unsigned int Bit6 : 1;
		volatile unsigned int Bit7 : 1;
	}PortBit;

	volatile unsigned int* Port;

}GpioPort;

volatile unsigned readPin(GpioPort* port, int BitNo)
{
	unsigned int value = 0;
	switch (BitNo)
	{
	case 0: {value = port->PortBit.Bit0; break;}
	case 1: {value = port->PortBit.Bit1; break;}
	case 2: {value = port->PortBit.Bit2; break;}
	case 3: {value = port->PortBit.Bit3; break;}
	case 4: {value = port->PortBit.Bit4; break;}
	case 5: {value = port->PortBit.Bit5; break;}
	case 6: {value = port->PortBit.Bit6; break;}
	case 7: {value = port->PortBit.Bit7; break;}
	}
	return value;
}


void writePin(GpioPort* port, int BitNo, int value)
{
	switch (BitNo)
	{
	case 0: {port->PortBit.Bit0 = value; break;}
	case 1: {port->PortBit.Bit1 = value; break;}
	case 2: {port->PortBit.Bit2 = value; break;}
	case 3: {port->PortBit.Bit3 = value; break;}
	case 4: {port->PortBit.Bit4 = value; break;}
	case 5: {port->PortBit.Bit5 = value; break;}
	case 6: {port->PortBit.Bit6 = value; break;}
	case 7: {port->PortBit.Bit7 = value; break;}
	}
}

void writePort(GpioPort* port, int value)
{
	port->Port = (unsigned int*)calloc(1, sizeof(unsigned int));
	if(port->Port)
		*(port->Port) = value;
}

unsigned int readPort(GpioPort* port)
{
	int value;
	value = *(port->Port);
	return value;
}


int main()
{
	volatile GpioPort* PortA = (GpioPort*)calloc(1, sizeof(GpioPort));
	volatile GpioPort* PortB = (GpioPort*)calloc(1, sizeof(GpioPort));
	unsigned int valuePortB;
	if (PortB)
	{
		printf("Address of structure Port Bit is %p\n", &(PortB->PortBit));
		printf("Address of unsigned int Port is %p\n", &(PortB->Port));
	}
	unsigned int valueBit1 = 0, valueBit3 = 0, valueBit2 = 0;

	if (PortA != NULL)
	{
		writePin(PortA, 1, 1);
		writePin(PortA, 2, 1);

		valueBit1 = readPin(PortA, 1);
		valueBit2 = readPin(PortA, 2);
		valueBit3 = readPin(PortA, 3);
	}
	else
		printf("Calloc is a null pointer");

	printf("Value of Bit 1 is %d\n", valueBit1);
	printf("Value of Bit 2 is %d\n", valueBit2);
	printf("Value of Bit 3 is %d\n", valueBit3);


	writePort(PortB, 0x68);

	valuePortB = readPort(PortB);

	printf("Value PortB %d", valuePortB);
	return 0;
}
