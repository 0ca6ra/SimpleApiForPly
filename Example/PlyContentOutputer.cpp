#include "PlyContentOutputer.h"

#include <iostream>

PlyContentOutputer::PlyContentOutputer() : 
    m_plyReader()
{
    m_plyReader.SetContentHandler(this);
    m_plyReader.SetErrorHandler(this);
}

bool PlyContentOutputer::WillReadInstancesOfElement(const std::string &elementName, std::size_t elementInstances)
{
    std::cout << std::endl;
    std::cout << "Will read instances (" << elementInstances << ") of \"" << elementName << "\" element" << std::endl;
    return true;
}

bool PlyContentOutputer::WillReadElement(const std::string &elementName, std::size_t elementInstance)
{
    std::cout << "    Will read instance (" << elementInstance << ") of \"" << elementName << "\" element" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned char *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const char *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned short *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const short *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const unsigned int *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const int *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const float *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElementProperty(const std::string &propertyName, std::size_t propertyValuesCount, const double *propertyValues)
{
    std::cout << "        Property \"" << propertyName << "\" = { ";
    for (std::size_t i = 0; i < propertyValuesCount; ++i)
    {
        std::cout << propertyValues[i] << " ";
    }
    std::cout << "}" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadElement(const std::string &elementName, std::size_t elementInstance)
{
    std::cout << "    Did read instances (" << elementInstance << ") of \"" << elementName << "\" element" << std::endl;
    return true;
}

bool PlyContentOutputer::DidReadInstancesOfElement(const std::string &elementName, std::size_t elementInstances)
{
    std::cout << "Did read instances (" << elementInstances << ") of \"" << elementName << "\" element" << std::endl;
    std::cout << std::endl;
    return true;
}

void PlyContentOutputer::DidFail(const std::string &errorMessage)
{
    std::cerr << errorMessage << std::endl;
}

bool PlyContentOutputer::Output(const std::string &filename)
{
    return m_plyReader.Read(filename);
}
