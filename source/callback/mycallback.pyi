#
# AUTOMATICALLY GENERATED FILE, DO NOT EDIT!
#

"""mycallback binding"""
from __future__ import annotations
import mycallback
import typing
import numpy
_Shape = typing.Tuple[int, ...]

__all__ = [
    "Buffer",
    "BufferReadOnly",
    "BufferReadOnlySelect",
    "CallbackTest",
    "ConstBuffer",
    "DerivedBuffer",
    "Matrix",
    "MyBufferf",
    "MyBufferx",
    "SquareMatrix",
    "TestSum",
    "Volume",
    "VolumeMerge",
    "buffer_info",
    "format_descriptor_format_buffer_info_equiv",
    "get_buffer_info",
    "long_double_and_double_have_same_size"
]


class Buffer():
    def __init__(self) -> None: ...
    @property
    def value(self) -> int:
        """
        :type: int
        """
    @value.setter
    def value(self, arg0: int) -> None:
        pass
    pass
class BufferReadOnly():
    def __init__(self, arg0: int) -> None: ...
    pass
class BufferReadOnlySelect():
    def __init__(self) -> None: ...
    @property
    def readonly(self) -> bool:
        """
        :type: bool
        """
    @readonly.setter
    def readonly(self, arg0: bool) -> None:
        pass
    @property
    def value(self) -> int:
        """
        :type: int
        """
    @value.setter
    def value(self, arg0: int) -> None:
        pass
    pass
class CallbackTest():
    def __init__(self) -> None: ...
    @staticmethod
    def run(*args, **kwargs) -> typing.Any: ...
    def set_callback(self, arg0: typing.Callable[[numpy.ndarray[numpy.float32, _Shape[m, n]]], int]) -> int: ...
    @property
    def nmae(self) -> str:
        """
        :type: str
        """
    @nmae.setter
    def nmae(self, arg0: str) -> None:
        pass
    pass
class ConstBuffer():
    def __init__(self) -> None: ...
    @property
    def value(self) -> int:
        """
        :type: int
        """
    @value.setter
    def value(self, arg1: int) -> None:
        pass
    pass
class DerivedBuffer():
    def __init__(self) -> None: ...
    @property
    def value(self) -> int:
        """
        :type: int
        """
    @value.setter
    def value(self, arg0: int) -> None:
        pass
    pass
class Matrix():
    def __getitem__(self, arg0: typing.Tuple[int, int]) -> float: ...
    @typing.overload
    def __init__(self, arg0: int, arg1: int) -> None: ...
    @typing.overload
    def __init__(self, arg0: buffer) -> None: ...
    def __setitem__(self, arg0: typing.Tuple[int, int], arg1: float) -> None: ...
    def cols(self) -> int: ...
    def rows(self) -> int: ...
    pass
class MyBufferf():
    @typing.overload
    def __init__(self) -> None: ...
    @typing.overload
    def __init__(self, arg0: numpy.ndarray[numpy.float32, _Shape[m, n]]) -> None: ...
    def buffinfo(self, arg0: buffer) -> None: ...
    def frombuffer(self, arg0: bytes) -> None: ...
    def fromstring(self, arg0: str) -> None: ...
    def get_memoryview(self) -> memoryview: ...
    def print(self) -> None: ...
    pass
class MyBufferx():
    def __init__(self, arg0: numpy.ndarray[numpy.float64, _Shape[m, n]]) -> None: ...
    def print(self) -> None: ...
    pass
class SquareMatrix(Matrix):
    def __init__(self, arg0: int) -> None: ...
    pass
class TestSum():
    def __init__(self) -> None: ...
    def set(self, arg0: CallbackTest) -> None: ...
    pass
class Volume():
    def __init__(self) -> None: ...
    pass
class VolumeMerge():
    def __init__(self) -> None: ...
    def test(self, arg0: buffer) -> None: ...
    def test2(self, arg0: typing.List[numpy.ndarray[numpy.float32, _Shape[m, n]]]) -> None: ...
    pass
class buffer_info():
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    @property
    def format(self) -> str:
        """
        :type: str
        """
    @property
    def itemsize(self) -> int:
        """
        :type: int
        """
    @property
    def ndim(self) -> int:
        """
        :type: int
        """
    @property
    def readonly(self) -> bool:
        """
        :type: bool
        """
    @property
    def shape(self) -> typing.List[int]:
        """
        :type: typing.List[int]
        """
    @property
    def size(self) -> int:
        """
        :type: int
        """
    @property
    def strides(self) -> typing.List[int]:
        """
        :type: typing.List[int]
        """
    pass
def format_descriptor_format_buffer_info_equiv(arg0: str, arg1: buffer) -> typing.Tuple[str, bool]:
    pass
def get_buffer_info(arg0: buffer) -> buffer_info:
    pass
long_double_and_double_have_same_size = True
