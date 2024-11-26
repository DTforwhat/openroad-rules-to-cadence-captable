import pymysql
import re 
import sys



###########################captable#generate#from#extraction_rules(opencx)#tool##################################
                        #author Fengwen(Stephen) Su<fengwen.su@aidatechs.com.cn#
################################################################################################################


class CaptableGen(object):

    def __init__(self, ifile_name = None, ofile_name = None):
        self.ifile_name = ifile_name
        self.ifile = None
        self.ofile_name = ofile_name
        if(ofile_name == None):
            self.ofile = sys.stdout
        
        if ifile_name == None:
            sys.stderr.write("ERROR: You aren't specfic a input file name.\n")
            sys.exit(1)
        else:
            self.open()
        self.parser()

    def parser():
        print("parsing......")
        file = open(self.ifile,r)
        try:
            line = file.readline()
            while line:
                data  = line.split()
                layer = int(data[1])
                over  = int(data[3])
                under = int(data[5])
                width = float(data[7])
                space = float(data[9])
                Cc    = float(data[11])
                GND   = float(data[13])
                Res   = float(data[17])
                LEN   = int(data[19])
                if (over != layer+1 and under != layer - 1):
                    continue
                sql   = "insert into captable(layer,over,under,width,space,Cc,GND,Res,LEN) values(%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%d)"
                cursor.execute(sql, (layer,over,under,width,space,Cc,GND,Res,LEN))
                db.commit()
        except:
            print("parsing done")

if __name__ == "__main__":
    print( '''***************** tbgen - Auto generate a testbench. *****************
Author: Fengwen(Stephen) Su <fengwen.su@aidatechs.com.cn>
License: MIT
''')
    db = pymysql.connect(host='localhost',user='root',password='',port=3306,db='tcbn65lphvt_9lmT2')

    cursor = db.cursor()

    sql = "create table if not exists captable(layer int not null, over int not null,under int not null,width float not null, space float not null, Cc float not null, GND float not null, Res float not null,LEN int not null,primary key(layer))"

    cursor.execute(sql)

    ofile_name = None
    if len(sys.argv) == 1:
        sys.stderr.write("ERROR: Input file not specified\n")
        print ("Usage: tbgen input_verilog_file_name [output_testbench_file_name]")
        sys.exit(1)
    elif len(sys.argv) == 3:
        ofile_name = sys.argv[2]
        
    tbg = TestbenchGenerator(sys.argv[1], ofile_name)



db.close()

