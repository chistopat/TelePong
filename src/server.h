//
// Created by Yegor Chistyakov on 19.12.2021.
//

#ifndef TELEPONG_SRC_SERVER_H_
#define TELEPONG_SRC_SERVER_H_

#define EVER ;;

#include <cstdlib>
#include <cinttypes>
#include <iostream>
#include <memory>

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

namespace telepong {

using boost::asio::ip::tcp;
using SocketHolder = std::shared_ptr<tcp::socket>;
using IOService = std::unique_ptr<boost::asio::io_service>;
using Acceptor = std::unique_ptr<boost::asio::ip::tcp::acceptor>;

class Server {
public:
  explicit Server(int port) : port_(port) {
    io_service_ = std::make_unique<boost::asio::io_service>();
    auto endpoint = tcp::endpoint(tcp::v4(), port_);
    acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(*io_service_, endpoint);
  }

  ~Server() {
    std::cout << "Server halted!" << std::endl;
  }

public:
  [[noreturn]] void run() {
    for (;;) {
      auto socket_ = std::make_shared<tcp::socket>(*io_service_);
      acceptor_->accept(*socket_);
      boost::thread thread([socket_] { return handle(socket_); });
    }
  }

private:
  static constexpr auto kMaxLength = 10;
private:
  static void handle(SocketHolder socket)
  {
    try
    {
      for (;;)
      {
        char data[kMaxLength];

        boost::system::error_code error;
        size_t length = socket->read_some(boost::asio::buffer(data), error);
        if (error == boost::asio::error::eof)
          break; // Connection closed cleanly by peer.
        else if (error)
          throw boost::system::system_error(error); // Some other error.

        boost::asio::write(*socket, boost::asio::buffer(data, length));
      }
    }
    catch (std::exception& e)
    {
      std::cerr << "Exception in thread: " << e.what() << "\n";
    }
  }

private:
  IOService io_service_;
  uint16_t port_;
  Acceptor acceptor_;
};

} // telepong namespace
#endif // TELEPONG_SRC_SERVER_H_
