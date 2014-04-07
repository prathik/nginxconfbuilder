CC=gcc

confbuilder: src/conf-builder.c
	$(CC) -o build/$@ src/conf-builder.c

.PHONY: clean
clean: 
	rm -f build/*
