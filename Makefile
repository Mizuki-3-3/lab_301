CPPFLAGS = g++ -std=c++20 -Wall -Wextra
LDFLAGS = -Iinclude -Isrc

TARGEt = main
SRC = share_ptr.cpp
		uni_ptr.cpp
		test.cpp
test: cmd.exe /c start cmd.exe /k plot "filename.txt" with lines