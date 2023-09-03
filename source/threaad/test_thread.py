import threading
import os
import time

class TestThread(threading.Thread):
    def __init__(self, *args, **kwargs):
        super(TestThread, self).__init__()
        self.time = kwargs.get('time', 5)
        self.callbacks = kwargs.get('callback', [])

    def run(self) -> None:
        time.sleep(self.time)
        for c in self.callbacks:
            c()
        return 'yosi run returnes'


def get_time_str():
    t1 = time.time()
    d = t1 - int(t1)
    us = int(d*1e6)
    # w = int(1e6)
    # t2 = t1 * w
    # ms = t2 - t2 % w
    # t1 * 1e6 -  t1 * 1e6
    pid = os.getpid()
    res = time.strftime('%Y%m%d%H%M%S')
    return '[' + str(pid) + ']:' + res + '_' + str(us)

def main():

    def callback():
        print("callback")

    thread_run = 3.5
    t = TestThread(time=thread_run, callback=[callback])
    t.start()
    """
        %Y  Year with century as a decimal number.
    %m  Month as a decimal number [01,12].
    %d  Day of the month as a decimal number [01,31].
    %H  Hour (24-hour clock) as a decimal number [00,23].
    %M  Minute as a decimal number [00,59].
    %S  Second as a decimal number [00,61].
    """
    print('yosi', get_time_str())
    sec = 2
    print('time sleec..', sec)

    time.sleep(sec)

    print('awke sleep')
    print('thread is alive', t.is_alive())
    # t.is_alive()
    t1 = time.time()

    res = t.join()
    print('joiding diff time', time.time() - t1)
    print('may be', max(thread_run - sec, 0))
    # t.
    print('joiding returens', res)


main()
# threading.Thread