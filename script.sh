cd Source

g++ -c *.cpp
mv *.o ./Obj/
cd Obj
g++ *.o -o ../../fs.exe
