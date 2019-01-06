import requests, time

def ledON():
 requests.get('http://192.168.1.32/H')
 
def ledOff():
 requests.get('http://192.168.1.32/L')
 
while True:
   ledON();
   time.sleep(2)
   ledOFF();
   time.sleep(2)
   ledON();
   time.sleep(2)
   time.sleep(2)
   ledOFF();
