import os
from Util import hasCUDASupport
os.environ["KERAS_BACKEND"] = "theano"
if(hasCUDASupport()):
	os.environ["THEANO_FLAGS"] ="floatX=float32,device=cuda"
else:
	os.environ["THEANO_FLAGS"] ="floatX=float32,device=cpu"


import random
import numpy
from keras import backend as K
from keras.models import Model
from keras.layers import Conv2D, Dense, Flatten, Input, merge
from keras.layers.normalization import BatchNormalization
from keras.optimizers import RMSprop
from theano.gradient import disconnected_grad

class DQN:
	def __init__(self, state_size=None, number_of_actions=1, epsilon=0.1, mbsz=32, discount=0.9, memory=40, save_name='basic', save_freq=10, learning_rate=0.0001):
		self.state_size = state_size
		self.number_of_actions = number_of_actions
		self.epsilon = epsilon
		self.mbsz = mbsz
		self.discount = discount
		self.memory = memory
		self.save_name = save_name
		self.states = []
		self.actions = []
		self.rewards = []
		self.experience = []
		self.learning_rate = learning_rate
		self.i = 1
		self.save_freq = save_freq
		print("Lets build functions!")
		self.build_functions()

	def build_model(self):
		S = Input(shape=self.state_size)
		h = Conv2D(256, (1,1), padding="same", kernel_initializer="uniform", strides=(1, 1), activation="relu")(S)
		h = Conv2D(128, (1,1), padding="same", kernel_initializer="uniform", strides=(1, 1), activation="relu")(h)
		#h = Conv2D(128, (1, 1), padding="same", kernel_initializer="uniform", strides=(1, 1), activation="relu")(h)
		h = Flatten()(h)
		h = Dense(256, activation='relu')(h)
		V = Dense(self.number_of_actions)(h)
		self.model = Model(S, V)
		try:
			self.model.load_weights('{}.h5'.format(self.save_name))
			print("loading from {}.h5".format(self.save_name))
		except:
			print("Training a new model")


	def build_functions(self):
		S = Input(shape=self.state_size)
		NS = Input(shape=self.state_size)
		A = Input(shape=(1,), dtype='int32')
		R = Input(shape=(1,), dtype='float32')
		T = Input(shape=(1,), dtype='int32')
		self.build_model()
		self.value_fn = K.function([S], self.model(S))

		VS = self.model(S)
		VNS = disconnected_grad(self.model(NS))
		future_value = (1-T) * VNS.max(axis=1, keepdims=True)
		discounted_future_value = self.discount * future_value
		target = R + discounted_future_value
		cost = ((VS[:, A] - target)**2).mean()
		opt = RMSprop(self.learning_rate)
		params = self.model.trainable_weights
		updates = opt.get_updates(params, [], cost)
		self.train_fn = K.function([S, NS, A, R, T], cost, updates=updates)

	def new_episode(self):
		self.states.append([])
		self.actions.append([])
		self.rewards.append([])
		self.states = self.states[-self.memory:]
		self.actions = self.actions[-self.memory:]
		self.rewards = self.rewards[-self.memory:]
		self.i += 1
		if self.i % self.save_freq == 0:
			self.model.save_weights('{}.h5'.format(self.save_name), True)

	def end_episode(self):
		pass

	def act(self, state):
		self.states[-1].append(state)
		values = self.value_fn([state[None, :]])
		if numpy.random.random() < self.epsilon:
			action = numpy.random.randint(self.number_of_actions)
		else:
			action = values.argmax()
		self.actions[-1].append(action)
		return action, values

	def train(self, reward):
		self.rewards[-1].append(reward)
		return self.iterate()

	def iterate(self):
		N = len(self.states)
		S = numpy.zeros((self.mbsz,) + self.state_size)
		NS = numpy.zeros((self.mbsz,) + self.state_size)
		A = numpy.zeros((self.mbsz, 1), dtype=numpy.int32)
		R = numpy.zeros((self.mbsz, 1), dtype=numpy.float32)
		T = numpy.zeros((self.mbsz, 1), dtype=numpy.int32)
		for i in range(self.mbsz):
			episode = random.randint(max(0, N-50), N-1)
			num_frames = len(self.states[episode])
			frame = random.randint(0, num_frames-1)
			S[i] = self.states[episode][frame]
			T[i] = 1 if frame == num_frames - 1 else 0
			if frame < num_frames - 1:
				NS[i] = self.states[episode][frame+1]
			A[i] = self.actions[episode][frame]
			R[i] = self.rewards[episode][frame]
		cost = self.train_fn([S, NS, A, R, T])
		return cost