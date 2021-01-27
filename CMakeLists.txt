CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(Encrypto
	src/main.cpp
	src/rsaCrypto.cpp
	src/primes.cpp
	src/mathFncts.cpp
)
