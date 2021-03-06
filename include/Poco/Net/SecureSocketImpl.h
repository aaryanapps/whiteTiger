//
// SecureSocketImpl.h
//
// $Id: //poco/svn/NetSSL_OpenSSL/include/Poco/Net/SecureSocketImpl.h#1 $
//
// Library: NetSSL_OpenSSL
// Package: SSLSockets
// Module:  SecureSocketImpl
//
// Definition of the SecureSocketImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef NetSSL_SecureSocketImpl_INCLUDED
#define NetSSL_SecureSocketImpl_INCLUDED


#include "Poco/Net/NetSSL.h"
#include "Poco/Net/SocketImpl.h"
#include <openssl/bio.h>
#include <openssl/ssl.h>


namespace Poco {
namespace Net {


class HostEntry;


class NetSSL_API SecureSocketImpl
	/// The SocketImpl for SecureStreamSocket.
{
public:
	SecureSocketImpl();
		/// Creates the SecureSocketImpl.

	SecureSocketImpl(SSL* _pSSL);
		/// Creates the SecureSocketImpl.

	virtual ~SecureSocketImpl();
		/// Destroys the SecureSocketImpl.

	SocketImpl* acceptConnection(SocketAddress& clientAddr);
		/// Get the next completed connection from the
		/// socket's completed connection queue.
		///
		/// If the queue is empty, waits until a connection
		/// request completes.
		///
		/// Returns a new TCP socket for the connection
		/// with the client.
		///
		/// The client socket's address is returned in clientAddr.
	
	void connect(const SocketAddress& address);
		/// Initializes the socket and establishes a connection to 
		/// the TCP server at the given address.
		///
		/// Can also be used for UDP sockets. In this case, no
		/// connection is established. Instead, incoming and outgoing
		/// packets are restricted to the specified address.

	void connect(const SocketAddress& address, const Poco::Timespan& timeout);
		/// Initializes the socket, sets the socket timeout and 
		/// establishes a connection to the TCP server at the given address.

	void connectNB(const SocketAddress& address);
		/// Initializes the socket and establishes a connection to 
		/// the TCP server at the given address. Prior to opening the
		/// connection the socket is set to nonblocking mode.
	
	void bind(const SocketAddress& address, bool reuseAddress = false);
		/// Bind a local address to the socket.
		///
		/// This is usually only done when establishing a server
		/// socket. TCP clients should not bind a socket to a
		/// specific address.
		///
		/// If reuseAddress is true, sets the SO_REUSEADDR
		/// socket option.
		
	void listen(int backlog = 64);
		/// Puts the socket into listening state.
		///
		/// The socket becomes a passive socket that
		/// can accept incoming connection requests.
		///
		/// The backlog argument specifies the maximum
		/// number of connections that can be queued
		/// for this socket.

	void close();
		/// Close the socket.
	
	int sendBytes(const void* buffer, int length, int flags = 0);
		/// Sends the contents of the given buffer through
		/// the socket. Any specified flags are ignored.
		///
		/// Returns the number of bytes sent, which may be
		/// less than the number of bytes specified.
	
	int receiveBytes(void* buffer, int length, int flags = 0);
		/// Receives data from the socket and stores it
		/// in buffer. Up to length bytes are received.
		///
		/// Returns the number of bytes received.
	
	int sendTo(const void* buffer, int length, const SocketAddress& address, int flags = 0);
		/// Sends the contents of the given buffer through
		/// the socket to the given address.
		///
		/// Returns the number of bytes sent, which may be
		/// less than the number of bytes specified.
	
	int receiveFrom(void* buffer, int length, SocketAddress& address, int flags = 0);
		/// Receives data from the socket and stores it
		/// in buffer. Up to length bytes are received.
		/// Stores the address of the sender in address.
		///
		/// Returns the number of bytes received.
	
	void sendUrgent(unsigned char data);
		/// Sends one byte of urgent data through
		/// the socket.
		///
		/// The data is sent with the MSG_OOB flag.
		///
		/// The preferred way for a socket to receive urgent data
		/// is by enabling the SO_OOBINLINE option.

	poco_socket_t sockfd();
		// Returns the socket.

	void setTunnelEndPoint(const std::string& endHost, Poco::UInt16 endPort);
		/// Due to the fact that SSLConnections that run over proxies require
		/// a different connect phase (ie send an unencrypted HTTP CONNECT before
		/// establishing, we must inform the socket that is only used as a proxy
		/// that works as a tunnel to the given endPoint.
		/// Only call this method on disconnected sockets.

protected:
	void setSockfd(poco_socket_t sock);
		/// Set a socket description iff no socket is already set.

	void invalidate();
		/// Invalidate the current socket. Must only be called on closed sockets.

	static long postConnectionCheck(bool onServer, SSL* pSSL, const std::string& host);
		/// PostConnectionCheck to verify that a peer really presented a valid certificate.
		/// if onserver is false, used by clients to verify that a server is really the one it claims.
		/// if onserver is true, used by the server to verify that a client is really the one it claims.

	void connectSSL(const SocketAddress& address);
		/// Creates and connects an SSL connection. Set _pSSL on success or exception otherwise.

	void establishTunnel();
		/// Creates a socket to the proxy and sends CONNECT.

	static bool containsWildcards(const std::string& commonName);
		/// Checks if the commonName of a certificate contains wildcards

	static bool matchByAlias(const std::string& alias, const HostEntry& heData);
		/// Checks if the alias is contained in heData

private:
	SecureSocketImpl(const SecureSocketImpl&);
	SecureSocketImpl& operator = (const SecureSocketImpl&);

private:
	BIO* _pBIO;
	SSL* _pSSL;
	SocketImpl   _socket;
	std::string  _endHost;
	Poco::UInt16 _endPort;
};


//
// inlines
//
inline poco_socket_t SecureSocketImpl::sockfd()
{
	return _socket.sockfd();
}


inline void SecureSocketImpl::setSockfd(poco_socket_t sock)
{
	_socket.setSockfd(sock);
}


inline void SecureSocketImpl::invalidate()
{
	_socket.invalidate();
}


inline void SecureSocketImpl::setTunnelEndPoint(const std::string& endHost, Poco::UInt16 endPort)
{
	poco_assert (endPort != 0 && !endHost.empty());

	_endHost = endHost;
	_endPort = endPort;
}


} } // namespace Poco::Net


#endif // NetSSL_SecureSocketImpl_INCLUDED
