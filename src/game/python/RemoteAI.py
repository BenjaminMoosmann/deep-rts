import time
import os 
import threading
import zmq
import json
from GameMessage_pb2 import GameMessage

class RemoteAI(threading.Thread):
    def __init__(self):
        print("start!")

    def connect(self, port):
        context = zmq.Context()
        print("Connecting to server...")
        self.socket = context.socket(zmq.REQ)
        self.socket.connect ("tcp://localhost:%s" % port)

    def getState(self):
        data = self.send({"type": "getState"})
        gMsg = GameMessage()
        gMsg.ParseFromString(data)
        return gMsg

    def doAction(self, d_):
        data = self.send({"type": "doAction", "data": d_})
        return json.loads(data)

    def send(self, msg):      
        self.socket.send_json(msg)
        message = self.socket.recv()
        return message

		
    def train(self):
        start = time.time()
        next  = start + 1
        counter = 0