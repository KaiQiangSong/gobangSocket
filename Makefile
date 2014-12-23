cc = g++-4.8
cflags = -lpthread -std=c++11 -std=gnu++11

All = gobang.o user.o match.o mutex.o socket.o msg.o msgr.o gobangServer.o serverSocket.o server.o

#Server

Server : serverSocket
	$(cc) -c server.cpp $(cflags)
	$(cc) -o $(All) $(cflags)

#GoBang Game Part
match : gobang user
	$(cc) -c match.cpp $(cflags)

user:
	$(cc) -c user.cpp $(cflags)

gobang :
	$(cc) -c gobang.cpp $(cflags)

#Socket Part
mutex:
	$(cc) -c mutex.cpp $(cflags)

socket :
	$(cc) -c socket.cpp $(cflags)

#msg & msgr Part

msg :
	$(cc) -c msg.cpp $(cflags)

msgr :
	$(cc) -c msgr.cpp $(cflags)

#goBang Server Part

gobangServer : mutex match msg msgr
	$(cc) -c gobangServer.cpp $(cflags)

#SocketServer Part

serverSocket : gobangServer socket
	$(cc) -c serverSocket.cpp $(cflags)

#Clean

clean :
	rm Sever $(ALL)
