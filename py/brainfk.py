# It's a brainfuck interpreter

from sys import argv, stderr

data = [0] * 30000
iptr = dptr = 0

def findnext(l):
    count = 1
    for i in range(len(l)):
        c = l[i]
        if c == '[':
            count += 1
        if c == ']':
            count -= 1
        if count == 0:
            return i
    raise ValueError(f'bruh: {count}')

def findprevious(l):
    count = 1
    for i in range(len(l) - 1, -1, -1):
        c = l[i]
        if c == ']':
            count += 1
        if c == '[':
            count -= 1
        if count == 0:
            return i
    raise ValueError('bruh')


with open(argv[1]) as file:
    program = file.read().replace('\n', '').replace(' ', '')

try:
    while iptr < len(program):
        char = program[iptr]
        if char == '>':
            dptr += 1
        elif char == '<':
            dptr -= 1
        elif char == '+':
            data[dptr] += 1
        elif char == '-':
            data[dptr] -= 1
        elif char == '.':
            print(chr(data[dptr]), end='', flush=True)
        elif char == ',':
            inp = input()
            if inp == '':
                data[dptr] = 0
            else:   
                data[dptr] = ord(inp[0])
        else:
            if char == '[':
                if data[dptr] == 0:
                    iptr = findnext(program[iptr + 1:]) + iptr + 1
                    continue
            elif char == ']':
                if data[dptr] != 0:
                    iptr = findprevious(program[:iptr - 1]) + 1
                    continue
            else:
                raise ValueError(f"Bad program")
        iptr += 1
except Exception as e:
    print(f'\nException at char [{iptr} - "{program[iptr]}"]; {e}', file=stderr)