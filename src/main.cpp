#include "debugger.cpp"
#include "CPU6502.cpp"
#include "bus.cpp"

int main (int argc, char *argv[])
{
	NESEmulatorDebugger debugger;
	debugger.Construct(680, 480, 2, 2);
	debugger.Start();

	return 0;
}
