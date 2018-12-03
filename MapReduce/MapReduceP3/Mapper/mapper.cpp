#include <iostream>

int main(int argc, char * argv[]) {

	std::cout << "child process created\n";
	for (int i = 0; i < argc; i++) {
		auto tmp = argv[i];
		std::cout << tmp<<"\n";
	}
	return 0;
}