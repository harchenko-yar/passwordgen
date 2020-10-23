#include "alphabet.h"
#include <errors.h>
#include <QCommandLineParser>
#include <iostream>
#include <QJsonDocument>
#include<QJsonObject>
#include<QDir>
#include<QFile>



namespace {
    const static std::string alphabet_simple{ "abcdefghijklmopqrtsuvwxyzABCDEFGHIJKLMOPQRTSUVWXYZ0123456789" };
    const static std::string alphabet_medium{ "abcdefghijklmopqrtsuvwxyzABCDEFGHIJKLMOPQRTSUVWXYZ0123456789!@#_" };
    const static std::string alphabet_strong{ "abcdefghijklmopqrtsuvwxyzABCDEFGHIJKLMOPQRTSUVWXYZ0123456789!@#$%^&*()-_+=" };
}

std::string read_json(const QString& name)
{
    QJsonDocument doc;
    QJsonObject obj;
    QFile file;
    QString str;
    file.setFileName(QDir::homePath() + "/.passwordgen");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        error("Something went wrong with opening ~/.passwordgen.");
    str = file.readAll();
    file.close();
    doc = QJsonDocument::fromJson(str.toUtf8());
    obj = doc.object();
    if (obj.contains(name)) {
        return obj.value(name).toString().toStdString();
    }
    else
        error("No alphabet with the given name in the JSON file.");
    return NULL;
}

const std::string& select_alphabet(const QCommandLineParser& parser) {
    int simple_set = 0, medium_set = 0, strong_set = 0, custom_set = 0;
    int f_set = 0;
    if (parser.isSet("length") && (parser.value("length").toUInt() <= 0 || parser.value("length").toUInt() >= MAX_LENGTH))
        error("Password length must be positive number and less than " + std::to_string(MAX_LENGTH) + ".");
    if (parser.isSet("simple"))
        simple_set = 1;
    if (parser.isSet("medium"))
        medium_set = 1;
    if (parser.isSet("strong"))
        strong_set = 1;
    if (parser.isSet("alphabet"))
        custom_set = 1;
    if (parser.isSet("from"))
        f_set = 1;
    int sum = f_set + simple_set + medium_set + strong_set + custom_set;
    if (sum > 1)
        error("You cannot specify more than one complexity level. Choose one of: --simple, --medium, --strong - or use your custom alphabet using --alphabet");
    if (medium_set)
        return alphabet_medium;
    else if (strong_set)
        return alphabet_strong;
    else if (custom_set) {
        static std::string customAlphabet(parser.value("alphabet").length(), 0);
        customAlphabet = parser.value("alphabet").toStdString();
        return customAlphabet;
    }
    else if (f_set) {
        static std::string jsonAlphabet(parser.value("alphabet").length(), 0);
        jsonAlphabet = read_json(parser.value("from"));
        return jsonAlphabet;
    }
    else
        return alphabet_simple;
}
