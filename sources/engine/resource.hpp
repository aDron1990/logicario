#pragma once

#include <engine/types.hpp>

#include <crossguid/guid.hpp>

#include <unordered_set>

namespace logicario::engine
{
    class Resource
    {
    public:
        Resource(const ID& id) : m_id{id} {};
        Resource() { m_id = xg::newGuid().str(); };
        ID getID() const noexcept { return m_id; };
        bool operator==(const Resource& resource) const noexcept { return m_id == resource.m_id; };

        struct Hash
        {
            size_t operator()(Resource& resource) { return std::hash<ID>{}(resource.getID()); }
        };

    protected:
        void setID(const ID& id) noexcept { m_id = id; };

    private:
        ID m_id;
    };
}