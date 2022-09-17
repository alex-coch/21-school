from os import system
import random
import os

orig_path = 'cat'
my_path = './cat/s21_cat'

flags = [
    '-e',
    '-b',
    '-n',
    '-s',
    '-t',
    '-v'
]

files = [
    'file/a',
    'file/b',
    'file/c',
    'file/d',
    'file/e',
    'file/f',
    'file/g',
    'file/weirdo.txt'
]


def args():
    curr = random.choice(flags)
    line = ''
    for i in range(random.randrange(1, 3)):
        line += random.choice(flags) + ' '
    for i in range(random.randrange(1, 3)):
        line += random.choice(files) + ' '
    return line


count_fails = 0
for i in range(500):
    add = args()
    # print(add)
    os.system(f'{orig_path} {add} > 0catres')
    os.system(f'{my_path} {add} > 0s21_catres')
    os.system('diff 0catres 0s21_catres > 0diff')
    stat = os.stat('0diff')
    if (stat.st_size == 0):
        # print('SUCCESS\n')
        pass
    else:
        # print('FAIL\n')
        print(f'{orig_path} {add} > 0catres')
        print(f'{my_path} {add} > 0s21_catres')
        print()
        count_fails += 1
        # input()
print(f'{i} total\t{i - count_fails} ok\t{count_fails} errors\n')
os.system(f'rm 0*')
