#!/usr/bin/env python3

import os
import shutil
import cUtils
import SyncWTarget as sync
import SSymlinker as link


def main():
    homePath = os.path.expanduser("~")
    cxcmplPath = f"{homePath}/cxcmpl"

    sync.syncAll(cxcmplPath)

    link.check_and_download_ssymlinker()
    link.linkAll()

    print("Done.")

if __name__ == "__main__":

    # run without sudo
    if cUtils.isRunningWithSudo():
        print("Please run this script without sudo.")
        exit()
    main()