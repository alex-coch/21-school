#!/bin/bash

gcc server.c -lfcgi -o server.fcgi
spawn-fcgi -p 8080 ./server.fcgi
nginx -g 'daemon off;'
