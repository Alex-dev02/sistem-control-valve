#include <gtest/gtest.h>
#include <fstream>
#include <string>

#include <system/system.hpp>

TEST(SystemTests, ExecuteCommand) {
    std::string text_to_write = "This is my file\nI will cat it";
    std::ofstream fout("file_to_cat");
    fout << text_to_write;
    fout.close();
    std::string response = System::ExecuteCommand("cat file_to_cat");
    EXPECT_EQ(text_to_write, response);
}

// EthPortIP is just a function that runs ExecuteCommand and extracts
// the ip of eth0. Can't test it since there is no guarantee of a eth0
// port running on the system 
