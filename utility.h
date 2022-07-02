#ifndef PROJECT_UTILITY_H
#define PROJECT_UTILITY_H

#include <string>

#include <sstream>

#include <regex>

#include <vector>


//in this method we remove extra spaces from a string
//using regex
//ref:https://en.cppreference.com/w/cpp/regex
//also used: https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c

std::string removeExtraSpaces(std::string str) {
  std::string result = str;
  result = regex_replace(result, std::regex("\\s*\n\\s*"), "\n");
  result = regex_replace(result, std::regex("\n\n"), "\n");
  result = regex_replace(result, std::regex("\t"), " ");

  //remove leading and trailing spaces
  result = regex_replace(result, std::regex("^\\s+"), "");
  result = regex_replace(result, std::regex("\\s+$"), "");

  return result;
}

std::vector < std::string > split(std::string str, char delimiter) {
  std::vector < std::string > result;
  std::string token;
  std::stringstream ss(str);
  while (std::getline(ss, token, delimiter)) {
    result.push_back(token);
  }

  return result;
}

//calculate the gcd of two integers
//we use the recursive approach
int gcd_euclid(int a, int b) {
  if (a == 0)
    return b;
  if (b == 0)
    return a;

  if (a > b)
    return gcd_euclid(a - b, b);
  else
    return gcd_euclid(a, b - a);
}

//this struct is used to store the amount and unit of an ingredient
//and to deal with fractions
// p + numerator / denominator = fraction
typedef struct fraction {
  int p; //the integer part of the fraction
  int numerator;
  int denominator;

  //method extract fraction from string
  static struct fraction fromString(std::string str) {
    struct fraction result;
    std::vector < std::string > parts = split(str, '-');
    if (parts.size() == 2) { //if there is a minus sign
      result.p = std::stoi(parts[0]);
      parts = split(parts[1], '/');
      result.numerator = std::stoi(parts[0]);
      result.denominator = std::stoi(parts[1]);
    } else { //if there is no minus sign
      result.p = 0;
      parts = split(parts[0], '/');
      result.numerator = std::stoi(parts[0]);
      if (parts.size() == 2) { //if there is a fraction
        result.denominator = std::stoi(parts[1]);
      } else {
        result.denominator = 1;
      }
    }
    return result;
  }

  //method to get string representation of fraction
  std::string toString() {
    std::string result = "";
    if (p != 0) {
      result += std::to_string(p);
    }
    if (numerator != 0) {
      if (p != 0)
        result += "-";
      result += std::to_string(numerator) + (denominator != 1 ? "/" + std::to_string(denominator) : "");
    }
    return result;
  }

  //method to adjust fraction
  // 4/8 -> 1/2
  // 1-4/3 -> 2-1/3
  void adjust() {
    if (numerator % denominator == 0) {
      p += numerator / denominator;
      numerator = 0;
      denominator = 1;
    } else if (float(numerator) / denominator > 1) {
      p += numerator / denominator;
      numerator %= denominator;
      int gcd = gcd_euclid(numerator, denominator);
      numerator /= gcd;
      denominator /= gcd;
    } else {
      int gcd = gcd_euclid(numerator, denominator);
      numerator /= gcd;
      denominator /= gcd;
    }
  }

  //method to calculate the amount of an ingredient in one serving
  // xAmount = "1/2" and serving = 2 -> return "1/4"  
  // xAmount = "3" and serving = 2 -> return "1-1/2"
  // xAmount = "2-1/2" and serving = 2 -> return "1-1/4"
  // xAmount = "1-1/4" and serving = 2 -> return "3/4"
  std::string perServing(int n) {
    std::string result = "";
    struct fraction f;
    int numerator_ = this -> numerator + denominator * p;
    int denominator_ = this -> denominator * n;

    f.p = numerator_ / denominator_;
    f.numerator = numerator_ % denominator_;
    f.denominator = denominator_;

    return f.toString();
  }

  void changeServings(int numerator, int denominator) {
    this -> numerator = (this -> p * this -> denominator + this -> numerator) * numerator;
    this -> denominator = this -> denominator * denominator;
    this -> p = 0;
    adjust();
  }

  //format the fraction to a regular fraction  n/d
  void toNumeratorAndDenominator(int & numerator, int & denominator) {
    numerator = this -> p * this -> denominator + this -> numerator;
    denominator = this -> denominator;
  }

}
Fraction;

#endif //PROJECT_UTILITY_H