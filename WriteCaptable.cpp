#include <iostream>
#include <fstream>
#include <string>
#include  "WriteCaptable.h"
#include <vector>



rtc::write_captable(ifstream* ifile ,ofstream* ofile)
{
    int met;
    rtc::fstring line();
    //read rules file line-by-line
    while(std::getline (ifile , *line.getline()))
    {

    //devide each line by words 
    fline data = line.devide ();

    if(fline.isMetOVER())
    {
        vector<vector<double>> captable;
        if (fline.getOVER() == 0)
        {
            met = data.getMetal();
            std::getline (ifile , *line.getline());
            fline data = line.devide ();
            for(int ii=0;ii<data.getDistcnt();ii++)
            {
                captable.push_bach(*(new vector<double>()));
                write_table(data.getWidth()   ,
                            data.getSpace()   ,
                            data.getCtot()    ,
                            data.getCc()      ,
                            data.getCarea()   ,
                            data.getCfrg()    ,
                            captable[ii]      ,
                            ii                );
            
            }
        }
        write_output(ofile,met,captable);
    }
    }
    return;
}


rtc::write_table(double width               , 
                 double space               , 
                 double Ctot                ,
                 double Cc                  ,
                 double Carea               ,
                 double Cfrg                ,
                 vector<double>* captable   , 
                 int ii
                 )
{
        captable[ii].push_back(width);
        captable[ii].push_back(space);
        captable[ii].push_back(Ctot);
        captable[ii].push_back(Cc);
        captable[ii].push_back(Carea);
        captable[ii].push_back(Cfrg);
}



rtc::write_output(ofstream* ofile,int met , vector<vector<double>> captable)
{
    
    
    
    return;

}