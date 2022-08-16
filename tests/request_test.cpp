#include <gtest/gtest.h>

#include <networking/request.hpp>

TEST(RequestTests, GetPath) {
    // IotDCP
    Request request("PUT /mypath/animals?animal=dog IotDCP/0.1\n127.0.0.1 4000");
    ASSERT_EQ(
        "/mypath/animals",
        request.GetPath()
    );
    request = Request("PUT /mywrongpath/animals=animal IotDCP/0.1\n127.0.0.1 4000");
    ASSERT_EQ(
        "/mywrongpath/animals=animal",
        request.GetPath()
    );
    request = Request("GET /path/without/any/vars/test IotDCP/0.1\n127.0.0.1 4000");
    ASSERT_EQ(
        "/path/without/any/vars/test",
        request.GetPath()
    );

    // HTTP

    request = Request("GET /mypath/http HTTP/1.1");
    ASSERT_EQ(
        "/mypath/http",
        request.GetPath()
    );

    request = Request("PUT /mypath/path?varname=varvalue HTTP/1.1");
    ASSERT_EQ(
        "/mypath/path",
        request.GetPath()
    );
}

TEST(RequestTests, GetPathVar) {
    // IotDCP
    Request request("PUT /mypath/animal?animal=cat&name=john&age=3 IotDCP/0.1\n127.0.0.1 4000");
    ASSERT_EQ(
        "cat",
        request.GetPathVar("animal")
    );
    ASSERT_EQ(
        "john",
        request.GetPathVar("name")
    );
    ASSERT_EQ(
        "3",
        request.GetPathVar("age")
    );

    request =
        Request("PUT /mypath/path?insect=fly&age=1 HTTP/1.1");
    ASSERT_EQ(
        "fly",
        request.GetPathVar("insect")
    );
    ASSERT_EQ(
        "1",
        request.GetPathVar("age")
    );
    ASSERT_THROW({
        try
        {
            std::string var = request.GetPathVar("notvalidvarname");
        }
        catch(const std::exception& e)
        {
            ASSERT_STREQ(
                "The var_name does not correspond to any variable: notvalidvarname",
                e.what()
            );
            throw;
        }
        
    }, std::exception);
}

TEST(RequestTest, GetRawRequest) {
    Request request("GET /path/to/source IotDCP/0.1\n127.0.0.1 4000");
    ASSERT_EQ(
        "GET /path/to/source IotDCP/0.1\n127.0.0.1 4000",
        request.GetRawRequest()
    );
    
    request = Request("PUT /home/page.php HTTP/1.1");
    ASSERT_EQ(
        "PUT /home/page.php HTTP/1.1",
        request.GetRawRequest()
    );
}

TEST(RequestTest, GetProtocol) {
    Request request("GET /path/to/source IotDCP/0.1\n127.0.0.1 4000");
    ASSERT_EQ(
        Utils::Protocol::IotDCP,
        request.GetProtocol()
    );

    request = Request("PUT /home/page.php HTTP/1.1");
    ASSERT_EQ(
        Utils::Protocol::HTTP,
        request.GetProtocol()
    );
}

TEST(RequestTest, GetIPAddressIotDCP) {
    Request request("GET /path/without/any/vars/test IotDCP/0.1\n127.0.0.1 4000");
    EXPECT_EQ("127.0.0.1", request.GetIPAddressIotDCP());
    request = Request("PUT /mypath/animals?animal=dog IotDCP/0.1\n168.172.0.1 5000");
    EXPECT_EQ("168.172.0.1", request.GetIPAddressIotDCP());
}

TEST(RequestTest, GetPortIotDCP) {
    Request request("GET /path/without/any/vars/test IotDCP/0.1\n127.0.0.1 4000");
    EXPECT_EQ(4000, request.GetPortIotDCP());
    request = Request("PUT /mypath/animals?animal=dog IotDCP/0.1\n168.172.0.1 5000");
    EXPECT_EQ(5000, request.GetPortIotDCP());
}
