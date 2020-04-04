# InfoPhone
<h1>Информация о телефоне</h1>
<p style="text-align: center"><h1>Linux</h1></p>
<p>Программа благодаря скрипту <ins>connectDevice.sh</ins> соединятся с устройством через ADB. После чего обращается к устройству для того что бы извлечь необходимую информацию</p>
<p>Для того что бы всё работало, надо скомпилировать программу и положить в папку release или debug файл <ins>connectDevice.sh</ins></p>

<p><img src="https://raw.githubusercontent.com/andrusha10t500/InfoPhone/master/InfoPhone.jpg" alt=""></p>

<p style="text-align: center"><h1>Windows 10</h1></p>
<p>Полезная информация для запуска программы из под Linux в Windows10 благодаря встроенной в неё Ubuntu.</p>
<p>Всё что нужно сделать:</p>
<ul>
        <li>
            Включить в дополнительных настройках консоль bash;
        </li>
        <li>
            Установить Ubuntu - я сделал это через магазин Windows;
        </li>
        <li>
            Установить какое нибудь окружение, я использовал вот эту ссылку:
            <a href="https://xakep.ru/2017/02/03/wsl-in-colors/">Ссылка</a>
        </li>
        <li>
            Далее в консоли bash нужно установить adb, qmake, make, g++. Можно это сделать командой <p ><div style="background: gray; color: black">$ sudo apt-get update && sudo apt-get upgrade && sudo apt-get install qt5-qmake android-tools-adb make g++ -y</div></p>
        </li>
        <li>
            т.к. USB - устройства не фиксируются в Windows'ком ubuntu - остаётся ловить телефон только по сети. Устройство и компьютер должны быть в одной сети.
        </li>
        <li>
            Должна выйти ошибка об авторизации в adb, если у Вас устройство показывает сообщение при подключении что то типа: "Разрешить отладку? ключ RSA..." и есть выбор - то нужно нажать ok.
            В противном случае если всё равно устройство <ins>unauthorized</ins>, то нужно вручную передать ключ RSA в андроид устройство: все ключи хранятся в файле /data/misc/adb/adb_keys, а сам ключ в компьютере в скрытой папке ~/.android/adbkey.pub
            нужно перенести ключ на телефон и сделать это командой к примеру: echo $(cat /storage/sdcard1/Download/adbkey.pub) >> /data/misc/adb/adb_keys
        </li>
        <li>
            Далее клонировать с git всё и скомпилировать:
            <u>
                <l>
                    cd
                </l>
                <l>
                    git clone https://github.com/andrusha10t500/InfoPhone.git
                </l>
                <l>
                    cd InfoPhone
                </l>
                <l>
                    qmake
                </l>
                <l>
                    make
                </l>
                <l>
                    sudo chmod 755 ./InfoPhone
                </l>
            </u>
        </li>
        <li>
            запустить приложение можно командой
            <u>
                <l>
                    ./InfoPhone
                </l>
            </u>
        </li>
</ul>
<img src="" alt="">