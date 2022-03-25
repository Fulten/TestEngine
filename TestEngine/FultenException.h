#pragma once

class FultenException : public std::exception
{
private:
	std::string message;
	const unsigned int line;
	std::string file;
	std::string description;

public:
	// accepts a c_string
	FultenException(const char* message, int line, const char* filename) noexcept :
		line(line),
		message(message),
		file(filename),
		description("none") {}

	// extended constructor accepts a description
	FultenException(const char* message, int line, const char* filename, const char* desc) noexcept :
		line(line),
		message(message),
		file(filename),
		description(desc) {}

	// accepts a hresult instead of a c_string
	FultenException(HRESULT message, int line, const char* filename) noexcept :
		line(line),
		file(filename),
		description("none")
	{ this->message = std::system_category().message(message); }

	// extended constructor accepts a description
	FultenException(HRESULT message, int line, const char* filename, HRESULT desc) noexcept :
		line(line),
		file(filename)
	{ this->message = std::system_category().message(message);
	  this->description = std::system_category().message(desc); }

	~FultenException() {}
	FultenException() = delete;

	// returns message as a std::string
	std::string getMessage() { return message; }

	// returns message as a std::wstring
	std::wstring getMessageW() 
	{ return std::wstring(message.begin(), message.end());}
	// returns the line the error was thrown at
	int getLine() { return line; }

	// returns the file name as a string
	std::string getFile()
	{ return file; }

	// returns the file name as a wstring
	std::wstring getFileW()
	{ return std::wstring(file.begin(), file.end()); }

	// returns file description as a string
	std::string getDesc()
	{ return description; }

	// returns file description as a wstring
	std::wstring getDescW()
	{ return std::wstring(description.begin(), description.end()); }


};