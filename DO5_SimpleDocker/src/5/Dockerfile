FROM nginx:latest

COPY ./ser.sh /ser.sh
COPY ./server.c /server.c
COPY ./nginx.conf /etc/nginx/

RUN \
apt-get update && apt-get install -y gcc libfcgi-dev spawn-fcgi && \
rm -rf /var/lib/apt/lists && \
gcc server.c -lfcgi -o server.fcgi && \
touch /var/run/nginx.pid && \
chown -R nginx:nginx /var/run/nginx.pid && \
chown -R nginx:nginx /var/log/nginx && \
chown -R nginx:nginx /var/cache/nginx && \
chown -R nginx:nginx /etc/nginx/nginx.conf && \
chown -R nginx:nginx /server.fcgi

USER nginx

HEALTHCHECK NONE

CMD sh ./ser.sh