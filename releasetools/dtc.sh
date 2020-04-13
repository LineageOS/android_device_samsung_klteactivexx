#!/sbin/sh
#

if getprop ro.bootloader | grep -q G870AUCU0AND7; then
  echo '[*] Locked bootloader version detected.'
  export C=/tmp/dtc_tmpdir
  mkdir -p $C
  cp /tmp/boot.img $C/boot.img
  echo '[*] Patching boot.img as necessary.'
  cat /tmp/install/bin/hack.bin $C/boot.img > $C/boot-final.img || exit 1
  echo '[*] Flashing modified boot.img to device.'
  dd if=$C/boot-final.img of=/dev/block/platform/msm_sdcc.1/by-name/boot
  rm -rf $C
else
  echo '[*] Unlocked bootloader version detected.'
  echo '[*] Flashing unmodified boot.img to device.'
  dd if=/tmp/boot.img of=/dev/block/platform/msm_sdcc.1/by-name/boot || exit 1
fi

exit 0
