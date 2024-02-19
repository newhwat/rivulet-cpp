#include <iostream>
#include <fstream>
#include <sstream>

#include "tokenization.h"


std::string tokens_to_asm(const std::vector<Token>& tokens) {
    std::stringstream output;
    output << "global _start\nstart:\n";
    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);
        
        /* Checking that there is exit, value, and semicol to end*/
        if (token.tokenType == TokenType::exit) {
            if(i + 1 < tokens.size() && tokens.at(i+1).tokenType == TokenType::int_lit) {
                if (i + 2 < tokens.size() && tokens.at(i+2).tokenType == TokenType::semicol) {
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens.at(i+1).value.value() << "\n";
                    output << "    syscall";
                }
            }
        }
    }
    return output.str();
}


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
    //std::cout << "File contents: " << contents << std::endl;

    // Move contents to tokenizer
    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();

    {
        std::fstream file("out.asm", std::ios_base::out);
        file << tokens_to_asm(tokens);
    }
    //std::cout << "test";
    system("nasm -felf64 out.asm");
    system("ld -o out out.o");


    return EXIT_SUCCESS;
}