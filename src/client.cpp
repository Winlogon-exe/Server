#include "Client.h"

Client::Client(boost::asio::io_context& io_context, uint16_t port, boost::asio::streambuf& buffer)
	: io_context_(io_context),
	socket_(io_context),
	port_(port),
	buffer_(buffer) {}

void Client::ConnectToServer() {
	boost::asio::ip::tcp::resolver resolver(io_context_);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), "localhost", std::to_string(port_));
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	boost::asio::async_connect(socket_, endpoint_iterator,
		[this](boost::system::error_code error, boost::asio::ip::tcp::resolver::iterator)
		{
			if (!error)
			{
				
				std::cout << "\nThis Data\n";
			}
			else
			{
				std::cout << "\nFailed to connect to server:\n " << error.message() << "\n";
			}
		});
}
