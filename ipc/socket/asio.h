boost::asio::

::io_service sendheart_io;//一般都需要一个server

::ip::tcp::resolver resolver(sendheart_io);//do what for resolver?
::ip::tcp::resolver::query query(string(ip), string(port))//ip/port

::ip::tcp::resolver::iterator = resolver.resolve(query);

::ssl::context ctx(::ssl::context::sslv23);

///////////construct
//但凡以handle开关的函数，都是成员函数，以async开关的都是stream socket_的成员函数
class temp;
{
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
}

::SSLAsyncClient(sendheart_io,
	ctx, iterator)
	:socket_(io_service, ctx)
	{
		socket_.lowest_layer().open(boost::asio::ip::tcp::v4());
		socket_.lowest_layer().set_option(boost::asio::ip::tcp::no_delay(true));
		socket_.set_verify_mode(boost::asio::ssl::verify_none);
		socket_.set_verify_callback(boost::bind(::verify_certificate, this, _1, _2));
		
		boost::system::error_code ec;
		boost::asio::connect(socket_.lowest_layer(), iterator, ec);
		
		socket_.async_handshake(boost:asio::ssl::stream_base::client,
			boost::bind(&::handle_handshake, this,//handle_handshake是成员函数，里面有 socket_.async_read_some
			boost::asio::placeholders::error));
	}
///////////////end onstruct
boost::asio::io_service * ioser = &sendheart_io;
error_code ec;
ioser->run(ec);
//////sendheart_io.run();
temp::send(data, len)
{
	boost::asio::async_write(socket_,//与async_read_some相似
		boost::asio::buffer(),
		boost::bind()...)//绑定了handle_write（只是做了错误判断）,
}

//others
sendheart_io.reset()//作用？
