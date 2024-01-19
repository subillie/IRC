#!/bin/bash
inspircd --runasroot --nofork &

sleep 3

echo ""
echo ""
echo "---------------- start debugging ----------------"
echo ""
echo ""

tcpflow -i lo port 6667 -c