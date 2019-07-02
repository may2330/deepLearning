from PIL import Image, ImageFilter

im = Image.open('/home/seulgi/data/lena.jpg')

# BLUR, CONTOUR, DETAIL, EDGE_EN~
blurImage = im.filter(ImageFilter.BLUR) 
blurImage.show()
blurImage.save('/home/seulgi/data/lena_blur.jpg')
