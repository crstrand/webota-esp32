# This python file is for use with the PlatformIO build system for microcontrollers
#  call it with extra_scripts = pre:git_rev_macro.py in platform.ini
#
import subprocess
import datetime
import os

Import("env")

VERSION_FILE = 'version'
VERSION_HEADER = 'Version.h'
VERSION_PREFIX = '0.1.'
VERSION_PATCH_NUMBER = 0

def revision():
    try:
        return (subprocess.check_output(["git", "describe", "--match=DoNotMatchTag", "--always", "--dirty"], stderr=subprocess.DEVNULL)
                .strip()
                .decode("utf-8"))
    except subprocess.CalledProcessError as e:
        return 'NO_GIT_REPO'

def branch():
    try:
        return (
            subprocess.check_output(["git", "branch", "--show-current"], stderr=subprocess.DEVNULL)
            .strip()
            .decode("utf-8")
        )
    except subprocess.CalledProcessError as e:
        return 'NO_BRANCH'

HEADER_FILE = """
// AUTO GENERATED FILE, DO NOT EDIT OR COMMIT
#ifndef VERSION
    #define GIT_REV "{}"
#endif
#ifndef BUILD_TIMESTAMP
    #define BUILD_TIMESTAMP "{}"
#endif
#ifndef PROGNAME
    #define PROGNAME "{}"
#endif
#ifndef GIT_BRANCH
    #define GIT_BRANCH "{}"
#endif

""".format(revision(), datetime.datetime.now().strftime("%Y%m%d_%H%M%S"),os.path.split(env.subst("$PROJECT_DIR"))[-1],branch())



if os.environ.get('PLATFORMIO_INCLUDE_DIR') is not None:
    VERSION_HEADER = os.environ.get('PLATFORMIO_INCLUDE_DIR') + os.sep + VERSION_HEADER
elif os.path.exists("include"):
    VERSION_HEADER = "include" + os.sep + VERSION_HEADER
else:
    PROJECT_DIR = env.subst("$PROJECT_DIR")
    os.mkdir(PROJECT_DIR + os.sep + "include")
    VERSION_HEADER = "include" + os.sep + VERSION_HEADER

with open(VERSION_HEADER, 'w+') as FILE:
    try:
        FILE.write(HEADER_FILE)
    except:
        print("\n%s: ERROR reading git repo information\n"%os.path.basename(__file__))
        if(os.path.exists(VERSION_HEADER)):
            os.remove(VERSION_HEADER)