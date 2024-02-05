#!/bin/bash

set -e

SIZES="
16,16x16
32,16x16@2x
32,32x32
64,32x32@2x
128,128x128
256,128x128@2x
256,256x256
512,256x256@2x
512,512x512
1024,512x512@2x
"

SVG="$1"
BASE=$(basename "$SVG" | sed 's/\.[^\.]*$//')
ICONSET="$3/$BASE.iconset"
mkdir -p "$ICONSET"
mkdir -p "$2"
for PARAMS in $SIZES; do
    SIZE=$(echo $PARAMS | cut -d, -f1)
    LABEL=$(echo $PARAMS | cut -d, -f2)
    convert -background none -density 600 "$SVG" -resize "${SIZE}x${SIZE}" "$ICONSET"/icon_$LABEL.png
done

iconutil -o "$2/$BASE.icns" -c icns "$ICONSET"
