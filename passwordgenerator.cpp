#include "passwordgenerator.h"
#include "errors.h"
#include <chrono>
#include<iostream>

PasswordGenerator::PasswordGenerator(const std::string& alphabet) :
    _alphabet(alphabet),
    _rand_gen(std::default_random_engine(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()))),
    _rand_distr(std::uniform_int_distribution<unsigned>(0, static_cast<unsigned>(alphabet.length() - 1)))
{}



SimpleGen::SimpleGen(const std::string& alphabet) :
    PasswordGenerator::PasswordGenerator(alphabet)
{}

MediumGen::MediumGen(const std::string& alphabet) :
    PasswordGenerator::PasswordGenerator(alphabet)
{}

HardGen::HardGen(const std::string& alphabet) :
    PasswordGenerator::PasswordGenerator(alphabet)
{}

CustomGen::CustomGen(const std::string& alphabet) :
    PasswordGenerator::PasswordGenerator(alphabet)
{}

JsonGen::JsonGen(const std::string& alphabet) :
    PasswordGenerator::PasswordGenerator(alphabet)
{}

int SimpleGen::checkCrit(std::string& password, unsigned length)
{
    int capital = 0, digit = 0;
    for (unsigned i = 0; i < length; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z')
            capital = 1;
        if (password[i] >= '0' && password[i] <= '9')
            digit = 1;
        if (digit && capital)
            return 1;
    }
    return 0;
}

int MediumGen::checkCrit(std::string& password, unsigned length)
{
    std::string ssigns = { "-_! @#$~" };
    int capital = 0, digit = 0, ss = 0, j = 0;
    for (unsigned i = 0; i < length; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z')
            capital = 1;
        if (password[i] >= '0' && password[i] <= '9')
            digit = 1;
        while (ssigns[j] != 0) {
            if (ssigns[j] == password[i])
                ss = 1;
            j++;
        }
        j = 0;
        if (digit && capital && ss)
            return 1;
    }
    return 0;
}

int HardGen::checkCrit(std::string& password, unsigned length)
{
    std::string ssigns = { "!@#$%^&*()~" };
    int capital = 0, digit = 0, ss = 0, j = 0;
    for (unsigned i = 0; i < length; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z')
            capital = 1;
        if (password[i] >= '0' && password[i] <= '9')
            digit = 1;
        while (ssigns[j] != 0) {
            if (ssigns[j] == password[i])
                ss++;
            j++;
        }
        j = 0;
        if (digit && capital && ss == 4)
            return 1;
    }
    return 0;
}

std::string JsonGen::generate(unsigned length)
{
    unsigned i;
    std::string password;
    if (!length)
        length = 8;
    for (i = 0; i < length; i++)
        password += _alphabet[_rand_distr(_rand_gen)];
    return password;
}
std::string SimpleGen::generate(unsigned length)
{
    std::string password;
    unsigned i = 0;
    if (!length)
        length = 8;
    for (i = 0; i < length; i++)
        password += _alphabet[_rand_distr(_rand_gen)];
    i = 0;
    while (!checkCrit(password, length)) {
        password[i] = _alphabet[_rand_distr(_rand_gen)];
        i++;
        if (i >= length)
            i = 0;
    }
    return password;
}
std::string MediumGen::generate(unsigned length)
{
    unsigned i;
    std::string password;
    if (!length)
        length = 8;
    for (i = 0; i < length; i++)
        password += _alphabet[_rand_distr(_rand_gen)];
    i = 0;
    while (!checkCrit(password, length)) {
        password[i] = _alphabet[_rand_distr(_rand_gen)];
        i++;
        if (i >= length)
            i = 0;
    }
    return password;
}
std::string HardGen::generate(unsigned length)
{
    unsigned i;
    std::string password;
    if (!length)
        length = 10;
    for (i = 0; i < length; i++)
        password += _alphabet[_rand_distr(_rand_gen)];
    i = 0;
    while (!checkCrit(password, length)) {
        password[i] = _alphabet[_rand_distr(_rand_gen)];
        i++;
        if (i >= length)
            i = 0;
    }
    return password;
}
std::string CustomGen::generate(unsigned length)
{
    std::string password;
    if (!length)
        length = 8;
    for (unsigned i = 0; i < length; i++)
        password += _alphabet[_rand_distr(_rand_gen)];

    return password;
}

void Client::setGenerator(PasswordGenerator* g)
{
    generator = g;
}
std::string Client::generate(unsigned length)
{
    return generator->generate(length);
}
