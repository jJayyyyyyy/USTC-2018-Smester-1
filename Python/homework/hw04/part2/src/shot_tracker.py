#!/usr/bin/python3
# -*- coding: utf-8 -*-

from projectile import Projectile
from graphics import Circle, Point

class ShotTracker(object):
	def __init__(self, win, angle, velocity, height):
		self.proj = Projectile(angle, velocity, height)
		self.marker = Circle(Point(0, height), 3)	# 圆心, 半径
		self.marker.setFill('red')
		self.marker.setOutline('red')
		self.marker.draw(win)

	def update(self, dt):
		self.proj.update(dt)

		center = self.marker.getCenter()
		dx = self.proj.getX() - center.getX()
		dy = self.proj.getY() - center.getY()
		self.marker.move(dx, dy)

	def getX(self):
		return self.proj.getX()

	def getY(self):
		return self.proj.getY()

	def undraw(self):
		self.marker.undraw()
