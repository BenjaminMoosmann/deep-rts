import numpy as np
import random
import tensorflow as tf
import matplotlib.pyplot as plt
import scipy.misc
import os
import csv
import itertools
import tensorflow.contrib.slim as slim

class DQN:
	def __init__(self, network_name="main"):
		self.replay_buffer = []
		self.replay_size = 1000

		#Setting the training parameters
		self.batch_size = 4 #How many experience traces to use for each training step.
		self.trace_length = 8 #How long each experience trace will be when training
		self.update_freq = 5 #How often to perform a training step.
		self.y = .99 #Discount factor on the target Q-values
		self.startE = 1 #Starting chance of random action
		self.endE = 0.1 #Final chance of random action
		self.anneling_steps = 10000 #How many steps of training to reduce startE to endE.
		self.num_episodes = 10000 #How many episodes of game environment to train network with.
		self.pre_train_steps = 10000 #How many steps of random actions before training begins.
		self.load_model = False #Whether to load a saved model.
		self.path = "./drqn" #The path to save our model to.
		self.h_size = 512 #The size of the final convolutional layer before splitting it into Advantage and Value streams.
		#self.max_epLength = 50 #The max allowed length of our episode.
		self.time_per_step = 1 #Length of each step used in gif creation
		self.summaryLength = 100 #Number of epidoes to periodically save for analysis
		self.tau = 0.001
		self.network_name = network_name

	def sample_replay(self, batch_size, trace_length):
		sampled_episodes = random.sample(self.replay_buffer, batch_size)
		sampledTraces = []

		for episode in sampled_episodes:
			point = np.random.randint(0,len(episode)+1-trace_length)
			sampledTraces.append(episode[point:point+trace_length])

		sampledTraces = np.array(sampledTraces)
		return np.reshape(sampledTraces,[batch_size*trace_length,5])		 

	def add(self,experience):
		if len(self.replay_buffer) + 1 >= self.replay_size:
			self.replay_buffer[0:(1+len(self.replay_buffer))-self.replay_size] = []
		self.replay_buffer.append(experience)

	def build_model(self):
		cell = tf.contrib.rnn.BasicLSTMCell(num_units=self.h_size, state_is_tuple=True)
		#The network recieves a frame from the game, flattened into an array.
		#It then resizes it and processes it through four convolutional layers.

		self.scalarInput =  tf.placeholder(shape=[None,21168],dtype=tf.float32)

		self.imageIn = tf.reshape(self.scalarInput,shape=[-1,84,84,3])

		self.conv1 = slim.convolution2d(inputs=self.imageIn,num_outputs=32,kernel_size=[8,8],stride=[4,4],padding='VALID', biases_initializer=None,scope=self.network_name+'_conv1')
		self.conv2 = slim.convolution2d(inputs=self.conv1,num_outputs=64,kernel_size=[4,4],stride=[2,2],padding='VALID', biases_initializer=None,scope=self.network_name+'_conv2')
		self.conv3 = slim.convolution2d(inputs=self.conv2,num_outputs=64,kernel_size=[3,3],stride=[1,1],padding='VALID', biases_initializer=None,scope=self.network_name+'_conv3')
		self.conv4 = slim.convolution2d(inputs=self.conv3,num_outputs=h_size,kernel_size=[7,7],stride=[1,1],padding='VALID',biases_initializer=None,scope=self.network_name+'_conv4')

		self.trainLength = tf.placeholder(dtype=tf.int32)

		#We take the output from the final convolutional layer and send it to a recurrent layer.
		#The input must be reshaped into [batch x trace x units] for rnn processing, 
		#and then returned to [batch x units] when sent through the upper levles.
		self.batch_size = tf.placeholder(dtype=tf.int32)
		self.convFlat = tf.reshape(slim.flatten(self.conv4),[self.batch_size,self.trainLength,h_size])
		self.state_in = cell.zero_state(self.batch_size, tf.float32)
		self.rnn,self.rnn_state = tf.nn.dynamic_rnn(inputs=self.convFlat,cell=rnn_cell,dtype=tf.float32,initial_state=self.state_in,scope=self.network_name+'_rnn')
		self.rnn = tf.reshape(self.rnn,shape=[-1,h_size])

		#The output from the recurrent player is then split into separate Value and Advantage streams
		self.streamA,self.streamV = tf.split(self.rnn,2,1)
		self.AW = tf.Variable(tf.random_normal([h_size//2,4]))
		self.VW = tf.Variable(tf.random_normal([h_size//2,1]))
		self.Advantage = tf.matmul(self.streamA,self.AW)
		self.Value = tf.matmul(self.streamV,self.VW)

		self.salience = tf.gradients(self.Advantage,self.imageIn)

		#Then combine them together to get our final Q-values.
		self.Qout = self.Value + tf.subtract(self.Advantage,tf.reduce_mean(self.Advantage,axis=1,keep_dims=True))
		self.predict = tf.argmax(self.Qout,1)

		#Below we obtain the loss by taking the sum of squares difference between the target and prediction Q values.
		self.targetQ = tf.placeholder(shape=[None],dtype=tf.float32)
		self.actions = tf.placeholder(shape=[None],dtype=tf.int32)
		self.actions_onehot = tf.one_hot(self.actions,4,dtype=tf.float32)

		self.Q = tf.reduce_sum(tf.multiply(self.Qout, self.actions_onehot), axis=1)

		self.td_error = tf.square(self.targetQ - self.Q)

		#In order to only propogate accurate gradients through the network, we will mask the first
		#half of the losses for each trace as per Lample & Chatlot 2016
		self.maskA = tf.zeros([self.batch_size,self.trainLength//2])
		self.maskB = tf.ones([self.batch_size,self.trainLength//2])
		self.mask = tf.concat([self.maskA,self.maskB],1)
		self.mask = tf.reshape(self.mask,[-1])
		self.loss = tf.reduce_mean(self.td_error * self.mask)

		self.trainer = tf.train.AdamOptimizer(learning_rate=0.0001)
		self.updateModel = self.trainer.minimize(self.loss)

		
		# Initialize 
		init = tf.global_variables_initializer()




	def new_episode(self):
		pass

	def end_episode(self):
		pass

	def act(self, state):
		pass

	def train(self, reward):
		pass

	def iterate(self):
		pass
		