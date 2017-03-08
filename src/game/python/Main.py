
import sys
import time

import RemoteAI
from DQN import DQN


remAI = RemoteAI.RemoteAI()
remAI.connect(5000)
network = DQN(remAI)
network.setup_pretrain()
while True:
   
    state = remAI.getState()
    network.train_step(state)