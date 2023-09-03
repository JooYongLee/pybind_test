from flask import Flask
import os
import time
from flask_cors import CORS

from common import get_time_str
app = Flask('testmy')
CORS(app)

@app.route('/', methods=['GET'])
def hello():
    return 'hello world'

@app.route('/test', methods=['GET'])
def hello2():
    return 'hello world-telow'
# from waitress import serve
# import main #main은 flask app을 작성한 py파일입니다.
# serve(main.app, host='0.0.0.0', port=5000)

def main(q):
    print("flask app process:{}".format(os.getpid()))
    print("putting... sleep", get_time_str())
    # time.sleep(2)
    # if q is not None:
    #     q.put('hellow this chiled-process')
    # res = q.get()
    # print('from parent', res)
    print("app=========run", get_time_str())
    app.run(host="0.0.0.0", port=5000, threaded=True)
    # app.run('0.0.0.0', port=5000)
    # serve(app, host=0.0.0)
    # serve(app, host='0.0.0.0', port=5000)

    print('======= flask app exit ========')

if __name__=='__main__':
    main(None)