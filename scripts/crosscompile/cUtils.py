import os

def isRunningWithSudo():
    return os.geteuid() == 0

def copy_if_not_exists(source, destination):
    if not os.path.exists(destination):
        if not os.path.exists(source):
            raise Exception(f"Source file {source} does not exist")
        shutil.copyfile(source, destination)
        print(f"Copied {source} to {destination}")