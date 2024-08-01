#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <string.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class mUdpServer {
private:
    udp::socket socket_;
    udp::endpoint sender_endpoint_;
    enum {max_length = 1024};
    char data_[max_length];

public:
    mUdpServer(boost::asio::io_service& io_service, short port) 
        : socket_(io_service, udp::endpoint(udp::v4(), port)) {
            mudp_receive();
    }

    void mudp_receive() {
        // do asyn receiving to buffer data_
        // [captures] (params) {body}
        socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_,
            [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                if (!ec && recvd_bytes > 0) {
                    std::cout << data_ << std::endl;
                    mudp_send_back();
                } else {
                    mudp_receive();
                }
            });
    }

    void mudp_send_back() {
        // do add sender information and send back
        std::string mStr = "Sender endpoint: ";
        mStr += sender_endpoint_.address().to_string().c_str();
        mStr += " port ";
        mStr += std::to_string((int)sender_endpoint_.port());
        mStr += data_;
        socket_.async_send_to(boost::asio::buffer(mStr.c_str(), mStr.length()), sender_endpoint_,
            [this] (boost::system::error_code ec, std::size_t recvd_bytes) {
                mudp_receive();
            });
    }
};

#endif
