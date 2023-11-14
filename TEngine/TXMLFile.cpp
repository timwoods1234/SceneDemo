#include "TXMLFile.h"
#include "TError.h"
#include "TXMLStream.h"
#include "TStringBuilder.h"

//-------------------------------------------------------------------------------
TXMLFile::TXMLFile()
:	m_currentIndex(0),
	m_error(false)
{
}

//-------------------------------------------------------------------------------
TXMLFile::TXMLFile(const char* filename)
:	m_currentIndex(0),
	m_error(false)
{
	Read(filename);
}

//-------------------------------------------------------------------------------
TXMLFile::~TXMLFile()
{
}

//-------------------------------------------------------------------------------
bool TXMLFile::WasError() const
{
	return m_error;
}

//-------------------------------------------------------------------------------
void TXMLFile::Read(const char* filename)
{
	TXMLStream stream;

	if (!stream.OpenRead(filename))
	{
		m_error = true;
	}

	if (!m_error)
	{
		while (!stream.EndOfFile())
		{
			ParseLine(stream.ReadString());
		}
	}
}

//-------------------------------------------------------------------------------
void TXMLFile::Rewind()
{
	m_currentIndex  = 0;
}

//-------------------------------------------------------------------------------
bool TXMLFile::HasMoreAttributes() const
{
	return m_currentIndex < m_data.GetSize();
}

//-------------------------------------------------------------------------------
const TXMLAttribute& TXMLFile::GetNextAttribute()
{
	TASSERT( (HasMoreAttributes()), "[TXMLFile::GetNextAttribute] No more attributes");

	m_currentIndex++;
	return m_data[m_currentIndex - 1];
}

//-------------------------------------------------------------------------------
void TXMLFile::ParseElementStart(const TString& line)
{
	int endIndex = line.IndexOf(' ');
	int startIndex = line.IndexOf('<');

	if (endIndex == -1)
	{
		endIndex = line.IndexOf('/');

		if (endIndex == startIndex + 1)
		{
			// end of a pair, the start tag should already have been added
			return;
		}
		else if (endIndex == -1)
		{
			endIndex = line.IndexOf('>');
		}
	}

	if (endIndex != -1)
	{
		TXMLAttribute elementStart;

		elementStart.type = TXMLAttribute::ElementStart;
		elementStart.id = line.SubString(startIndex + 1, endIndex - (startIndex + 1));

		m_data.Add(elementStart);
	}
	else
	{
		TASSERT(false, "[TXMLFile::ParseElementName] Bad line format");
	}
}

//-------------------------------------------------------------------------------
void TXMLFile::ParseElementEnd(const TString& line)
{
	int indexOfSlash = line.IndexOf('/');

	if (indexOfSlash == -1)
	{
		// start of a pair
		return;
	}

	int startIndex = line.IndexOf('<');
	int endIndex = -1;

	if (indexOfSlash == startIndex + 1)
	{
		endIndex = line.IndexOf('>');
		startIndex = indexOfSlash;
	}
	else
	{
		int indexOfSpace = line.IndexOf(' ');

		if (indexOfSpace != -1)
		{
			endIndex = indexOfSpace;
		}
		else
		{
			endIndex = indexOfSlash;
		}
	}

	TXMLAttribute elementEnd;

	elementEnd.type = TXMLAttribute::ElementEnd;
	elementEnd.id = line.SubString(startIndex + 1, endIndex - (startIndex + 1));

	m_data.Add(elementEnd);
}

//-------------------------------------------------------------------------------
void TXMLFile::ParseElementAttributes(const TString& line)
{
	int tagStartIndex = line.IndexOf('<');

	int startIndex = line.Find(" ", tagStartIndex) + 1;

	if (startIndex == 0)
	{
		return;
	}
	
	int attributeSeparatorIndex = line.Find("=", startIndex);
	int valueBeginIndex;
	int valueEndIndex;

	while (attributeSeparatorIndex != -1)
	{
		// ignore ="
		valueBeginIndex = attributeSeparatorIndex + 2;

		valueEndIndex = line.Find("\"", valueBeginIndex + 1);

		TXMLAttribute attribute;
		attribute.type = TXMLAttribute::Attribute;

		attribute.id = line.SubString(startIndex, attributeSeparatorIndex - startIndex);
		attribute.value = line.SubString(valueBeginIndex, valueEndIndex - valueBeginIndex);

		m_data.Add(attribute);

		startIndex = valueEndIndex + 2;
		attributeSeparatorIndex = line.Find("=", attributeSeparatorIndex + 1);
	}
}

//-------------------------------------------------------------------------------
bool TXMLFile::IsLineValid(const TString& line)
{
	if (line.Find("<!--") != -1)
	{
		// comment line
		return false;
	}
	else if (line.IndexOf('<') == -1)
	{
		// blank line or end of file
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------
void TXMLFile::ParseLine(const char* line)
{
	TString strLine = line;

	if (!IsLineValid(strLine))
	{
		return;
	}

	ParseElementStart(strLine);

	ParseElementAttributes(strLine);

	ParseElementEnd(strLine);
}

//-------------------------------------------------------------------------------
void TXMLFile::Save(const char* filename)
{
	TXMLStream output;
	bool openResult = output.OpenWrite(filename);

	if (!openResult)
	{
		TDebugPrint(("[TXMLFile::Save] Can't write to file: %s", filename));

		return;
	}

	TStringBuilder builder;

	Rewind();

	TXMLAttribute currentAttribute = GetNextAttribute();
	TXMLAttribute::TXMLAttributeType lastAttributeType = TXMLAttribute::ElementEnd;

	while (HasMoreAttributes())
	{
		if (currentAttribute.type == TXMLAttribute::ElementStart)
		{
			if (lastAttributeType != TXMLAttribute::ElementEnd)
			{
				builder.Append(">");
				builder.Append("\n");

				output.WriteString(builder.GetResult());
				output.SetIndentLevel( output.GetIndentLevel() + 1 );
			}

			builder.Clear();

			builder.Append("<");
			builder.Append(currentAttribute.id.GetPointer());
		}
		else if (currentAttribute.type == TXMLAttribute::ElementEnd)
		{
			if (lastAttributeType == TXMLAttribute::Attribute || lastAttributeType == TXMLAttribute::ElementStart)
			{
				builder.Append("/>");
				builder.Append("\n");

				output.WriteString(builder.GetResult());
			}
			else
			{
				builder.Clear();

				builder.Append("</");
				builder.Append(currentAttribute.id.GetPointer());
				builder.Append(">");
				builder.Append("\n");

				output.SetIndentLevel( output.GetIndentLevel() - 1 );
				output.WriteString(builder.GetResult());
			}

			builder.Clear();
		}
		else if (currentAttribute.type == TXMLAttribute::Attribute)
		{
			builder.Append(" ");
			builder.Append(currentAttribute.id.GetPointer());
			builder.Append("=");
			builder.Append("\"");
			builder.Append(currentAttribute.value.GetPointer());
			builder.Append("\"");
		}

		lastAttributeType = currentAttribute.type;
		currentAttribute = GetNextAttribute();
	}

	if (currentAttribute.type == TXMLAttribute::ElementEnd)
	{
		builder.Clear();
		builder.Append("</");
		builder.Append(currentAttribute.id.GetPointer());
		builder.Append(">");
		builder.Append("\n");

		output.SetIndentLevel( output.GetIndentLevel() - 1 );
		output.WriteString(builder.GetResult());
	}
	else
	{
		TASSERT(false, "[TXMLFile::Save] File has bad format");
	}
}

//-------------------------------------------------------------------------------
void TXMLFile::AddXMLAttribute(const TXMLAttribute &newAttribute)
{
	m_data.Add(newAttribute);
}
