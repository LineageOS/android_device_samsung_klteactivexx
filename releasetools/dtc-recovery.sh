#!/system/bin/sh
#
# This leverages the dtc vulnerability created by oscardagrach
# See here for more information on the dtc vulnerability: https://github.com/oscardagrach/galaxy_s5_dev_tree_appended_bug
#

OLD_RECSHA1=$(sha1sum /dev/block/platform/msm_sdcc.1/by-name/recovery)
NEW_RECSHA1=$(sha1sum /vendor/etc/recovery.img)

if grep -E -q -e 'G870AUCU0AND7' /proc/cmdline; then
  log -t recovery "Locked bootloader version detected"
  need_dtc=1
  export C=/data/local/tmp/dtc_tmpdir
  rm -rf $C
  mkdir -p $C
else
  export C=/dev/block/platform/msm_sdcc.1/by-name/
fi

if [ "${OLD_RECSHA1}" != "${NEW_RECSHA1}" ]; then
  log -t recovery "Installing new recovery image"

  if [ $need_dtc -eq 1 ]; then
    cat /vendor/etc/hack.bin /vendor/etc/recovery.img > $C/recovery-final.img || exit 1
    dd if=$C/recovery-final.img of=/dev/block/platform/msm_sdcc.1/by-name/recovery || exit 1
  else
    dd if=/vendor/etc/recovery.img of=/dev/block/platform/msm_sdcc.1/by-name/recovery
  fi
else
  log -t recovery "Recovery image already installed"
fi

if [ $need_dtc -eq 1 ]; then
  rm -rf $C
fi

exit 0
