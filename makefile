about:
	@echo "Crypto lab report"
	@echo "eg. make run f=title.c"

run:
	@g++ title.c -o ./output/title.out && ./output/title.out
	@g++ $(f) -o ./output/${basename}.out
	@./output/${basename}.out


dir := $(dir $(f))
filename := $(notdir $(f))
basename := $($(dir))$(basename $(filename))
