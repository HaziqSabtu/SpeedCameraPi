import os

def isRunningWithSudo():
    return os.geteuid() == 0