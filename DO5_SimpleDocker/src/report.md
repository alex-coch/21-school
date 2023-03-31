## Part 1. Готовый докер

- Взять официальный докер образ с nginx и выкачать его при помощи docker pull
![pull](img/1.pull.png)

- Проверить наличие докер образа через docker images
![images](img/1.images.png)

- Запустить докер образ через docker run -d [image_id|repository]
![images](img/1.run.png)

- Проверить, что образ запустился через docker ps
![images](img/1-ps.png)

- Посмотреть информацию о контейнере через docker inspect [container_id|container_name] ![images](img/1-inspect.png)
    - размер контейнера, список замапленных портов и ip контейнера<br>
    ![images](img/1-size.png) ![images](img/1-ports.png) ![images](img/1-ip.png)

- Остановить докер образ через docker stop [container_id|container_name] и Проверить, что образ остановился через docker ps
![images](img/1-stop-ps.png)

- Запустить докер с замапленными портами 80 и 443 на локальную машину через команду run
![images](img/1-80-443.png)

- Проверить, что в браузере по адресу localhost:80 доступна стартовая страница nginx
![images](img/1-local.png)

- Перезапустить докер контейнер через docker restart [container_id|container_name] и проверить что контейнер запустился
![images](img/1-restart-ps.png)

## Part 2. Операции с контейнером.

- Прочитать конфигурационный файл nginx.conf внутри докер контейнера через команду exec
![images](img/2-read-conf.png)

- Создать на локальной машине файл nginx.conf и настроить в нем по пути /status отдачу страницы статуса сервера nginx
![images](img/2-loc-conf.png)

- Скопировать созданный файл nginx.conf внутрь докер образа через команду docker cp и Перезапустить nginx внутри докер образа через команду exec
![images](img/2-cp-reload.png)

- Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx
![images](img/2-status.png)

- Экспортировать контейнер в файл container.tar через команду export и остановить контейнер
![images](img/2-export-stop.png)

- Удалить образ через docker rmi [image_id|repository] послу удалить остановленный контейнер
![images](img/2-rm-image-contai.png)

- Импортировать контейнер обратно через команду import ![images](img/2-import.png)

- Запустить импортированный контейнер ![images](img/2-run.png)

- Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx
![images](img/2-status2.png)

## Part 3. Мини веб-сервер

- запускаем контейнер и копируем в него все нужные нам файлы ![images](img/3-run-cp.png)

- запускаем терминал контейнера __docker exec -it [container_id] bash__ и устанавлеваем нужные нам утилиты (apt-get update, apt-get install -y sudo, apt-get install -y gcc,sudo apt-get install -y libfcgi-dev, sudo apt-get install -y spawn-fcgi)

- компилируем наш мини-сервер (gcc server.c -lfcgi -o server) и запускаем сервер на порту 8080 (spawn-fcgi -p 8080 ./server)

- проверяем через браузер localhost:81 ![images](img/3-81.png)

## Part 4. Свой докер

- Собрать написанный докер образ через docker build при этом указав имя и тег и Проверить через docker images, что все собралось корректно - docker build -t image1:tag1 .
![images](img/4-build-img.png)

- Запустить собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а
![images](img/4-run.png)

- Проверить, что по localhost:80 доступна страничка написанного мини сервера
![images](img/4-local.png)

- Дописать в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx(так же как и в part 2) и Перезапустить докер образ
![images](img/4-rest.png)

- Проверить, что теперь по localhost:80/status отдается страничка со статусом nginx
![images](img/4-status.png)

## Part 5. Dockle

- Просканировать образ из предыдущего задания через dockle [image_id|repository]
![images](img/5-before.png)

- Исправить образ так, чтобы при проверке через dockle не было ошибок и предупреждений
![images](img/5-after.png)

## Part 6. Базовый Docker Compose

- Написать файл docker-compose.yml ![images](img/6-yml.png)

- показываем что нет запущенных контейнеров ![images](img/6-ps.png)

- Собрать и запустить проект с помощью команд docker-compose build
![images](img/6-build.png)

- docker-compose up ![images](img/6-up.png)

- Проверить, что в браузере по localhost:80 отдается написанная вами страничка, как и ранее
![images](img/6-local.png)