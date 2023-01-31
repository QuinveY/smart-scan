#include <iomanip>
#include <iostream>
#include <simpleble/Utils.h>
#include <string> 

namespace SimpleBLE {

OperatingSystem get_operating_system() {
#ifdef _WIN32
    return OperatingSystem::WINDOWS;
#elif __APPLE__
    return OperatingSystem::MACOS;
#elif __linux__
    return OperatingSystem::LINUX;
#endif
}

}  // namespace SimpleBLE

void Utils::print_byte_array(const SimpleBLE::ByteArray& bytes) {
    for (auto b : bytes) {
        std::cout << std::dec << (uint32_t)((uint8_t)b);
       
    }
    std::cout << std::endl;
}

std::optional<std::size_t> Utils::getUserInputInt(const std::string& line, std::size_t max) {
    std::size_t ret;

    while (!std::cin.eof()) {
        std::cout << line << " (0-" << max << "): ";
        std::cin >> ret;

        if (!std::cin) {
            return {};
        }

        if (ret <= max) {
            return ret;
        }
    }
    return {};
}

std::optional<SimpleBLE::Adapter> Utils::getAdapter() {
    if (!SimpleBLE::Adapter::bluetooth_enabled()) {
        std::cout << "\t\t\tBluetooth is not enabled!" << std::endl;
        return {};
    }

    auto adapter_list = SimpleBLE::Adapter::get_adapters();

    // no adapter found
    if (adapter_list.empty()) {
        std::cerr << "\t\t\tNo adapter was found." << std::endl;
        return {};
    }

    // only one found, returning directly
    if (adapter_list.size() == 1) {
        auto adapter = adapter_list.at(0);
        std::cout << "\t\t\tUsing adapter: " << adapter.identifier() << " [" << adapter.address() << "]" << std::endl;
        return adapter;
    }

    // multiple adapters found, ask user to select one
    std::cout << "\t\t\tAvailable adapters:" << std::endl;
    int i = 0;
    for (auto& adapter : adapter_list) {
        std::cout << "\t\t\t[" << i++ << "] " << adapter.identifier() << " [" << adapter.address() << "]" << std::endl;
    }

    auto adapter_selection = Utils::getUserInputInt("\t\t\tSelect an adapter", adapter_list.size() - 1);

    if (!adapter_selection.has_value()) {
        return {};
    }

    return adapter_list[adapter_selection.value()];
}
