#include "web_server.hpp"
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include "nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include <atomic>
#include <unistd.h>
#include <fcntl.h> 
#include <poll.h> 
#include <chrono>
#include <exception>
#include <cstring>
#include "simdjson.h"  
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <memory>
using namespace simdjson;
using namespace boost::system;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;
using namespace boost::asio::placeholders;




WebServer::WebServer(boost::filesystem::path web_root) :
		web_root(web_root) {
	server = NULL;
}

WebServer::~WebServer() {
	if (server)
		delete server;
}





 




void WebServer::defaultGet(std::shared_ptr<HttpServer::Response> response,
	std::shared_ptr<HttpServer::Request> request) {
	boost::filesystem::path path = web_root;
	

   

	path /= request->path;

			if (boost::filesystem::is_directory(path))
				path /= "index.html";
			

			std::string url = request->path;
			std::cout << "get_response call from URL: " << url << std::endl;
			if(url == "/Chart.json")
			{
										
     			nlohmann::json output = nlohmann::json::array();
				output.push_back(getJSONdata_1());
				output.nlohmann::json::push_back(getJSONdata_2());
				output.nlohmann::json::push_back(getJSONdata_3());
				output.nlohmann::json::push_back(getJSONdata_4());
				output.nlohmann::json::push_back(getJSONdata_5());
				output.nlohmann::json::push_back(getJSONdata_6());
				output.nlohmann::json::push_back(getJSONdata_7());
				
				send(response, output);
				return;
			}
			else if (boost::filesystem::exists(path)){	
				auto ifs = std::make_shared<std::ifstream>();
				ifs->open(path.string(), std::ifstream::in | std::ios::binary);
				if (*ifs) {
					
					std::streamsize buffer_size = 131072;
					auto buffer = std::make_shared<std::vector<char> >(
							buffer_size);

					std::cout << "Path: " << path.string() << std::endl;
				

					ifs->seekg(0, std::ios::end);
					auto length = ifs->tellg();

					ifs->seekg(0, std::ios::beg);

				
					*response << "HTTP/1.1 200 OK\r\nContent-Length: " << length
							<< "\r\n\r\n";
					defaultResourceSend(*server, response, ifs, buffer);
					return;
				}
			}		
			else
			{
				std::string sHTML = "<html><body><h1>404 Not Found</h1><p>There's nothing here.</p></body></html>";
				send(response, sHTML);	
				return;
			}
			
		

	badRequest(response, request);
}

void WebServer::setup() {

	server = new HttpServer();
	server->config.port = 8080;

	std::string url =
			"^((http[s]?|ftp):\\/)?\\/?([^:\\/\\s]+)((\\/\\w+)*\\/)([\\w\\-\\.]+[^#?\\s]+)(.*)?(#[\\w\\-]+)?$";
	std::string jsonUrl =
			"^/(v\\d+(\\.\\d+)*)/json/([\\w\\-\\.]+[^#?\\s]+)(.*)?(#[\\w\\-]+)?";

	server->resource[jsonUrl]["GET"] =
			[&](std::shared_ptr<HttpServer::Response> response,
					std::shared_ptr<HttpServer::Request> request) {
	
				std::string version = request->path_match[URLPOSITIONVERSION];
				std::string path=request->path_match[URLPOSITIONPATH];
				std::vector<std::string> path_segments;
				boost::split( path_segments, path, boost::is_any_of("/"), boost::token_compress_on );

				std::string query = request->query_string;
				std::vector<std::string> query_segments;
				boost::split( query_segments, query, boost::is_any_of("&"), boost::token_compress_on );

			
			};

	//Default GET. If no other matches, this anonymous function will be called.
	//Will respond with content in the web/-directory, and its subdirectories.
	//Default file: index.html
	//Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
	server->default_resource["GET"] = std::bind(&WebServer::defaultGet, this, std::placeholders::_1, std::placeholders::_2);
}

void WebServer::defaultResourceSend(const HttpServer &server,
		std::shared_ptr<HttpServer::Response> response,
		std::shared_ptr<std::ifstream> ifs,
		std::shared_ptr<std::vector<char> > buffer) {
	std::streamsize read_length;
	if ((read_length = ifs->read(&(*buffer)[0], buffer->size()).gcount()) > 0) {
		response->write(&(*buffer)[0], read_length);
		if (read_length == static_cast<std::streamsize>(buffer->size())) {
			response->send(
					[this, &server, response, ifs, buffer](const boost::system::error_code &ec) {
						if(!ec)
							defaultResourceSend(server, response, ifs, buffer);
						else
							std::cerr << "Connection interrupted" << std::endl;
					});
		}
	}
	return;
}

void WebServer::send(std::shared_ptr<HttpServer::Response> response,
		nlohmann::json o) {
	std::stringstream contentStream;
	contentStream << o;
	std::string message = contentStream.str();
	*response << "HTTP/1.1 200 OK\r\n";
	*response << "Content-Length: " << message.length() << "\r\n";
	*response << "Content-Type: application/json" << "\r\n\r\n";
	*response << message;
	return;
}










