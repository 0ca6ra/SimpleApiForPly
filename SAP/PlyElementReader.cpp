#include "PlyElementReader.h"

std::unique_ptr<SAP::PlyElementReader> SAP::CreateElementReader(const std::string &name, unsigned long instances)
{
    if (instances > 0)
    {
        return std::make_unique<SAP::PlyElementReader>(name, instances);
    }

    return nullptr;
}
