import os
import re
import sys 
import platform

argvs = sys.argv
if platform.system() != "Darwin":
    reg = re.compile("\.(h|cpp)$")
else:
    reg = re.compile("\.(h|cpp|mm)$")

def find_all_files(directory):
    for root, dirs, files in os.walk(directory):
        yield root
        for file in files:
            yield os.path.join(root, file)

for file in find_all_files(argvs[1]):
    if reg.search(file):
        print("'" + file + "'")
