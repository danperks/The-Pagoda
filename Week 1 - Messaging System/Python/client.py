import socket, getpass

HOST = str(input("Enter the server IP: "))
PORT = 65432        # The port used by the server

username = getpass.getuser()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(username.encode())
    data = s.recv(1024)

while True:
    print('RESPONSE: ', repr(data))
    data = input("TO SEND: ")
    s.sendall(data.encode())