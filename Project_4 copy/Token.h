#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <sstream>

enum class TokenType {
	COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
    COLON,
    COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	EOF_TYPE,
    // TODOne: add the other types of tokens
    UNDEFINED
};

class Token
{
private:
	TokenType type;
	std::string description;
	int line;
    // TODOne: add member variables for information needed by Token

public:
    Token(TokenType type, std::string description, int line);

	friend std::ostream& operator<< (std::ostream& os, const Token& token);

	std::string toString() const;

	std::string typeToString(TokenType strType) const;

	TokenType getTokenType() const;

	std::string getTokenString() const;


    // TODOne: add other needed methods
};

#endif // TOKEN_H

