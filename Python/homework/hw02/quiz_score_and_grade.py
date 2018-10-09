#!/usr/bin/python3
# -*- coding: utf-8 -*-

class Quiz(object):
	def __init__(self):
		pass

	# 把 `5~0` 的分数转换成 `A~F` 的成绩
	def getGrade(self, score):
		grade = None
		if score <= 5 and score >= 0:
			# 利用 chr(), ord(), 以及 ASCII 码进行转换
			grade = chr(ord('F') - score)
		return grade

	def getScore(self, grade):
		score = None
		if isinstance(grade, str) and len(grade) == 1 and grade.isalpha():
			tmpScoreA = ord('A')
			tmpScoreF = ord('F')
			tmpScore = ord(grade)
			if tmpScore >= tmpScoreA and tmpScore <= tmpScoreF:
				score = tmpScoreF - tmpScore
		return score

	# 测试函数
	def test(self):
		# 预期结果
		expScore = {5:'A', 4:'B', 3:'C', 2:'D', 1:'E', 0:'F', 6:None, -1:None}
		# expGrade = {'A':5, 'B':4, 'C':3, 'D':2, 'E':1, 'F':0, 'G':None, 'hi':None}

		print('Test function getGrade()')
		print('Score\t\tExpected Grade\t\tTest Grade\tIs Same')
		
		for score, grade in expScore.items():
			tmpGrade = self.getGrade(score)		# getGrade() 得到的结果
			isSame = bool(grade == tmpGrade)	# 与预期结果进行对比
			print(score, '\t\t', grade, '\t\t\t', tmpGrade, '\t\t', isSame)

		# print('\n\nTest function getScore()')
		# print('Grade\t\tExpected Score\t\tTest Score\tIs Same')
		# for grade, score in expGrade.items():
		# 	tmpScore = self.getScore(grade)
		# 	isSame = bool(score == tmpScore)
		# 	print(grade, '\t\t', score, '\t\t\t', tmpScore, '\t\t', isSame)

if __name__ == '__main__':
	quiz = Quiz()
	quiz.test()
