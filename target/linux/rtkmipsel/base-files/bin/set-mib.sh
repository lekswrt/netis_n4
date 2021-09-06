#! /bin/sh
dd if=/dev/mtdblock1  of=/tmp/wlan_mib
set

ifconfig wlan0 hw ether `echo $HW_WLAN0_WLAN_ADDR | hexdump -s46  -n 6 -C /tmp/wlan_mib |  cut -c 11-27|sed 's/ /:/g'`
ifconfig wlan1 hw ether `echo $HW_WLAN1_WLAN_ADDR | hexdump -s52  -n 6 -C /tmp/wlan_mib |  cut -c 11-27|sed 's/ /:/g'`
ifconfig eth0 hw ether `echo $HW_NIC0_ADDR | hexdump -s34  -n 6 -C /tmp/wlan_mib |  cut -c 11-27|sed 's/ /:/g'`
ifconfig eth1 hw ether `echo $HW_NIC1_ADDR | hexdump -s40  -n 6 -C /tmp/wlan_mib |  cut -c 11-27|sed 's/ /:/g'`

ifconfig wlan1 up
ifconfig wlan0 up

iwpriv wlan1 set_mib pwrlevelHT40_1S_A=$(hexdump -s1673  -n 14 -C /tmp/wlan_mib | cut -c 11-50|sed 's/ //g')
iwpriv wlan1 set_mib pwrlevelHT40_1S_B=$(hexdump -s1687  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan1 set_mib pwrlevelCCK_B=$(hexdump -s1659  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan1 set_mib pwrlevelCCK_A=$(hexdump -s1645  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan1 set_mib pwrdiffHT20=$(hexdump -s1715  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan1 set_mib pwrdiffOFDM=$(hexdump -s1735  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan1 set_mib xcap=43
iwpriv wlan1 set_mib ther=38
iwpriv wlan1 set_mib pwrdiffHT40_2S=$(hexdump -s1701  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan1 set_mib regdomain=$HW_WLAN1_REG_DOMAIN
iwpriv wlan1 set_mib 2ndchoffset=2
iwpriv wlan1 set_mib use40M=2
iwpriv wlan1 set_mib shortGI20M=1
iwpriv wlan1 set_mib ldpc=1
iwpriv wlan1 set_mib ampdu=1
iwpriv wlan1 set_mib coexist=1


iwpriv wlan0 set_mib pwrdiff_40BW2S_20BW2S_A=$(hexdump -s1279  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan0 set_mib pwrdiff_40BW2S_20BW2S_B=$(hexdump -s1503  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan0 set_mib pwrdiff_20BW1S_OFDM1T_A=$(hexdump -s1265  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan0 set_mib pwrdiff_20BW1S_OFDM1T_B=$(hexdump -s1489  -n 16 -C /tmp/wlan_mib | cut -c 11-52|sed 's/ //g')
iwpriv wlan0 set_mib xcap=34
iwpriv wlan0 set_mib ther=26
iwpriv wlan0 set_mib pwrlevel5GHT40_1S_A=$(hexdump -s180  -n 16 -C /tmp/wlan_mib | cut -c 11-402|sed 's/ //g')
iwpriv wlan0 set_mib pwrlevel5GHT40_1S_B=$(hexdump -s408  -n 16 -C /tmp/wlan_mib | cut -c 11-402|sed 's/ //g')
iwpriv wlan0 set_mib regdomain=$HW_WLAN0_REG_DOMAIN
iwpriv wlan0 set_mib 2ndchoffset=2
iwpriv wlan0 set_mib use40M=2
iwpriv wlan0 set_mib shortGI20M=1
iwpriv wlan0 set_mib ldpc=1
iwpriv wlan0 set_mib ampdu=1
iwpriv wlan0 set_mib coexist=1

ifconfig wlan0 down
ifconfig wlan1 down
ifconfig wlan1 up
ifconfig wlan0 up

( sleep 25 ; /sbin/wifi ; ) &
