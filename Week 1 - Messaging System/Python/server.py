#!/usr/bin/env python3

import socket

HOST = str(socket.gethostbyname(socket.gethostname())) 
PORT = 65432 

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
print("Server IP: ", HOST)
server.listen()
conn, addr = server.accept()
with conn:
    data = conn.recv(1024)
    print('Connection by', data)
    conn.sendall(b"Connection Success")
    while True:
        try:
            data = conn.recv(1024)
        except ConnectionResetError:
            print("Closed connection")
        print(data)
        if not data:
            break
        string = "Server Recieved Message - " + str(data)
        try:
            conn.sendall(string.encode())
        except ConnectionResetError:
            print("Closed connection")