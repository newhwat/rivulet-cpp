#pragma once

#include <string>
#include <optional>
#include <vector>
#include <cctype>

/* Simple Lexer for .rw extension */
/* Eventually want to create a parser to do this all automatically */
/* Need to do research on this*/

/* For creating the different tokens */
enum class TokenType {
    _return,
    int_lit,
    semicol
};

/* Token Objects */
struct Token {
    TokenType tokenType; // define the type of token
    std::optional<std::string> value {}; // using optional to indicate it doesn't have to have a value
};

/* Creating Tokens from file */
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;

    std::string currentToken;

    for (char c: input) {
        /* Adding if keyword is a word -- keeps going until word is fully read */
        if (std::isalpha(c)) {
            currentToken += c;
        }
        /* Check what keyword it is */
        else {
            if (currentToken == "bounce" || currentToken == "stream") {
                tokens.push_back({TokenType::_return, std::nullopt}); // Add the token to token vector with no value
            } 
            currentToken.clear(); // Move to next token
        }

        if (std::isdigit(c)) {
            currentToken += c;
        } else {
            tokens.push_back({TokenType::int_lit, currentToken});
            currentToken.clear();
        }

        if (c == ';') {
            tokens.push_back({TokenType::semicol, std::nullopt});
        }
    }

}
