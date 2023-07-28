from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import os
import glob
import shutil

__version__ = '0.0.1'

# dcmtk library. it needs others library?, define some util-function
path_to_fname = lambda x : os.path.splitext(os.path.basename(x))[0]

file_path = os.path.dirname(os.path.abspath(__file__))

internal_lib_path = os.path.join(file_path, '../../../internal_libs')
external_lib_path = os.path.join(file_path, '../../../external_libs')
meshlibs_path = os.path.join(internal_lib_path, 'meshlibs')

include_path_list = [	
    os.path.join(meshlibs_path, "include"), # meshlibs
    os.path.join(external_lib_path, "eigen339"),
    os.path.join(external_lib_path, "eigen339/Eigen"),
    os.path.join(external_lib_path, "plog115"),
]

check = [os.path.exists(p) for p in include_path_list]
assert all(check), "conatin invalid folder"

others_libs = [
    "Ws2_32",
    "Iphlpapi",
    "netapi32",
]

third_libs = [
    #*others_libs
]

all_meshlibs_libs = glob.glob(os.path.join(meshlibs_path, "lib/*.lib"))
all_meshlibs_libs = [path_to_fname(path) for path in all_meshlibs_libs]
all_meshlibs_dlls = glob.glob(os.path.join(meshlibs_path, "dll/*.dll"))

# filtering lib name
ext_meshlibs = [
    "meshCoreBase",
    "meshAlgorithmBase",
    "meshMiscellUtils",
    "meshSampling",
    "meshTree",
    "meshlinalg",
    "meshIglUtils"
]

def filtering(targets, filters):
    outs = []
    for name in targets:
        for _check in filters:
            if name.find(_check) >= 0:
                outs.append(name)
    return outs

meshlibs_libs = filtering(all_meshlibs_libs, ext_meshlibs)
meshlibs_dlls = filtering(all_meshlibs_dlls, ext_meshlibs)

print("filtered meshlibs:{}".format(meshlibs_libs))
path_to_fname = lambda x : os.path.splitext(os.path.basename(x))[0]
vtk_library_path = os.path.join(external_lib_path, "vtk/lib")
vtk_libs = glob.glob(vtk_library_path +  "/*.lib")
vtk_libs = [path_to_fname(path) for path in vtk_libs]
vtk_libs = [path for path in vtk_libs if path[-1] != "d"]

all_libs = [
    *meshlibs_libs,
]

# all_dll_copys = [
#
# ]

library_dirs = [
    # vtk_library_path,
    os.path.join(meshlibs_path, "lib"),
    os.path.join(external_lib_path, 'jsoncpp/lib/x64/Release'), # json

]

print(meshlibs_libs, all_libs)

check = [os.path.exists(p) for p in include_path_list]
assert all(check), "contain some invalid directory for library"
extension_sources = []

for root, dirs, files in os.walk(os.path.join(file_path, 'src')):
    ext_filters = ['cpp', 'cxx']
    
    for file in files:
        if file.lower().endswith(tuple(ext_filters)):
            relapath = os.path.relpath(root, file_path)            
            extension_sources.append(os.path.join(relapath, file))
print("all cpp files:\n{}".format(extension_sources))

class get_pybind_include(object):
    """Helper class to determine the pybind11 include path

    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


ext_modules = [
    Extension(
        'meshlibs',
        extension_sources,
        include_dirs=[
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True),
			*include_path_list,
        ],
        libraries= all_libs,
        library_dirs= library_dirs,
        define_macros = [("EXTENSION_ALL", "")], # macro define for all extension
        language='c++'
    ),
]


# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14/17] compiler flag.

    The newer version is prefered over c++11 (when it is available).
    """
    flags = ['-std=c++17', '-std=c++14', '-std=c++11']

    for flag in flags:
        if has_flag(compiler, flag): return flag

    raise RuntimeError('Unsupported compiler -- at least C++11 support '
                       'is needed!')


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }
    l_opts = {
        'msvc': [],
        'unix': [],
    }

    if sys.platform == 'darwin':
        darwin_opts = ['-stdlib=libc++', '-mmacosx-version-min=10.7']
        c_opts['unix'] += darwin_opts
        l_opts['unix'] += darwin_opts

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        link_opts = self.l_opts.get(ct, [])
        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
        for ext in self.extensions:
            ext.extra_compile_args = opts
            ext.extra_link_args = link_opts
        build_ext.build_extensions(self)

setup(
    name='meshlibs',
    version=__version__,
    author='jooyongLee',
    author_email='yong86@dio.co.kr',
    url='',
    description='meshlibs python userdefined project using pybind11',
    long_description='',
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.3'],
    setup_requires=['pybind11>=2.3'],
    cmdclass={'build_ext': BuildExt},
    zip_safe=False,
)


all_dll_copys = meshlibs_dlls
to_save_dirs_dll = file_path
for src_file in all_dll_copys:
    fname = os.path.basename(src_file)
    tar_file = os.path.join(to_save_dirs_dll, fname)
    shutil.copy(src_file, tar_file)

print("dlls copy complete #{}".format(len(all_dll_copys)))

