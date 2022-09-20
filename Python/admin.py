from socket import *
import uuid
import datetime

macAddr = hex(uuid.getnode())
serverName = 'localhost'
serverPort = 18000
clientSocket = socket(AF_INET, SOCK_DGRAM)


print("*ADMIN CLIENT*")
print("Sending LIST message to the server")
message7 = "15" + "," + macAddr
clientSocket.sendto(message7.encode(), (serverName, serverPort))
message, serverAddress = clientSocket.recvfrom(2048)
message_lis = message.decode().split(',')
status = message_lis[0]
if(status == "15"):
    print("Got reply from server with records")
    str_message = message.decode()
    str_message = str_message.replace("15","")
    str_message = str_message.replace(",","")
    client_record = list(str_message.split(" "))
    for i in client_record:
        print(i)
else:
    print("Unknow reply from server")