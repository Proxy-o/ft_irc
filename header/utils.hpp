#pragma once 

#include "Server.hpp"
#include <string>


/**
 * Splits a string into a vector of substrings based on a delimiter.
 *
 * @param buffer The string to be split.
 * @param delimiter The delimiter used to split the string.
 * @return A vector of substrings.
 */
std::vector<std::string> ft_split(std::string buffer, std::string delimiter);
/**
 * Prints the elements of a vector of strings.
 * 
 * @param vec The vector of strings to be printed.
 */
void printVector(std::vector<std::string> &vec);
/**
 * @brief Formats the given message.
 * 
 * This function formats the message by modifying it in-place by 
 * removing " \r \n" from the start and the end.
 * 
 * @param message The message to be formatted.
 */
void formatMessage(std::string &message);