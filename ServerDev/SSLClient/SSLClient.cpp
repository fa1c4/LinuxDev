#include <iostream>
#include "SSLClient.h"


SSLClient::SSLClient(boost::asio::io_context &io_context,
                        boost::asio::ssl::context &ssl_context,
                        const tcp::resolver::results_type &endpoints,
                        char* message): socket_(io_context, ssl_context) {
    memset(sendBuffer, '\0', max_length);
    memset(recvBuffer, '\0', max_length);
    memcpy(sendBuffer, message, strlen(message));

    socket_.set_verify_mode(boost::asio::ssl::verify_peer);
    socket_.set_verify_callback(
        std::bind(&SSLClient::verify_certificate, this, std::placeholders::_1, std::placeholders::_2)
    );
    start(endpoints);
}

bool SSLClient::verify_certificate(bool preverified, boost::asio::ssl::verify_context &ctx) {
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

    return preverified;
}

void SSLClient::start(const tcp::resolver::results_type &endpoints) {
    boost::asio::async_connect(socket_.lowest_layer(), endpoints,
        boost::bind(&SSLClient::handle_connect, this, boost::asio::placeholders::error));
}

void SSLClient::handle_connect(const boost::system::error_code &error) {
    if (!error) {
        socket_.async_handshake(boost::asio::ssl::stream_base::client,
            boost::bind(&SSLClient::handle_handshake, this, boost::asio::placeholders::error));
    } else {
        std::cout << "Connect Failed: " << error.message() << std::endl;
    }
}

void SSLClient::handle_handshake(const boost::system::error_code &error) {
    if (!error) {
        size_t length = std::strlen(sendBuffer);
        boost::asio::async_write(socket_, boost::asio::buffer(sendBuffer, length),
            boost::bind(&SSLClient::handle_write, this,
                boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Handshake Failed: " << error.message() << std::endl;
    }
}

void SSLClient::handle_write(const boost::system::error_code &error, std::size_t length) {
    if (!error) {
        boost::asio::async_read(socket_, boost::asio::buffer(recvBuffer, length),
            boost::bind(&SSLClient::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Write Failed: " << error.message() << std::endl;
    }
}

void SSLClient::handle_read(const boost::system::error_code &error, std::size_t length) {
    if (!error) {
        std::cout << "Reply: " << recvBuffer << std::endl;
    } else {
        std::cout << "Read Failed: " << error.message() << std::endl;
    }
}


int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Usage: ssl_client <host> <port> <PEM file> <message>" << std::endl;
        exit(-1);
    }

    try {
        // step1: start io context
        boost::asio::io_context io_context;
        // step2: resolve host and port
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);
        // step3: init ssl_context
        boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::sslv23);
        ssl_ctx.load_verify_file(argv[3]);
        // step4: init. ssl_client
        SSLClient sslc(io_context, ssl_ctx, endpoints, argv[4]);
        io_context.run();
        exit(0);
    } catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

/*
openssl reg -x509 -sha256 -nodes -newkey rsa::2048 -keyout server.key -out server.pem
*/
