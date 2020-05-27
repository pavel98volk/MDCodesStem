filenames = ['./voly_processed.txt', './bible_processed.txt', './hp1_processed.txt']
with open('./processed.txt', 'w') as outfile:
    for fname in filenames:
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)
