#pragma once

#include <string>

namespace SAP
{
    struct IPlyErrorHandler
    {
        virtual ~IPlyErrorHandler()
        {
        }

        virtual void DidFailWithMessage(const std::string &errorMessage) = 0;
    };
}