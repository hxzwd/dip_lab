
import os
import sys

import numpy as np

from PIL import Image
from struct import unpack

w_size = 512
h_size = 512


input_bin = "baboon_out.bin"
output_png = "baboon_out.png"

input_bin = "baboon_out_t.bin"
output_png = "baboon_out_t.png"

bin_data = b""
image_array = []


handle = open(input_bin, "rb")

bin_data = handle.read()
handle.close()

for one_byte in bin_data:
	image_array.append(unpack("B", one_byte))


image_array = np.array(image_array, dtype = np.uint8)


image_array = image_array.reshape(w_size, h_size)
image_array.dtype = np.uint8

image_handle = Image.fromarray(image_array)

image_handle.save(output_png)

