#pragma once

#include "PlyReader.h"
#include "PlyContentHandler.h"
#include "PlyErrorHandler.h"

class PlyContentOutputer : 
    public SAP::IPlyContentHandler,
    public SAP::IPlyErrorHandler
{
public:
    PlyContentOutputer();

    // Implementation of IPlyContentHandler interface
    bool WillReadInstancesOfElement(const std::string &elementName, std::size_t elementInstances) override;
    bool WillReadElement(const std::string &elementName, std::size_t elementInstance) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned char *propertyValues) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const char *propertyValues) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned short *propertyValues) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const short *propertyValues) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned int *propertyValues) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const int *propertyValues) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const float *propertyValues) override;
    bool DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const double *propertyValues) override;
    bool DidReadElement(const std::string &elementName, std::size_t elementInstance) override;
    bool DidReadInstancesOfElement(const std::string &elementName, std::size_t elementInstances) override;

    // Implementation of IPlyErrorHandler interface
    virtual void DidFailWithMessage(const std::string &errorMessage) override;

public:
    bool Output(const std::string &filename);

private:
    SAP::PlyReader m_plyReader;
};
