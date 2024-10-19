import socket
# Server IP and port
server_ip = "192.168.1.11"
server_port = 8080

def createSocket():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_ip, server_port))
    print(f"Connected to {server_ip}:{server_port}")
    return client_socket

def send_command_to_server(client_socket,command):
    # Send the command to the server
    client_socket.sendall(command.encode('utf-8'))
    # Receive the response from the server
    response = client_socket.recv(1024).decode('utf-8')
    print("Server response:", response)

def closeSocket(client_socket):
    # Close the connection
    client_socket.close()


if __name__ == "__main__":
    cs = createSocket()
    command = ""
    while(command != "exit"):
        command = input("Enter command to send to server (e.g., 'facebook', 'exit'): ")
        send_command_to_server(cs,command)
    closeSocket(cs)