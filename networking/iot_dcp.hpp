#pragma once

#include <string>

#include "utils.hpp"
#include "request.hpp"
#include "response.hpp"

// IotDeviceCommunicationProtocol

/*
    ### Requests
    - start with the name of the acction: GET or PUT
        - GET is used for retrieving data from the server
        - PUT is used for saving/modifing data on the server
    - the path, which will represent the name of the function to execute
        ex: /AddValve
    - we can specify name of variables and their values by attaching them
        to the path, like HTTP does: /AddValue?var=5
    - the path must be followed by a white space
    - the abreviation of the protocol's name and it's version
        ex: IotDCP/0.1
    - a new line followed by the IP and PORT of the server
    ### Responses
    - must start with a response code and the meaning of it:
        - 0 Server, Error for faild to GET/PUT 
        - 1 OK, for success
        - 2 Not Found, for path not found
        - 3 Not Authorized, for unauthorized
    - the response code must be followed by a white spaces,
        the abreviation of the protocol and its version: 1 IotDCP/0.1
    - the response code and protocol name must be followed by a new line
    - the next line must be specifing the length of the data sent back by the
        server, if any: Length 0
    - new line before the content, if any
    
    ex of full request:
        GET /current_temp IotDCP/0.1 
        127.0.0.1 4000
    ex of full response:
        1 OK IotDCP/0.1
        Length 3
        20C


*/

class IotDCP {
public:
    IotDCP();

    std::string GetVersion() const;

    Request CreateRequest(Utils::RequestType type, std::string path, std::string ip_address, uint16_t port) const;
    Response CreateResponse(Utils::IotDCPResponseCode response_code, std::string content = "") const;

private:
    std::string m_version = "0.1";
};
