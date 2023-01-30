#pragma once

#include "pyhelper.h"
#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

int pyHandler(vector<string> pythonArgs, path pluginFolder);