# NamedPipeServerClient
This is an example of client server application using named pipe. 
It provides a basic framework to send request to server and recieve response in return.
Client can add, update, delete and view students. while the server maintains the list of student.
I have used json library (https://github.com/nlohmann/json) to serialize and deserialize complex objects while sending or receiving data from server.
server side has the MapRoute function that maps a incoming request to corrensponding action.
multiple client can connect to server but a single students list is maintained by server for all clients
