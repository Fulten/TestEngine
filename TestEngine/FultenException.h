#pragma once


class FultenException
{
private:
	std::string message;
	const unsigned int line;

public:
	// accepts a c string
	FultenException(char* message, int line) :
		line(line),
		message(message)
	{}
	// accepts an hresult
	FultenException(HRESULT message, int line) :
		line(line)
	{ this->message = std::system_category().message(message); }
	~FultenException()
	{}

	FultenException() = delete;

	// returns message as a std::string
	std::string getMessage()
	{ return message; }

	// returns message as a std::wstring
	std::wstring getMessageW()
	{ return std::wstring(message.begin(), message.end());}

	int getLine()
	{ return line; }

};