all: server serverTwoClients impatientServer client longClient

server: server.c common.h
	gcc server.c -o server

serverTwoClients: serverTwoClients.c common.h
	gcc serverTwoClients.c -o serverTwoClients

client: client.c common.h
	gcc client.c -o client
	
impatientServer: impatientServer.c common.h
	gcc impatientServer.c -o impatientServer

longClient: longClient.c common.h
	gcc longClient.c -o longClient

clean:
	-rm server serverTwoClients impatientServer client longClient *.o
