FROM nginx:latest

COPY ./ser.sh /ser.sh
COPY ./server.c /server.c
COPY ./nginx.conf /etc/nginx/

RUN apt-get update && apt-get install -y gcc libfcgi-dev spawn-fcgi 

CMD sh ./ser.sh