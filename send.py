import socket

UDP_PORT = 55555
MESSAGE = "Hello, World!"

print "UDP target port:", UDP_PORT
print "message:", MESSAGE
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.sendto(MESSAGE, ("255.255.255.255", UDP_PORT))
