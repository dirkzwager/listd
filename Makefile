listd: main.o Base.o Pair.o Int.o Pnt.o Sym.o Str.o Prim.o Comp.o Spec.o Buffer.o itoa.o 
	g++ -o listd main.o Base.o Pair.o Int.o Pnt.o Sym.o Str.o Prim.o Comp.o Spec.o Buffer.o itoa.o

main.o: main.cpp
	g++ -c main.cpp

Base.o: Base.cpp Base.h
	g++ -c Base.cpp

Pair.o: Pair.cpp Pair.h
	g++ -c Pair.cpp

Int.o: Int.cpp Int.h
	g++ -c Int.cpp

Pnt.o: Pnt.cpp Pnt.h
	g++ -c Pnt.cpp

Sym.o: Sym.cpp Sym.h
	g++ -c Sym.cpp

Str.o: Str.cpp Str.h
	g++ -c Str.cpp

Prim.o: Prim.cpp Prim.h
	g++ -c Prim.cpp

Comp.o: Comp.cpp Comp.h
	g++ -c Comp.cpp

Spec.o: Spec.cpp Spec.h
	g++ -c Spec.cpp 

itoa.o: itoa.cpp itoa.h
	g++ -c itoa.cpp

Buffer.o: Buffer.cpp Buffer.h
	g++ -c Buffer.cpp

clean:
	rm -rf *.o