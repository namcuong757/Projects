import random
from socket import *
import uuid

serverName = 'localhost'
serverPort = 18000
clientSocket = socket(AF_INET, SOCK_DGRAM)

print("Start to ATTACK the SERVER...")

for i in range (14):
    fake_message = "0,02:00:00:%02x:%02x:%02x" % (random.randint(0, 255),random.randint(0, 255),random.randint(0, 255))
    clientSocket.sendto(fake_message.encode(), (serverName, serverPort))
