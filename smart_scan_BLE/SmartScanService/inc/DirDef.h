#pragma once

#include <filesystem>
#include <fstream>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~Directory Definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define DIR_FILTER_PLUGINS			"./plugins/"
#define DIR_CONFIG					"./configs/"
#define DIR_SETTINGS				"./configs/settings.ini"
#define DIR_TEMP					"./temp/"
#define DIR_SCANS					"./scans/"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INI sections~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define SECTION_SYSTEM				"system"
#define SECTION_SENSOR				"sensor"
#define SECTION_BLE					"bluetooth"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INI parameters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define PARAM_SYS_TRANS_ID			"transmitterID"
#define PARAM_SYS_MEAS_RATE			"measurementRate"
#define PARAM_SYS_PWR_LINE_FREQ		"powerLineFreq"
#define PARAM_SYS_MAX_RANGE			"maxRangeInch"

#define PARAM_SNSR_REF_SERIAL		"referenceSerial"
#define PARAM_SNSR_THUMB_SERIAL		"thumbSerial"
#define PARAM_SNSR_INDEX_SERIAL		"indexSerial"
#define PARAM_SNSR_MIDDLE_SERIAL	"middleSerial"
#define PARAM_SNSR_AZIMUTH_OFFSET	"offsetAzimuth"
#define PARAM_SNSR_ELEVATION_OFFSET	"offsetElevation"
#define PARAM_SNSR_ROLL_OFFSET		"offsetRoll"

#define PARAM_BLE_THUMB_INDEX		"thumbIndex"
#define PARAM_BLE_INDEX_INDEX		"indexIndex"
#define PARAM_BLE_MIDDLE_INDEX		"middleIndex"
#define PARAM_BLE_MAC_ADDR			"MAC"