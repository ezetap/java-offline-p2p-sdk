#include "ezewbsclient.hpp"
//#include "ezewbsclient.cpp" // <-- include only if you don't want compile separately
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <string>
#include <iostream>

using ezewbsclient::EzeWebSocket;
static EzeWebSocket::pointer ws = NULL;

void handle_message(const std::string & message)
{
    printf(">>> %s\n", message.c_str());
    if (message == "world") { ws->close(); }
}

int main()
{
#ifdef _WIN32
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        return 1;
    }
#endif    
    std::cout << "1. Login" << "\n" << "2. Pay" << "\n" << "3. Void" << "\n" << "4. Txn Details" << "\n" << "5. Refund" << "\n";
	std::cout << "Enter your choice to execute the corresponding operation" << "\n";
    std::string web_url = "ws://localhost:8083";//Update the port number on which your jar file is running
    std::string request_body;
    
    int choice = 0;

    std::cin >> choice;

    switch(choice)
    {
        case 1:
            web_url += "/login";
            request_body = "{\"username\": \"Test_User\"}";
            break;
        case 2:
            web_url += "/pay";
            request_body = "{	\
                            \"username\":\"Test_User\", \
                            \"transaction\":{  \
                                \"amount\":100, \
                                \"orderId\":\"Test10\", \
                                \"externalRef2\":\"EzeTest\", \
                                \"externalRef3\":\"Mobile\", \
                                \"customerMobile\":\"1234567890\" \
                            } \
                        }";
            break;
        case 3:
            web_url += "/void";
            request_body = "{	\
                            \"username\":\"Test_User\", \
                            \"txnId\":\"test_txn_id\" /* Update the proper txn id here */ \
                        }";
            break;
        case 4:
            web_url += "/details";
            request_body = "{	\
                            \"username\":\"Test_User\", \
                            \"orderId\":\"Test10\" \
                            }"; 
            break;
        case 5:
            web_url += "/refund";
            request_body = "{	\
                            \"username\":\"Test_User\", \
                            \"amount\":50,\
                            \"txnId\":\"test_txn_id\",  /* Update the proper txn id here */ \
                            \"orderId\":\"Test10\" \
                        }";
            break;
        default:
            break;
    }    

    ws = EzeWebSocket::from_url(web_url);
    assert(ws);
    //ws->send("goodbye");
    //ws->send("hello");
    ws->send(request_body);
    while (ws->getReadyState() != EzeWebSocket::CLOSED) {
      ws->poll();
      ws->dispatch(handle_message);
    }
    delete ws;
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
