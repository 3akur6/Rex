from PIL import Image

# whole = Image.open('assets/trex_8.png')

# subimage_position_list = [
#     {'name': 'cactus_large', 'x': 652, 'y': 2, 'width': 25, 'height': 50},
#     {'name': 'cactus_small', 'x': 446, 'y': 2, 'width': 17, 'height': 35},
#     {'name': 'cloud', 'x': 166, 'y': 2, 'width': 46, 'height': 14},
#     {'name': 'horizon', 'x': 2, 'y': 104, 'width': 600, 'height': 12},
#     {'name': 'moon', 'x': 954, 'y': 2, 'width': 20, 'height': 40},
#     {'name': 'pterodactyl', 'x': 260, 'y': 2, 'width': 46, 'height': 40},
#     {'name': 'text_sprite', 'x': 1294, 'y': 2, 'width': 191, 'height': 11},
#     {'name': 'trex', 'x': 1678, 'y': 2, 'width': 44, 'height': 47},
#     {'name': 'star', 'x': 1276, 'y': 2, 'width': 20, 'height': 40}
# ]

# for item in subimage_position_list:
#     name = "{}.png".format(item['name'])
#     x = item['x']
#     y = item['y']
#     width = item['width'] * 2
#     height = item['height'] * 2
#     region = whole.crop((x, y, x + width, y + height))
#     region.save(name)

assets = 'assets'
rects = [
    {'x': 2, 'y': 7, 'width': 10, 'height': 54},
    {'x': 6, 'y': 0, 'width': 12, 'height': 68},
    {'x': 12, 'y': 4, 'width': 14, 'height': 28},
]

for i in range(0, 3, 1):
    rect = rects[i]
    image = Image.open('{}/cactus_small_1.png'.format(assets, i))
    name = 'cactus_small_part_{}.png'.format(i)
    x = rect['x']
    y = rect['y']
    width = rect['width']
    height = rect['height']
    region = image.crop((x, y, x + width, y + height))
    region.save(name)

