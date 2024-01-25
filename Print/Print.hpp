#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <string>

#include "../Macros/Colors.hpp"

template <typename T>
void printBlack(const T& val) {
  std::cout << BLACK << val << RESET << std::endl;
}

template <typename T>
void printRed(const T& val) {
  std::cout << RED << val << RESET << std::endl;
}

template <typename T>
void printGreen(const T& val) {
  std::cout << GREEN << val << RESET << std::endl;
}

template <typename T>
void printYellow(const T& val) {
  std::cout << YELLOW << val << RESET << std::endl;
}

template <typename T>
void printBlue(const T& val) {
  std::cout << BLUE << val << RESET << std::endl;
}

template <typename T>
void printPurple(const T& val) {
  std::cout << PURPLE << val << RESET << std::endl;
}

template <typename T>
void printCyan(const T& val) {
  std::cout << CYAN << val << RESET << std::endl;
}

template <typename T>
void printWhite(const T& val) {
  std::cout << WHITE << val << RESET << std::endl;
}

template <typename T>
void printDebug(const std::string& key, const T& val) {
  std::cout << "=============\n";
  std::cout << key << ": " << val << std::endl;
  std::cout << "=============\n";
}

void printPikachu();

void printHi();

#endif