from PIL import Image
import sys

def resize(img, size):
	newSize = (size, size)
	newImage = img.resize(newSize, Image.ANTIALIAS)		# 平滑抗锯齿
	return newImage

def get_portrait(filename):
	img = Image.open(filename)
	return resize(img, 886)

def main():
	filename = sys.argv[1]
	portrait = get_portrait(filename)
	stamp = Image.open('ustc60.png').convert('RGBA')
	alpha = stamp.split()[3]
	region = (0, 0);
	portrait.paste(stamp, region, mask=alpha)
	portrait = resize(portrait, 640)
	portrait.save('stamped_portrait.jpg', 'jpeg')

if __name__ == '__main__':
	main()
