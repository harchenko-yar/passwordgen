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
        auto parser = parse_args(QCoreApplication(argc, argv));
        auto pwdgen = PasswordGenerator(select_alphabet(*parser));
        auto length = parser->value("length").toUInt();
        std::cout << pwdgen.generate(length) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "ERROR: " << ex.what() << std::endl;
    }

    return 0;
}
