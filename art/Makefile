tiles = end.png flat.png ne.png nw.png se.png start.png sw.png
small_tiles = $(patsubst %.png, %-small.png, $(tiles))

.PHONY: all
	
all: $(small_tiles)

$(small_tiles): %-small.png: %.png
	convert $< -resize 25% $@

tileset.png: $(tiles)
	montage $(tiles) -tile x1 -geometry 256x256+0+0 -background transparent tileset.png
