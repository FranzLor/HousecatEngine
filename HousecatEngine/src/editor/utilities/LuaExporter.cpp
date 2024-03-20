#include "LuaExporter.h"
#include <cassert>

LuaExporter::LuaExporter()
	: indent(0),
	newLine(false), 
	valueWritten(false),
	suppress(false),
	minimize(false),
	separator(',') {

}

void LuaExporter::WriteIndent(std::fstream& file) {
	for (int level = indent; level; level--) {
		Write("  ", file);
	}
}

void LuaExporter::WriteNewLine(std::fstream& file) {
	if (newLine) {
		return;
	}

	if (!minimize) {
		if (suppress) {
			Write(' ', file);
		}
		else {
			Write('\n', file);
			WriteIndent(file);
		}
	}

	newLine = true;
}

void LuaExporter::WriteNewValue(std::fstream& file) {
	if (!valueWritten) {
		WriteNewLine(file);
	}
	else {
		Write(separator, file);
		if (!minimize) {
			Write(' ', file);
		}
	}
}


void LuaExporter::StartDocument() {
	assert(indent = 0);
}

void LuaExporter::EndDocument(std::fstream& file) {
	assert(indent = 0);
	Write('\n', file);
}

void LuaExporter::SeparationLine(std::fstream& file) {
	Write("---------------", file);
	Write('\n', file);
}

void LuaExporter::CommentLine(const std::string& comment, std::fstream& file) {
	Write("-- ", file);
	Write('\n', file);
}

void LuaExporter::StartTable(std::fstream& file) {
	NewLine(file);

	Write('{', file);
	indent++;
	newLine = false;
	valueWritten = false;
}

void LuaExporter::DeclareTable(const std::string name, std::fstream& file) {
	NewLine(file);

	Write(name, file);
	Write(minimize ? "={" : " = {", file);
	indent++;
	newLine = false;
	valueWritten = false;
}

void LuaExporter::EndTable(std::fstream& file) {
	NewLine(file);

	indent--;
	if (valueWritten) {
		WriteNewLine(file);
	}
	Write('}', file);
	newLine = false;
	valueWritten = true;
}

void LuaExporter::EndTable(bool sameLine, std::fstream& file) {
	indent--;
	if (valueWritten && !sameLine) {
		WriteNewLine(file);
	}
	Write('}', file);
	newLine = false;
	valueWritten = true;
}

void LuaExporter::EndTableSeparation(bool sameLine, std::fstream& file) {
	indent--;
	if (valueWritten && !sameLine) {
		WriteNewLine(file);
	}
	Write('}', file);
	Write(separator, file);
	newLine = false;
	valueWritten = true;
}

void LuaExporter::NewLine(std::fstream& file) {
	if (valueWritten) {
		Write(separator, file);
		valueWritten = false;
	}
	WriteNewLine(file);
}

std::string LuaExporter::MakeQuote(const std::string& quote) {
	std::string quoted;

	quoted.reserve(quote.length() + 2);
	quoted += '"';

	for (const char c : quote) {
		switch (c) {
		case '\\':
			quoted.append("\\\\");
			break;

		case '"':
			quoted.append("\\\"");
			break;

		case '\n':
			quoted.append("\\n");
			break;

		default:
			quoted += c;
		}
	}

	quoted += '"';
	return quoted;
}