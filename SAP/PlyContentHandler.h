#pragma once

#include <string>

namespace SAP
{
    struct IPlyContentHandler
    {
        virtual ~IPlyContentHandler()
        {
        }

        virtual bool WillReadInstancesOfElement(const std::string &elementName, std::size_t elementInstances) = 0;
        virtual bool WillReadElement(const std::string &elementName, std::size_t elementInstance) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned char *propertyValues) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const char *propertyValues) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned short *propertyValues) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const short *propertyValues) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned int *propertyValues) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const int *propertyValues) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const float *propertyValues) = 0;
        virtual bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const double *propertyValues) = 0;
        virtual bool DidReadElement(const std::string &elementName, std::size_t elementInstance) = 0;
        virtual bool DidReadInstancesOfElement(const std::string &elementName, std::size_t elementInstances) = 0;

    };
}