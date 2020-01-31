import socket, getpass

HOST = input("Enter the server IP: ")
PORT = 27015        # The port used by the server

username = getpass.getuser()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(username.encode())
    data = s.recv(1024)
    while True:
        print('RESPONSE: ', repr(data))
        data_in = input("TO SEND: ")
        s.sendall(data_in.encode())