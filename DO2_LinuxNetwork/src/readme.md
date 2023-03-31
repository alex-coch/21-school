## Отчет по проекту Linux Network
- Установлена VM Ubuntu 20.04 Server LTS 
<br>![Ubuntu 20.04 Server LTS](images/0-os.jpg) 

## Part 1. ipcalc tool
### 1.1. Сети и маски
- Сетевой адрес 192.167.38.54/13 
<br>![192.167.38.54/13](images/11-ipcalc.jpg) 
- Перевести маску 255.255.255.0 в префиксную и двоичную 
<br>![255.255.255.0](images/12-ipcalc.jpg)
- Перевести маску /15 в обычную и двоичную 
<br>![/15](images/122-ipcalc.jpg)
- Перевести маску 11111111.11111111.11111111.11110000 в обычную и префиксную 
<br>![11111111.11111111.11111111.11110000](images/123-ipcalc.jpg)
<br>	-Минимальный и максимальный хост в сети 12.167.38.4/8 
<br>![12.167.38.4/8](images/13-ipcalc.jpg)
- 11111111.11111111.00000000.00000000 
<br>![11111111.11111111.00000000.00000000](images/131-ipcalc.jpg)
- 255.255.254.0 
<br>![255.255.254.0](images/132-ipcalc.jpg)
- /4 
<br>![/4](images/133-ipcalc.jpg)

### 1.2. localhost	
- Определить доступность по ip-адресам
- 194.34.23.100 
<br>![194.34.23.100](images/1.21-ipcalc.jpg) 
- 127.0.0.2 
<br>![127.0.0.2](images/1.22-ipcalc.jpg)
- 127.1.0.1 
<br>![127.1.0.1](images/1.23-ipcalc.jpg)
- 128.0.0.1 
<br>![128.0.0.1](images/1.24-ipcalc.jpg)

### 1.3. Сетевые дипазоны и сегменты
IP-addresses:
- 10.0.0.45 
<br>![10.0.0.45](images/1.31-ipcalc.jpg) частный
- 134.43.0.2 
<br>![134.43.0.2](images/1.32-ipcalc.jpg) публичный 
- 92.168.4.2 
<br>![92.168.4.2](images/1.33-ipcalc.jpg) публичный
- 172.20.250.4 
<br>![172.20.250.4](images/1.34-ipcalc.jpg) частный
- 172.0.2.1 
<br>![172.0.2.1](images/1.35-ipcalc.jpg) публичный
- 192.172.0.1 
<br>![192.172.0.1](images/1.36-ipcalc.jpg) публичный
- 172.68.0.2 
<br>![172.68.0.2](images/1.37-ipcalc.jpg) публичный
- 172.16.255.255 
<br>![172.16.255.255](images/1.38-ipcalc.jpg) частный
- 10.10.10.10 
<br>![10.10.10.10](images/1.39-ipcalc.jpg) частный
- 192.169.168.1 
<br>![192.169.168.1](images/1.310-ipcalc.jpg) публичный

Gateways:
- Для сети 
<br>![10.10.0.0/18](images/1.311-ipcalc.jpg) 
<br>возможные gateways:
- 10.0.0.1 x
- 10.10.0.2 v 
- 10.10.10.10 v 
- 10.10.100.1 x 
- 10.10.1.255 v

## Part 2. Static routing between two machines
ip a:
- ws1 
<br>![ws1 ip](images/2.0-ip.jpg)
- ws2 
<br>![ws2 ip](images/2.02-ip.jpg)

etc/netplan/00-installer-config.yaml:
- ws1 
<br>![ws1 ip](images/2.03-ip.jpg)
- ws2 
<br>![ws2 ip](images/2.04-ip.jpg)

sudo netplan apply:
- ws1 
<br>![ws1 ip](images/2.05-ip.jpg)
- ws2 
<br>![ws2 ip](images/2.05-ip.jpg)

### 2.1 Добавление статического маршрута вручную
- ws1 
<br>![ws1](images/2.1.1-ip.jpg)
- ws2 
<br>![ws2](images/2.1.2-ip.jpg)

Ping:
- ws1 
<br>![ws1](images/2.1.3-ip.jpg)
- ws2 
<br>![ws2](images/2.1.4-ip.jpg)

## Part 3. iperf3
### 3.1 Скорость соединения
- 8 Mbps = 1 MB/s 
- 100 MB/s = 100000 Kbps 
- 1 GB/S = 1000 Mbps

### 3.2 iperf3
- ws1 
<br>![ws1](images/3.2.1-iperf3.jpg)
- ws2 
<br>![ws2](images/3.2.1-iperf3.jpg)

## Part 4. Firewall
### iptables
- ws1 etc/firewall.sh 
<br>![ws1 etc/firewall.sh](images/4.1.1-iptables.jpg)
- ws2 etc/firewall.sh 
<br>![ws2 etc/firewall.sh](images/4.1.2-iptables.jpg)
- 1я стратегия на ws1 разрешает ping, 2я на ws2 - запрещает

### nmap
- ws2 nmap 
<br>![ws2 nmap](images/4.2-nmap.jpg)

## Part 5. Static network routing
### 5.1. Конфигурация
- ws11 
<br>![ws11](images/5.1.1-stat.jpg)
- ws21 
<br>![ws21](images/5.1.2-stat.jpg)
- ws22 
<br>![ws22](images/5.1.3-stat.jpg)
- r1 
<br>![r1](images/5.1.5-stat.jpg)
- r2 
<br>![r1](images/5.1.7-stat.jpg)
- ping ws22 from ws21 
<br>![ping ws22 from ws21](images/5.1.4-stat.jpg)
- ping r1 from ws11 
<br>![ping r1 from ws11](images/5.1.6-stat.jpg)

### Part 5.2. IP forwarding
- sysctl -w net.ipv4.ip_forward=1 on r1 
<br>![r1](images/5.2.1-for.jpg)
- sysctl -w net.ipv4.ip_forward=1 on r2 
<br>![r2](images/5.2.1-for.jpg)
- /etc/sysctl.conf on r1 
<br>![r1](images/5.2.3-for.jpg)
- /etc/sysctl.conf on r2 
<br>![r2](images/5.2.3-for.jpg)

### 5.3. Default route configuration
- ws11 
<br>![ws11](images/5.3.1.jpg)
- ws21 
<br>![ws21](images/5.3.2.jpg)
- ws22 
<br>![ws22](images/5.3.3.jpg)
- Ping r2 router from ws11 
<br>![ping](images/5.3.4.jpg)
- tcpdump -tn -i eth1 
<br>![tcpdump](images/5.3.5.jpg)

### 5.4. Adding static routes
- r1 
<br>![r1](images/5.4.1.jpg)
- r2 
<br>![r2](images/5.4.2.jpg)
ip r:
- r1 
<br>![r1](images/5.4.3.jpg)
- r2 
<br>![r2](images/5.4.4.jpg)
- ip r list 10.10.0.0/[netmask] and ip r list 0.0.0.0/0 commands on ws11 
<br>![ws11](images/5.4.5.jpg)
<br>Для адреса 10.10.0.0/18 был выбран маршрут, отличный от 0.0.0.0/0, потому что маска /18 описывает маршрут к сети точнее, в отличие от маски /0

### 5.5. Making a router list
- ws1 traceroute 
<br>![ws1](images/5.4.7.jpg)
- r1 tcpdump 
<br>![r1](images/5.4.6.jpg)
- Путь строится от узла к узлу до того момента, пока не будет достигнута конечная точка. Каждый пакет проходит на своем пути определенное количество узлов, пока не достигнет своей цели. На каждом узле добавляется счетчик, который отслеживает количество пройденых узлов.
- ws1 ping 
<br>![ws1](images/5.4.8.jpg)
- r1 tcpdump 
<br>![r1](images/5.4.9.jpg)

## Part 6. Dynamic IP configuration using DHCP
- r2 /etc/dhcp/dhcpd.conf 
<br>![r2](images/6.1.jpg)
- resolv.conf 
<br>![r2](images/6.2.jpg)
- systemctl restart isc-dhcp-server 
<br>![r2](images/6.3.jpg)
- ws21 ip a 
<br>![ws21](images/6.4.jpg)
- ping ws22 from ws21 
<br>![ws21](images/6.5.jpg)
- ws11 
<br>![ws11](images/6.6.jpg)
- r1 
<br>![r1](images/6.7.jpg)
- ip a ws11 
<br>![ws11](images/6.8.jpg)
- ip a ws12 before 
<br>![ws21](images/6.9.jpg)
- ip a ws11 after 
<br>![ws21](images/6.10.jpg)
- В данном пункте используем опции: 'dhclient -r', 'dhclient -v'

## Part 7. NAT
- r1 /etc/apache2/ports.conf & service apache2 start 
<br>![r1](images/7.1.jpg)
- ws22 /etc/apache2/ports.conf & service apache2 start 
<br>![ws22](images/7.2.jpg)
- r2 
<br>![r2](images/7.3.jpg)
- ping 
<br>![r1](images/7.4.jpg)
- Allow routing of all ICMP protocol packets 
<br>![r1](images/7.5.jpg)
- ping 
<br>![r1](images/7.6.jpg)
- SNAT, DNAT 
<br>![r2](images/7.7.jpg)
- from ws22 
<br>![ws22](images/7.8.jpg)
- from r1 
<br>![r1](images/7.9.jpg)

## Part 8. SSH
- ws22 
<br>![ws22](images/8.1.jpg)
- ws21 
<br>![ws21](images/8.2.jpg)
- ws11 
<br>![ws11](images/8.3.jpg)
- ws22 
<br>![ws22](images/8.4.jpg)
- ws21 <br>![ws21](images/8.5.jpg)
