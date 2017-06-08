#pragma once

#include "PlyContentHandler.h"
#include "PlyPropertyReader.h"

#include <memory>
#include <vector>

namespace SAP
{
    struct PlyElementReader : 
        public IPlyContentReader
    {
        std::string m_name;
        std::size_t m_instances;
        std::vector<std::unique_ptr<PlyPropertyReader>> m_propertyReaders;

        PlyElementReader(const std::string &name, unsigned long instances) :
            m_name(name),
            m_instances(instances)
        {
        }

        bool Read(std::ifstream &stream, const std::string &format, IPlyContentHandler *pContentHandler) override
        {
            if (pContentHandler != nullptr && !pContentHandler->WillReadInstancesOfElement(m_name, m_instances))
            {
                return false;
            }
                
            for (std::size_t instance = 0; instance < m_instances; ++instance)
            {
                if (pContentHandler != nullptr && !pContentHandler->WillReadElement(m_name, instance))
                {
                    return false;
                }

                for (auto &propertyReader : m_propertyReaders)
                {
                    if (!propertyReader->Read(stream, format, pContentHandler))
                    {
                        return false;
                    }
                }

                if (pContentHandler != nullptr && !pContentHandler->DidReadElement(m_name, instance))
                {
                    return false;
                }
            }

            if (pContentHandler != nullptr && !pContentHandler->DidReadInstancesOfElement(m_name, m_instances))
            {
                return false;
            }

            return true;
        }
    };

    std::unique_ptr<PlyElementReader> CreateElementReader(const std::string &name, unsigned long instances);
}