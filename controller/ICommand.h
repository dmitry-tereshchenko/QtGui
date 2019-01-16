#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

namespace InputCommand {
    struct Command : public QObject
    {
        Q_OBJECT
        Q_ENUMS(Engine)
    public:
        enum Engine {
            BASE_ENGINE = 0x42,
            DUAL_ENGINE = 0x4F,
            ALL_ENGINES = 0x41
        };
    };
}

namespace OutputCommand {
    struct Command : public QObject
    {
        Q_OBJECT
        Q_ENUMS(ProcessEngine)
    public:
        enum ProcessEngine {
            RUN_BASE_ENGINE,
            RUN_DUAL_ENGINE,
            STOP_BASE_ENGINE,
            STOP_DUAL_ENGINE,
            ACCELERATES_BASE_ENGINE,
            ACCELERATES_DUAL_ENGINE,
            RUN_ALL,
            STOP_ALL,
        };
    };
}
#endif // ICOMMAND_H

