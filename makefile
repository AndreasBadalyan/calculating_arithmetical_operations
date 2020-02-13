EXE:=main
S:=$(wildcard src/*.cpp)
O:=$(patsubst src/%.cpp,res/%.o,$(S))
D:=$(patsubst src/%.cpp,res/%.dep,$(S))

$(EXE): $(O)
	gcc $^ -lstdc++ -o $@

res/%.o: src/%.cpp
	#@mkdir -p res
	gcc -xc++ -c $< -o $@

res/%.dep: src/%.cpp
	@mkdir -p res
	gcc -xc++ -MM $< -MT "$@ $(patsubst res/%.dep,res/%.o,$@)" -o $@

-include $(D)

.PHONY: clean
clean: 
	rm -r res $(EXE)
