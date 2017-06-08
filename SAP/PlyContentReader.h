#pragma once

#include <fstream>
#include <string>

#include "PlyContentHandler.h"

namespace SAP
{
    struct IPlyContentReader
    {
        virtual ~IPlyContentReader()
        {
        }

        virtual bool Read(std::ifstream &stream, const std::string &format, IPlyContentHandler *pContentHandler) = 0;
    };
}