import tarfile
import subprocess
import shutil

# Step 1: Zip a folder with tar
def zip_folder(folder_path, output_tar):
    with tarfile.open(output_tar, 'w:gz') as tar:
        tar.add(folder_path, arcname='.')

# Step 2: Send the tar to target via SCP (SSH)
def send_tar_via_scp(output_tar, target_ip, target_path):
    scp_command = f'scp {output_tar} {target_ip}:{target_path}'
    subprocess.run(scp_command, shell=True)

# Step 3: Extract the tar on the target
def extract_tar_on_target(target_ip, target_path):
    ssh_command = f'ssh {target_ip} "tar -xzf {target_path} -C /usr/local/"'
    subprocess.run(ssh_command, shell=True)

# Define paths and credentials
home_dir = os.path.expanduser("~")

cxcmpl_path = f'{home_dir}/cxcmpl'
lib_path = f'{cxcmpl_path}/cv'
output_tar = f'{lib_path}/cv.tar'
target_ip = 'RPi0'
target_path = '~/'

# Step 1: Zip the folder
zip_folder(lib_path, output_tar)

# Step 2: Send the tar via SCP
send_tar_via_scp(output_tar, target_ip, target_path)

# Step 3: Extract the tar on the target
extract_tar_on_target(target_ip, target_path)
