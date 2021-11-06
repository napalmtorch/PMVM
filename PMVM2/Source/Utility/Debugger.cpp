#include "Utility/Debugger.hpp"
#include "Utility/Console.hpp"
#include "Utility/StringUtil.hpp"

namespace Debug
{
	bool Enabled = false;

	void NewLine()
	{
		printf("\n");
	}

	void WriteNonFormatted(std::string text)
	{
		if (!Enabled) { return; }
		Console::Write(text);
	}

	void WriteNonFormatted(std::string text, ConsoleColor fg)
	{
		if (!Enabled) { return; }
		Console::Write(text, fg);
	}

	void WriteLineNonFormatted(std::string text)
	{
		if (!Enabled) { return; }
		Console::WriteLine(text);
	}

	void WriteLineNonFormatted(std::string text, ConsoleColor fg)
	{
		if (!Enabled) { return; }
		Console::WriteLine(text, fg);
	}

	void Write(std::string fmt, ...)
	{
		if (!Enabled) { return; }
		va_list args;
		va_start(args, fmt);
		vprintf(fmt.c_str(), args);
		va_end(args);
	}

	void WriteLine(std::string fmt, ...)
	{
		if (!Enabled) { return; }
		va_list args;
		va_start(args, fmt);
		vprintf(std::string(fmt + "\n").c_str(), args);
		va_end(args);
	}

	void Header(std::string text, ConsoleColor fg)
	{
		if (!Enabled) { return; }
		WriteNonFormatted("[", ConsoleColor::White);
		WriteNonFormatted(text, fg);
		WriteNonFormatted("] ", ConsoleColor::White);
	}

	void Info(std::string fmt, ...)
	{
		if (!Enabled) { return; }
		Header("  >>  ", ConsoleColor::Cyan);
		va_list args;
		va_start(args, fmt);
		vprintf(fmt.c_str(), args);
		va_end(args);
		NewLine();
	}

	void OK(std::string fmt, ...)
	{
		if (!Enabled) { return; }
		Header("  OK  ", ConsoleColor::Green);
		va_list args;
		va_start(args, fmt);
		vprintf(fmt.c_str(), args);
		va_end(args);
		NewLine();
	}

	void Warning(std::string fmt, ...)
	{
		if (!Enabled) { return; }
		Header("  ??  ", ConsoleColor::Yellow);
		va_list args;
		va_start(args, fmt);
		vprintf(fmt.c_str(), args);
		va_end(args);
		NewLine();
	}

	void Error(std::string fmt, ...)
	{
		if (!Enabled) { return; }
		Header("  !!  ", ConsoleColor::Red);
		va_list args;
		va_start(args, fmt);
		vprintf(fmt.c_str(), args);
		va_end(args);
		NewLine();
	}
}