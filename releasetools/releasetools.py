"""Custom OTA commands for klte* devices with locked bootloaders"""

def FullOTA_InstallEnd(info):
  info.script.script = [cmd for cmd in info.script.script if not "boot.img" in cmd]
  info.script.script = [cmd for cmd in info.script.script if not "show_progress(0.100000, 0);" in cmd]
  info.script.AppendExtra('mount("ext4", "EMMC", "/dev/block/by-name/system", "/mnt/system");');
  info.script.AppendExtra('package_extract_file("boot.img", "/tmp/boot.img");')
  info.script.AppendExtra('assert(run_program("/sbin/sh", "/mnt/system/system/etc/dtc.sh") == 0);')
  info.script.AppendExtra('unmount("/mnt/system");');
