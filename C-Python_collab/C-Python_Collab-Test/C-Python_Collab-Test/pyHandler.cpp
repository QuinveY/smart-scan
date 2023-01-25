#include "pyHandler.h"

// Uncomment for debug mode
#define DEBUG

int pyHandler(vector<string> pythonArgs, path pluginFolder) {
	PyObject* pName, * pModule, * pFunc;
	PyObject* pArgs, * pValue;
	int i;
	
	if (pythonArgs.size() < 3) { // Check for correct usage
		fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
		return 1;
	}

	//Py_Initialize();
	init_python("smartscan");
	
	PyObject* sysPath = PySys_GetObject((char*)"path"); // Add pluginfolder to path
	PyList_Append(sysPath, (PyUnicode_FromString(pluginFolder.string().c_str())));
	
	pName = PyUnicode_DecodeFSDefault(pythonArgs.at(0).c_str());
	/* Error checking of pName left out */

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, pythonArgs.at(1).c_str());
		/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(pythonArgs.size() - 2);
			for (i = 0; i < pythonArgs.size() - 2; ++i) {
				pValue = PyLong_FromLong(atoi(pythonArgs.at(i + 2).c_str()));

				#ifdef DEBUG
					cout << PyLong_Check(pValue) << endl;
					cout << PyLong_AsLong(pValue) << endl;
				#endif // DEBUG	

				if (!pValue) {
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert argument\n");
					return 1;
				}
				/* pValue reference stolen here: */
				PyTuple_SetItem(pArgs, i, pValue);
				#ifdef DEBUG
					cout << PyTuple_Check(pArgs) << endl;
					cout << PyLong_AsLong(PyTuple_GetItem(pArgs, i)) << endl;
				#endif // DEBUG
				Py_DECREF(pValue);
			}

			#ifdef DEBUG
				cout << "Printing a Tuple: " << endl;
				for (int j = 0; j < PyTuple_Size(pArgs); j++) {
					cout << PyLong_AsLong(PyTuple_GetItem(pArgs, j)) << endl;
				}
			#endif // DEBUG	

			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);

			#ifdef DEBUG
				cout << PyCallable_Check(pFunc) << endl;
				if (PyErr_Occurred()) {
					PyErr_PrintEx(0);
					PyErr_Clear(); // this will reset the error indicator so you can run Python code again
				}
				cout << PyLong_Check(pValue) << endl;
				cout << PyLong_AsLong(pValue) << endl;
			#endif // DEBUG	


			if (pValue != NULL) {
				printf("Result of call: %ld\n", PyLong_AsLong(pValue));
				Py_DECREF(pValue);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				return 1;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", pythonArgs.at(1).c_str());
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", pythonArgs.at(0).c_str());
		return 1;
	}
	if (Py_FinalizeEx() < 0) {
		return 120;
	}
	return 0;
}