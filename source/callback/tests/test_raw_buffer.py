import mycallback
import numpy as np
np.set_printoptions(5)
x = np.random.randn(3, 2).astype(np.float32)
print(x.dtype)
# mycallback.MyBufferf()
buf = mycallback.MyBufferf(x)
buf.print()
print(x)
x[0] = 10
buf.print()
print(x)

arr = buf.get_memoryview()
print(arr)
m = np.asarray(arr)
# print(m)
# print(arr[0])
arr[0] = 10
print(arr.tolist())
buf.print()
print(m)
m[1] = 5
print(m)
buf.print()
print(m.tobytes())
# print(m.tobytes().decode())

m2 = np.frombuffer(m.tobytes(), m.dtype)
print(m2)

# m.tobytes().de
# print(m.tobytes().hex())/
# v = arr * 10.
# print(v)

# for _ in range(10):
bytes_data = m.tobytes()

for i in range(3):
    t2 = mycallback.MyBufferf()
    # t2.print()

    t2.frombuffer(bytes_data)
    # t2.buffinfo(bytes_data)
    # m[-2] = -1
    # m[-3] = 100
    # print(m2, bytes_data, len(m2.tobytes()), m2.size)
    # print('bytes size', len(m2.tobytes()). m2.size)
    # print(m2)
    # print(m2.dtype)
    # r = t2.get_memoryview
    # m[-1]= 10
    # x[3] = 10
    print("t2.print()", i)
    # t2.print()
    # arr2 = np.asarray(t2.get_memoryview())
    print(m)
    # np.testing.assert_allclose(arr2, m)
    # t2.get_memoryview()

# t2.print()
print('--------------------ok-------------')