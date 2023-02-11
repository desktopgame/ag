import os
from typing import List

header: List[str] = []
header.append('#pragma once')
header.append('#include <string>')
header.append('')
header.append('namespace ag {')
header.append('namespace internal {')

body: List[str] = []

footer: List[str] = []
footer.append('}')
footer.append('}')

def varname(file: str) -> str:
    pos: int = file.index('.')
    if pos == -1:
        return file
    return file[0:pos]

with open('shader/Build.txt', 'r', encoding='UTF-8') as fp:
    lines: List[str] = fp.readlines()
    line: str
    for line in lines:
        file: str = f'shader/{line.rstrip()}'
        if not os.path.exists(file):
            continue
        body.append(f'    static constexpr inline const char* {varname(line.rstrip())} = R"(')
        fp = open(file, 'r', encoding='UTF-8')
        for part in fp.readlines():
            part = part.rstrip()
            if len(part) == 0:
                body.append('')
            else:
                body.append(f'        {part}')
        body.append(f'    )";')
        fp.close()

with open('src/include/ag/graphics/ShaderCode.hpp', 'w', encoding='UTF-8') as fp:
    for h in header:
        fp.write(f'{h}\n')
    for b in body:
        fp.write(f'{b}\n')
    for f in footer:
        fp.write(f'{f}\n')
