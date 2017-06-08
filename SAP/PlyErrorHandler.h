#pragma once

#include <string>
#include <iostream>

namespace SAP
{
    struct IPlyErrorHandler
    {
        virtual ~IPlyErrorHandler()
        {
        }

        virtual void DidFail(const std::string &errorMessage) = 0;
    };
}