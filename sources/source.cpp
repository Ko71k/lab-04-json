// Copyright 2021 Lasar1k <alf.ivan2002@gmail.com>

#include <any>
#include "../include/header.hpp"

using json = nlohmann::json;

std::string get_name(json* stt) {
  std::string name;
  if (stt->at("name").is_string()) {
    name = stt->at("name").get<std::string>();
  }
  return name;
}

std::any get_group(json* stt) {
  std::any group;
  if (stt->at("group").is_string()) {
    group = stt->at("group").get<std::string>();
  }

  if (stt->at("group").is_number_integer()) {
    group = stt->at("group").get<int>();
  }

  return group;
}

std::any get_avg(json* stt) {
  std::any avg;
  if (stt->at("avg").is_number_integer()) {
    avg = stt->at("avg").get<int>();
  }

  if (stt->at("avg").is_string()) {
    avg = stt->at("avg").get<std::string>();
  }

  if (stt->at("avg").is_number_float()) {
    avg = stt->at("avg").get<float>();
  }

  return avg;
}
// dssad
std::any get_debt(json* stt) {
  std::any debt;
  if (stt->at("debt").is_string()) {
    debt = stt->at("debt").get<std::string>();
  }

  if (stt->at("debt").is_null()) {
    debt = (std::string) "null";
  }

  if (stt->at("debt").is_array()) {
    debt = static_cast<int>(stt->at("debt").size());
  }

  return debt;
}

std::pair<std::vector<student>, std::string> parse_json(const json & jf) {
  std::pair<std::vector<student>, std::string> answer;

  if (!jf.at("items").is_array()) {
    answer.first = std::vector<student>{};
    answer.second = "Items is not an array!";
    return answer;
  }
  if (jf.at("items").size() != jf.at("_meta").at("count")) {
    answer.first = std::vector<student>{};
    answer.second = "Invalid number of students. The counter doesn't match";
    return answer;
  }
  std::vector<student> the_students;
  for (auto& el : jf.at("items").items()) {
    json stt = el.value();
    student the_student;
    // NAME-----------------------------------------
    the_student.name = get_name(&stt);
    if (the_student.name == "") {
      std::string error =
          "Incorrect name of student:  " + to_string(stt.at("name"));
      answer.first = std::vector<student>{};
      answer.second = error;
      return answer;
    }
    //----------------------------------------------

    // GROUP----------------------------------------
    the_student.group = get_group(&stt);
    if (!the_student.group.has_value()) {
      //      std::cout << "Incorrect group of student " << stt.at("group")
      //                << std::endl;
      answer.first = std::vector<student>{};
      answer.second =
          "Incorrect group of student " + to_string(stt.at("group"));
      return answer;
    }
    //    if (stt.at("group").is_number_float()) {
    //      the_student.group = (float)stt.at("group");
    //    }
    //----------------------------------------------

    // AVG------------------------------------------
    the_student.avg = get_avg(&stt);
    if (!the_student.avg.has_value()) {
      //      std::cout << "Incorrect avg of student " << stt.at("avg") <<
      //      std::endl;
      answer.first = std::vector<student>{};
      answer.second = "Incorrect avg of student " + to_string(stt.at("avg"));
      return answer;
    }
    //----------------------------------------------

    // DEBT-----------------------------------------
    the_student.debt = get_debt(&stt);
    if (!the_student.debt.has_value()) {
      //      std::cout << "Incorrect debt of student " << stt.at("debt") <<
      //      std::endl;
      answer.first = std::vector<student>{};
      answer.second = "Incorrect debt of student: " + to_string(stt.at("debt"));
      return answer;
    }
    //----------------------------------------------
    //    the_students[counter] = the_student;
    //    counter++;
    the_students.push_back(the_student);
  }
  answer.first = the_students;
  answer.second = "";
  return answer;
}

Lengths get_lengths(std::vector<student> the_students) {
  Lengths ls{0, 0, 0, 0};
  for (student the_student1 : the_students) {
    if (static_cast<int>(the_student1.name.length()) > ls.name) {
      ls.name = static_cast<int>(the_student1.name.length());
    }

    if (the_student1.group.type() == typeid(int)) {
      std::string strgroup = std::to_string(std::any_cast<int>(the_student1.group));

      if (static_cast<int>(strgroup.length()) > ls.group) {
        ls.group = static_cast<int>(strgroup.length());
      }
    } else if (the_student1.group.type() == typeid(std::string)) {
      //      std::cout <<
      //      (int)std::any_cast<std::string>(the_student1.group).length() << "  "
      //      << std::any_cast<std::string>(the_student1.group) << std::endl;
      if (static_cast<int>(
              std::any_cast<std::string>(the_student1.group).length()) > ls.group) {
        ls.group = static_cast<int>(
            std::any_cast<std::string>(the_student1.group).length());
      }
    } else {
      return Lengths{};
    }
    if (the_student1.avg.type() == typeid(int)) {
      std::string stravg = std::to_string(std::any_cast<int>(the_student1.avg));
      if (static_cast<int>(stravg.length()) > ls.avg) {
        ls.avg = static_cast<int>(stravg.length());
      }
    } else if (the_student1.avg.type() == typeid(std::string)) {
      if (static_cast<int>(std::any_cast<std::string>(the_student1.avg).length()) >
          ls.avg) {
        ls.avg =
            static_cast<int>(std::any_cast<std::string>(the_student1.avg).length());
      }
    } else if (the_student1.avg.type() == typeid(float)) {
      std::string stravg = std::to_string(std::any_cast<float>(the_student1.avg));
      if (static_cast<int>(stravg.length()) > ls.avg) {
        ls.avg = static_cast<int>(stravg.length());
      }
    } else {
      return Lengths{};
    }
    if (the_student1.debt.type() == typeid(std::string)) {
      if (static_cast<int>(std::any_cast<std::string>(the_student1.debt).length()) >
          ls.debt) {
        ls.debt = static_cast<int>(
            std::any_cast<std::string>(the_student1.debt).length());
      }
    } else if (the_student1.debt.type() == typeid(int)) {
      std::string strdebt = std::to_string(std::any_cast<int>(the_student1.debt));
      if (static_cast<int>(strdebt.length()) + 6 > ls.debt) {
        ls.debt = static_cast<int>(strdebt.length()) + 6;
      }
    } else {
      return Lengths{};
    }
  }
  return ls;
}

bool output(const std::vector<student>& the_students, std::ostream& os) {
  std::string s = "-";
  std::stringstream ss;
  ss.precision(5);
  char dash;
  dash = s[0];
  std::string s2 = " ";
  char space;
  space = s2[0];
  os.precision(2);
  os.fill(dash);
  os.setf(std::ios::left);
  Lengths ls = get_lengths(the_students);
  os << std::setw(ls.name + 5) << "|" << std::setw(ls.group + 7) << "|"
     << std::setw(ls.avg + 5) << "|" << std::setw(ls.debt + 5) << "|";
  os << "|" << std::endl;
  os.fill(space);
  os << std::setw(ls.name + 5) << "| name" << std::setw(ls.group + 7)
     << "| group" << std::setw(ls.avg + 5) << "| avg" << std::setw(ls.debt + 5)
     << "| debt";
  os << "|" << std::endl;
  for (student the_student : the_students) {
    os.fill(dash);
    os << std::setw(ls.name + 5) << "|" << std::setw(ls.group + 7) << "|"
       << std::setw(ls.avg + 5) << "|" << std::setw(ls.debt + 5) << "|";
    os << "|" << std::endl;
    os.fill(space);
    std::string nametable = "| " + the_student.name;
    os << std::setw(ls.name + 5) << nametable;

    if (the_student.group.type() == typeid(int)) {
      std::string grouptable =
          "| " + std::to_string(std::any_cast<int>(the_student.group));
      os << std::setw(ls.group + 7) << grouptable;
    } else if (the_student.group.type() == typeid(std::string)) {
      std::string grouptable = "| " + std::any_cast<std::string>(the_student.group);
      os << std::setw(ls.group + 7) << grouptable;
    } else {
      return false;
    }
    if (the_student.avg.type() == typeid(int)) {
      std::string avgtable =
          "| " + std::to_string(std::any_cast<int>(the_student.avg));
      os << std::setw(ls.avg + 5) << avgtable;
    } else if (the_student.avg.type() == typeid(std::string)) {
      std::string avgtable = "| " + std::any_cast<std::string>(the_student.avg);
      os << std::setw(ls.avg + 5) << avgtable;
    } else if (the_student.avg.type() == typeid(float)) {
      ss << "| " << std::any_cast<float>(the_student.avg);
      std::string avgtable = ss.str();
      os << std::setw(ls.avg + 5) << avgtable;
    } else {
      return false;
    }
    if (the_student.debt.type() == typeid(std::string)) {
      std::string debttable = "| " + std::any_cast<std::string>(the_student.debt);
      os << std::setw(ls.debt + 5) << debttable;
    } else if (the_student.debt.type() == typeid(int)) {
      std::string debttable =
          "| " + std::to_string(std::any_cast<int>(the_student.debt)) + " items";
      os << std::setw(ls.debt + 5) << debttable;
    } else {
      return false;
    }
    os << "|" << std::endl;
  }
  os.fill(dash);
  os << std::setw(ls.name + 5) << "|" << std::setw(ls.group + 7) << "|"
     << std::setw(ls.avg + 5) << "|" << std::setw(ls.debt + 5) << "|";
  os << "|" << std::endl;
  return true;
}
