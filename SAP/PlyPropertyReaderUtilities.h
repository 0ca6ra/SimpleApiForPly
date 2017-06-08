#pragma once

#include <cstdint>
#include <fstream>
#include <sstream>

namespace SAP
{
    template <typename ValueType>
    bool ReadAscii(std::ifstream &stream, ValueType &value)
    {
        stream >> value;

        if (!stream)
        {
            return false;
        }

        return true;
    }

    template <>
    bool ReadAscii(std::ifstream &stream, unsigned char &value)
    {
        unsigned short ushortValue = 0;

        stream >> ushortValue;

        if (!stream || UINT8_MAX < ushortValue)
        {
            return false;
        }

        value = static_cast<unsigned char>(ushortValue);

        return true;
    }

    template <>
    bool ReadAscii(std::ifstream &stream, char &value)
    {
        short shortValue = 0;

        stream >> shortValue;

        if (!stream || shortValue < INT8_MIN || INT8_MAX < shortValue)
        {
            return false;
        }

        value = static_cast<char>(shortValue);

        return true;
    }

    enum class ByteOrdering
    {
        BigEndian,
        LittleEndian
    };

    template <typename ValueType>
    void ReverseBytes(ValueType &value)
    {
        size_t size = sizeof(value);

        char *valueBytes = reinterpret_cast<char *>(&value);

        for (size_t i = 0; i < size / 2; ++i)
        {
            std::swap(valueBytes[i], valueBytes[size - 1 - i]);
        }
    }

    template <ByteOrdering byteOrdering, typename ValueType>
    bool ReadBinary(std::ifstream &stream, ValueType &value)
    {
        stream.read(reinterpret_cast<char *>(&value), sizeof(value));

        if (!stream)
        {
            return false;
        }

        if (byteOrdering == ByteOrdering::BigEndian)
        {
            ReverseBytes(value);
        }

        return true;
    }

    template <typename ValueType>
    bool Read(std::ifstream &stream, const std::string &format, ValueType &value)
    {
        if (format == "ascii")
        {
            return ReadAscii(stream, value);
        }

        if (format == "binary_big_endian")
        {
            return ReadBinary<ByteOrdering::BigEndian>(stream, value);
        }

        if (format == "binary_little_endian")
        {
            return ReadBinary<ByteOrdering::LittleEndian>(stream, value);
        }

        return false;
    }
}