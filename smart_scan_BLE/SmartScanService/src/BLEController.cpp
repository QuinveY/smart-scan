#include "../inc/BLEController.h"
#include <iostream>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>


using namespace SimpleBLE;
using namespace std::chrono_literals;

PressureSensors::PressureSensors() {
	
}

PressureSensors::~PressureSensors() {

}

int PressureSensors::ConnectToGlove(std::string macAddress) {
	bool foundMeas = false;
	bool foundSpeed = false;

	// Check if a usuable adapter is present
	std::optional<Adapter> adapter_optional = Utils::getAdapter();

	// Return error incase no adapter has been assigned
	if (!adapter_optional.has_value()) {
		std::cout << "\t\t\tError: no bluetooth adapters have been found.";
		return EXIT_FAILURE;
	}

	// Save the adapter
	adapter = adapter_optional.value();
	std::vector<SimpleBLE::Peripheral> peripherals;

	// Attach callback to automatically connect
	adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral foundPer) { peripherals.push_back(foundPer); });

	// Attach callbacks to the the start and stop scan functions
	//adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });
	// Scan for 5 seconds and return.
	adapter.scan_for(5000);
	while (adapter.scan_is_active()) { ; }

	for (size_t j = 0; j < peripherals.size(); j++) {
		// std::cout << "found device with name: " << peripherals[j].identifier() << " and address: [" << peripherals[j].address() << "]" << std::endl;
		// Check if the found device has a matching MAC address
		if (strncmp(peripherals[j].address().c_str(), macAddress.c_str(), peripherals[j].address().size()) == 0) {
			peripheral = peripherals[j];
		}
		// Or if the name is the same as the expected name, if there isn't already a glove found
		else if (strncmp(peripherals[j].identifier().c_str(), GLOVE_NAME, 22) == 0 && strncmp(peripherals[j].address().c_str(), macAddress.c_str(), peripherals[j].address().size()) != 0) {
			peripheral = peripherals[j];
		}
	}

	if (peripheral.initialized()) {
		std::cout << "\t\t\tConnecting to " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
		peripheral.connect();

		if (peripheral.is_connected()) {
			std::cout << "\t\t\tSuccessfully connected to pressure glove" << std::endl;
		}

		// Store all service and characteristic uuids in a vector.
		std::vector<std::pair<BluetoothUUID, BluetoothUUID>> uuids;
		for (Service service : peripheral.services()) {
			for (Characteristic characteristic : service.characteristics()) {
				uuids.push_back(make_pair(service.uuid(), characteristic.uuid()));
			}
		}

		// List found characteristics and services
		for (size_t i = 0; i < uuids.size(); i++) {
			if (strncmp(uuids[i].second.c_str(), UUID_PRESSURE, 37) == 0) {
				measUUID.first = uuids[i].first;
				measUUID.second = uuids[i].second;
				foundMeas = true;
			}
			else if (strncmp(uuids[i].second.c_str(), UUID_SAMPLING, 37) == 0) {
				sampleSpeedUUID.first = uuids[i].first;
				sampleSpeedUUID.second = uuids[i].second;
				foundSpeed = true;
			}
		}
	}
	else {
		std::cout << "\t\t\tCould not connect to found device" << std::endl;
		return EXIT_FAILURE;
	}
	
	if (!foundMeas || !foundSpeed) {
		std::cout << "\t\t\tCould not find sampling speed or measurement characteristic." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

std::string PressureSensors::GetMacAddress(void) {
	// Return MAC address
	if (peripheral.is_connected()) {
		return peripheral.address();
	}
	// Return NULL if no glove is connected
	return std::string("NULL");
}

bool PressureSensors::IsConnected(void) {
	// Check if a glove is connected
	return peripheral.is_connected();
}

std::string PressureSensors::GetData(void) {
	// Read characteristic
	std::string dummy("[6666;666,666,666,666,666,666,666]");
	// return rx_data = peripheral.read(measUUID.first, measUUID.second);
	return dummy;
}

void PressureSensors::SetDelayInMillis(int delayInMillis) {
	std::string data = std::to_string(delayInMillis);
	peripheral.write_command(sampleSpeedUUID.first, sampleSpeedUUID.second, data);
}