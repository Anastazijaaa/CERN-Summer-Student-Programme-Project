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
#include "web_server.hpp"
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

const char* HELP =
    R"FOO(Usage: fm_client [options]

Connects to a remote FULL-mode FELIX host and subscribes to all links.

Options are:

  -b BACKEND      Use the specified netio backend. Default: posix.
  -H HOSTNAME     Connect to the specified hostname. Default: 127.0.0.1.
  -p PORT         Connect to the specified port on the remote. Default: 12350.
  -t THREADS      Number of threads (=ports) of the felixcore instance. Default: 2.
  -i              Interactive mode, prints received messages to the screen.
  -z              Enable zero-copy mode.
  -V              Display version.
  -h              Display this help message.
)FOO";


unsigned ELINKS[] = {
   0*64, 1*64, 2*64, 3*64, 4*64, 5*64,
   2048+0*64, 2048+1*64, 2048+2*64, 2048+3*64, 2048+4*64, 2048+5*64
 };


 inline void set_thread_name(const char* name, unsigned n)
 {
     char tname[16];
     snprintf(tname, 16, "fm-%s-%d", name, n);
     pthread_setname_np(pthread_self(), tname);
 }

      
   std::string getExecutablePath() {
    char exePath[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath));
    if (len == -1 || len == sizeof(exePath))
        len = 0;
    exePath[len] = '\0';
    return std::string(exePath);
}


 void start_web_server(){

  //Find Web Root
  boost::filesystem::path executable = getExecutablePath();
  //development path
  boost::filesystem::path web_root = executable.parent_path() / "share/felix-monitoring/web";
  //for the distribution
  if(!boost::filesystem::exists(web_root)) {
    web_root = executable.parent_path().parent_path() / "share/felix-monitoring/web";
  }

  //for the real installation
  if(!boost::filesystem::exists(web_root)) {
    web_root = "/usr/local/share/felix-monitoring/web";
  }

  //final verdict on webroot
  if (boost::filesystem::exists(web_root)) {
    std::cout << "Web Root found at: " << web_root << std::endl;
  } else {
    printf("Web Root could NOT be found in above locations");
  }
  // Starting web server
  WebServer webServer(web_root);
  
  webServer.setup();

  webServer.start();

}



int main(int argc, const char * argv[]) {

std::vector<std::string> fifo;
fifo.push_back ("/tmp/ERS");
fifo.push_back("/tmp/STATS");
std::thread reader(&read_fifo, fifo);
start_web_server();
return 0;

}
