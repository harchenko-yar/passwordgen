#include "alphabet.h"
#include <errors.h>
#include <QCommandLineParser>

namespace {
    const static std::string alphabet_simple {"abcdefghijklmopqrtsuvwxyzABCDEFGHIJKLMOPQRTSUVWXYZ0123456789"};
    const static std::string alphabet_medium {"abcdefghijklmopqrtsuvwxyzABCDEFGHIJKLMOPQRTSUVWXYZ0123456789!@#_"};
    const static std::string alphabet_strong {"abcdefghijklmopqrtsuvwxyzABCDEFGHIJKLMOPQRTSUVWXYZ0123456789!@#$%^&*()-_+="};
}

const std::string& select_alphabet(const QCommandLineParser& parser) {
    auto medium_set = parser.isSet("medium");
    auto strong_set = parser.isSet("strong");
    auto simple_set = parser.isSet("simple");

    if ((simple_set && (strong_set || medium_set || (medium_set && strong_set))) || (strong_set && medium_set))
        error("You cannot specify more than one complexity level. Choose one of: --simple, --medium or --strong");

    if (medium_set)
        return alphabet_medium;
    else if (strong_set)
        return alphabet_strong;
    else
        return alphabet_simple;
}
