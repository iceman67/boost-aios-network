#include <iostream>
#include <boost/thread.hpp>

using namespace std;


boost::mutex a;
const int THREAD_COUNT = 10;

void worker(int i) {
    a.lock();
    // sleep for 3 seconds
    boost::posix_time::seconds workTime(1);
    boost::this_thread::sleep(workTime);

    cout << "Worker thread " << i << endl;
    a.unlock();
}

int main(int argc, char** argv)
{
    boost::thread *threads[THREAD_COUNT];

    // Creation
    for(int i = 0; i < THREAD_COUNT; i++) {
        threads[i] = new boost::thread(worker, i);
    }

    std::cout << "main: waiting for thread" << std::endl;

    // Cleanup
    for(int i = 0; i < THREAD_COUNT; i++) {
        threads[i]->join();
        delete threads[i];
    }
    std::cout << "main: done" << std::endl;

    return 0;
}