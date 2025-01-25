#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

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
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <folder_path>\n";
        return 1;
    }

    fs::path folderPath(argv[1]);

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath))
    {
        std::cerr << "Folder does not exist\n";
        return 1;
    }

    // OUTPUT FILE
    std::string outputFileName = "reporte-de-integridad.txt";
    std::ofstream outputFile(outputFileName);

    if (!outputFile)
    {
        std::cerr << "Failed to open " << outputFileName << " for writing\n";
        return 1;
    }

    std::cout << "Processing folder: " << folderPath << "\n";
    processFolder(folderPath, outputFile);
    std::cout << "Report saved to " << outputFileName << "\n";

    return 0;
}
