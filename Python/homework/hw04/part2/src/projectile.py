#!/usr/bin/python3
# -*- coding: utf-8 -*-

# cannonball
from math import sin, cos, radians

class Projectile:

	"""Simulates the flight of simple projectiles near the earth's
	surface , ignoring wind resistance . Tracking is done in two
	dimensions , height (y) and distance (x) . """

	def __init__(self, angle, velocity, height):
		self.posX = 0.0
		self.posY = height
		theta = radians(angle)
		self.velX = velocity * cos(theta)
		self.velY = velocity * sin(theta)
		self.maxY = 0.0

	def getX(self):
		return self.posX

	def getY(self):
		return self.posY

	def update(self, timeInterval):
		self.posX = self.posX + self.velX * timeInterval
		nextVelY = self.velY - 9.8 * timeInterval
		self.posY = self.posY + (self.velY + nextVelY)/2 * timeInterval
		if self.maxY < self.posY:
			self.maxY = self.posY
		self.velY = nextVelY

def getInput():
	angle = float(input("Angle: "))
	velocity = float(input('Velocity: '))
	h0 = float(input("H0: "))
	timeInterval = float(input("time interval(second): "))
	return angle, velocity, h0, timeInterval

def main():
	angle, velocity, h0, timeInterval = getInput()
	cball = Projectile(angle, vel, h0)

	while cball.getY() >= 0:
		cball.update(timeInterval)

