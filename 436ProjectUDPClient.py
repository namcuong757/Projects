from socket import *
import uuid
import datetime
"""
0 DISCOVER
1 OFFER
2 REQUEST
3 ACKNOWLEDGE
4 DECLINE
5 RELEASE
6 RENEW
15 LIST (ADMIN USER)
"""
def convert_str_to_time(string):
    date_time_obj = datetime.datetime.strptime(string, '%Y-%m-%d %H:%M:%S.%f')
    return date_time_obj
def menu(macAddr, ip_add, clientSocket):
    print("1. RELEASE")
    print("2. RENEW")
    print("3. QUIT")
    choice = input('Enter corresponding number (1-3): ')
    if choice == "1":
        message5 = "5" + "," + macAddr + "," + ip_add
        clientSocket.sendto(message5.encode(), (serverName, serverPort))
        print("Released Client " + macAddr + "with assigned IP Address " + ip_add)
        menu(macAddr, ip_add, clientSocket)
    elif choice == "2":
        message6 = "6" + "," + macAddr + "," + ip_add
        clientSocket.sendto(message6.encode(), (serverName, serverPort))
    elif choice == "3":
        quit()
    else:
        print("Invalid Input")
    
macAddr = hex(uuid.getnode())
#macAddr = "0xa45e60dda7d2"
serverName = 'localhost'
serverPort = 18000
clientSocket = socket(AF_INET, SOCK_DGRAM)

message0 = "0" + "," + macAddr
print("Client sending DISCOVER message...")
clientSocket.sendto(message0.encode(), (serverName, serverPort))
while(1):
    #step 4 receive OFFER
    message, serverAddress = clientSocket.recvfrom(2048)
    message_lis = message.decode().split(',')
    status = message_lis[0]
    if (status == "1"):
        server_mac_add = message_lis[1]
        ip_add = message_lis[2]
        timestamp = convert_str_to_time(message_lis[3])
        if server_mac_add == macAddr and timestamp > datetime.datetime.now():
                userChoice1 = input('Do you accept? Y/N: ')
                if(userChoice1 == 'Y' or userChoice1 == 'y'):
                    print("Sending REQUEST message to Server")
                    message2 = "2" + "," + macAddr + "," + ip_add + "," + str(timestamp)
                    clientSocket.sendto(message2.encode(), (serverName, serverPort))
                elif(userChoice1 == 'N' or userChoice1 == 'n'):
                    print("New IP rejected")
                    quit()
                else:
                    print("Not a valid response, program terminating")
                    clientSocket.close()
        else:
            print("Error at OFFER STEP 4")
            quit()        
    elif(status == "3"):
        server_mac_add = message_lis[1]
        ip_add = message_lis[2]
        timestamp = convert_str_to_time(message_lis[3])
        if server_mac_add == macAddr:
            print("IP Address: " + ip_add + "was assigned to this client, which will be expire at " + str(timestamp))
            menu(server_mac_add, ip_add, clientSocket)
        else:
            print("The ACKNOWLEDGE message did not match this client mac address. Terminating...")
            clientSocket.close()
        
    elif (status == "4"):
        print("Server DECLINE the REQUEST. Try Again")
        quit()
    else:
        print("Unknown Message")
        clientSocket.close()

