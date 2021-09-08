#include <cstdio>
#include <string>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>

#include "docopt/docopt.h"

#include "felix/felix_client_properties.h"
#include "felix/felix_client_status.h"
#include "felix/felix_client_exception.hpp"
#include "felix/felix_client_thread.hpp"



static const char USAGE[] =
R"(felix-client-thread-subscribe - Subscribes to a felix-id using felix-bus to find the publisher.

    Usage:
      local_test_2 [options] <local_ip_or_interface> <fids>...

    Options:
      -h --help                         Show this screen.
      --version                         Show version.
      --log-level=<loglevel>            Specify level of logging (trace, debug, info, notice, warning, error, fatal) [default: info]
      --verbose-bus                     Show bus information
      --bus-dir=<directory>             Set directory for bus to use [default: ./bus]
      --bus-group-name=<group-name>     Set group-name for bus to use [default: FELIX]
      --timeout=<timeoutms>             Set timeout to subscribe (0 is no timeout) [default: 0]
      --messages=<no_messages>          Exit after no_messages are received [default: 0]
      --netio-pages=<pages>             Number of pages for buffer [default: 256]
      --netio-pagesize=<pagesize>       Pagesize for buffer in bytes [default: 65536]
)";





class UserClass {

public:
    UserClass(std::map<std::string, docopt::value> &args) {

        try {
            

            FelixClientThread::Config config;
            config.on_init_callback = std::bind(&UserClass::on_init, this);
            config.on_data_callback = std::bind(&UserClass::on_data, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
            config.on_connect_callback = std::bind(&UserClass::on_connect, this, std::placeholders::_1);
            config.on_disconnect_callback = std::bind(&UserClass::on_disconnect, this, std::placeholders::_1);

            config.property[FELIX_CLIENT_LOCAL_IP_OR_INTERFACE] = args["<local_ip_or_interface>"].asString();
            config.property[FELIX_CLIENT_LOG_LEVEL] = args["--log-level"].asString();
            config.property[FELIX_CLIENT_BUS_DIR] = args["--bus-dir"].asString();
            config.property[FELIX_CLIENT_BUS_GROUP_NAME] = args["--bus-group-name"].asString();
            config.property[FELIX_CLIENT_VERBOSE_BUS] = args["--verbose-bus"].asBool() ? "True" : "False";
            config.property[FELIX_CLIENT_TIMEOUT] = args["--timeout"].asString();
            config.property[FELIX_CLIENT_NETIO_PAGES] = args["--netio-pages"].asString();
            config.property[FELIX_CLIENT_NETIO_PAGESIZE] = args["--netio-pagesize"].asString();

            client = new FelixClientThread(config);

            FelixClientThread::UserFunction user_function = std::bind(&UserClass::on_exec, this);
            client->exec(user_function);

            

            std::vector<std::string> fid_list = args["<fids>"].asStringList();
            for(std::vector<std::string>::iterator it = fid_list.begin(); it != fid_list.end(); ++it) {
                uint64_t fid = std::stoul(*it, 0, 0);
                
                client->subscribe(fid);
            }

            while(true) {
                sleep(30);
            }

            exit(0);
        } catch (FelixClientResourceNotAvailableException& exc) {
            std::cerr << "Timed out on subscription" << std::endl;
            std::exit(1);
        } catch (std::invalid_argument const& error) {
            std::cerr << "Argument or option of wrong type" << std::endl;
            std::cout << std::endl;
            std::cout << USAGE << std::endl;
            std::exit(-1);
        }
    }

    ~UserClass() {
        delete client;
    }

private:
    void on_init() {
        printf("on_init called\n");
    }

    void on_connect(uint64_t fid) {
        printf("on_connect called 0x%lx\n", fid);
    }

    void on_disconnect(uint64_t fid) {
        printf("on_disconnect called 0x%lx\n", fid);
    }

    void on_data(uint64_t fid, const uint8_t* data, size_t size, uint8_t status) {

    size_t i = 0;
    for( ; i < size; ++i ){       
    printf("%c", data[i]); 
    }
printf("\n");


  
     printf("on_data called for %lu with size %lu and status %u for data %c\n", fid, size, status, *data);
     

 

      
        
 
    }

    void on_exec() {
        printf("on_exec called\n");
    }

    FelixClientThread* client;
};


/*int main(int argc, char** argv) {
    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                            { argv + 1, argv + argc },
                            true,               // show help if requested
                            (std::string(argv[0]) + " " + FELIX_TAG).c_str());  // version string

    UserClass userClass(args);
}*/
