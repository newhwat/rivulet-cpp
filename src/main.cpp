#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char* argv[]) {

    /* Improper Use Case*/
    if (argc != 2) {
        std::cerr << "Incorrect Usage. Use..." << std::endl;
        std::cerr << "rivulet <input.rw>" << std::endl;
        return EXIT_FAILURE;
    }

    /* File Reading*/
    std::string filePath = argv[1];
    std::fstream inputFile(filePath, std::ios_base::in);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return EXIT_FAILURE;
    }
    std::stringstream fileBuffer;
    fileBuffer << inputFile.rdbuf();
    inputFile.close();
    

    
    /* FILE CONTENTS */
    std::string contents = fileBuffer.str();
    std::cout << "File contents: " << contents << std::endl;

    return EXIT_SUCCESS;
}