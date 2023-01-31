#pragma once

#include "pyHandler.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Point3.h"

using namespace std;
using namespace filesystem;
using namespace SmartScan;


/// <summary>
/// Lists all files in the directory
/// </summary>
/// <param name="fileLpluginFolderocation">Directory location to look for plugin files</param>
vector<string> pluginFilesList(path pluginFolder);

/// <summary>
/// Checks if the folder exists, if not it creates it
/// </summary>
/// <param name="folderPath"></param>
/// <returns>true when succeeded
/// false when failed</returns>
bool folderCheck(path folderPath);

/// <summary>
/// Checks if a textfile exists, if not it creates it
/// </summary>
/// <param name="fileFolder"></param>
/// <param name="fileName"></param>
/// <returns>true when succeeded
/// false when failed</returns>
bool txtFileCheck(path fileFolder, string fileName);

/// <summary>
/// Function to ask the user what filter to use, and returns the python modulename.
/// </summary>
/// <param name="filters"></param>
/// <param name="filePath"></param>
/// <returns>Chosen Python filter</returns>
string askUserWhatFilter(vector<string> filters, path filePath);