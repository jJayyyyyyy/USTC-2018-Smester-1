#!/usr/bin/python3
# -*- coding: utf-8 -*-
from math import pi as PI

def get_radius():
	r = int(input('Please input radius: '))
	return r

def get_V(r):
	V =  PI * pow(r, 3) * 4 / 3
	return V

def get_A(r):
	A = PI * pow(r, 2) * 4
	return A

def main():
	r = get_radius()
	V = get_V(r)
	A = get_A(r)
	print("Volume:\t", V)
	print("Area:\t", A)

if __name__ == '__main__':
	main()

