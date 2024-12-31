#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

// Function to load attack signatures
std::unordered_map<std::string, std::string> loadSignatures() {
    std::unordered_map<std::string, std::string> signatures;
    signatures["SQL Injection"] = "SELECT.*FROM.*WHERE.*=.*;";
    signatures["XSS"] = "<script>.*</script>";
    signatures["Brute Force"] = "Failed login attempt";
    return signatures;
}

// Function to scan log files for suspicious activity
void scanLogs(const std::string& fileName, const std::unordered_map<std::string, std::string>& signatures) {
    std::ifstream logFile(fileName);
    if (!logFile.is_open()) {
        std::cerr << "Error: Unable to open log file." << std::endl;
        return;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(logFile, line)) {
        lineNum++;
        for (const auto& entry : signatures) {
            std::regex pattern(entry.second);
            if (std::regex_search(line, pattern)) {
                std::cout << "[ALERT] " << entry.first << " detected on line " << lineNum << ": " << line << std::endl;
            }
        }
    }

    logFile.close();
}

int main() {
    std::cout << "Welcome to the Simple Intrusion Detection System (IDS)\n";

    // Load attack signatures
    auto signatures = loadSignatures();

    // Ask user for log file name
    std::string logFileName;
    std::cout << "Enter the name of the log file to scan: ";
    std::cin >> logFileName;

    // Scan the log file
    scanLogs(logFileName, signatures);

    std::cout << "Scanning completed.\n";
    return 0;
}