#include <gtest/gtest.h>

#include "../networking/IotDCP/IotDCP.hpp"

TEST(IotDCPTests, CheckVersion) {
    IotDCP dcp;
    EXPECT_EQ("0.1", dcp.GetVersion());
}

TEST(IotDCPTests, CreateGETRequest) {
    IotDCP dcp;

    Request request = dcp.CreateRequest(
        IotDCP::RequestType::GET,
        "/test/path"
    );
    EXPECT_EQ(
        "GET /test/path IotDCP/0.1",
        request.GetRawRequest()
    );
    
    request = dcp.CreateRequest(
        IotDCP::RequestType::GET,
        "/test/path?var=var1"
    );
    EXPECT_EQ(
        "GET /test/path?var=var1 IotDCP/0.1",
        request.GetRawRequest()
    );
}

TEST(IotDCPTests, CreatePUTRequest) {
    IotDCP dcp;

    Request request = dcp.CreateRequest(
        IotDCP::RequestType::PUT,
        "/test/path"
    );
    EXPECT_EQ(
        "PUT /test/path IotDCP/0.1",
        request.GetRawRequest()
    );

    request = dcp.CreateRequest(
        IotDCP::RequestType::PUT,
        "/test/path?var=232"
    );
    EXPECT_EQ(
        "PUT /test/path?var=232 IotDCP/0.1",
        request.GetRawRequest()
    );
}

TEST(IotDCPTests, CreateOKResponse) {
    IotDCP dcp;

    Response response = dcp.CreateResponse(
        IotDCP::ResponseCode::OK,
        "some content"
    );
    EXPECT_EQ(
        "1 OK IotDCP/0.1\nLength 12\nsome content",
        response.GetRawIotDCPResponse()
    );
}
