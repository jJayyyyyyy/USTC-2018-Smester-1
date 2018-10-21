#!/usr/bin/python3
# -*- coding: utf-8 -*-

from graphics import Point, GraphWin, Text, Entry
from button import Button

class InputDialog(object):
	def __init__(self, angle, vel, height):
		self.win = win = GraphWin('Init', 200, 300)
		win.setCoords(0, 4.5, 4, 0.5)
		Text(Point(1,1), 'angle: ').draw(win)
		self.angle = Entry(Point(3, 1), 5).draw(win)
		self.angle.setText(str(angle))
		Text(Point(1, 2), 'velocity: ').draw(win)
		self.vel = Entry(Point(3, 2), 5).draw(win)
		self.vel.setText(str(vel))

		Text(Point(1, 3), 'Height').draw(win)
		self.height = Entry(Point(3, 3), 5).draw(win)
		self.height.setText(str(height))

		self.fire = Button(win, Point(1, 4), 1.25, 0.5, 'Fire!')
		self.fire.activate()
		self.quit = Button(win, Point(3, 4), 1.25, 0.5, 'Quit')
		self.quit.activate()

	def interact(self):
		while True:
			pt = self.win.getMouse()
			if self.quit.clicked(pt):
				print('quit')
				return "Quit"
			if self.fire.clicked(pt):
				print('fire')
				return "Fire"

	def getValues(self):
		a= float(self.angle.getText() )
		v = float(self.vel.getText () )
		h = float(self.height.getText() )
		return a,v,h 

	def close(self):
		self.win.close()
