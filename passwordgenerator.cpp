#include "passwordgenerator.h"
#include "errors.h"
#include <chrono>

PasswordGenerator::PasswordGenerator(const std::string& alphabet)
    : _alphabet(alphabet),
      _rand_gen(std::default_random_engine(
          static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()))
      ),
      _rand_distr(std::uniform_int_distribution<unsigned>(0, static_cast<unsigned>(alphabet.length() - 1)))
{}

std::string PasswordGenerator::generate(unsigned length) {
    if (length <= 0 || length >= MAX_LENGTH)
        error("Password length must be positive number and less than " + std::to_string(MAX_LENGTH) + ".");

    std::string password;
    for (unsigned i = 0; i < length; i++)
        password += _alphabet[_rand_distr(_rand_gen)];

    return password;
}
