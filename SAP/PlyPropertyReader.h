#pragma once

#include "PlyContentReader.h"

#include <memory>

namespace SAP
{
    struct PlyPropertyReader : 
        public IPlyContentReader
    {
        std::string m_name;

        explicit PlyPropertyReader(const std::string &name) :
            m_name(name)
        {
        }

        virtual ~PlyPropertyReader()
        {
        }
    };

    template <typename ScalarType>
    struct PlyScalarPropertyReader : 
        public PlyPropertyReader
    {
        explicit PlyScalarPropertyReader(const std::string &name) :
            PlyPropertyReader(name)
        {
        }

        bool Read(std::ifstream &stream, const std::string &format, IPlyContentHandler *pContentHandler) override;
    };

    std::unique_ptr<PlyPropertyReader> CreateScalarPropertyReader(const std::string &scalarType, const std::string &name);

    template <typename SizeType, typename ItemsType>
    struct PlyListPropertyReader : 
        public PlyPropertyReader
    {
        explicit PlyListPropertyReader(const std::string &name) :
            PlyPropertyReader(name)
        {
        }

        bool Read(std::ifstream &stream, const std::string &format, IPlyContentHandler *pContentHandler) override;
    };

    std::unique_ptr<SAP::PlyPropertyReader> CreateListPropertyReader(const std::string &sizeType, const std::string &itemsType, const std::string &name);
}