import os
from typing import List

def readdir(d: str, p: str, dst: List[str]):
    for file in os.listdir(d):
        if not file.endswith('.hpp') or 'agOne' in file or 'ag.hpp' in file:
            continue
        dst.append(f'#include <{p}/{file}>')

lines: List[str] = []
lines.append('#pragma once')
readdir('./src/include/ag', 'ag', lines)
readdir('./src/include/ag/graphics', 'ag/graphics', lines)

with open('./src/include/ag/agOne.hpp', 'w', encoding='utf-8', newline='\n') as fp:
    for line in lines:
        print(f'{line}', file=fp)