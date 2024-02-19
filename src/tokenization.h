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
    _exit,
    int_l,
    _semi
};

/* Token Objects */
struct Token {
    TokenType tokenType; // define the type of token
    std::optional<std::string> value {}; // using optional to indicate it doesn't have to have a value
};

/* Creating Tokens from file */
class Tokenizer{
public:
    inline explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    inline std::vector<Token> tokenize(){
        std::vector<Token> tokens;
        std::string cur_token;


        // Loop while value exists
        while(peek().has_value()) {
            if (std::isalpha(peek().value())) {
                //std::cout << "read word" << std::endl;
                cur_token.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    cur_token.push_back(consume());
                }
                if (cur_token == "bounce"){
                    tokens.push_back({TokenType::_exit });
                    cur_token.clear();
                    continue;
                }
                else {
                    std::cerr << "Error" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(peek().value())) {
                cur_token.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    cur_token.push_back(consume());
                }
                tokens.push_back({TokenType::int_l, cur_token});
                cur_token.clear();
                continue;
            }
            else if (peek().value() == ';') {
                consume();
                //std::cout << "read semicolon" << std::endl;
                tokens.push_back({TokenType::_semi});
                continue;
            }
            else if (std::isspace(peek().value())) {
                consume();
                continue;
            }
            else {
                std::cerr << "Error" << std::endl;
            }

            m_idx = 0;
            return tokens;

        }
    }
private:
    /* Member variables */
    const std::string m_src;
    int m_idx = 0;

    // Look at character
    [[nodiscard]] std::optional<char> peek(int ahead = 1) const {
        // If at end of file, return nothing
        if (m_idx + ahead > m_src.length()) {
            return std::nullopt;
        }
        else { // return next character
            return m_src.at(m_idx);
        }
    }

    // Consume character -- incrementing value
    char consume() {
        return m_src.at(m_idx++);
    }


};
