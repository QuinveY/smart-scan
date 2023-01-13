#include "Python.h"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;


int main() {
	std::cout << "Directory we're in: " << current_path() << endl << endl;
	
	//std::cout << PYTHONHOME << endl;

	Py_SetPath();
	Py_Initialize();

	Py_Finalize();
}