#include <gtest/gtest.h>

#include "../networking/communication/Request.hpp"

TEST(RequestTests, GetPath) {
    Request request("PUT /mypath/animals?animal=dog IotDCP/0.1");
    ASSERT_EQ(
        "/mypath/animals",
        request.GetPath()
    );
    request = Request("PUT /mywrongpath/animals=animal IotDCP/0.1");
    ASSERT_EQ(
        "/mywrongpath/animals=animal",
        request.GetPath()
    );
    request = Request("GET /path/without/any/vars/test IotDCP/0.1");
    ASSERT_EQ(
        "/path/without/any/vars/test",
        request.GetPath()
    );
}

TEST(RequestTests, GetPathVar) {
    Request request("PUT /mypath/animal?animal=cat&name=john&crash IotDCP/0.1");
    ASSERT_EQ(
        "cat",
        request.GetPathVar("animal")
    );
    ASSERT_EQ(
        "john",
        request.GetPathVar("name")
    );
}
