import os
cur_dir = os.path.dirname(os.path.realpath(__file__))
input_dir = os.path.join(cur_dir, 'input')

if not os.path.exists(input_dir):
    os.mkdir(input_dir)

def write_file(i):
    fp = os.path.join(input_dir, str(i) + '.txt')
    s = str(i) + ' '
    s += 'url:' + str(i) + ' '
    s += 'storage-type' + ' '
    s += str(i) + ' ' #face_detect
    s += '0 ' #face_recognise
    s += '0 ' #activity_recognise
    s += '0 ' #speech_recognise
    open(fp, 'w').write(s)

if __name__ == '__main__':
    for i in range(1, 101):
        write_file(i)


