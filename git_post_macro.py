# This python file is for use with the PlatformIO build system for microcontrollers
#  call it with extra_scripts = post:git_post_macro.py in platform.ini
#
import subprocess
import os
import shutil

Import("env")

def repo():
    return subprocess.check_output(["git", "remote", "get-url", "origin"], stderr=subprocess.DEVNULL).strip().decode("utf-8").split('/')[-1]

def revision():
    return subprocess.check_output(["git", "describe", "--match=DoNotMatchTag", "--always", "--dirty"], stderr=subprocess.DEVNULL).strip().decode("utf-8")

def post_program_action(source, target, env):
    try:
        program_name = os.path.basename(target[0].get_path()).split('.')[0]
        if env['BOARD_MCU']=='rp2040':
            firmware_extension = 'uf2'
        else:
            firmware_extension = 'bin'

        SourcePath = os.path.join(env.subst("$BUILD_DIR"),program_name+'.'+firmware_extension)
        #BackupPath = os.path.join(env.subst("$PROJECT_DIR"),env.subst("$PIOENV"),firmware_extension+'_backups')
        BackupPath = os.path.join(env.subst("$PROJECT_DIR"),firmware_extension+'_backups')
        # copy Path to Path+gitHash
        if not os.path.exists(BackupPath):
            #os.mkdir(BackupPath)
            os.makedirs(BackupPath, mode=0o777, exist_ok=True)
        hashPath = os.path.join(BackupPath,repo().split('.')[0]+'_'+env.subst("$PIOENV")+'_'+revision()+'.'+firmware_extension)
        print("hashpath = ",hashPath,"\nSourcePath = ",SourcePath)
        shutil.copyfile(SourcePath, hashPath)
        print("\nFirmware saved as ", hashPath, "\n")
    except:
        print("\n########################\n%s: ERROR %s file not backed up to %s\n########################\n"%(env.subst("$PROJECT_DIR"),firmware_extension,BackupPath))
        
env.AddPostAction("$PROGPATH", post_program_action)
