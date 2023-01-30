#include "../inc/BLEController.h"

using namespace SimpleBLE;
using namespace std;

PressureSensors::PressureSensors() {
	
}

PressureSensors::~PressureSensors() {

}

int PressureSensors::Connect() {

	// Check if a usuable adapter is present
	optional<Adapter> adapter_optional = Utils::getAdapter();

	// Return error incase no adapter has been assigned
	if (!adapter_optional.has_value()) {
		cout << "Error: no bluetooth adapters have been found.";
		return EXIT_FAILURE;
	}

	// Save the adapter
	adapter = adapter_optional.value();

	// Attach callback tp when a peripheral has been found
	vector<Peripheral> peripherals;

	// Attach callbacks to the the start and stop scan functions
	adapter.set_callback_on_scan_start([]() { cout << "Scan started." << endl; });
	adapter.set_callback_on_scan_stop([]() { cout << "Scan stopped." << endl; });
	// Scan for 5 seconds and return.
	adapter.scan_for(5000);

	// List the devices
	cout << "The following devices were found:" << endl;
	for (size_t i = 0; i < peripherals.size(); i++) {
		cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]" << endl;
	}

	// Request which device needs to be connected too
	optional<size_t> selection = Utils::getUserInputInt("Please select a device to connect to", peripherals.size() - 1);
	if (!selection.has_value()) {
		return EXIT_FAILURE;
	}

	//Save and connected to the selected peripheral
	pressureGlove = peripherals[selection.value()];
	cout << "Connecting to " << pressureGlove.identifier() << " [" << pressureGlove.address() << "]" << endl;
	pressureGlove.connect();

	cout << "Successfully connected, printing services and characteristics.." << endl;

	// Store all service and characteristic uuids in a vector.
	vector<pair<BluetoothUUID, BluetoothUUID>> uuids;
	for (Service service : pressureGlove.services()) {
		for (Characteristic characteristic : service.characteristics()) {
			uuids.push_back(make_pair(service.uuid(), characteristic.uuid()));
		}
	}

	// List found characteristics and services
	cout << "The following services and characteristics were found:" << endl;
	for (size_t i = 0; i < uuids.size(); i++) {
		cout << "[" << i << "] " << uuids[i].first << " " << uuids[i].second << endl;
	}

	selection = Utils::getUserInputInt("Please select a characteristic to read", uuids.size() - 1);

	if (!selection.has_value()) {
		return EXIT_FAILURE;
	}

	measUUID.first = uuids[selection.value()].first;
	measUUID.second = uuids[selection.value()].second;

	return EXIT_SUCCESS;
}

int PressureSensors::Connect(std::string macAddress)
{
	return 0;
}

void PressureSensors::OffsetCalibration(int index)
{
	// Read characteristic
	// Compare all differences
	// Save the one with the largest difference

}

string PressureSensors::GetData(void)
{
	// Read characterisitc
	return 0;
}

int PressureSensors::GetLatestPoint(int index)
{
	// Read characteristic
	// Split up received string
	// Remove calibrated offset
	return 0;
}

vector<int> PressureSensors::GetLatestPoint(const vector<int> indeces)
{
	// Read characteristic
	// Split up received string
	// Remove calibrated offset
	return vector<int>();
}
