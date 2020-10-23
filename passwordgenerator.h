#pragma once
#include <string>
#include <random>

class PasswordGenerator {
public:
    PasswordGenerator(const std::string& alphabet);
    std::string generate(unsigned length);

private:
    std::string _alphabet;
    std::default_random_engine _rand_gen;
    std::uniform_int_distribution<unsigned> _rand_distr;

    static const unsigned MAX_LENGTH = 1024;
};

