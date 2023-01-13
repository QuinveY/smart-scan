#pragma once

#define PY_SSIZE_T_CLEAN
#include "pyhelper.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;


/// <summary>
/// Lists all files in the directory
/// </summary>
/// <param name="pluginFolder">Directory location to look for plugin files</param>
/// <param name="fileName">Name of the text file to save the list into</param>
vector<string> pluginFilesList(path pluginFolder, string fileName);


/// <summary>
/// Checks if the folder exists, if not it creates it
/// </summary>
/// <param name="folderPath"></param>
/// <returns>true when succeeded
/// false when failed</returns>
bool folderCheck(path folderPath);


bool txtFileCheck(path fileFolder, string fileName);