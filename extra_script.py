Import ("env","projenv")
import shutil, os
import hashlib
BUF_SIZE = 65536  # lets read stuff in 64kb chunks!

# access to global build environment
print(env)

# access to project build environment (is used source files in "src" folder)
print(projenv)
#
# Dump build environment (for debug purpose)
# print(env.Dump())
#

#
# (Optional) Do not run extra script when IDE fetches C/C++ project metadata
#
from SCons.Script import COMMAND_LINE_TARGETS

if "idedata" in COMMAND_LINE_TARGETS:
    env.Exit(0)


def sha256_of_file(firmware_path):
    # copy firmware.bin from ./.pio/<wherever> to ./
    #print("firmware_path ", firmware_path)
    shutil.copy2(firmware_path,"./")
    #print("file: ",os.path.realpath(target[0]))
    #shutil.copy2(target[1],"./")
    # copy ./firmware.bin to ./temp.bin
    #shutil.copy2("./firmware.bin","./temp.bin")
    # remove last 32 bytes of temp.bin (the sha256 sum footer)
    with open("./firmware.bin", 'rb') as in_file:
        with open("./temp.bin", 'wb') as out_file:
          shutil.copyfileobj(in_file, out_file)
          out_file.seek(-32, os.SEEK_END)
          out_file.truncate()
    # calculate the sha256 of ./temp.bin
    sha256 = hashlib.sha256()

    with open("./temp.bin", 'rb') as f:
        while True:
            data = f.read(BUF_SIZE)
            if not data:
                break
            sha256.update(data)
    sha256str = format(sha256.hexdigest().upper())
    print("sha256: ",sha256str)
    # write uppercase sha256 sum to sha256.txt
    with open("./sha256.txt", 'w') as f:
      f.write(sha256str)
    os.remove("./temp.bin")

#sha256_of_file*("$BUILD_DIR/${PROGNAME}.bin")

#
# Change build flags in runtime
#
#env.ProcessUnFlags("-DVECT_TAB_ADDR")
#env.Append(CPPDEFINES=("VECT_TAB_ADDR", 0x123456789))

#
# Upload actions
#

def before_upload(source, target, env):
    print("\nbefore_upload\n")
    # do some actions

def after_upload(source, target, env):
    print("after_upload")
    # do some actions

print("\nCurrent build targets", map(str, BUILD_TARGETS))

#env.AddPreAction("upload", before_upload)
#env.AddPostAction("upload", after_upload)

#
# Custom actions when building program/firmware
#
def after_build(source,target,env):
    # only runs after a "Compiling" just a "Building in release mode" will not trigger this callback
    print("\nafter_build\n")
    
#env.AddPreAction("buildprog", callback...)
#env.AddPostAction("buildprog", after_build)

#
# Custom actions for specific files/objects
#
    

def after_fwbin(source,target,env):
    # only run after creation of a new binary file
    firmware_path = str(target[0]).replace("\\","/")
    print("\nafter_fwbin\ncalc ESP32 SHA256 of ",firmware_path,"\n");
    sha256_of_file(firmware_path)

env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", after_fwbin)

#env.AddPreAction("$BUILD_DIR/${PROGNAME}.elf", [callback1, callback2,...])
#env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", callback...)

# custom action before building SPIFFS image. For example, compress HTML, etc.
#env.AddPreAction("$BUILD_DIR/spiffs.bin", callback...)

# custom action for project's main.cpp
#env.AddPostAction("$BUILD_DIR/src/main.cpp.o", callback...)

# Custom HEX from ELF
#env.AddPostAction(
#    "$BUILD_DIR/${PROGNAME}.elf",
#    env.VerboseAction(" ".join([
#        "$OBJCOPY", "-O", "ihex", "-R", ".eeprom",
#        "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
#    ]), "Building $BUILD_DIR/${PROGNAME}.hex")
#)