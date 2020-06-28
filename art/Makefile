names = end flat ne nw se start sw
large_tiles = $(patsubst %, %-256x256.png, $(names))
small_tiles = $(patsubst %, %-64x64.png, $(names))

.PHONY: all
	
all: tileset-64x64.png tileset-256x256.png

tileset-64x64.png: $(small_tiles)
	montage $^ -tile x1 -geometry 64x64+0+0 -background transparent $@

tileset-256x256.png: $(large_tiles)
	montage $^ -tile x1 -geometry 256x256+0+0 -background transparent $@
