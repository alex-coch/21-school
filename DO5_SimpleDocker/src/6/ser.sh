#!/bin/bash

spawn-fcgi -p 8080 ./server.fcgi
nginx -g 'daemon off;'
