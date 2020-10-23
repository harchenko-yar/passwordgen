#include "argparser.h"
#include "errors.h"
#include <QCoreApplication>

QScopedPointer<QCommandLineParser> parse_args(const QCoreApplication& app) {
    auto parser = new QCommandLineParser;

    parser->setApplicationDescription("Password generator app.");
    parser->addHelpOption();

    parser->addOption({
        "simple",
        "Generates simple password."
    });

    parser->addOption({
        {"medium", "m"},
        "Generates medium complexity password."
    });

    parser->addOption({
        {"strong", "s"},
        "Generates most complex password."
    });

    parser->addOption({
        {"length", "l"},
        "Generates password of specified length.",
        "LENGTH",
        "10"
    });

    parser->process(app);

    if (!parser->parse(QCoreApplication::arguments()))
        error(parser->errorText().toLatin1().toStdString());

    return QScopedPointer(parser);
}
