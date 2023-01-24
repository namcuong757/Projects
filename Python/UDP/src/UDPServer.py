from re import I
from socket import *
import datetime

class clientData:
    def __init__(self, recNumber, macAddr, ip_add, timeStamp, acked):
        self.recNumber = recNumber  # record number
        self.mac_add = macAddr  # client MAC address
        self.ip_add = ip_add  # client IP
        self.timestamp = timeStamp  # expiration time
        # Boolean indicating whether the assigned IP address has been acknowledged by the server
        self.acked = acked

def print_client_list(client_list):
    print("CLIENT LIST:")
    for i in client_list:
        print("Record Number: " + str(i.recNumber))
        print("Mac Address: " + i.mac_add)
        print("Assigned IP Address: " + i.ip_add)
        print("Date-Time: " + str(i.timestamp))
        print("Acked: " + str(i.acked))

def convert_str_to_time(string):
    date_time_obj = datetime.datetime.strptime(string, '%Y-%m-%d %H:%M:%S.%f')
    return date_time_obj

def is_client_in_list(mac_add):
    lis = []
    for i in client_list:
        if i.mac_add == mac_add:
            return True, i 
    return False, lis

def client_ip_match_in_list(client_list, ip_add):
    for i in client_list:
        if i.ip_add == ip_add:
            return client_list.index(i)

def expired_client_in_list(client_list):
    temp = []
    for i in client_list:
        if i.timestamp < datetime.datetime.now():
            return True, i
    return False, temp


def timestamp_generator():
    current = datetime.datetime.now()
    timestamp = current + datetime.timedelta(0, 60)
    return timestamp


def ip_generator():
    fo = open("IpAddress.txt", "r+")
    ip_list = [line for line in fo.readlines() if line.strip()]
    if not ip_list:
        return "", ip_list
    ip_add = ip_list[0]
    ip_list.pop(0)
    fo.seek(0)
    for i in ip_list:
        fo.write(i)
    fo.truncate()
    fo.close()
    return ip_add, ip_list


count = 0
assigned_ip_add = ""
client_list = []
serverPort = 18000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
print('The server is ready to receive')

while 1:
    message, clientAddress = serverSocket.recvfrom(2048)
    message_list = message.decode().split(',')
    status = message_list[0]
    if(status == "0"):
        client_mac_add = message_list[1]
        check, client = is_client_in_list(client_mac_add)
        print("Recieve DISCOVER message from client with mac address " + client_mac_add )
        if (check):  # if mac is in list
            # Acknowledge message step 2c
            # not final
            timestamp = client.timestamp
            record_num = client.recNumber
            mac_add = client.mac_add
            ip_add = client.ip_add

            if(timestamp > datetime.datetime.now()):
                message3 = "3" + "," + mac_add + "," + ip_add + "," + str(timestamp)
                print("Sending ACKNOWLEGE message for existed Client")
                print("Client Mac Address: " + mac_add)
                print("Assigned IP: " + ip_add)
                print("Timestamp: " + str(timestamp))
                serverSocket.sendto(message3.encode(), clientAddress)
            # end
            # Update and Offer step 2c
            else:
                timestamp =  datetime.datetime.now() + datetime.timedelta(0, 60)
                message1 = "1" + "," + mac_add + "," + ip_add + "," + str(timestamp)
                print("Sending UPDATED OFFER with new time")
                print("Client Mac Address: " + mac_add)
                print("Assigned IP: " + ip_add)
                print("Timestamp: " + str(timestamp))
                serverSocket.sendto(message1.encode(), clientAddress)
            # 2d New Client
        else:
            ip_add, ip_list = ip_generator()
            mac_add = message_list[1]
            if ip_add != "":
                count = count + 1
                timestamp = timestamp_generator()
                new_client = clientData(count, mac_add, ip_add, timestamp, False)
                client_list.append(new_client)
                message1 = "1" + "," + mac_add + "," + ip_add + "," + str(timestamp)
                print("Sending OFFER for new client(IP available)")
                print("Client Mac Address: " + mac_add)
                print("Assigned IP: " + ip_add)
                print("Timestamp: " + str(timestamp))
                serverSocket.sendto(message1.encode(), clientAddress)
                assigned_ip_add = ip_add
            else:
                check, client = expired_client_in_list(client_list)
                # 2E New Client but ip not available
                if check == True:
                    timestamp = timestamp_generator()
                    index = client_list.index(client)
                    client_list[index].mac_add = mac_add
                    client_list[index].timestamp = timestamp
                    client_list[index].acked = False
                    message1 = "1" + "," + client_list[index].mac_add + "," + \
                        client_list[index].ip_add + "," + \
                        str(client_list[index].timestamp)
                    print("Sending OFFER for new client(IP from expired client)")
                    print("Client Mac Address: " + mac_add)
                    print("Assigned IP: " + ip_add)
                    print("Timestamp: " + str(timestamp))
                    serverSocket.sendto(message1.encode(), clientAddress)
                    assigned_ip_add = client_list[index].ip_add
                # 2F
                else:
                    message4 = "4"
                    print("No IP Add available. Sending DECLINE message to Client")
                    serverSocket.sendto(message4.encode(), clientAddress)
    # REQUEST
    elif(status == "2"):
        client_mac_add = message_list[1]
        client_ip_add = message_list[2]
        client_timestamp = convert_str_to_time(message_list[3])
        if(client_ip_match_in_list(client_list, client_ip_add) != None):
            if client_timestamp > datetime.datetime.now():
                index_client = client_ip_match_in_list(client_list, client_ip_add)
                client_list[index_client].acked = True
                message3 = "3" + "," + client_mac_add + "," + client_ip_add + "," + str(client_timestamp)
                print("Sending ACKNOWLEDGE for existed Client")
                print("Client Mac Address: " + client_mac_add)
                print("Assigned IP: " + client_ip_add)
                print("Timestamp: " + str(client_timestamp))
                serverSocket.sendto(message3.encode(), clientAddress)
            else:
                message4 = "4"
                serverSocket.sendto(message4.encode(), clientAddress)
        else:
            message4 = "4"
            serverSocket.sendto(message4.encode(), clientAddress)
    
    elif(status == "5"):
        client_mac_add = message_list[1]
        client_ip_add = message_list[2]
        check, lis = is_client_in_list(client_mac_add)
        if(check):
            index = client_ip_match_in_list(client_list, client_ip_add)
            if(client_list[index].timestamp > datetime.datetime.now()):
                client_list[index].timestamp = datetime.datetime.now()
                client_list[index].acked = False
                print("Released client " + client_mac_add)
                print("Assigned IP: " + client_ip_add)
                print("Timestamp: " + str(client_list[index].timestamp))
                print_client_list(client_list)
            else:
                client_list[index].acked = False
                print("IP Address for client " + client_mac_add + "has already been released")
    elif(status == "6"):
        client_mac_add = message_list[1]
        check, lis = is_client_in_list(client_mac_add)
        if(check):
            client_ip_add = message_list[2]
            index = client_ip_match_in_list(client_list, client_ip_add)
            client_list[index].timestamp = datetime.datetime.now() + datetime.timedelta(0, 60)
            client_list[index].acked = True
            message3 = "3" + "," + client_mac_add + "," + client_ip_add + "," + str(client_list[index].timestamp)
            print("Sending ACKNOWLEGE message for existed Client")
            print("Client Mac Address: " + client_mac_add)
            print("Assigned IP: " + client_ip_add)
            print("Timestamp: " + str(client_list[index].timestamp))
            serverSocket.sendto(message3.encode(), clientAddress)
        else:
            ip_add, ip_list = ip_generator()
            if ip_add != "":
                count = count + 1
                timestamp = timestamp_generator()
                mac_add = message_list[1]
                new_client = clientData(count, mac_add, ip_add, timestamp, False)
                client_list.append(new_client)
                message1 = "1" + "," + mac_add + "," + ip_add + "," + str(timestamp)
                print("Sending OFFER for new client(IP available)")
                print("Client Mac Address: " + mac_add)
                print("Assigned IP: " + ip_add)
                print("Timestamp: " + str(timestamp))
                serverSocket.sendto(message1.encode(), clientAddress)
                assigned_ip_add = ip_add
            else:
                check, client = expired_client_in_list(client_list)
                if check == True:
                    mac_add = message_list[1]
                    timestamp = timestamp_generator()
                    index = client_list.index(client)
                    client_list[index].mac_add = mac_add
                    client_list[index].timestamp = timestamp
                    client_list[index].acked = False
                    message1 = "1" + "," + client_list[index].mac_add + "," + \
                        client_list[index].ip_add + "," + \
                        str(client_list[index].timestamp)
                    print("Sending OFFER for new client(IP from expired client)")
                    print("Client Mac Address: " + mac_add)
                    print("Assigned IP: " + client_list[index].ip_add)
                    print("Timestamp: " + str(timestamp))
                    serverSocket.sendto(message1.encode(), clientAddress)
                    assigned_ip_add = client_list[index].ip_add
                else:
                    message4 = "4"
                    serverSocket.sendto(message4.encode(), clientAddress)
    elif(status == "15"):
        mac_add = message_list[1]
        print("Recived LIST message from client " + mac_add)
        message7 = "15" + ","
        for i in client_list:
            message7 = message7 + " Record_Number:" + str(i.recNumber) + " Mac_address:" + i.mac_add + " IP_Adress:" + i.ip_add + " Date-Time:" + str(i.timestamp) + " Acked:" + str(i.acked)
        serverSocket.sendto(message7.encode(), clientAddress)