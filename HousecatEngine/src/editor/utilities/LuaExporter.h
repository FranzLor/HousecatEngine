#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//-----------------------------------------------------//
//                    LuaExporter                      //
//  Utility class for exporting data to Lua scripts.   //
//  It allows structured writing of Lua tables and     //
//  supports features like indentation, comments,      //
//  minimizing output, and suppression of certain      //
//  format features for compact file generation.       //
//-----------------------------------------------------//


class LuaExporter {
private:
	int indent;
	char separator;

	bool newLine;
	bool valueWritten;
	bool minimize;
	bool suppress;

	void WriteIndent(std::fstream& file);

	void WriteNewLine(std::fstream& file);

	void StartNewValue(std::fstream& file);

	template <typename T>
	void Write(const T value, std::fstream& file);

public:
	LuaExporter();
	~LuaExporter() = default;

	void StartDocument();

	void EndDocument(std::fstream& file);

	void SeparationLine(std::fstream& file);

	void CommentLine(const std::string& comment, std::fstream& file);

	void StartTable(std::fstream& file);

	void DeclareTable(const std::string name, std::fstream& file);
	
	void EndTable(std::fstream& file);
	void EndTable(bool sameLine, std::fstream& file);

	void EndTableSeparation(bool sameLine, std::fstream& file);

	void StartNewLine(std::fstream& file);

	std::string MakeQuote(const std::string& quote);

	inline void SetSupress(bool suppress) {
		this->suppress = suppress;
	}
	
	inline const bool IsSuppressed() const {
		return suppress;
	}

	inline void SetMinimize(bool minimize) {
		this->minimize = minimize;
	}

	inline const bool IsMinimized() const {
		return minimize;
	}

	template <typename TValue> void WriteValue(TValue value, std::fstream& file, bool indent = false);
	template <typename TValue> void WriteWords(TValue value, std::fstream& file, bool indent = false);
	template <typename TName> void WriteStartTable(TName name, bool quoted, std::fstream& file);
	template <typename TValue> void WriteUnquotedValue(TValue value, std::fstream& file);
	template <typename TValue> void WriteUnquotedValue(TValue value, bool newLine, std::fstream& file);
	template <typename TKey, typename TValue> void WriteQuotedKeyAndValue(TKey key, TValue value, std::fstream& file);
	template <typename TKey, typename TValue> void WriteKeyAndValue(TKey key, TValue value, std::fstream& file);
	template <typename TKey, typename TValue> void WriteKeyAndValue(TKey key, TValue value, bool finalValue, std::fstream& file);
	template <typename TKey, typename TValue> void WriteKeyAndUnquotedValue(TKey key, TValue value, std::fstream& file, bool sameLine = false, bool lastValue = false);
	template <typename TKey, typename TValue> void WriteKeyAndQuotedValue(TKey key, TValue value, std::fstream& file, bool finalValue = false);
};



template <typename T>
void LuaExporter::Write(const T value, std::fstream& fileName) {
	fileName << value;
}

template <typename TValue>
void LuaExporter::WriteValue(TValue value, std::fstream& file, bool indent) {
	WriteUnquoatedValue(value, file);
	
	if (indent) {
		this->indent++;
	}
}

template <typename TValue>
void LuaExporter::WriteWords(TValue value, std::fstream& file, bool indent) {
	file << value;
	
	if (indent) {
		this->indent++;
	}
}

template <typename TName>
void LuaExporter::WriteStartTable(TName name, bool quoted, std::fstream& file) {
	StartNewLine(file);
	Write('[', file);
	
	if (quoted) {
		std::cout << "quoted" << std::endl;
	}
	else {
		Write(name, file);
	}

	Write(minimize ? "]={" : "] = {", file);
	indent++;

	newLine = false;
	valueWritten = false;
}

template <typename TValue> 
void LuaExporter::WriteUnquotedValue(TValue value, std::fstream& file) {
	StartNewValue(file);

	Write(value, file);
	newLine = false;
	valueWritten = true;
}

template <typename TValue>
void LuaExporter::WriteUnquotedValue(TValue value, bool newLine, std::fstream& file) {
	if (newLine) {
		StartNewValue(file);
	}

	Write(value, file);
	this->newLine = newLine;
	valueWritten = true;
}

template <typename TKey, typename TValue> 
void LuaExporter::WriteQuotedKeyAndValue(TKey key, TValue value, std::fstream& file) {
	StartNewValue(file);

	Write('[', file);
	Write(Quote(key), file);
	Write(minimize ? "]=" : "] = ", file);
	Write(value, file);
}

template <typename TKey, typename TValue> 
void LuaExporter::WriteKeyAndValue(TKey key, TValue value, std::fstream& file) {
	StartNewLine(file);

	Write(' ', file);
	Write(key, file);
	Write(minimize ? "=" : " = ", file);
	Write('"', file);
	Write(value, file);

	newLine = false;
	valueWritten = true;
}

template <typename TKey, typename TValue>
void LuaExporter::WriteKeyAndValue(TKey key, TValue value, bool finalValue, std::fstream& file) {
	Write(' ', file);
	Write(key, file);
	Write(minimize ? "=" : " = ", file);
	Write(value, file);

	if (!finalValue) {
		Write(separator, file);
	}
	
	newLine = false;
	valueWritten = true;
}

template <typename TKey, typename TValue>
void LuaExporter::WriteKeyAndUnquotedValue(TKey key, TValue value, std::fstream& file, bool sameLine, bool lastValue) {
	if (!sameLine) {
		StartNewLine(file);
	}

	Write(key, file);
	Write(minimize ? "=" : " = ", file);
	Write(value, file);

	if (sameLine && !lastValue) {
		Write(separator, file);
	}

	newLine = false;
	valueWritten = true;
}

template <typename TKey, typename TValue> 
void LuaExporter::WriteKeyAndQuotedValue(TKey key, TValue value, std::fstream& file, bool finalValue) {
	StartNewLine(file);

	Write(key, file);
	Write(minimize ? "=" : " = ", file);
	Write(MakeQuote(value), file);

	if (!finalValue) {
		Write(separator, file);
	}

	newLine = false;
	valueWritten = true;
}




/**
 * @file LuaExporter.h
 * @brief Utility class for exporting structured data to Lua script format.
 *
 * The LuaExporter class offers a structured way to write data into Lua table
 * format, which can be particularly useful for game settings, level designs, or
 * any application that uses Lua for configuration. This class provides methods
 * to handle different types of data input, support for indentation, line breaks,
 * minimizing text output, and suppression of optional format features.
 *
 * Key Features:
 * - Writing key-value pairs in Lua table format.
 * - Support for nested tables.
 * - Options to minimize output and suppress certain formatting features.
 * - Methods to handle comments and separators for readability.
 *
 * Usage:
 * - Use `StartDocument` and `EndDocument` to manage document bounds.
 * - `WriteValue`, `WriteKeyAndValue`, etc., to write data.
 * - Control format with `SetMinimize` and `SetSupress`.
 * 
 * Examples:
 * - luaExporter.StartDocument();
 * - luaExporter.SeparationLine(projectFile);
 * - luaExporter.CommentLine("", projectFile);
 * 
 */