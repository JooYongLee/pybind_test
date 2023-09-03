import time, os

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