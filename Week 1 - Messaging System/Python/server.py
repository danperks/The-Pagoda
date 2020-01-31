#!/usr/bin/env python3

import socket

HOST = str(socket.gethostbyname(socket.gethostname())) 
PORT = 65432 

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
servers.bind((HOST, PORT))
server.listen()
conn, addr = s.accept()
with conn:
    print('Connected by', addr)
    while True:
        data = conn.recv(1024)
        if not data:
            break
        conn.sendall(data)