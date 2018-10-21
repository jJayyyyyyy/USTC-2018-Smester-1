#!/usr/bin/python3
# -*- coding: utf-8 -*-

from graphics import *
from button import Button
from shot_tracker import ShotTracker
from input_dialog import InputDialog

def main():
	win = GraphWin('Animation', 640, 480, autoflush=False)
	win.setCoords(-10, -10, 210, 155)
	Line(Point(-10, 0), Point(210, 0)).draw(win)
	for x in range(0, 210, 50):
		Text(Point(x, -5), str(x)).draw(win)
		Line(Point(x, 0), Point(x, 2)).draw(win)

	while True:

		inputWin = InputDialog(90, 30, 0)
		choice = inputWin.interact()
		inputWin.close()

		if choice == 'Fire':
			angle, vel, height = inputWin.getValues()
			shot = ShotTracker(win, angle, vel, height)

			while 0 <= shot.getY() and shot.getX() > -10 and shot.getX() <= 210:
				shot.update(1/30)
				update(30)
			# 显示最大高度
			maxHeight = "最大高度: %.2f 米" % shot.proj.maxY
			maxHeightWin = GraphWin('Max Height', 240, 180)
			Text(Point(120, 90), maxHeight).draw(maxHeightWin)
		else:
			break

if __name__ == '__main__':
	main()
