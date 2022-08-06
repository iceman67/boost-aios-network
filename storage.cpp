#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>
#include "Message.hpp"
#include <boost/serialization/vector.hpp>


using namespace boost::archive;

std::vector<Message> vec;

void save(std::string msg)
{
  std::ofstream file{"archive.txt"};
  text_oarchive oa{file};

  oa << msg;
}

void save_m(Message msg)
{
  std::ofstream file{"archive.txt"};
  text_oarchive oa{file};

  
  vec.push_back(msg);

  oa & vec;

}

void load()
{
  std::ifstream file{"archive.txt"};
  text_iarchive ia{file};
  std::string msg;
  ia >> msg;
  std::cout << msg << '\n';
}


void load_m()
{
  std::ifstream file{"archive.txt"};
  text_iarchive ia{file};

  vector<Message> dst;
  Message msg;
  ia >> dst;
  std::cout << dst.size() << '\n';
}

/*
int main()
{
    std::string msg = "hello";
    
    save(msg);
    load();
}
*/
