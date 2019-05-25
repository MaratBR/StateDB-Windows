#include "stdafx.h"
#include "asio_stream.h"
#include "net_utils.h"

using namespace statedb::utils;
using namespace statedb::net;
using namespace boost;

size_t _asio_seek_impl(tcp::socket& socket_, std::streamoff off, std::ios_base::seekdir way)
{
	assert(way == std::ios::cur);
	return utils::skip_bytes(socket_, static_cast<int>(off));
}

void asio_istream::read(byte_t* dest, size_t count)
{
	assert(socket_.read_some(boost::asio::buffer(dest, count)) == count);
}

std::streampos asio_istream::tellg()
{
	return pos;
}

abstract_istream& asio_istream::seekg(std::streampos pos_)
{
	assert(pos_ >= pos);
	pos += _asio_seek_impl(socket_, pos_ - pos, std::ios::cur);
	return *this;
}

abstract_istream& asio_istream::seekg(std::streamoff off, std::ios_base::seekdir way)
{
	pos += _asio_seek_impl(socket_, off, way);
	return *this;
}

void statedb::net::asio_ostream::write(byte_t* src, size_t srcLen)
{
	assert(socket_.write_some(boost::asio::buffer(src, srcLen)) == srcLen);
}

std::streampos statedb::net::asio_ostream::tellp()
{
	return std::streampos();
}

abstract_ostream& asio_ostream::seekp(std::streampos pos_)
{
	assert(pos_ >= pos);
	pos += _asio_seek_impl(socket_, pos_ - pos, std::ios::cur);
	return *this;
}

abstract_ostream& asio_ostream::seekp(std::streamoff off, std::ios_base::seekdir way)
{
	pos += _asio_seek_impl(socket_, off, way);
	return *this;
}

statedb::net::asio_base_stream::asio_base_stream(tcp::socket& socket_)
	: socket_(socket_)
{
}

void asio_buf_ostream::write(byte_t* src, size_t srcLen)
{
	assert(!locked());
	buffer.insert(buffer.end(), src, src + srcLen);
	pos += srcLen;
}

std::streampos asio_buf_ostream::tellp()
{
	return pos;
}

abstract_ostream& asio_buf_ostream::seekp(std::streampos pos)
{
	assert(!locked());
	assert(pos >= this->pos);
	while (pos > this->pos)
	{
		buffer.push_back(EMPTY_SPACE_BYTE);
		pos -= 1;
	}
	return *this;
}

abstract_ostream& asio_buf_ostream::seekp(std::streamoff off, std::ios_base::seekdir way)
{
	assert(way == std::ios::cur);
	while (off > 0)
	{
		buffer.push_back(EMPTY_SPACE_BYTE);
		off -= 1;
	}
	return *this;
}

size_t asio_buf_ostream::flush_to(tcp::socket& socket_)
{
	return socket_.write_some(asio::buffer(buffer));
}

void asio_buf_ostream::async_flush_to(tcp::socket& socket_, boost::function<void(const boost::system::error_code&, size_t)> h)
{
	assert(!locked());
	lock();
	socket_.async_write_some(asio::buffer(buffer), [&h, this](const boost::system::error_code & ec, size_t bt) { this->unlock(); this->discard(); h(ec, bt); });
}
