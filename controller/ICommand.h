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
        BASE_ENGINE = 0x142,
        DUAL_ENGINE = 0x163,
        ALL_ENGINES = 0x157
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
        BASE_ENGINE = 'b',
        DUAL_ENGINE = 'd',
        ALL_ENGINES = 'a'
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

