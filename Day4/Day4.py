import hashlib
from itertools import count


base_string = "bgvyzdsv"
target_prefix = "00000"

for i in count(0):
    hasher = hashlib.md5()
    hasher.update(bytes(base_string + str(i), 'utf-8'))
    digest = hasher.hexdigest()
    if (i % 1000 == 0):
        print(i)
    if (digest[0:5] == target_prefix):
        print(i)
        break

