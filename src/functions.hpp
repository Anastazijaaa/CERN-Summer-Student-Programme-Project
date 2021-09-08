#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <atomic>
#include <unistd.h>
#include <fcntl.h> 
#include <poll.h> 
#include <chrono>
#include <map>
#include <iterator>

#include <exception>
#include <cstring>
#include "simdjson.h"  
#include "nlohmann/json.hpp"


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




int read_data(char* c, uint64_t size);



std::vector<uint64_t> getTimestamp_dataRate();
std::vector<double> getSecondData_dataRate();
std::vector<uint64_t> getTimestamp_fid();
std::vector<double> getSecondData_fid();


std::vector<uint64_t> getTimestamp_blockRate();
std::vector<double> getSecondData_blockRate();


std::vector<uint64_t> getTimestamp_chunkRate();
std::vector<double> getSecondData_chunkRate();


std::vector<uint64_t> getTimestamp_buff_events();
std::vector<double> getSecondData_buff_events();


std::vector<uint64_t> getTimestamp_interrupts();
std::vector<uint64_t> getSecondData_interrupts();


std::vector<uint64_t> getTimestamp_polls();
std::vector<uint64_t> getSecondData_polls();




 nlohmann::json getJSONdata_1();

 nlohmann::json getJSONdata_2();
 
 nlohmann::json getJSONdata_3();

 nlohmann::json getJSONdata_4();
 
 nlohmann::json getJSONdata_5();
 
 nlohmann::json getJSONdata_6();
 
 nlohmann::json getJSONdata_7();


  int read_fifo(const std::vector<std::string>& paths);

 
#endif
