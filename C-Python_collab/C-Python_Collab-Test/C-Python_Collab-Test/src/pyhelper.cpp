#include "pyhelper.h"

/// <summary>
/// Sets up embedded Python module
/// </summary>
/// <param name="program_name">Name of the program</param>
/// <returns></returns>
PyStatus init_python(const char* program_name) {
	PyStatus status;

	PyConfig config;
	PyConfig_InitPythonConfig(&config);

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

	/* Append our standard packages search path to sys.path */
	status = PyWideStringList_Append(&config.module_search_paths, L"../pythonTest/inc/python-3.10.9-embed-amd64/python310");
	if (PyStatus_Exception(status)) {
		goto done;
	}

	/* Append our custom packages search path to sys.path */
	status = PyWideStringList_Append(&config.module_search_paths, L"../pythonTest/inc/python-3.10.9-embed-amd64/Lib/site-packages");
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