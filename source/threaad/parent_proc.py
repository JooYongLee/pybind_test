# from requests import request, get, post
import requests
import multiprocessing
import child_main as childmain
import os
import time
import random
import sys
from common import get_time_str

def time_fn(fn):
    def inner(*args, **kwargs):
        t1 = time.time()
        res = fn(*args, **kwargs)
        print(fn.__name__, 'took', time.time()-t1)
        return res
    return inner


@time_fn
def child_requiest():
    resp = requests.get('http://127.0.0.1:5000/')
    # print(resp)
    print(resp.content.decode())

def main():
    print("process...{}".format(os.getpid()))
    q = multiprocessing.Queue()
    p = multiprocessing.Process(target=childmain.main, args=(q,))
    p.daemon = True
    p.start()
    print(get_time_str())
    print(q.get())
    w = 2
    print("putting...wait...{}sec".format(w))
    # time.sleep(w)
    # q.put('this is server')
    print('--------ok========')
    print('requesting.........')
    child_requiest()
    print('is running', p.pid, p.is_alive())
    time.sleep(10)
    print('============complete========')

    # p.join()
    p.terminate()
    time.sleep(0.1)
    print('is running', p.pid, p.is_alive())
    print('finished==========')
    # p.close()

def process(instance):
    total_time = random.uniform(0, 2)
    time.sleep(total_time)
    print('Process %s : completed in %s sec' % (instance, total_time))

def main2():
# if __name__ == '__main__':
    """Demonstration of GIL-friendly asynchronous development with Python's multiprocessing module"""


    for i in range(10):
        """Create 10 non-blocking subprocesses that will have random runtimes"""
        multiprocessing.Process(target=process, args=(i,)).start()

if __name__ == '__main__':
    # childmain.main()
    # main2()
    # main()
    for _ in range(5):
        child_requiest()


