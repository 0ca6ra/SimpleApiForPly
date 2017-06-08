#include "PlyPropertyReader.h"
#include "PlyPropertyReaderUtilities.h"

template <typename ScalarType>
bool SAP::PlyScalarPropertyReader<ScalarType>::Read(std::ifstream &stream, const std::string &format, SAP::IPlyContentHandler *pContentHandler)
{
    ScalarType item(ScalarType(0));

    if (!SAP::Read(stream, format, item))
    {
        return false;
    }

    if (pContentHandler != nullptr && !pContentHandler->DidReadElementProperty(m_name, 1, &item))
    {
        return false;
    }

    return true;
}

std::unique_ptr<SAP::PlyPropertyReader> SAP::CreateScalarPropertyReader(const std::string &scalarType, const std::string &name)
{
    if (scalarType == "uchar" || scalarType == "uint8")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<unsigned char>>(name);
    }

    if (scalarType == "char" || scalarType == "int8")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<char>>(name);
    }

    if (scalarType == "ushort" || scalarType == "uint16")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<unsigned short>>(name);
    }

    if (scalarType == "short" || scalarType == "int16")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<short>>(name);
    }

    if (scalarType == "uint" || scalarType == "uint32")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<unsigned int>>(name);
    }

    if (scalarType == "int" || scalarType == "int32")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<int>>(name);
    }

    if (scalarType == "float" || scalarType == "float32")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<float>>(name);
    }

    if (scalarType == "double" || scalarType == "float64")
    {
        return std::make_unique<SAP::PlyScalarPropertyReader<double>>(name);
    }

    return nullptr;
}

template <typename SizeType, typename ItemsType>
bool SAP::PlyListPropertyReader<SizeType, ItemsType>::Read(std::ifstream &stream, const std::string &format, SAP::IPlyContentHandler *pContentHandler)
{
    SizeType size = SizeType(0);

    if (!SAP::Read(stream, format, size))
    {
        return false;
    }

    std::vector<ItemsType> items(size, ItemsType(0));

    for (SizeType i = SizeType(0); i < size; ++i)
    {
        if (!SAP::Read(stream, format, items[i]))
        {
            return false;
        }
    }

    if (pContentHandler != nullptr && !pContentHandler->DidReadElementProperty(m_name, items.size(), items.data()))
    {
        return false;
    }

    return true;
}

template <typename SizeType>
std::unique_ptr<SAP::PlyPropertyReader> CreateListPropertyReader(const std::string &itemsType, const std::string &name)
{
    if (itemsType == "uchar" || itemsType == "uint8")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, unsigned char>>(name);
    }

    if (itemsType == "char" || itemsType == "int8")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, char>>(name);
    }

    if (itemsType == "ushort" || itemsType == "uint16")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, unsigned short>>(name);
    }

    if (itemsType == "short" || itemsType == "int16")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, short>>(name);
    }

    if (itemsType == "uint" || itemsType == "uint32")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, unsigned int>>(name);
    }

    if (itemsType == "int" || itemsType == "int32")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, int>>(name);
    }

    if (itemsType == "float" || itemsType == "float32")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, float>>(name);
    }

    if (itemsType == "double" || itemsType == "float64")
    {
        return std::make_unique<SAP::PlyListPropertyReader<SizeType, double>>(name);
    }

    return nullptr;
}

std::unique_ptr<SAP::PlyPropertyReader> SAP::CreateListPropertyReader(const std::string &sizeType, const std::string &itemsType, const std::string &name)
{
    if (sizeType == "uchar" || sizeType == "uint8")
    {
        return ::CreateListPropertyReader<unsigned char>(itemsType, name);
    }

    if (sizeType == "ushort" || sizeType == "uint16")
    {
        return ::CreateListPropertyReader<unsigned short>(itemsType, name);
    }

    if (sizeType == "uint" || sizeType == "uint32")
    {
        return ::CreateListPropertyReader<unsigned int>(itemsType, name);
    }

    return nullptr;
}

