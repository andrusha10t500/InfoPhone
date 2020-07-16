#!/bin/bash
#cd ~/InfoPhone
if [ ! -d "SMS" ] 
then mkdir SMS
fi
DBContacts=$(adb shell su -c find /data/ -name contacts2.db)
DBSMS=$(adb shell su -c find /data/ -name mmssms.db)
#adb shell su -c cp $DBContacts /storage/sdcard1/Download/SMS/
adb shell su -c cp /data/data/com.android.providers.contacts/databases/contacts2.db /storage/sdcard1/Download/SMS/
#adb shell su -c cp $DBSMS /storage/sdcard1/Download/SMS/
adb shell su -c cp /data/user_de/0/com.android.providers.telephony/databases/mmssms.db /storage/sdcard1/Download/SMS/
adb pull /storage/sdcard1/Download/SMS ./SMS/
