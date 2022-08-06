#pragma once

#include <string>
#include <iostream>
#include <cstdio> 
using namespace std;

#include <boost/serialization/serialization.hpp>

class Message {
 public:
  Message(std::string msg = "", string hash = "") {
    msg_ = msg;
    hash_ = hash;
  }

  std::string get_messge() {
    return msg_;
  }

  std::string get_hash() {
    return hash_;
  }

  /**
   * @brief This method is used to compare loaded data from the original one. No need to implement
   * this if you don't need it.
   *
   */
  friend bool operator==(const Message &c1, const Message &c2) {
    return (c1.msg_ == c2.msg_) && (c1.hash_ == c2.hash_);
  }

 private:
  string hash_;
  string msg_;

  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;
  // Implement serialize method
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &msg_ &hash_;  // Simply serialize the data members
  }
};