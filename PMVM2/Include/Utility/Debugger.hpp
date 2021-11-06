#pragma once
#include <stddef.h>
#include <stdarg.h>
#include <string>
#include <string.h>
#include "Console.hpp"

namespace Debug
{
	extern bool Enabled;

	void NewLine();
	void WriteNonFormatted(std::string text);
	void WriteNonFormatted(std::string text, ConsoleColor fg);
	void WriteLineNonFormatted(std::string text);
	void WriteLineNonFormatted(std::string text, ConsoleColor fg);

	void Write(std::string fmt, ...);
	void WriteLine(std::string fmt, ...);

	void Header(std::string text, ConsoleColor fg);

	void Info(std::string fmt, ...);
	void OK(std::string fmt, ...);
	void Warning(std::string fmt, ...);
	void Error(std::string fmt, ...);
}