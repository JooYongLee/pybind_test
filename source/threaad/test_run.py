# @time_fn
import time

import requests
def child_requiest():
    resp = requests.get('http://127.0.0.1:8080')
    # print(resp)
    print(resp.content.decode())

for _ in range(5):

    child_requiest()

# import threading
#
# for i in range(10):
#     s = threading.Thread(target=child_requiest, args=())
#     s.start()
#
# print("thread run")
# time.sleep(10)