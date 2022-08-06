#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "include/Message.hpp"

using boost::asio::ip::tcp;

// class session
std::string SHA256HashString(std::string aString);
void save_m(Message msg);
void load_m();


class session 
: public std::enable_shared_from_this<session>
{
    
public: 
    session(tcp::socket socket)
    : socket_(std::move(socket))
    {

    }

    tcp::socket& socket() {
        return socket_;
        
    }

    void start()
    {
        do_read();
    }
    
    
    private: 

    std::string build_sha256(std::string aString){
      std::string s = SHA256HashString(aString);
      return s;

    }

    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            std::cout << "Read data : " << data_ << std::endl;
            hash_ = build_sha256(data_);
            std::cout << "SHA-256: " <<  hash_ << std::endl;
           
            Message m = Message(data_, hash_);
            save_m(m);
            load_m();

            do_write(hash_.length());
          }
        });
        
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
           
        boost::asio::async_write(socket_, boost::asio::buffer(hash_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
           
            do_read();
          }
        });
    }
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    std::string hash_;
};

// end of session
class server
{
public:
  server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    server s(io_context, std::atoi(argv[1]));

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
