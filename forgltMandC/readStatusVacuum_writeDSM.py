#from bs4 import BeautifulSoup
import subprocess, os, sys, time
import socket, datetime

'''
TestDSM=['DSM_Test_C1','DSM_Test_F',]
finalvals=["A",3.15]
subprocess.call(["/var/www/cgi-bin/GLT/write_char_DSM", TestDSM[0], finalvals[0] ]);
subprocess.call(["/var/www/cgi-bin/GLT/write_float_DSM", listMaserDSM[1], finalvals[1] ]);
'''

#running  cpy3 pfeiffer_sd.py

vacuumgauge_addr = ('192.168.1.229', 8000) # for vacuum gauge via XS1000 RS232-ETHERNET adaptor


sv = socket.create_connection(vacuumgauge_addr) # open vacuum socket
cmd = b'PRX\r'
sv.sendall(cmd)
r = sv.recv(32)
#print(r.decode())

cmd = b'\05'
sv.sendall(cmd)
r = sv.recv(32).decode()
print(r)
#1.3600E+01 or 9.9800E-07 1.0200E-06  
print('The vacuum of Dewar:',r[3:13],'  Pump:',r[17:27])
dewar=r[3:6]+r[9:10]+r[12]
pump=r[17:20]+r[23:24]+r[26]
print('The vacuum of Dewar:',dewar,'  Pump:',pump)
#
#subprocess.call(["/var/www/cgi-bin/GLT/write_char_DSM", 'DSM_PUMP_PRESS_C7', '2.03E-2']);
#subprocess.call(["/var/www/cgi-bin/GLT/write_char_DSM", listMaserDSM[i], finalvals[i]]);
