import os
from typing import List

glfw: str = '/opt/homebrew/include/GLFW/glfw3.h'
print('#pragma once')
print('namespace ag {')
print('enum class KeyCode : int {')
with open(glfw, 'r') as fp:
    line: str
    deflines: List[str] = list(filter(lambda line: line.startswith('#define'), fp.readlines()))
    keylines: List[str] = list(filter(lambda line: 'GLFW_KEY' in line, deflines))
    keyline: str
    for keyline in keylines:
        vals: List[str] = keyline.split(' ')
        vals = list(filter(lambda val: val != ' ' and val != '' and '*' not in val, vals))
        vals = list(map(lambda val: val.strip(), vals))
        name: str = vals[1]
        val: str = vals[2]
        if name == 'GLFW_KEY_LAST':
            continue
        name_parts: List[str] = name.split('_')
        name_parts = name_parts[2:]
        name_parts = list(map(lambda np: np.capitalize(), name_parts))
        name = ''.join(name_parts)
        if len(name) == 1 and name in '0123456789':
            name = f'Num{name}'
        # if len(name) == 1 and name in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
        #     name = f'Alpha{name}'
        print(f'    {name} = {val},')
print('};')
print('}')