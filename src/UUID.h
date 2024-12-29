#pragma once

#include <sys/types.h>

class UUID
{
   public:
    UUID();
    UUID(u_int64_t uuid);
    UUID(const UUID&) = default;

    operator u_int64_t() const { return m_UUID; }

   private:
    u_int64_t m_UUID;
};

namespace std
{
template <typename T>
struct hash;

template <>
struct hash<UUID>
{
    size_t operator()(const UUID& uuid) const { return (u_int64_t)uuid; }
};

}  // namespace std