from PIL import Image

whole = Image.open('assets/200-offline-sprite.png')

whole_size = whole.size
whole_width = whole_size[0]
whole_height = whole_size[1]

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
name = "trex_9.png"
x = 2321
y = 36
width = 118
height = 60
region = whole.crop((x, y, x + width, y + height))
region.save(name)

