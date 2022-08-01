#include <gtest/gtest.h>

#include "../networking/communication/IotDCP.hpp"
#include "../networking/communication/Utils.hpp"

TEST(IotDCPTests, CheckVersion) {
    IotDCP dcp;
    EXPECT_EQ("0.1", dcp.GetVersion());
}

TEST(IotDCPTests, CreateGETRequest) {
    IotDCP dcp;

    Request request = dcp.CreateRequest(Utils::RequestType::GET, "/test/path");
    EXPECT_EQ(
        "GET /test/path IotDCP/0.1",
        request.GetRawRequest()
    );
    
    request = dcp.CreateRequest(Utils::RequestType::GET, "/test/path?var=var1");
    EXPECT_EQ(
        "GET /test/path?var=var1 IotDCP/0.1",
        request.GetRawRequest()
    );
}

TEST(IotDCPTests, CreatePUTRequest) {
    IotDCP dcp;

    Request request = dcp.CreateRequest(Utils::RequestType::PUT, "/test/path");
    EXPECT_EQ(
        "PUT /test/path IotDCP/0.1",
        request.GetRawRequest()
    );

    request = dcp.CreateRequest(Utils::RequestType::PUT, "/test/path?var=232");
    EXPECT_EQ(
        "PUT /test/path?var=232 IotDCP/0.1",
        request.GetRawRequest()
    );
}

TEST(IotDCPTests, CreateOKResponse) {
    IotDCP dcp;

    Response response = dcp.CreateResponse(Utils::IotDCPResponseCode::I_OK, "some content");
    EXPECT_EQ(
        "1 OK IotDCP/0.1\nLength 12\nsome content",
        response.GetRawResponse()
    );
}

TEST(IotDCPTests, CreateServErrReponse) {
    IotDCP dcp;

    Response response = dcp.CreateResponse(Utils::IotDCPResponseCode::I_ServErr, "Error");
    EXPECT_EQ(
        "0 Server Error IotDCP/0.1\nLength 5\nError",
        response.GetRawResponse()
    );
}
