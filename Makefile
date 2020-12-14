conv: convolution.cpp
	g++ -std=c++11 -o convolution.out convolution.cpp

clean:
	$(RM) convolution.out