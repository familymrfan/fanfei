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
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


int count = 0;

void print(const boost::system::error_code& /*e*/){
  std::cout << "print:aysn wait"<<std::endl;
}

void print_param(const boost::system::error_code& /*e*/,boost::asio::deadline_timer *t){
  if(count > 10)
    return ;
  std::cout << "print_param:aysn wait"<<count++<<" thread id"<< std::this_thread::get_id() <<std::endl;
  t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
  t->async_wait(boost::bind(print_param,boost::asio::placeholders::error, t));
}

class Print
{
public:
  Print(boost::asio::io_service& io)
      : timer_(io, boost::posix_time::seconds(10)){
	  timer_.async_wait(boost::bind(&Print::print, this));
  }
  void print()
  {
      std::cout<< "class print:aysn wait" << std::endl;
  }
private:
  boost::asio::deadline_timer timer_;
};

void io_run(boost::asio::io_service *io){
    io->run();
}

int main()
{
    boost::asio::io_service io;
    Print p(io);
    boost::asio::deadline_timer t(io,boost::posix_time::seconds(5));
    t.async_wait(&print);
    t.async_wait(boost::bind(print_param,boost::asio::placeholders::error, &t));
    t.wait();
    std::cout << "sync wait\n";
    std::thread thrd(io_run,&io);
    io.run();
    thrd.join();
    std::cout << "do some after" << std::endl;
  
    return 0;
}