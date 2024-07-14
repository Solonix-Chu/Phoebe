echo 'not for run buddy, use cat'
exit

# ------------------- Samba server -------------------
sudo apt update
sudo apt install samba

sudo nano /etc/samba/smb.conf

# add this shit:
'''
[share]
path = /home/linaro/shared
available = yes
valid users = linaro
read only = no
browsable = yes
public = yes
writable = yes
'''

sudo mkdir -p /home/linaro/shared
sudo chown -R linaro:linaro /home/linaro/shared

sudo smbpasswd -a linaro

sudo systemctl restart smbd

# ------------------- Windows Client -------------------
# \\<Linux_IP_address>\share

# ------------------- Linux Client -------------------
sudo apt update
sudo apt install smbclient cifs-utils

# mount
sudo mkdir -p /mnt/samba_share

sudo mount.cifs //server_ip/share /mnt/samba_share -o username=linaro,password=your_password
