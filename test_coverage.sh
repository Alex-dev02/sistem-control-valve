cd build
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory out
cd out
firefox index.html
