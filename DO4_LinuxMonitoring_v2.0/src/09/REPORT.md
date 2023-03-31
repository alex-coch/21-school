## Part 9. Дополнительно. Свой *node_exporter*

![DO4_LinuxMonitoring_v2.0](img/9.1.png)
![DO4_LinuxMonitoring_v2.0](prometheous.yml)

##### Добавить на дашборд **Grafana** отображение ЦПУ, оперативной памяти, обьем жесткого диска.
![DO4_LinuxMonitoring_v2.0](img/9.2.png)

##### Запустить ваш bash-скрипт из Части 2
##### Посмотреть на нагрузку жесткого диска (место на диске и операции чтения/записи)
![DO4_LinuxMonitoring_v2.0](img/9.3.png)

##### Установить утилиту **stress** и запустить команду `stress -c 2 -i 1 -m 1 --vm-bytes 32M -t 10s`
##### Посмотреть на нагрузку жесткого диска, оперативной памяти и ЦПУ
![DO4_LinuxMonitoring_v2.0](img/9.4.png)
