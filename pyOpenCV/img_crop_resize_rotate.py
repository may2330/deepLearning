from PIL import Image
im = Image.open('/home/seulgi/data/lena.jpg')

cropImage = im.crop((100,100,350,350))
cropImage.show()
cropImage.save('/home/seulgi/data/lena_crop.jpg')

im = Image.open('/home/seulgi/data/lena.jpg')

img2 = im.resize((600,600))
img2.save('/home/seulgi/data/lena_resise.jpg')

im = Image.open('/home/seulgi/data/lena.jpg')
img3 = im.rotate(90)
img3.save('/home/seulgi/data/lena_rotate.jpg')
