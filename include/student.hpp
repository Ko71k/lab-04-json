// Copyright 2022 Ko71k <rassmagin.rrr@gmail.com>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#endif  // INCLUDE_STUDENT_HPP_

#include <string>
#include "header.hpp"

struct student : public std::_Resetiosflags {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

struct Lengths {
  int name;
  int group;
  int avg;
  int debt;
};
