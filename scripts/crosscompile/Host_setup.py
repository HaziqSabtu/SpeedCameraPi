#!/usr/bin/env python3

import os
import shutil

def run_command(command):
    os.system(command)

def install_packages():
    packages = [
        "build-essential",
        "cmake",
        "unzip",
        "gfortran",
        "gcc",
        "git",
        "bison",
        "python",
        "gperf",
        "pkg-config",
        "gdb-multiarch",
        "wget",
        "rsync",
        "g++",
        "flex",
        "texinfo",
        "gawk",
        "bison",
        "openssl",
        "pigz",
        "libncurses-dev",
        "autoconf",
        "automake",
        "tar",
        "figlet"
    ]
    for package in packages:
        run_command(f"sudo apt install -y {package}")

def create_directories():
    user = os.getenv('SUDO_USER')
    dirs = [
        f"/home/{user}/cxcmpl",
        f"/home/{user}/cxcmpl/tools",
        f"/home/{user}/cxcmpl/build",
        f"/home/{user}/cxcmpl/sysroot",
        f"/home/{user}/cxcmpl/sysroot/usr",
        f"/home/{user}/cxcmpl/sysroot/opt"
    ]
    for directory in dirs:
        run_command(f"sudo -u {user} mkdir {directory}")
        run_command(f"sudo chown -R 1000:1000 {directory}")

def download_toolchain():
    os.chdir(f"/home/{os.getenv('SUDO_USER')}/cxcmpl/tools")
    run_command("wget https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Bullseye/GCC%2010.3.0/Raspberry%20Pi%203A%2B%2C%203B%2B%2C%204/cross-gcc-10.3.0-pi_3%2B.tar.gz")
    run_command("tar xf cross-gcc-*.tar.gz")

def copy_files():
    user = os.getenv('SUDO_USER')
    source_dir = f"/home/{user}/SpeedCameraPi/scripts/crosscompile/"
    
    os.chdir(source_dir)
    
    source_file = "sysroot-relativelinks.py"
    destination_dir = f"/home/{user}/cxcmpl/"

    shutil.copy(source_file, destination_dir)
    os.chmod(f"{destination_dir}sysroot-relativelinks.py", 0o755)
    
    source_file = "PI.cmake"
    destination_dir = f"/home/{user}/cxcmpl/tools/"

    shutil.copy(source_file, destination_dir)

def main():
    run_command("sudo apt update")
    run_command("sudo apt dist-upgrade -y")
    install_packages()
    create_directories()
    os.chdir(f"/home/{os.getenv('SUDO_USER')}/cxcmpl")
    download_toolchain()
    copy_files()
    print("All required packages have been installed")

if __name__ == "__main__":
    main()