import hashlib
from itertools import count


base_string = "bgvyzdsv"
target_prefix_easy = "00000"
target_prefix_hard = "000000"

def n_prefixed(n):
    target_prefix = n * '0'
    for i in count(0):
        hasher = hashlib.md5()
        hasher.update(bytes(base_string + str(i), 'utf-8'))
        digest = hasher.hexdigest()
        if (digest[0:n] == target_prefix):
            return i

def easy():
    return n_prefixed(5)


def hard():
    return n_prefixed(6)

print(easy())
print(hard())