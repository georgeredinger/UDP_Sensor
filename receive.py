import select, socket

#port = 12345  # where do you expect to get a msg?
port = 55555  # where do you expect to get a msg?
bufferSize = 1024 # whatever you need

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#s.bind(('<broadcast>', port))
s.bind(('192.168.1.100', port))
#s.bind(('0.0.0.0', port))
s.setblocking(0)

while True:
  result = select.select([s],[],[])
  msg = result[0][0].recv(bufferSize)
  print msg


