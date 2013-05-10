//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/concept_check.hpp>
#include <thread>
#include <functional>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    message_ = make_daytime_string();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }

  tcp::socket socket_;
  std::string message_;
};

class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), 13))
  {
    start_accept();
  }

private:
  void start_accept()
  {
    tcp_connection::pointer new_connection =
      tcp_connection::create(acceptor_.get_io_service());

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
    }

    start_accept();
  }

  tcp::acceptor acceptor_;
};

class udp_server
{
public:
  udp_server(boost::asio::io_service& io_service)
    : socket_(io_service, udp::endpoint(udp::v4(), 13))
  {
    start_receive();
  }

private:
  void start_receive()
  {
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive(const boost::system::error_code& error,
      std::size_t /*bytes_transferred*/)
  {
    if (!error || error == boost::asio::error::message_size)
    {
      boost::shared_ptr<std::string> message(
          new std::string(make_daytime_string()));

      socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
          boost::bind(&udp_server::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

      start_receive();
    }
  }

  void handle_send(boost::shared_ptr<std::string> /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/)
  {
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 1> recv_buffer_;
};

void runServiceTCP(boost::asio::io_service *io){
    io->run();
}

void runServiceUDP(boost::asio::io_service *io){
    io->run();
}

int main()
{
  try
  {
    std::cout<< "start TCP service"<<std::endl;
    boost::asio::io_service io_service_server_tcp;
    tcp_server server_tcp(io_service_server_tcp);
    std::thread thrd_tcp(std::bind(runServiceTCP,&io_service_server_tcp));
    
    std::cout<< "start UDP service"<<std::endl;
    boost::asio::io_service io_service_server_udp;
    udp_server server_udp(io_service_server_udp);
    std::thread thrd_udp(std::bind(runServiceUDP,&io_service_server_udp));
    
    {
      std::cout<< "start TCP client"<<std::endl;
      boost::asio::io_service io_service_client_tcp;
      tcp::resolver resolver(io_service_client_tcp);
      tcp::resolver::query query("127.0.0.1", "daytime");
      tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
      tcp::socket socket(io_service_client_tcp);
      boost::asio::connect(socket, endpoint_iterator);
      
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error != boost::asio::error::eof && !error){
	std::cout.write(buf.data(), len);
      }
    }
    
    {
      std::cout<< "start UDP client"<<std::endl;
      boost::asio::io_service io_service_server_udp;

      udp::resolver resolver(io_service_server_udp);
      udp::resolver::query query(udp::v4(), "127.0.0.1", "daytime");
      udp::endpoint receiver_endpoint = *resolver.resolve(query);

      udp::socket socket(io_service_server_udp);
      socket.open(udp::v4());

      boost::array<char, 1> send_buf  = {{ 0 }};
      socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

      boost::array<char, 128> recv_buf;
      udp::endpoint sender_endpoint;
      size_t len = socket.receive_from(
	  boost::asio::buffer(recv_buf), sender_endpoint);

      std::cout.write(recv_buf.data(), len);
    }
    thrd_tcp.join();
    thrd_udp.join();
  } 
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}