#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;

std::string getTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto nowTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm localTm = *std::localtime(&nowTimeT);

    std::ostringstream oss;
    oss << std::put_time(&localTm, "%Y-%m-%d-%H-%M-%S");
    return oss.str();
}

void processFolder(const fs::path &folderPath, std::ofstream &outputFile)
{
    for (const auto &entry : fs::recursive_directory_iterator(folderPath))
    {
        if (fs::is_directory(entry))
        {
            outputFile << "DIR: " << entry.path().string() << "\n";
        }
        else if (fs::is_regular_file(entry))
        {
            outputFile << "FILE: " << entry.path().string()
                       << " | SIZE: " << fs::file_size(entry) << " bytes\n";
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <folder_path> <output_file>\n";
        return 1;
    }

    fs::path folderPath(argv[1]);
    std::string outputFileName = argv[2];

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath))
    {
        std::cerr << "Folder does not exist\n";
        return 1;
    }

    fs::path logsFolder = "watchdog-logs";
    if (!fs::exists(logsFolder))
    {
        fs::create_directory(logsFolder);
    }

    // OUTPUT FILE
    std::string timestamp = getTimestamp();
    std::string fullOutputFileName = logsFolder / (timestamp + "-" + outputFileName);

    std::ofstream outputFile(fullOutputFileName);
    if (!outputFile)
    {
        std::cerr << "Failed to open " << fullOutputFileName << " for writing\n";
        return 1;
    }

    std::cout << "Processing folder: " << folderPath << "\n";
    processFolder(folderPath, outputFile);
    std::cout << "Report saved to " << fullOutputFileName << "\n";

    return 0;
}
