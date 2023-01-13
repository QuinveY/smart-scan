#include "Python.h"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;



PyStatus init_python(const char* program_name) {
    PyStatus status;

    PyConfig config;
    PyConfig_InitPythonConfig(&config);

    /* Set the program name before reading the configuration
       (decode byte string from the locale encoding).

       Implicitly preinitialize Python. */
    status = PyConfig_SetBytesString(&config, &config.program_name, program_name);
    if (PyStatus_Exception(status)) {
        goto done;
    }

    /* Read all configuration at once */
    status = PyConfig_Read(&config);
    if (PyStatus_Exception(status)) {
        goto done;
    }

    /* Append our custom search path to sys.path */
    status = PyWideStringList_Append(&config.module_search_paths, L"../pythonTest/inc/python-3.10.9-embed-amd64/python310.zip");
    if (PyStatus_Exception(status)) {
        goto done;
    }

    /* Override executable computed by PyConfig_Read() */
    status = PyConfig_SetString(&config, &config.executable, L"../pythonTest/inc/python-3.10.9-embed-amd64");
    if (PyStatus_Exception(status)) {
        goto done;
    }

    status = Py_InitializeFromConfig(&config);

done:
    PyConfig_Clear(&config);
    return status;
}


int main() {
	cout << "Directory we're in: " << current_path() << endl << endl;
	
	init_python("smartscan");

    PyRun_SimpleString("import sys\n");
   
    PyRun_SimpleString("print(sys.executable)\n");
    	
	Py_Finalize();


    cout << endl << endl; 
    system("pause");
    return 0;
}