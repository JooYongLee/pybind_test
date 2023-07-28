from pybind11_stubgen import ModuleStubsGenerator
# https://github.com/robotpy/robotpy-build/issues/1
print(ModuleStubsGenerator)
# import meshlibs_env
# import env
import meshlibs

def generate():
    module = ModuleStubsGenerator(meshlibs)
    module.parse()
    # stubgen.generate_stubs(res)
    
    module.write_setup_py = False
    
    init_pyi = "meshlibs.pyi"
    with open(init_pyi, "w") as fp:
        fp.write("#\n# AUTOMATICALLY GENERATED FILE, DO NOT EDIT!\n#\n\n")
        fp.write("\n".join(module.to_lines()))
    
    print("generate stub files :{}".format(init_pyi))

generate()