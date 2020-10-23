#include "errors.h"
#include "argparser.h"
#include "alphabet.h"
#include "passwordgenerator.h"

#include <iostream>
#include <stdexcept>
#include <map>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QScopedPointer>

int main(int argc, char** argv) {
    try {
        Client cli;
        unsigned length = 0;
        auto parser = parse_args(QCoreApplication(argc, argv));
        std::string alphabet = select_alphabet(*parser);
        MediumGen m(alphabet);
        SimpleGen s(alphabet);
        HardGen h(alphabet);
        CustomGen c(alphabet);
        JsonGen j(alphabet);

        if (parser->isSet("length"))
            length = parser->value("length").toUInt();
        if (parser->isSet("medium"))
            cli.setGenerator(&m);
        else if (parser->isSet("strong"))
            cli.setGenerator(&h);
        else if (parser->isSet("alphabet"))
            cli.setGenerator(&c);
        else if (parser->isSet("from"))
            cli.setGenerator(&j);
        else
            cli.setGenerator(&s);
        std::cout << cli.generate(length) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "ERROR: " << ex.what() << std::endl;
    }

    return 0;
}
