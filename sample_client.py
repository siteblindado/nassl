#!/usr/bin/python2.7
import socket
from nassl import TLSV1, SSL_VERIFY_NONE
from nassl.debug_ssl_client import DebugSslClient


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.settimeout(5)
sock.connect(("www.google.com", 443))

ssl_client = DebugSslClient(ssl_version=TLSV1, sock=sock, ssl_verify=SSL_VERIFY_NONE)
ssl_client.do_handshake()

print('Certificate chain')
for cert in ssl_client.get_peer_cert_chain():
    print(cert.as_dict()['subject']['commonName'])

print('\nCipher suite')
print(ssl_client.get_current_cipher_name())

print('\nHTTP response')
ssl_client.write('GET / HTTP/1.0\r\nUser-Agent: Test\r\nHost: www.google.com\r\n\r\n')
print(ssl_client.read(2048))
