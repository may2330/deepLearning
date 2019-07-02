from PIL import Image

# Take two images for blending them together
image1 = Image.open("/home/seulgi/data/apple.jpg")
image2 = Image.open("/home/seulgi/data/orange.jpg")

# resize
image1 = image1.resize((512,512))
image2 = image2.resize((512,512))

# Make sure images got an alpha channel
image5 = image1.convert("RGBA")
image6 = image2.convert("RGBA")

# alpha-blend the images with varying values of alpha
alphaBlended1 = Image.blend(image5, image6, alpha=.2)
alphaBlended2 = Image.blend(image5, image6, alpha=.8)

# Display the alpha-blended images
alphaBlended1.show()
alphaBlended2.show()
