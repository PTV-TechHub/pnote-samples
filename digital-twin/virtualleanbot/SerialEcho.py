import sys

from pyLeanbot import *

count = 0        # số message đã echo
line = ''        # phần message đang gom, chưa gặp ký tự xuống dòng


def setup():
    Serial.begin(9600)
    Serial.println('Serial echo ready. Type a message and press Send.')


def loop():
    global count, line

    while Serial.available() > 0:            # còn ký tự trong buffer thì đọc tiếp
        value = Serial.read()                # int: mã ký tự, -1 khi buffer rỗng
        if value < 0:
            break

        char = chr(value)
        if char != '\n' and char != '\r':    # chưa hết dòng -> gom tiếp
            line += char
            continue

        if line:                             # trang chốt mỗi message bằng '\n'
            count += 1
            Serial.println(str(count) + ': ' + line)
            line = ''



# Trang mặc định chạy trên Simulator (có module leanbot_runtime): chương trình chạy một mạch từ trên
# xuống, nên tự lặp loop(). Mỗi lần gọi Serial tốn 1 ms thời gian mô phỏng, nên nút STOP vẫn dừng được.
# ?sim=0 chạy trên runner cũ: Leanbot.run() gọi lại loop() theo nhịp, Serial tới giữa hai lần gọi.
if sys.modules.get('leanbot_runtime') is not None:
    setup()
    while True:
        loop()
else:
    Leanbot.run(setup, loop)
