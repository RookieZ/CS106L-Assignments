/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Xiaochen Zhang"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::ifstream istream(filename.c_str());
  std::set<std::string> result;

  if(!istream.is_open()) {
    std::cerr << "打开文件失败" << std::endl;
    return result;
  }

  std::string line;
  while(getline(istream, line)) {
    result.insert(line);
  }

  return result;
}

bool is_initials_equal(std::string n1, std::string n2) {
  std::string r1 = n1.substr(0, 1);
  r1 += n1.substr(n1.find(" ") + 1, 1);
  std::string r2 = n2.substr(0, 1);
  r2 += n2.substr(n2.find(" ") + 1, 1);

  return r1 == r2;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::queue<const std::string*> result;
  for(const auto& student_name : students) {
    if(is_initials_equal(name, student_name)) {
      result.push(&student_name);
    }
  }

  return result;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.
  if(matches.empty()) {
    return std::string{"NO MATCHES FOUND."};
  } else {
    const std::string* result = matches.front();
    return *result;
  }
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
