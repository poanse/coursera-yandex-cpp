#include "tests.h"
#include "run.h"
#include <string>

int main(int argc, char **argv) {
	if (argc == 2) {
		auto parameter = std::string(argv[1]);
		if (parameter == "-test") {
			RunTests();
			return 0;
		} else if (parameter == "-run") {
			RunJson(std::cin, std::cout);
			return 0;
		} else {
			std::cout << "Unknown parameter\n";
		}
	} else if (argc == 1) {
		std::cout << "No parameters given: add \"-test\" to run tests or \"-run\" to run program\n";
	} else {
		std::cout << "Too many parameters given\n";
	}
}
