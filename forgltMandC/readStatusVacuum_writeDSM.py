#from bs4 import BeautifulSoup
import subprocess, os, sys, time
import socket, datetime

'''
TestDSM=['DSM_Test_C1','DSM_Test_F',]
finalvals=["A",3.15]
subprocess.call(["/var/www/cgi-bin/GLT/write_char_DSM", TestDSM[0], finalvals[0] ]);
subprocess.call(["/var/www/cgi-bin/GLT/write_float_DSM", listMaserDSM[1], finalvals[1] ]);
'''


vacuumgauge_addr = ('192.168.1.229', 8000) # for vacuum gauge via XS1000 RS232-ETHERNET adaptor


sv = socket.create_connection(vacuumgauge_addr) # open vacuum socket
cmd = b'PRX\r'
sv.sendall(cmd)
r = sv.recv(32)

cmd = b'\05'
sv.sendall(cmd)
r = sv.recv(32).decode()


print('The vacuum of Dewar:',r[3:13],'  Pump:',r[17:27])
#
