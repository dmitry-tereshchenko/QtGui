#include "Operator.h"

namespace Operator
{
    Info *m_info;

    void setOperator(const Info& info)
    {
         m_info = new Info(info);
    }

    bool can(const PermissionsList&& perm)
    {
        if ((perm < 0) || m_info->permission.isEmpty())
            return false;

        if (m_info->permission.at(perm).digitValue() == 1)
            return true;

        return false;
    }

    const QString& name()
    {
        return m_info->usrName;
    }

    const QString& level()
    {
        return m_info->usrLevel;
    }

    const QString &phone()
    {
        return m_info->usrPhone;
    }

    const QString &password()
    {
        return m_info->usrPassword;
    }

    const Id &id()
    {
        return m_info->idOper;
    }
}