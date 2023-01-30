#include "pyhelper.h"

std::filesystem::path pythonLocation = std::filesystem::current_path() / ".." / "C-Python_Collab-Test" / "inc" / "python-3.10.9-embed-amd64";
std::filesystem::path moduleLocation = pythonLocation;

/// <summary>
/// Sets up embedded Python module
/// </summary>
/// <param name="program_name">Name of the program</param>
/// <returns></returns>
PyStatus init_python(const char* program_name) {
	PyStatus status;

	PyConfig config;
	PyConfig_InitIsolatedConfig(&config); // init the config settings, for default isolated mode

	/* Set the program name before reading the configuration
	   (decode byte string from the locale encoding).
	   Implicitly preinitialize Python. */
	status = PyConfig_SetBytesString(&config, &config.program_name, program_name);
	//Py_SetProgramName(L"python");
	if (PyStatus_Exception(status)) {
		goto done;
	}

	/* Read all configuration at once */
	status = PyConfig_Read(&config);
	if (PyStatus_Exception(status)) {
		goto done;
	}

	moduleLocation = pythonLocation / "python310";
	/* Append our standard packages search path to sys.path */
	status = PyWideStringList_Append(&config.module_search_paths, moduleLocation.generic_wstring().c_str()); //L"../C-Python_Collab-Test/inc/python-3.10.9-embed-amd64/python310"
	if (PyStatus_Exception(status)) {
		goto done;
	}

	moduleLocation = pythonLocation / "Lib" / "site-packages";
	/* Append our custom packages search path to sys.path */
	status = PyWideStringList_Append(&config.module_search_paths, moduleLocation.generic_wstring().c_str()); // L"../C-Python_Collab-Test/inc/python-3.10.9-embed-amd64/Lib/site-packages/"
	if (PyStatus_Exception(status)) {
		goto done;
	}
	
	/* Override executable computed by PyConfig_Read() */
	status = PyConfig_SetString(&config, &config.executable, pythonLocation.generic_wstring().c_str()); // L"../C-Python_Collab-Test/inc/python-3.10.9-embed-amd64"
	if (PyStatus_Exception(status)) {
		goto done;
	}

	//status = PyConfig_SetString(&config, &config.base_prefix, L"");

	// This initialises the Python interpreter, and prints 
	status = Py_InitializeFromConfig(&config);

done:
	PyConfig_Clear(&config);
	return status;
}