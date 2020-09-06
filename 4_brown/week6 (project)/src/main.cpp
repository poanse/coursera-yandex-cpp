#include "tests.h"
#include "run.h"

int main() {
	RunTests();
	//Run(std::cin, std::cout);
	RunJson(std::cin, std::cout);
}
