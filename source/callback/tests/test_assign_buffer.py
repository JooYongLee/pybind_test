import mycallback
import numpy as np

x = np.arange(6).reshape([-1, 2]).astype(np.float32) + 2
bytes_data = x.tobytes()

for i in range(3):
    t2 = mycallback.MyBufferf()
    # t2.frombuffer(bytes_data)
    # t2.buffinfo(x)
    # t2.buffinfo(x.tobytes())
    # t2.fromstring(bytes_data)
    t2.frombuffer(bytes_data)

    x2 = np.asarray(t2.get_memoryview())
    x2[i] = 2 *i
    t2.print()
    print(x2.dtype, x2.shape)
    print(i, '----->', x2)

with open('../test.bin', 'wb') as f:
    f.write(bytes_data)
