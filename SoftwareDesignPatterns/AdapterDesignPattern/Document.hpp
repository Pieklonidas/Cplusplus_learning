#pragma once

#include <iostream>

class JSONExportable
{
public:
    virtual ~JSONExportable() = default;
    virtual void exportToJSON() const = 0;
};

class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual void serialize() const = 0;
};

class Document : public JSONExportable
               , public Serializable
{};