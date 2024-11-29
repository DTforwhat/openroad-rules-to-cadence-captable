
###########################captable#generate#from#extraction_rules(opencx)#tool##################################
                        #author Fengwen(Stephen) Su<fengwen.su@aidatechs.com.cn#
################################################################################################################

import pymysql
import re 
import sys


db = pymysql.connect(host='localhost',user='root',password='',port=3306,db='tcbn65lphvt_9lmT2',autocommit=True)

cursor = db.cursor()

cursor.execute("drop table captable")

sql = "create table if not exists captable(layer int not null,width float not null,space float not null,Coupling float not null,Cfrg float not null,Res float not null)"

cursor.execute(sql)


class CaptableGen(object):

    def __init__(self, ifile_name = None, ofile_name = None):
        self.ifile_name = ifile_name
        self.ifile = None
        self.ofile_name = ofile_name
        self.cnt = 0
        self.linecnt = 0
        self.LayerCount = 0
        if(ofile_name == None):
            self.ofile = sys.stdout

        if ifile_name == None:
            sys.stderr.write("ERROR: Input file not specified\n")
            sys.exit(1)
        self.file =open(self.ifile_name,'r')

        self.parser()
        self.writecaptable()

    def writesql(self,layer = 0):
        line  = self.file.readline()
        data  = line.split()
        if(data[0] == "DIST"):
            distcnt = int(data[2])
            width = float(data[4])
            for i in range(distcnt):
                line     = self.file.readline()
                data     = line.split()
                space    = float(data[0])
                Coupling = float(data[1])
                Cfrg     = float(data[2])
                Res      = float(data [3])
                sql   = "insert into captable(layer,width,space,Coupling,Cfrg,Res) values(%s,%s,%s,%s,%s,%s)"
                param = (layer,width,space,Coupling,Cfrg,Res)
                try:
                    cursor.execute(sql,param)
                    self.cnt+=1
                except pymysql.MySQLError as ex:
                        print("parsing error: %s" % ex )

    def writecaptable(self):
        sql = "select * from captable"
        cursor.execute(sql)
        curlayer  = 0
        formlayer = 0

        try:
            file = open(self.ofile_name , 'w')
            print("wirting captable......")
            file.write("BASIC_CAP_TABLE ...")
        except Exception as e:
            print("error writting captable:" % e)

        while True:
            dist = cursor.fetchone()
            if (dist == None):
                print("captable written !\ntotoal line read: %d\ntotoal wires written:%d" % (self.linecnt,  self.cnt))
                file.write("\n\nEND_BASIC_CAP_TABLE")
                break
            curlayer = dist[0]
            if(curlayer != formlayer):
                datalist = ["\n\n\n","M",str(dist[0]),"\n","Width".ljust(10),"space".ljust(10),"Cc".ljust(15),"Cfrg".ljust(15),"Res","\n"]
                file.writelines(datalist)
            datalist = [ str(dist[1]).ljust(10),str(dist[2]).ljust(10),str(dist[3]).ljust(15),str(dist[4]).ljust(15),str(dist[5]).ljust(15),'\n']
            file.writelines(datalist)
            formlayer = dist[0]


    def parser(self):
        print("parsing......")
        cnt = 0
        try:
            for line in self.file:
                self.linecnt+=1
                if(self.linecnt%1000 == 0):
                    print("%s line read" % self.linecnt)
                data  = line.split()

                if(len(data)==0):
                    continue

                if(data[0]=="LayerCount"):
                    self.LayerCount = int(data[1])
                    continue

                if(data[0] == "Metal"and len(data)>=4):
                    layer   = int(data[1])

                    if(layer == 1 and data[2] == "UNDER"):
                        undermet = int(data[3])
                        if(undermet == 2):
                            self.writesql(layer)
                        else:
                            continue

                    elif(layer == self.LayerCount and data [2] == "OVER"):
                        overmet = int(data[3])
                        if(overmet == self.LayerCount -1 ):
                            self.writesql(layer)
                        else:
                            continue

                    elif(len(data)>=6):
                        overmet = int(data[3])
                        undermet = int(data[5])
                        if(overmet == layer -1 and undermet == layer +1):
                            self.writesql(layer)
                        else:
                            continue

                    else:
                        continue

        except Exception as e:
            print("parsing error: %s" % e )

if __name__ == "__main__":
    print( '''\n\n\n***************** cpgen - Auto generate a captable. *****************
Author: Fengwen(Stephen) Su <fengwen.su@aidatechs.com.cn>
License: MIT
*********************************************************************\n
''')
    db = pymysql.connect(host='localhost',user='root',password='',port=3306,db='tcbn65lphvt_9lmT2')

    ofile_name = None
    if len(sys.argv) == 1:
        sys.stderr.write("ERROR: Input file not specified\n")
        print ("Usage: capgen input_rules_file_name [output_captable_file_name]")
        sys.exit(1)
    elif len(sys.argv) == 3:
        ofile_name = sys.argv[2]

    tbg = CaptableGen(sys.argv[1], ofile_name)


    db.close()

