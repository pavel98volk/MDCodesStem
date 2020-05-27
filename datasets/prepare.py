import string;
import re;
file_name = "voly"
with open("./"+file_name+".txt", "r") as inp:
    with open("./"+file_name+"_processed.txt", "w") as out:
        n = 0
        for line in inp:
            n+=1
            line = line.lower()
            line = line.translate(str.maketrans('', '', string.punctuation+"0123456789"))
            line = line.replace("\n", " ")
            line = re.sub("\s+", " ", line)
            out.write(line)
