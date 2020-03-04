all: run

.PHONY: run
run: MainKt.class
	cd out && kotlin MainKt
	cd ..

MainKt.class: *.kt
	mkdir -p out
	kotlinc -d out/ $^

.PHONY: clean
clean:
	rm -r out
