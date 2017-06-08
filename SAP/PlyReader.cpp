#pragma once

#include <sstream>

#include "PlyReader.h"
#include "PlyErrorHandler.h"

SAP::PlyReader::PlyReader() : 
    m_pContentHandler(nullptr),
    m_pErrorHandler(nullptr)
{
}

void SAP::PlyReader::SetContentHandler(IPlyContentHandler *pContentHandler)
{
    m_pContentHandler = pContentHandler;
}

void SAP::PlyReader::SetErrorHandler(IPlyErrorHandler *pErrorHandler)
{
    m_pErrorHandler = pErrorHandler;
}

bool SAP::PlyReader::Read(const std::string &plyFile)
{
    if (!OpenStream(plyFile))
    {
        return false;
    }

    if (!ParseHeader())
    {
        return false;
    }

    if (!ReadContent())
    {
        return false;
    }

    return true;
}

bool SAP::PlyReader::OpenStream(const std::string &plyFile)
{
    m_stream.open(plyFile, std::ifstream::in | std::ifstream::binary);

    if (!m_stream)
    {
        if (m_pErrorHandler != nullptr)
        {
            m_pErrorHandler->DidFail("Error: Failed to open " + plyFile);
        }

        return false;
    }

    return true;
}

bool SAP::PlyReader::ParseHeader()
{
    ParserState nextParserState = ParserState::ParseMagicNumber;

    while (nextParserState != ParserState::Done)
    {
        std::string line;

        if (!ReadLine(line))
        {
            return false;
        }

        switch (nextParserState)
        {
            case ParserState::ParseMagicNumber:
                if (!ParseMagicNumber(line, nextParserState))
                {
                    if (m_pErrorHandler != nullptr)
                    {
                        m_pErrorHandler->DidFail("Error: Invalid ply magic number: " + line);
                    }

                    return false;
                }
                break;

            case ParserState::ParseFormat:
                if (!ParseFormat(line, nextParserState))
                {
                    if (m_pErrorHandler != nullptr)
                    {
                        m_pErrorHandler->DidFail("Error: Invalid ply format: " + line);
                    }

                    return false;
                }
                break;

            case ParserState::ParseUntilEndHeader:
                if (!ParseUntilEndHeader(line, nextParserState))
                {
                    if (m_pErrorHandler != nullptr)
                    {
                        m_pErrorHandler->DidFail("Error: Invalid ply header option: " + line);
                    }

                    return false;
                }
                break;

            default:
                return false;
        }
    }

    return nextParserState == ParserState::Done;
}

bool SAP::PlyReader::ParseMagicNumber(const std::string &line, ParserState &nextParserState)
{
    std::vector<std::string> words;

    if (!ExtractWords(line, words))
    {
        return false;
    }

    if (words.size() != 1)
    {
        return false;
    }
    
    if (words[0] != "ply")
    {
        return false;
    }

    nextParserState = ParserState::ParseFormat;

    return true;
}

bool SAP::PlyReader::ParseFormat(const std::string &line, ParserState &nextParserState)
{
    std::vector<std::string> words;

    if (!ExtractWords(line, words))
    {
        return false;
    }

    if (words.size() != 3)
    {
        return false;
    }

    if (words[0] != "format")
    {
        return false;
    }

    if (words[1] != "ascii" && words[1] != "binary_big_endian" && words[1] != "binary_little_endian")
    {
        return false;
    }

    if (words[2] != "1.0")
    {
        return false;
    }

    m_format = words[1];

    nextParserState = ParserState::ParseUntilEndHeader;

    return true;
}

bool SAP::PlyReader::ParseUntilEndHeader(const std::string &line, ParserState &nextParserState)
{
    std::vector<std::string> words;

    if (!ExtractWords(line, words))
    {
        return false;
    }

    if (words.size() < 1)
    {
        return false;
    }

    if (words.size() == 1 && words[0] == "end_header")
    {
        nextParserState = ParserState::Done;

        return true;
    }

    if (words[0] == "comment")
    {
        words.erase(words.begin());

        return ParseCommentArguments(words);
    }

    if (words[0] == "obj_info")
    {
        words.erase(words.begin());

        return ParseObjInfoArguments(words);
    }

    if (words[0] == "element")
    {
        words.erase(words.begin());

        return ParseElementArguments(words);
    }

    if (words[0] == "property")
    {
        words.erase(words.begin());

        return ParseScalarPropertyArguments(words) || ParseListPropertyArguments(words);
    }

    return false;
}

bool SAP::PlyReader::ParseCommentArguments(std::vector<std::string> &arguments)
{
    return true;
}

bool SAP::PlyReader::ParseObjInfoArguments(std::vector<std::string> &arguments)
{
    return true;
}

bool SAP::PlyReader::ParseElementArguments(std::vector<std::string> &arguments)
{
    if (arguments.size() != 2)
    {
        return false;
    }

    std::unique_ptr<PlyElementReader> elementReader = CreateElementReader(arguments[0], std::strtoul(arguments[1].c_str(), nullptr, 10));

    if (elementReader == nullptr)
    {
        return false;
    }

    m_elementReaders.push_back(std::move(elementReader));

    return true;
}

bool SAP::PlyReader::ParseScalarPropertyArguments(std::vector<std::string> &arguments)
{
    if (arguments.size() != 2)
    {
        return false;
    }

    if (m_elementReaders.empty())
    {
        return false;
    }

    std::unique_ptr<PlyPropertyReader> propertyReader(CreateScalarPropertyReader(arguments[0], arguments[1]));

    if (propertyReader == nullptr)
    {
        return false;
    }

    m_elementReaders.back()->m_propertyReaders.push_back(std::move(propertyReader));

    return true;
}

bool SAP::PlyReader::ParseListPropertyArguments(std::vector<std::string> &arguments)
{
    if (arguments.size() != 4)
    {
        return false;
    }

    if (arguments[0] != "list")
    {
        return false;
    }

    if (m_elementReaders.empty())
    {
        return false;
    }

    std::unique_ptr<PlyPropertyReader> propertyReader(CreateListPropertyReader(arguments[1], arguments[2], arguments[3]));

    if (propertyReader == nullptr)
    {
        return false;
    }

    m_elementReaders.back()->m_propertyReaders.push_back(std::move(propertyReader));

    return true;
}

bool SAP::PlyReader::ReadContent()
{
    for (auto &elementReader : m_elementReaders)
    {
        if (!elementReader->Read(m_stream, m_format, m_pContentHandler))
        {
            return false;
        }
    }

    return true;
}

bool SAP::PlyReader::ReadLine(std::string &line)
{
    std::getline(m_stream, line, '\n');

    if (!m_stream)
    {
        return false;
    }

    if (0 < line.size() && line[line.size() - 1] == '\r')
    {
        line = line.substr(0, line.size() - 1);
    }

    return true;
}

bool SAP::PlyReader::ExtractWords(const std::string &line, std::vector<std::string> &words)
{
    std::istringstream lineStream(line);

    while (lineStream && !lineStream.eof())
    {
        std::string word;

        lineStream >> word;

        if (!word.empty())
        {
            words.push_back(word);
        }
    }

    return true;
}
