// SmartScanService.cpp : This file contains the 'main' function. Program execution begins and ends here.
// This provides an interface for the SmartScanServices.

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include "SmartScanService.h"

using namespace std;
using namespace SmartScan;

// Glove setup
int rThumbSerial;								// Only used for setting reference points and ZOffsets calibration.
int rIndexSerial;								// Only used for setting reference points and ZOffsets calibration.
int rMiddleSerial;								// Only used for setting reference points and ZOffsets calibration.
int refSensorSerial = -1;						// Serial number of the reference sensor, set as -1 when no reference sensor is used.

// Data-acquisition configuration
short int transmitterID = 0;                    // Port of the transmitter, is usually 0 with one trakStar device.
double measurementRate = 250;                   // Between 20.0 and 255.0
double powerLineFrequency = 50.0;               // Either 50.0 or 60.0
double maximumRange = 36.0;                     // Either 36.0 (914,4 mm), 72.0 and 144.0.
double frameRotations[3] = { 0, 0, 0 };			// Set the rotation of the measurement frame, azimuth, elevation and roll. (0, 0, 0) is default. 

// Pre-define functions
void Usage();
void RawPrintCallback(const vector<SmartScan::Point3>& record);
int SensorIdentification(const char* sensorName);

// Create SmartScanService object
SmartScanService s3;
SmartScan::DataAcqConfig acquisitionConfig = { transmitterID, measurementRate, powerLineFrequency, maximumRange, refSensorSerial, frameRotations };

int main() {
	// Print welcome screen.
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "                /$$$$$$                                      /$$      /$$$$$$                               " << endl;
	cout << "               /$$__  $$                                    | $$     /$$__  $$                              " << endl;
	cout << "              | $$  \\__/ /$$$$$$/$$$$   /$$$$$$   /$$$$$$  /$$$$$$  | $$  \\__/  /$$$$$$$  /$$$$$$  /$$$$$$$ " << endl;
	cout << "              |  $$$$$$ | $$_  $$_  $$ |____  $$ /$$__  $$|_  $$_/  |  $$$$$$  /$$_____/ |____  $$| $$__  $$" << endl;
	cout << "               \\____  $$| $$ \\ $$ \\ $$  /$$$$$$$| $$  \\__/  | $$     \\____  $$| $$        /$$$$$$$| $$  \\ $$" << endl;
	cout << "               /$$  \\ $$| $$ | $$ | $$ /$$__  $$| $$        | $$ /$$ /$$  \\ $$| $$       /$$__  $$| $$  | $$" << endl;
	cout << "              |  $$$$$$/| $$ | $$ | $$|  $$$$$$$| $$        |  $$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$  | $$" << endl;
	cout << "               \\______/ |__/ |__/ |__/ \\_______/|__/         \\___/   \\______/  \\_______/ \\_______/|__/  |__/" << endl;
	cout << endl << "\t\t\t\t Changing orthopaedic footwear from an art to a science" << endl << endl << endl << endl;
	cout << endl << "\t\tInitializing..." << endl;

	// Initialise the service:
	try {
		s3.Init(acquisitionConfig);
		s3.RegisterRawDataCallback(RawPrintCallback);
	}
	catch (ex_trakStar e) {
		cerr << "\t\tException thrown in TrakStar initialization: " << endl << "\t\t- " << e.what() << endl;
	}
	catch (ex_acq e) {
		cerr << "\t\tException thrown in Data-acquisition initialization: " << endl << "\t\t- " << e.what() << endl;
	}
	catch (ex_scan e) {
		cerr << "\t\tException thrown in Scan initialization: " << endl << "\t\t- " << e.what() << endl;
	}
	catch (...)	{
		cerr << "\t\tUnknown exception. Could not initialise Smart Scan Service" << endl;
		return -1;
	}

	// Print general info.
	//cout << "\t\tApplication " << (mockMode ? "" : "not ") << "in mockmode" << endl;
	cout << "\t\tFound " << s3.NumAttachedBoards() << " attached board(s)" << endl; 
	cout << "\t\tFound " << s3.NumAttachedTransmitters() << " attached transmitter(s)" << endl; 
	cout << "\t\tFound " << s3.NumAttachedSensors(true) << " attached sensor(s)" << endl << endl << endl;

	// Print the help screen:
	cout << "Welcome to the SmartScan command line application! (Type help to see a full list of commands)" << endl;

	// Check if json files exist

	// Read serial numbers and compared them to the connected serial numbers

	// Run through sensor identification
	/*
	refSensorSerial = SensorIdentification("reference");
	rThumbSerial = SensorIdentification("thumb");
	rIndexSerial = SensorIdentification("index finger");
	rMiddleSerial = SensorIdentification("middle finger");
	*/

	rThumbSerial = 55435;						// Only used for setting reference points and ZOffsets calibration.
	rIndexSerial = 55429;						// Only used for setting reference points and ZOffsets calibration.
	rMiddleSerial = 55430;						// Only used for setting reference points and ZOffsets calibration.
	refSensorSerial = 55432;					// Serial number of the reference sensor, set as -1 when no reference sensor is used.

	// Save serial numbers
	s3.SensorSetup(refSensorSerial, rThumbSerial, rIndexSerial, rMiddleSerial);

	char cmd[128];
	do {

		// Print prompt.
		cout << "SmartScan>";

		// Wait for user input and store it in cmd.
		cin.getline(cmd, 128);

		// Create a new scan.
		if (!strcmp(cmd, "new")) {
			try {
				int numRefPoints;
				ScanConfig config;

				cout << "Welcome to the scan creation wizard!" << endl;
				cout << "Enter the number of desired reference points: " << flush;
				while (!(cin >> numRefPoints)) { // Make sure the user can only input numbers.
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input.  Try again: ";
				}
				cin.ignore();

				cout << "Position the thumb and index finger around the reference point and press any key when ready.";
				for (int i = 0; i < numRefPoints; i++) { // Collect the same amount of reference points as specified earlier.
					cin.ignore();
					Point3 PointThumb = s3.GetSingleSample(rThumbSerial);
					Point3 PointIndex = s3.GetSingleSample(rIndexSerial);
					Point3 refPoint;

					// Average every coordinate to get the point in between the two fingers.
					refPoint.x = ((PointThumb.x + PointIndex.x) / 2);
					refPoint.y = ((PointThumb.y + PointIndex.y) / 2);
					refPoint.z = ((PointThumb.z + PointIndex.z) / 2);

					config.refPoints.push_back(refPoint);
					cout << "Reference point number " << i << " set at (" << refPoint.x << ',' << refPoint.y << ',' << refPoint.z << ").";
				}

				cout << endl << "Enter the desired filtering precision (180 needs to be a multiple): " << flush;
				while (!(cin >> config.filteringPrecision)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input.  Try again: ";
				}
				cin.ignore();

				try {
					s3.NewScan(config);
					cout << "New scan created" << endl;
				}
				catch (ex_smartScan e) {
					cerr << e.what() << " Thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
			}
			catch (ex_trakStar e) {
				cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
			}
			catch (ex_acq e) {
				cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
			}
			catch (ex_smartScan e) {
				cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
			}
			catch (ex_scan e) {
				cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
			}
		}
		// Calibrate the sensor offset with respect to the glove and finger t h i c c n e s s.
		// This function probably still needs adjustsments or a better implementation.
		else if (!strcmp(cmd, "calibrate")) {
			try {
				cout << "Put your hand on the table of the transmitter and press enter when ready." << flush;
				cin.ignore();

				s3.CorrectZOffset(rThumbSerial);
				s3.CorrectZOffset(rIndexSerial);
				s3.CorrectZOffset(rMiddleSerial);

				cout << "New offset calculated succesfully!" << endl;
			}
			catch (ex_trakStar e) {
				cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
			}
			catch (ex_acq e) {
				cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
			}
		}
		// Print 1 point of all sensors
		else if (!strcmp(cmd, "highest")) {
			int serial = s3.HighestSensor();
		}
		// List all the created scans and its options.
		else if (!strcmp(cmd, "list")) {
			cout << "Scan ID\t\tNumRefs\t\tPrecision\tStopAt" << endl;//\t\tThreshold" << endl;

			for (int s = 0; s < s3.GetScansList().size(); s++) {
				cout << s3.GetScansList().at(s)->mId << "\t\t" << s3.GetScansList().at(s)->NumRefPoints() << "\t\t" << s3.GetScansList().at(s)->GetFilteringPrecision() << "\t\t";
				cout << s3.GetScansList().at(s)->GetStopAtSample() << endl;  //<< "\t\t" << s3.GetScansList().at(s)->GetOutlierThreshold() << endl;
			}
		}
		// Print the help menu.
		else if (!strcmp(cmd, "help")) {
			Usage();
		}
		// Clear all recorded data.
		else if (!strcmp(cmd, "clear")) {
			s3.ClearData();
			cout << "All data cleared!" << endl;
		}
		// These commands are only allowed when there is a scan created
		else if (s3.NumOfScans() > 0) {
			// Start collecting data.
			if (!strcmp(cmd, "start")) {
				try {
					s3.StartScan();

					// Print legend.
					cout << setw(4) << "Sec" << setw(4) << "But";

					for (int i = 0; i < s3.NumAttachedSensors(false); i++) {
						cout << setw(4) << 'X' << i << setw(4) << 'Y' << i << setw(4) << 'Z' << i;
					}
					cout << endl;
				}
				catch (ex_acq e) {
					cerr << e.what() << " Thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
				catch (ex_smartScan e) {
					cerr << e.what() << " Thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
				catch (ex_scan e) {
					cerr << e.what() << " Thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
				catch (...) {
					cerr << "Unnable to start the scan due to an unknow error. \n";
				}
			}
			// Start collecting data for specific scan.
			else if (strlen(cmd) > 6 && !strncmp(cmd, "start ", 6)) {
				// Get the id from the comand:
				string sCmd = cmd;

				// Find the space in the string
				uint32_t idIndex = sCmd.find(' ', 0);

				//Convert the string between the spaces into a number
				int id = atoi(sCmd.substr((idIndex + 1)).c_str());

				try {
					s3.StartScan(id);

					// Print legend.
					cout << setw(4) << "Sec" << setw(4) << "But" << setw(4) << 'X' << setw(4) << 'Y' << setw(4) << 'Z' << endl;
				}
				catch (ex_acq e) {
					cerr << e.what() << " Thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
				catch (ex_smartScan e) {
					cerr << e.what() << " Thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
				catch (ex_scan e) {
					cerr << e.what() << " Thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
				catch (...) {
					cerr << "Unnable to start the scan due to an unknow error. \n";
				}
			}
			// Stop collecting data.
			else if (!strcmp(cmd, "stop")) {
				s3.StopScan();
				cout << "All scans have stopped!" << string(70, ' ') << endl;
			}
			// Stop collecting data for a specific scan.
			else if (strlen(cmd) > 5 && !strncmp(cmd, "stop ", 5)) {
				// Get the id from the comand:
				string sCmd = cmd;
				// Find the space in the string
				uint32_t idIndex = sCmd.find(' ', 0);

				//Convert the string between the spaces into a number
				int id = atoi(sCmd.substr((idIndex + 1)).c_str());

				if( s3.StopScan(id) ) {
					cout << "Scan " << id << " has stopped!" << string(70, ' ') << endl;
				}
				else {
					cout << "Scan " << id << " has not been found!" << string(70, ' ') << endl;
				}
			}
			// Set the max amount of samples number, at which a scan would stop scanning
			else if (strlen(cmd) > 7 && !strncmp(cmd, "scan-size ", 10)) {
				// Get the id and size from the comand:
				string sCmd = cmd;

				// Find the space in the string
				uint32_t idIndex = sCmd.find(' ', 0);
				uint32_t sizeIndex = sCmd.find(' ', idIndex + 1);

				//Convert the string between the spaces into a number
				int id = atoi(sCmd.substr((idIndex + 1), (sizeIndex - idIndex + 1)).c_str());
				int size = atoi(sCmd.substr((sizeIndex + 1)).c_str());

				if (sCmd.c_str()[idIndex] == ' ' && sCmd.c_str()[sizeIndex] == ' ') {
					try {
						s3.SetStopSample(size, id);
						cout << "Max number of samples of scan " << id << " is set to: " << size << endl;
					}
					catch (ex_smartScan e) {
						cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
					}
				}
				else {
					cout << "Missing id and/or new sample size" << endl;
				}
			}
			// Delete all the scans.
			else if (!strcmp(cmd, "delete")) {
				char ack[128];
				cout << "Are you sure you want to delete all? answer y/n: ";
				cin.getline(ack, 128);

				if (!strncmp(ack, "y", 1)) {
					try {
						s3.DeleteScan();
						cout << "Deleted all scans!" << endl;
					}
					catch (ex_smartScan e) {
						cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
					}
				}
			}
			// Delete a specific scan.
			else if (strlen(cmd) > 7 && !strncmp(cmd, "delete ", 7)) {
				// Get the id from the comand:
				string sCmd = cmd;
				// Find the space in the string
				uint32_t idIndex = sCmd.find(' ', 0);

				//Convert the string between the spaces into a number
				int id = atoi(sCmd.substr((idIndex + 1)).c_str());

				try {
					s3.DeleteScan(id);
					cout << "Scan " << id << " has been deleted" << endl;
				}
				catch (ex_smartScan e) {
					cerr << e.what() << " thrown in function " << e.get_function() << " in file " << e.get_file() << endl;
				}
			}
			// Export x,y,z of specific scan.
			else if (strlen(cmd) > 7 && !strncmp(cmd, "export ", 7)) {
				// Get the id from the comand:
				string sCmd = cmd;
				sCmd.shrink_to_fit();

				uint32_t idIndex = sCmd.find(' ', 0);
				uint32_t nameIndex = sCmd.find(' ', idIndex + 1);
				int id = atoi(sCmd.substr((idIndex + 1), (nameIndex - idIndex + 1)).c_str());

				// Cut the filepath out:
				string filepath = sCmd.substr((nameIndex + 1), sCmd.max_size());
				cout << "exporting filtered data from scan: " << id << " into file: " << filepath << endl;

				try {
					s3.ExportPointCloud(filepath + ".csv", id);
					cout << "Done.\n";
				}
				catch (ex_export e) {
					cerr << e.what() << endl;
				}
				catch (...) {
					cerr << "Could not export csv file" << endl;
				}
			}
			// Export all data of a specific scan.
			else if (strlen(cmd) > 12 && !strncmp(cmd, "full-export ", 12)) {
				// Get the id from the comand:
				string sCmd = cmd;
				sCmd.shrink_to_fit();

				uint32_t idIndex = sCmd.find(' ', 0);
				uint32_t nameIndex = sCmd.find(' ', idIndex + 1);
				int id = atoi(sCmd.substr((idIndex + 1), (nameIndex - idIndex + 1)).c_str());

				// Cut the filepath out:
				string filepath = sCmd.substr((nameIndex + 1), sCmd.max_size());
				cout << "exporting raw data from scan: " << id << " into file: " << filepath << endl;

				try {
					s3.ExportCSV(filepath + ".csv", id);
					cout << "Done.\n";
				}
				catch (ex_export e) {
					cerr << e.what() << endl;
				}
				catch (...) {
					cerr << "Could not export csv file" << endl;
				}
			}
			// Export x,y,z raw data (except for the reference sensor) without any filtering, but with reference sensor correction.
			else if (strlen(cmd) > 11 && !strncmp(cmd, "export-raw ", 11)) {
				// Get the id from the comand:
				string sCmd = cmd;
				sCmd.shrink_to_fit();

				uint32_t nameIndex = sCmd.find(' ', 0);

				// Cut the filepath out:
				string filepath = sCmd.substr((nameIndex + 1), sCmd.max_size());
				cout << "Exporting raw data into file: " << filepath << endl;

				try {
					s3.ExportPointCloud(filepath + ".csv", 0, true);
					cout << "Done.\n";
				}
				catch (ex_export e) {
					cerr << e.what() << endl;
				}
				catch (...) {
					cerr << "Could not export csv file" << endl;
				}
			}
			// Export all raw data (except for the reference sensor) without any filtering, but with reference sensor correction.
			else if (strlen(cmd) > 16 && !strncmp(cmd, "full-export-raw ", 16)) {
				// Get the id from the comand:
				string sCmd = cmd;
				sCmd.shrink_to_fit();

				uint32_t nameIndex = sCmd.find(' ', 0);

				// Cut the filepath out:
				string filepath = sCmd.substr((nameIndex + 1), sCmd.max_size());
				cout << "Exporting raw data into file: " << filepath << endl;

				try {
					s3.ExportCSV(filepath + ".csv", 0, true);
					cout << "Done.\n";
				}
				catch (ex_export e) {
					cerr << e.what() << endl;
				}
				catch (...) {
					cerr << "Could not export csv file" << endl;
				}
			}
		}
		// Incase of an unknown command
		else {
			cout << "Command not recognized or unavailable, retry or type \"help\" to see all available commands." << endl;
		}
	} while (strcmp(cmd, "exit"));	// Exit the application.
}

// Help menu.
void Usage()
{
	cout << endl;
	cout << "\tCommand" << "\t\t\t\t" << "Description" << endl;
	cout << "\t*start [id]\t\t\tStart the measurement. Leave id blank to start all scans." << endl;
	cout << "\t*stop [id]\t\t\tStop the measurement. Leave id blank to stop all scans." << endl;
	cout << "\tnew\t\t\t\tCreate a new measurement." << endl;
	cout << "\tcalibrate\t\t\tCalibrate the sensor offsets with respect to finger t h i c c n e s s." << endl;
	cout << "\t*scan-size [id] [size]\t\tSet the max amount of samples to be measured." << endl << "\t\t\t\t\tScanning will stop at this number of samples (-1 for infite duration)." << endl;
	cout << "\tclear\t\t\t\tClear all recorded data." << endl;
	cout << "\t*delete [id]\t\t\tDelete a measurement. Leave id blank to delete all scans" << endl << "\t\t\t\t\t" << "and clear the raw data." << endl;
	cout << "\tlist\t\t\t\tPrint all the existing Scans to the console." << endl;
	cout << "\t*export [id] [filename]\t\tExport the filtered data of the scan id as a CSV file with" << endl << "\t\t\t\t\tthe given filename (no spaces allowed in filename)." << endl << "\t\t\t\t\tIncludes: x, y, z." << endl;
	cout << "\t*full-export [id] [filename]\tExport the filtered data of the scan id as a CSV file with" << endl << "\t\t\t\t\tthe given filename (no spaces allowed in filename)." << endl << "\t\t\t\t\tIncludes: time, x, y, z, roll, elevation, azimuth, quality" << endl << "\t\t\t\t\t\t  and button state." << endl;
	cout << "\t*export-raw [filename]\t\tExport the raw data of all the sensors as a CSV file with" << endl << "\t\t\t\t\tthe given filename (no spaces allowed in filename)." << endl << "\t\t\t\t\tIncludes: x, y, z." << endl;
	cout << "\t*full-export-raw [filename]\tExport the raw data of all the sensors as a CSV file with" << endl << "\t\t\t\t\tthe given filename (no spaces allowed in filename)." << endl << "\t\t\t\t\tIncludes: time, x, y, z, roll, elevation, azimuth, quality " << endl << "\t\t\t\t\t\t  and button state." << endl;
	cout << "\thelp \t\t\t\tPrint this screen again." << endl;
	cout << "\texit \t\t\t\tCleanly exit the application." << endl;
	cout << endl;
	cout << "\t* \t\t\t\tCommand is only allowed to be run when at least 1 scan is created with \"new\"" << endl;
	cout << endl;
}

// Function that is called everytime a new set of samples has been collected.
void RawPrintCallback(const vector<SmartScan::Point3>& record)
{
	cout << '\r'; // Set cursor to the beginning of the line to prevent messy couts.
	// All data is casted to an int so that the amount of characters that are going to be printed are predictable and concise.
	// This is important since you can only rewrite over the current line, so all sensor data needs to be printed on one line.
	cout << setw(4) << (int)record[0].time;
	cout << setw(4) << (int)record[0].buttonState;

	for (int i = 0; i < record.size(); i++) {
		cout << setw(5) << (int)record[i].x;
		cout << setw(5) << (int)record[i].y;
		cout << setw(5) << (int)record[i].z;
	}
	cout << ' ' << '\r' << flush;
}

int SensorIdentification(const char* sensorName) {
	char input[128];

	cout << "Is there a " << sensorName << " sensor (y/n) > " << flush;
	do {
		cin.getline(input, 128);
		if (strncmp(input, "y", 1) == 0 || strncmp(input, "Y", 1) == 0) {
			cout << "Please hold up the " << sensorName << " sensor and hit enter when ready." << flush;
			cin.ignore(10, '\n');
			//Check which sensor is the highest
			int serial = s3.HighestSensor();
			cout << "Measured sensor ID " << serial << " which is: ";
			switch (serial) {
			case 55435:
				cout << "thumb sensor" << endl;
				break;
			case 55429:
				cout << "index sensor" << endl;
				break;
			case 55430:
				cout << "middle sensor" << endl;
				break;
			case 55432:
				cout << "reference sensor" << endl;
				break;
			default:
				cout << "unknown" << endl;
				break;
			}
			return serial;
		}
		else if (strncmp(input, "n", 1) == 0 || strncmp(input, "N", 1) == 0) {
			return -1;
		}
		else {
			cout << "Incorrect input please try again." << flush;
		}
	} while (true);
}