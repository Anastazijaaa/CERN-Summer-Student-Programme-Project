
#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP


#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <memory>
#include <ios>

#define URLPOSITIONVERSION 1
#define URLPOSITIONPATH 3

#define BOOST_SPIRIT_THREADSAFE
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "nlohmann/json.hpp"


#include "server_http.hpp"
#include "functions.hpp"


typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

class WebServer {


public:
	WebServer(boost::filesystem::path web_root);

	~WebServer();

	void setup();

	inline void start() { server->start(); }

	inline void stop() { server->stop(); }

	inline void badRequest(std::shared_ptr<HttpServer::Response>& response,
			std::shared_ptr<HttpServer::Request>& request) {
		std::string content="Could not open path " + request->path;
		*response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
	}

private:
	HttpServer* server;
	boost::filesystem::path web_root;

	void defaultResourceSend(const HttpServer&				server,
			std::shared_ptr<HttpServer::Response>			response,
			std::shared_ptr<std::ifstream>					ifs,
			std::shared_ptr<std::vector<char>>				buffer);

	void defaultGet(std::shared_ptr<HttpServer::Response>	response,
			std::shared_ptr<HttpServer::Request>			request);

	void send(std::shared_ptr<HttpServer::Response>			response,
			nlohmann::json									o);
};


#endif