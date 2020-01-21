import sys
lines = []
def readDic():
	with open('dictionary.txt') as dict:
		for line in dict:
			if line[0]=='/':
				idx = line.find('/',1)
				line = line[idx + 1:]
			lines.append(line.strip())

def lookWord(word):
	for v in range(0,len(lines)-1):
		if word==lines[v]:
			print(lines[v+1])
			return
	print("No result found in dictionary");

readDic()
lookWord(sys.argv[1])