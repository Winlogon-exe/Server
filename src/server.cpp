#include"server.h"

Server::Server(boost::asio::io_context& io_context, uint16_t port, boost::asio::streambuf& buffer)
	: io_context_(io_context),
	port_(port),
	acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}


Connection::Connection(boost::asio::io_context& io_context) :
	socket_(io_context),
	buffer_(std::make_shared<boost::asio::streambuf>()) {}

void Connection::Start()
{
	ReadData();
}

boost::asio::ip::tcp::socket& Connection::socket()
{
	return socket_;
}

void Connection::ReadData()
{
	auto self = shared_from_this();
	boost::asio::async_read_until(socket_, *buffer_, "\n",
		[this, self](boost::system::error_code error, std::size_t bytes_transferred)
		{
			if (!error)
			{
				std::istream input_stream(buffer_.get());
				std::string data;
				std::getline(input_stream, data);
				std::cout << "\nПрочитанные данные: \n" << data << std::endl;
				ReadData();
			}
			else
			{
				std::cout << "Failed to read data: " << error.message() << std::endl;
			}
		});
}

void Server::Listening()
{
	//create object when makes connection 
	auto connection = std::make_shared<Connection>(io_context_);
	acceptor_.async_accept(connection->socket(), [this, connection](const boost::system::error_code& error)
		{
			if (!error)
			{
				std::cout << "Connection LOG\n";
				connection->Start();
			}
			else
			{
				std::cout << "\nFailed listening server: \n" << error.message() << "\n";
			}
			Listening(); 
		});
}

