import os
import shutil
from typing import List

tests: List[str] = os.listdir('tests')
test: str
external_d: str = os.path.join(os.getcwd(), 'external')
testdata_d: str = os.path.join(os.getcwd(), 'testdata')
freeimage_dll: str = os.path.join(external_d, 'FreeImage', 'Dist', 'x64', 'FreeImage.dll')
freetype_dll: str = os.path.join(external_d, 'freetype-2.12.1', 'objs', 'x64', 'Debug', 'freetype.dll')
glew_dll: str = os.path.join(external_d, 'glew-2.1.0', 'bin', 'Release', 'x64', 'glew32.dll')

if not os.path.exists(freeimage_dll):
    print(f'{freeimage_dll} is not found.')
    exit(1)

if not os.path.exists(freetype_dll):
    print(f'{freetype_dll} is not found.')
    exit(1)

if not os.path.exists(glew_dll):
    print(f'{glew_dll} is not found.')
    exit(1)

for test in tests:
    test_d: str = os.path.join(os.getcwd(), 'tests', test)
    if not os.path.exists(test_d):
        continue
    try:
        shutil.copy(freeimage_dll, test_d)
        shutil.copy(freetype_dll, test_d)
        shutil.copy(glew_dll, test_d)
    except:
        pass
    try:
        shutil.copytree(testdata_d, os.path.join(test_d, 'testdata'))
    except:
        pass