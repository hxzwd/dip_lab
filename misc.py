
import os
import sys

import numpy as np

from PIL import Image
from struct import pack

image_in_filename = "images/baboon.png"
image_out_filename = "baboon.bin"


image_handle = Image.open(image_in_filename)
image_array = np.array(image_handle)

w, h = image_array.shape

fd = open(image_out_filename, "wb")

#fd.write("{}\n".format(w))
#fd.write("{}\n".format(h))


tmp_str = b""

for i in image_array:
	for j in i:
#		tmp_str = tmp_str + "{} ".format(j)
		tmp_str += pack("B", j)


#fd.write(tmp_str.strip())
fd.write(tmp_str)

#fd.write("\n")
fd.close()

sys.exit(0)
