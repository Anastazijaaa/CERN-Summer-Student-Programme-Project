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
#include "functions.hpp"
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




std::vector< uint64_t > fid_arr;
std::vector< double > datarate_arr;
std::vector< double > blockrate_arr;
std::vector< double > chunkrate_arr;
std::vector< double > buff_events_arr;
std::vector< uint64_t > interrupts_arr;
std::vector< uint64_t > polls_arr;
std::vector< std::string_view> ts_arr;

int read_data(char* c, uint64_t size){
  
char json[strlen(c) + SIMDJSON_PADDING];
strcpy(json, c);

try{
bool is_ok = simdjson::validate_utf8(json, strlen(json));
if (is_ok) {
ondemand::parser parser;
 
auto doc = parser.iterate(json, strlen(json), sizeof(json));
ondemand::object object = doc.get_object();
for(auto field : object) {


   // parses and writes out the key, after unescaping it,
   // to a string buffer. It causes a performance penalty.
   std::string_view keyv = field.unescaped_key();
   if(keyv == "fid") { 
     uint64_t fid = uint64_t(field.value());
     std::cout << fid << std::endl; 
     fid_arr.push_back(fid);
     }
     if(keyv == "ts") { 
      std::string_view ts_value = field.value();
     std::cout << ts_value << std::endl; 
         ts_arr.push_back(ts_value);
     }
      if(keyv == "datarate[Gbps]") { 
      double datarate = double(field.value());
     std::cout << datarate << std::endl; 
         datarate_arr.push_back(datarate);
     }
      if(keyv == "blockrate[MBlocks/s]") { 
     double blockrate = double(field.value());
     std::cout << blockrate << std::endl; 
         blockrate_arr.push_back(blockrate);
     }
      if(keyv == "chunkrate[MChunks/s]") { 
     double chunkrate = double(field.value());
     std::cout << chunkrate << std::endl; 
         chunkrate_arr.push_back(chunkrate);
     }
      if(keyv == "interrupts") { 
     uint64_t interrupts = uint64_t(field.value());
     std::cout << interrupts << std::endl; 
         interrupts_arr.push_back(interrupts);
     }
      if(keyv == "buffer-events") { 
     uint64_t buffer_events = uint64_t(field.value());
     std::cout << buffer_events << std::endl; 
         buff_events_arr.push_back(buffer_events);
     }
      if(keyv == "polls") { 
     uint64_t polls = uint64_t(field.value());
     std::cout << polls << std::endl; 
         polls_arr.push_back(polls);
     }
 
 }}
 else {
} 
 
   } 
  catch (const simdjson::simdjson_error &e) {
   
}

return 0;}  



std::vector<uint64_t> getTimestamp_dataRate(){
 

  std::map<uint64_t, double> dataRateArray;
  //map contains <timestamp, datarate>
  dataRateArray[0] = datarate_arr[0];
  dataRateArray[1] = datarate_arr[1];
  dataRateArray[2] = datarate_arr[2];
  dataRateArray[3] = datarate_arr[3];
  dataRateArray[4] = datarate_arr[4];
  dataRateArray[5] = datarate_arr[5];
  dataRateArray[6] = datarate_arr[6];
  dataRateArray[7] = datarate_arr[7];


std::map<uint64_t, double>::iterator itr;
std::vector<uint64_t> first_data;

for (itr = dataRateArray.begin(); itr != dataRateArray.end(); ++itr) {
  first_data.push_back(itr->first);
}




return first_data;
}

std::vector<uint64_t> getTimestamp_fid(){
 

  std::map<uint64_t, double> fidArray;
 
  fidArray[0] = fid_arr[0];
  fidArray[1] = fid_arr[1];
  fidArray[2] = fid_arr[2];
  fidArray[3] = fid_arr[3];
  fidArray[4] = fid_arr[4];
  fidArray[5] = fid_arr[5];
  fidArray[6] = fid_arr[6];
  fidArray[7] = fid_arr[7];




std::map<uint64_t, double>::iterator itr;
std::vector<uint64_t> first_data;

for (itr = fidArray.begin(); itr != fidArray.end(); ++itr) {
  first_data.push_back(itr->first);
}




return first_data;
}


std::vector<uint64_t> getTimestamp_blockRate(){
 



  std::map<uint64_t, double> blockRateArray;

  blockRateArray[0] = blockrate_arr[0];
  blockRateArray[1] = blockrate_arr[1];
  blockRateArray[2] = blockrate_arr[2];
  blockRateArray[3] = blockrate_arr[3];
  blockRateArray[4] = blockrate_arr[4];
  blockRateArray[5] = blockrate_arr[5];
  blockRateArray[6] = blockrate_arr[6];
  blockRateArray[7] = blockrate_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<uint64_t> first_data;



for (itr = blockRateArray.begin(); itr != blockRateArray.end(); ++itr) {
  first_data.push_back(itr->first);
}



return first_data;

}

std::vector<uint64_t> getTimestamp_chunkRate(){
 



  std::map<uint64_t, double> chunkRateArray;

  chunkRateArray[0] = chunkrate_arr[0];
  chunkRateArray[1] = chunkrate_arr[1];
  chunkRateArray[2] = chunkrate_arr[2];
  chunkRateArray[3] = chunkrate_arr[3];
  chunkRateArray[4] = chunkrate_arr[4];
  chunkRateArray[5] = chunkrate_arr[5];
  chunkRateArray[6] = chunkrate_arr[6];
  chunkRateArray[7] = chunkrate_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<uint64_t> first_data;



for (itr = chunkRateArray.begin(); itr != chunkRateArray.end(); ++itr) {
  first_data.push_back(itr->first);
}



return first_data;

}



std::vector<uint64_t> getTimestamp_buff_events(){
 



  std::map<uint64_t, double> buff_events_Array;

  buff_events_Array[0] = buff_events_arr[0];
  buff_events_Array[1] = buff_events_arr[1];
  buff_events_Array[2] = buff_events_arr[2];
  buff_events_Array[3] = buff_events_arr[3];
  buff_events_Array[4] = buff_events_arr[4];
  buff_events_Array[5] = buff_events_arr[5];
  buff_events_Array[6] = buff_events_arr[6];
  buff_events_Array[7] = buff_events_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<uint64_t> first_data;



for (itr = buff_events_Array.begin(); itr != buff_events_Array.end(); ++itr) {
  first_data.push_back(itr->first);
}



return first_data;

}


std::vector<uint64_t> getTimestamp_interrupts(){
 



  std::map<uint64_t, uint64_t> interruptsArray;
 
  interruptsArray[0] = interrupts_arr[0];
  interruptsArray[1] = interrupts_arr[1];
  interruptsArray[2] = interrupts_arr[2];
  interruptsArray[3] = interrupts_arr[3];
  interruptsArray[4] = interrupts_arr[4];
  interruptsArray[5] = interrupts_arr[5];
  interruptsArray[6] = interrupts_arr[6];
  interruptsArray[7] = interrupts_arr[7];


std::map<uint64_t, uint64_t>::iterator itr;

std::vector<uint64_t> first_data;



for (itr = interruptsArray.begin(); itr != interruptsArray.end(); ++itr) {
  first_data.push_back(itr->first);
}



return first_data;

}




std::vector<uint64_t> getTimestamp_polls(){
 



  std::map<uint64_t, uint64_t> pollsArray;
 
  pollsArray[0] = polls_arr[0];
  pollsArray[1] = polls_arr[1];
  pollsArray[2] = polls_arr[2];
  pollsArray[3] = polls_arr[3];
  pollsArray[4] = polls_arr[4];
  pollsArray[5] = polls_arr[5];
  pollsArray[6] = polls_arr[6];
  pollsArray[7] = polls_arr[7];


std::map<uint64_t, uint64_t>::iterator itr;

std::vector<uint64_t> first_data;



for (itr = pollsArray.begin(); itr != pollsArray.end(); ++itr) {
  first_data.push_back(itr->first);
}



return first_data;

}





std::vector<double> getSecondData_fid(){
 

  std::map<uint64_t, double> fidArray;
 
  fidArray[0] = fid_arr[0];
  fidArray[1] = fid_arr[1];
  fidArray[2] = fid_arr[2];
  fidArray[3] = fid_arr[3];
  fidArray[4] = fid_arr[4];
  fidArray[5] = fid_arr[5];
  fidArray[6] = fid_arr[6];
  fidArray[7] = fid_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<double> second_data;



for (itr = fidArray.begin(); itr != fidArray.end(); ++itr) {
  second_data.push_back(itr->second);
}



return second_data;
}




std::vector<double> getSecondData_dataRate(){
 

  std::map<uint64_t, double> dataRateArray;
 
  dataRateArray[0] = datarate_arr[0];
  dataRateArray[1] = datarate_arr[1];
  dataRateArray[2] = datarate_arr[2];
  dataRateArray[3] = datarate_arr[3];
  dataRateArray[4] = datarate_arr[4];
  dataRateArray[5] = datarate_arr[5];
  dataRateArray[6] = datarate_arr[6];
  dataRateArray[7] = datarate_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<double> second_data;



for (itr = dataRateArray.begin(); itr != dataRateArray.end(); ++itr) {
  second_data.push_back(itr->second);
}



return second_data;
}



std::vector<double> getSecondData_blockRate(){
 

  std::map<uint64_t, double> blockRateArray;

  blockRateArray[0] = blockrate_arr[0];
  blockRateArray[1] = blockrate_arr[1];
  blockRateArray[2] = blockrate_arr[2];
  blockRateArray[3] = blockrate_arr[3];
  blockRateArray[4] = blockrate_arr[4];
  blockRateArray[5] = blockrate_arr[5];
  blockRateArray[6] = blockrate_arr[6];
  blockRateArray[7] = blockrate_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<double> second_data;



for (itr = blockRateArray.begin(); itr != blockRateArray.end(); ++itr) {
  second_data.push_back(itr->second);
}



return second_data;
}



std::vector<double> getSecondData_chunkRate(){
 

  std::map<uint64_t, double> chunkRateArray;

  chunkRateArray[0] = chunkrate_arr[0];
  chunkRateArray[1] = chunkrate_arr[1];
  chunkRateArray[2] = chunkrate_arr[2];
  chunkRateArray[3] = chunkrate_arr[3];
  chunkRateArray[4] = chunkrate_arr[4];
  chunkRateArray[5] = chunkrate_arr[5];
  chunkRateArray[6] = chunkrate_arr[6];
  chunkRateArray[7] = chunkrate_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<double> second_data;



for (itr = chunkRateArray.begin(); itr != chunkRateArray.end(); ++itr) {
  second_data.push_back(itr->second);
}



return second_data;
}



std::vector<double> getSecondData_buff_events(){
 



  std::map<uint64_t, double> buff_events_Array;
 
  buff_events_Array[0] = buff_events_arr[0];
  buff_events_Array[1] = buff_events_arr[1];
  buff_events_Array[2] = buff_events_arr[2];
  buff_events_Array[3] = buff_events_arr[3];
  buff_events_Array[4] = buff_events_arr[4];
  buff_events_Array[5] = buff_events_arr[5];
  buff_events_Array[6] = buff_events_arr[6];
  buff_events_Array[7] = buff_events_arr[7];


std::map<uint64_t, double>::iterator itr;

std::vector<double> second_data;



for (itr = buff_events_Array.begin(); itr != buff_events_Array.end(); ++itr) {
  second_data.push_back(itr->second);
}



return second_data;

}



std::vector<uint64_t> getSecondData_interrupts(){
 



  std::map<uint64_t, uint64_t> interruptsArray;

  interruptsArray[0] = interrupts_arr[0];
  interruptsArray[1] = interrupts_arr[1];
  interruptsArray[2] = interrupts_arr[2];
  interruptsArray[3] = interrupts_arr[3];
  interruptsArray[4] = interrupts_arr[4];
  interruptsArray[5] = interrupts_arr[5];
  interruptsArray[6] = interrupts_arr[6];
  interruptsArray[7] = interrupts_arr[7];


std::map<uint64_t, uint64_t>::iterator itr;

std::vector<uint64_t> second_data;



for (itr = interruptsArray.begin(); itr != interruptsArray.end(); ++itr) {
  second_data.push_back(itr->second);
}



return second_data;

}

std::vector<uint64_t> getSecondData_polls(){
 




  std::map<uint64_t, uint64_t> pollsArray;
  
  pollsArray[0] = polls_arr[0];
  pollsArray[1] = polls_arr[1];
  pollsArray[2] = polls_arr[2];
  pollsArray[3] = polls_arr[3];
  pollsArray[4] = polls_arr[4];
  pollsArray[5] = polls_arr[5];
  pollsArray[6] = polls_arr[6];
  pollsArray[7] = polls_arr[7];


std::map<uint64_t, uint64_t>::iterator itr;

std::vector<uint64_t> second_data;



for (itr = pollsArray.begin(); itr != pollsArray.end(); ++itr) {
  second_data.push_back(itr->second);
}



return second_data;

}






 nlohmann::json getJSONdata_1(){
  nlohmann::json output;
  
std::vector<uint64_t> first_data = getTimestamp_dataRate();
std::vector<double> second_data = getSecondData_dataRate();


//x, y values
  output[first_data[0]] = second_data[0];
  output[first_data[1]] = second_data[1];
  output[first_data[2]] = second_data[2];
  output[first_data[3]] = second_data[3];
  output[first_data[4]] = second_data[4];
  output[first_data[5]] = second_data[5];
  output[first_data[6]] = second_data[6];
  output[first_data[7]] = second_data[7];
   return output;
   } 



 nlohmann::json getJSONdata_2(){
  nlohmann::json output;
std::vector<uint64_t> third_data = getTimestamp_fid();
std::vector<double> fourth_data = getSecondData_fid();
  output[third_data[0]] = fourth_data[0];
  output[third_data[1]] = fourth_data[1];
  output[third_data[2]] = fourth_data[2];
  output[third_data[3]] = fourth_data[3];
  output[third_data[4]] = fourth_data[4];
  output[third_data[5]] = fourth_data[5];
  output[third_data[6]] = fourth_data[6];
  output[third_data[7]] = fourth_data[7]; 

  return output;
} 


nlohmann::json getJSONdata_3(){
nlohmann::json output;
  
std::vector<uint64_t> first_data = getTimestamp_blockRate();
std::vector<double> second_data = getSecondData_blockRate();

  output[first_data[0]] = second_data[0];
  output[first_data[1]] = second_data[1];
  output[first_data[2]] = second_data[2];
  output[first_data[3]] = second_data[3];
  output[first_data[4]] = second_data[4];
  output[first_data[5]] = second_data[5];
  output[first_data[6]] = second_data[6];
  output[first_data[7]] = second_data[7];
   return output; 
} 


nlohmann::json getJSONdata_4(){
nlohmann::json output;
  
std::vector<uint64_t> first_data = getTimestamp_chunkRate();
std::vector<double> second_data = getSecondData_chunkRate();

  output[first_data[0]] = second_data[0];
  output[first_data[1]] = second_data[1];
  output[first_data[2]] = second_data[2];
  output[first_data[3]] = second_data[3];
  output[first_data[4]] = second_data[4];
  output[first_data[5]] = second_data[5];
  output[first_data[6]] = second_data[6];
  output[first_data[7]] = second_data[7];
   return output; 
} 

nlohmann::json getJSONdata_5(){
nlohmann::json output;
  
std::vector<uint64_t> first_data = getTimestamp_buff_events();
std::vector<double> second_data = getSecondData_buff_events();

  output[first_data[0]] = second_data[0];
  output[first_data[1]] = second_data[1];
  output[first_data[2]] = second_data[2];
  output[first_data[3]] = second_data[3];
  output[first_data[4]] = second_data[4];
  output[first_data[5]] = second_data[5];
  output[first_data[6]] = second_data[6];
  output[first_data[7]] = second_data[7];
   return output; 
} 


nlohmann::json getJSONdata_6(){
nlohmann::json output;
  
std::vector<uint64_t> first_data = getTimestamp_interrupts();
std::vector<uint64_t> second_data = getSecondData_interrupts();

  output[first_data[0]] = second_data[0];
  output[first_data[1]] = second_data[1];
  output[first_data[2]] = second_data[2];
  output[first_data[3]] = second_data[3];
  output[first_data[4]] = second_data[4];
  output[first_data[5]] = second_data[5];
  output[first_data[6]] = second_data[6];
  output[first_data[7]] = second_data[7];
   return output; 
} 


nlohmann::json getJSONdata_7(){
nlohmann::json output;
  
std::vector<uint64_t> first_data = getTimestamp_polls();
std::vector<uint64_t> second_data = getSecondData_polls();

  output[first_data[0]] = second_data[0];
  output[first_data[1]] = second_data[1];
  output[first_data[2]] = second_data[2];
  output[first_data[3]] = second_data[3];
  output[first_data[4]] = second_data[4];
  output[first_data[5]] = second_data[5];
  output[first_data[6]] = second_data[6];
  output[first_data[7]] = second_data[7];
   return output; 
} 





  int read_fifo(const std::vector<std::string>& paths){
    const uint64_t size = paths.size();
    struct pollfd pfds[size];
    int n, k;
    char buf[1024];
    short revents;
    for(n = 0; n < size; n++){
        int fd = open(paths[n].c_str(), O_RDONLY | O_NONBLOCK);
        if (fd == -1){printf("Can't read fifo.");}
        pfds[n].fd = fd;
        pfds[n].events = POLLIN;
        
    }

    while(1){
        int i = poll(pfds, size, -1);
        if (i == -1){printf("Polling error.");}
        for (auto ff : pfds){
            revents = ff.revents;
            if (revents & POLLIN) {
                k = read(ff.fd, buf, sizeof(buf));
                printf("POLLIN i=%d k=%d buf=", i, k);
                std::cout << buf << std::endl;
                read_data(buf, sizeof(buf));
                //std::cout<<strlen(buf)<<std::endl;
                            
              

            }
            
            if (revents & POLLHUP) {
                printf("POLLHUP i=%d\n", i);
                close(ff.fd);
                ff.fd *= -1;
            }
        }
    }
}

 

