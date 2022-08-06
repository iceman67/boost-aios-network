#include <iostream>
#include <boost/thread.hpp>

using namespace std;

void readerApi(int* readVar)
{
  for (int i=0; i < 10; i++) {
    usleep(400);
    cout << "readerApi: " << *readVar
              << endl;
  }
}
void writerApi(int* writeVar)
{
  for (int i=0; i < 10; i++) {
    cout << "writerApi: " << *writeVar
              << endl;
    usleep(400);
    *writeVar = (*writeVar)++;
  }
}

int main()
{
  int variable = 100;
  boost::thread readerThread(readerApi, &variable);
  boost::thread writerThread(writerApi, &variable);

  readerThread.join();
  writerThread.join();
}