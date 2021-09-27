cd Source
ls
for file in *.cpp; do
	g++ -c ${file}
done;
a = ""
for file in *.o:
	a += ${file} + " "

g++ a -o fs.exe

