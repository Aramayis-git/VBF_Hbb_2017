fin1 = open("MC_Info.txt")
fout = open("Map.txt",'wr')
xsec=0
for line1 in fin1:
    name = line1.split(",")[0]
    fin2 = open("XSec.txt")
    for line2 in fin2:
	if name in line2:
	    xsec=line2.split()[1]
    fout.write('{"'+line1.split(",")[0]+'",{'+xsec+','+line1.split(",")[1].rstrip()+'}},\n')
    fin2.close()

fin1.close()
fout.close()