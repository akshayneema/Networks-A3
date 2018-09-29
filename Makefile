CXX = g++ -std=c++11

# server : server.o protocol_server.o
# 		$(CXX) -o server server.o protocol_server.o

# server.o : server.cpp protocol_server.cpp protocol_server.h
# 		$(CXX) -c server.cpp


# protocol_server.o : protocol_server.cpp protocol_server.h
# 		$(CXX) -c protocol_server.cpp

# .PHONY : clean

# clean :
# 		$(RM) server *.o *~



# client : client.o protocol.o
# 		$(CXX) -o client client.o protocol.o

# client.o : client.cpp protocol.cpp protocol.h
# 		$(CXX) -c client.cpp


# protocol.o : protocol.cpp protocol.h
# 		$(CXX) -c protocol.cpp

# .PHONY : clean

# clean :
# 		$(RM) client *.o *~



server : server.o protocol.o
		$(CXX) -o server server.o protocol.o

server.o : server.cpp protocol.cpp protocol.h
		$(CXX) -c server.cpp


protocol.o : protocol.cpp protocol.h
		$(CXX) -c protocol.cpp

.PHONY : clean

clean :
		$(RM) server *.o *~



