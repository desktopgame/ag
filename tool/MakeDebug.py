import json
import os

def makeConf(name: str):
    return {
            'type': 'lldb',
            'request': 'launch',
            'name': f'tests/{name}',
            'program': f'${{workspaceFolder}}/tests/{name}/{name}',
            'args': [],
            'cwd': '${workspaceFolder}'
    }

obj = {
    'version': '0.2.0',
    'configurations': list(map(makeConf, filter(lambda d: d != 'Template' and 'gitignore' not in d and 'DS_Store' not in d, os.listdir('tests'))))
}
json.dump(obj, open('.vscode/launch.json', 'w'), indent='    ')