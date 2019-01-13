#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

namespace InputCommand {
struct Command : public QObject
{
    Q_OBJECT
    Q_ENUMS(Engine)
    Q_ENUMS(ProcessEngine)

public:
    enum Engine {
        BASE_ENGINE = 0x42,
        DUAL_ENGINE = 0x4F,
        ALL_ENGINES = 0x41
    };

    enum ProcessEngine {
        RUN,
        STOP,
        RUN_ALL,
        STOP_ALL
    };
};
}

namespace OutputCommand {
struct Command : public QObject
{
    Q_OBJECT
    Q_ENUMS(Engine)
    Q_ENUMS(ProcessEngine)

public:
    enum Engine {
        BASE_ENGINE = 0x66,
        DUAL_ENGINE = 0x79,
        ALL_ENGINES = 0x65
    };

    enum ProcessEngine {
        RUN,
        STOP,
        RUN_ALL,
        STOP_ALL
    };
};
}
#endif // ICOMMAND_H

