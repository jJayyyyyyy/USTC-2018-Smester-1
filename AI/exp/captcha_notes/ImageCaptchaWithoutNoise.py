import random
from PIL import ImageFilter
from captcha.image import ImageCaptcha, random_color

# https://github.com/lepture/captcha/blob/master/captcha/image.py
class ImageCaptchaWithoutNoise(ImageCaptcha):
	def generate_image(self, chars):
		background = random_color(238, 255)
		color = random_color(10, 200, random.randint(220, 255))
		im = self.create_captcha_image(chars, color, background)
		im = im.filter(ImageFilter.SMOOTH)
		return im

if __name__ == '__main__':
	image = ImageCaptchaWithoutNoise()
	data = image.generate('1234')
	image.write('1234', 'out.png')