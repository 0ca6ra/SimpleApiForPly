#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <vector>

#include "PlyElementReader.h"

namespace SAP
{
    struct IPlyContentHandler;
    struct IPlyErrorHandler;

    class PlyReader
    {
    public:
        PlyReader();
        PlyReader(const PlyReader &) = delete;
        PlyReader(const PlyReader &&) = delete;
        PlyReader &operator=(const PlyReader &) = delete;
        PlyReader &operator=(const PlyReader &&) = delete;

        void SetContentHandler(IPlyContentHandler *pContentHandler);
        void SetErrorHandler(IPlyErrorHandler *pErrorHandler);
        bool Read(const std::string &filename);

    private:
        bool OpenStream(const std::string &filename);
        bool ParseHeader();
        bool ReadContent();

    private:
        bool ReadLine(std::string &line);
        bool ExtractWords(const std::string &line, std::vector<std::string> &words);

    private:
        enum class ParserState
        {
            ParseMagicNumber,
            ParseFormat,
            ParseUntilEndHeader,
            Done,
        };

        bool ParseMagicNumber(const std::string &line, ParserState &nextParserState);
        bool ParseFormat(const std::string &line, ParserState &nextParserState);
        bool ParseUntilEndHeader(const std::string &line, ParserState &nextParserState);

    private:
        bool ParseCommentArguments(std::vector<std::string> &arguments);
        bool ParseObjInfoArguments(std::vector<std::string> &arguments);
        bool ParseElementArguments(std::vector<std::string> &arguments);
        bool ParseScalarPropertyArguments(std::vector<std::string> &arguments);
        bool ParseListPropertyArguments(std::vector<std::string> &arguments);

    private:
        std::ifstream m_stream;
        std::string m_format;
        std::vector<std::unique_ptr<PlyElementReader>> m_elementReaders;
        IPlyContentHandler *m_pContentHandler;
        IPlyErrorHandler *m_pErrorHandler;
    };
}
