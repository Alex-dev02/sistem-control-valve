#include <gtest/gtest.h>

#include <networking/iot_dcp.hpp>
#include <networking/utils.hpp>

static IotDCP dcp;

// Get Version Unit Tests

TEST(IotDCPTests, CheckVersion) {
    EXPECT_EQ("0.1", dcp.GetVersion());
}

// Create Request Unit Tests

TEST(IotDCPTests, CreateGETRequest) {
    Request request = dcp.CreateRequest(Utils::RequestType::GET, "/test/path", "127.0.0.1", 4000);
    EXPECT_EQ(
        "GET /test/path IotDCP/0.1",
        request.GetRawRequest()
    );
    
    request = dcp.CreateRequest(Utils::RequestType::GET, "/test/path?var=var1", "127.0.0.1", 4000);
    EXPECT_EQ(
        "GET /test/path?var=var1 IotDCP/0.1",
        request.GetRawRequest()
    );
}

TEST(IotDCPTests, CreatePUTRequest) {
    Request request = dcp.CreateRequest(Utils::RequestType::PUT, "/test/path", "127.0.0.1", 4000);
    EXPECT_EQ(
        "PUT /test/path IotDCP/0.1",
        request.GetRawRequest()
    );

    request = dcp.CreateRequest(Utils::RequestType::PUT, "/test/path?var=232", "127.0.0.1", 4000);
    EXPECT_EQ(
        "PUT /test/path?var=232 IotDCP/0.1",
        request.GetRawRequest()
    );
}

// Create Response Unit Tests

TEST(IotDCPTests, CreateOKResponse) {
    Response response = dcp.CreateResponse(Utils::IotDCPResponseCode::I_OK, "some content");
    EXPECT_EQ(
        "1 OK IotDCP/0.1\nLength 12\nsome content",
        response.GetRawResponse()
    );
}

TEST(IotDCPTests, CreateServErrReponse) {
    Response response = dcp.CreateResponse(Utils::IotDCPResponseCode::I_ServErr, "Error");
    EXPECT_EQ(
        "0 Server Error IotDCP/0.1\nLength 5\nError",
        response.GetRawResponse()
    );
}

TEST(IotDCPTests, CreateNotFoundReponse) {
    Response response = dcp.CreateResponse(Utils::IotDCPResponseCode::I_NotFound, "Not Found");
    std::cout << response.GetRawResponse();
    EXPECT_EQ(
        "2 Not Found IotDCP/0.1\nLength 9\nNot Found",
        response.GetRawResponse()
    );
}

TEST(IotDCPTests, CreateNotAuthReponse) {
    Response response = dcp.CreateResponse(Utils::IotDCPResponseCode::I_NotAuth, "Not Authorized");
    EXPECT_EQ(
        "3 Not Authorized IotDCP/0.1\nLength 14\nNot Authorized",
        response.GetRawResponse()
    );
}
