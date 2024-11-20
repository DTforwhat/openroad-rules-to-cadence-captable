#include <iostream>
#include <fstream>
#include <string>
#include  "WriteCaptable.h"

int main() {
    // Define the input file path and output file path
    std::string inputFilePath;
    std::string outputFilePath;

    // Ask the user for the input and output file paths
    std::cout << "Enter the path of the input file: ";
    std::getline(std::cin, inputFilePath);  
    // Read the input file path

    std::cout << "Enter the path for the output file: ";
    std::getline(std::cin, outputFilePath);  
    // Read the output file path

    // Open the input file for reading
    std::ifstream inputFile(inputFilePath);
    if (!inputFile) 
    {
        std::cerr << "Error opening input file: " << inputFilePath << std::endl;
        return 1;
    }

    // Open the output file for writing
    std::ofstream outputFile(outputFilePath);
    if (!outputFile) 
    {
        std::cerr << "Error opening output file: " << outputFilePath << std::endl;
        return 1;
    }

    // Read the input file line by line and write to the output file
    rtc::write_captable(&inputFile , &outputFile);

    // Close both files
    inputFile.close();
    outputFile.close();

    std::cout << "File transformed successful!" << outputFilePath << std::endl;

    return 0;
}
