import requests, time

def ledON():
 requests.get('http://192.168.1.32/H')
 
def ledOff():
 requests.get('http://192.168.1.32/L')
 
def relayON():
 requests.get('http://192.168.1.32/RelayOn')
 
def relayOFF():
 requests.get('http://192.168.1.32/RelayOff')
 
def relay2sec():
 relayON();
 time.sleep(2)
 relayOFF();
 time.sleep(2)
 relayON();
 time.sleep(2)
 time.sleep(2)
 relayOFF();

def led2sec():
 ledON();
 time.sleep(2)
 ledOFF();
 time.sleep(2)
 ledON();
 time.sleep(2)
 time.sleep(2)
 ledOFF();