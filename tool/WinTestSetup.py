import os
import shutil
from typing import List

tests: List[str] = os.listdir('tests')
dll_d: str = os.path.join(os.getcwd(), 'external', 'dll')
testdata_d: str = os.path.join(os.getcwd(), 'testdata')

test: str
for test in tests:
    test_d: str = os.path.join(os.getcwd(), 'tests', test)
    if not os.path.exists(test_d) or test == '.gitignore':
        continue
    dll: str
    for dll in os.listdir(dll_d):
        try:
            dll_p: str = os.path.join(dll_d, dll)
            if dll_p.endswith('.dll'):
                shutil.copyfile(dll_p, os.path.join(test_d, dll))
        except:
            pass
    try:
        shutil.copytree(testdata_d, os.path.join(test_d, 'testdata'))
    except:
        pass