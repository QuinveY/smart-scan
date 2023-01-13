// C-Python_Collab-Test.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "C-Python_Collab-Test.h"

// Uncomment for debug mode
#define DEBUG

int main(int argc, char* argv[]) {
	
	#ifdef DEBUG
		cout << "Directory we're in: " << current_path() << endl << endl;
	#endif

	// Plugin folder naming
	path pluginFolder = "."; // start from .exe folder location
	pluginFolder /= "plugins";

	// Check for files in the pluginfolder
	vector<string> fileList = pluginFilesList(pluginFolder, "files"); 
	



	/*CPyInstance hInstance;

	CPyObject pName = PyUnicode_FromString("test");
	CPyObject pModule = PyImport_Import(pName);
	CPyObject pFunc = PyObject_GetAttrString(pModule, (char*)"test");
	CPyObject pValue = PyObject_CallFunction(pFunc, NULL);*/

	/*auto result = _PyUnicode_AsString(pValue);
	std::cout << result << std::endl;*/
	


	cout << endl << endl;
	system("pause");
	return 0;
}


/// <summary>
/// Lists all files in the directory
/// </summary>
/// <param name="fileLpluginFolderocation">Directory location to look for plugin files</param>
/// <param name="fileName">Name of the text file to save the list into</param>
vector<string> pluginFilesList(path pluginFolder, string fileName) {
	//ofstream file;
	
	// Append .txt as filetype
	//fileName += ".txt";

	vector<string> filesFound;

	// Check if folder exists
	folderCheck(pluginFolder);

	// Check if file exists
	// txtFileCheck(pluginFolder, fileName);

	// List all files from the plugin folder in the file
	try {
		// Create a full path string
		//path filePath = pluginFolder / fileName;

		// file.open(filePath);

		for (const auto& entry : directory_iterator(pluginFolder)) {	// loop through all files in this folder
			#ifdef DEBUG
				cout << "Found file: " << entry.path() << endl;
			#endif
			
			if (entry.path().extension() == ".py") {					// check for python files
				#ifdef DEBUG
					cout << "Saving file: " << entry.path() << endl;
				#endif

				filesFound.push_back(entry.path().string());
				//file << entry.path() << endl;							// save the found file
			}
			if (entry.path().extension() == ".r") {						// check for R files
				#ifdef DEBUG
					cout << "Saving file: " << entry.path() << endl;
				#endif

				filesFound.push_back(entry.path().string());
				//file << entry.path() << endl;							// save the found file
			}
		}

		#ifdef DEBUG
			cout << "Files found: " << endl;
			for (int i = 0; i < filesFound.size(); i++) {
				cout << filesFound[i] << endl;
			}
		#endif

		return filesFound;
		//file.close();
	}
	catch (filesystem_error const& e) {
		cout << endl << "Error: " << e.what() << endl;
	}

	return filesFound;
}

/// <summary>
/// Checks if the folder exists, if not it creates it
/// </summary>
/// <param name="folderPath"></param>
/// <returns>true when succeeded
/// false when failed</returns>
bool folderCheck(path folderPath) {
	// Try to find the folder's location
	try {
		if (!exists(folderPath)) { // if not exist
			#ifdef DEBUG
				cout << "Plugin folder does not exist, creating it now" << endl;
			#endif
			create_directory(folderPath); // create folder
		}
		else {
			#ifdef DEBUG
				cout << "Plugin folder exist, continuing" << endl;
			#endif
		}
		return true;
	}
	catch (filesystem_error e) {
		cout << endl << "Error: " << e.what() << endl;
		return false;
	}
}

/// <summary>
/// Checks if a textfile exists, if not it creates it
/// </summary>
/// <param name="fileFolder"></param>
/// <param name="fileName"></param>
/// <returns>true when succeeded
/// false when failed</returns>
bool txtFileCheck(path fileFolder, string fileName) {
	ofstream file;

	// Create a full path string
	path filePath = fileFolder / fileName;

	// Check if file exists
	if (!exists(filePath)) {
		#ifdef DEBUG
			cout << "File does not exist, creating it now" << endl;
		#endif

		try {
			file.open(filePath); // Create the file

			file << "newStuff\n";
			return true;
		}
		catch (filesystem_error const& e) {
			cout << endl << "Error: " << e.what() << endl;
		}
	}
	else {
		#ifdef DEBUG
			cout << "File \"" << fileName << "\" exists, continuing" << endl;
		#endif

		try {
			file << "goodstuff";
			return true;
		}
		catch (filesystem_error const& e) {
			cout << endl << "Error: " << e.what() << endl;
		}
	}

	#ifdef DEBUG
		cout << filePath << endl;
	#endif
	return false;
}