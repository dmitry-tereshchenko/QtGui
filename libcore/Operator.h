#ifndef OPERATOR_H
#define OPERATOR_H
#include "Types.h"

namespace Operator
{
    const Id& id();
    const QString& name();
    const QString& level();
    const QString& phone();
    const QString& password();
    const Info& info();
    bool can(const PermissionsList &&perm);
    void setOperator(const Info& info);
}

#endif // OPERATOR_H
