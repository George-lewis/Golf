all: run

.PHONY: run
run: out/MainKt.class
	cd out && kotlin MainKt
	cd ..

out/MainKt.class: *.kt
	mkdir -p out
	kotlinc -d out/ $^

.PHONY: clean
clean:
	rm -r out
