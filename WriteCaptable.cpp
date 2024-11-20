#include  "include/WriteCaptable.h"


void rtc::write_captable(std::ifstream* ifile ,std::ofstream* ofile)
{
    int met;
    std::string line;
    //read rules file line-by-line
    while(std::getline (*ifile , line))
    {
        //devide each line by words 
        rtc::fline data = rtc::devide(line);

        if(data.isMetOVER())
        {
            std::vector<std::vector<double>> captable;
            if (data.getOVER() == 0)
            {
                int Width;
                Width = data.getWidth();
                met   = data.getMetal();
                std::getline (*ifile , line);
                fline data  = rtc::devide (line);
                int Distcnt = data.getDistcnt();
                for(int ii=0;ii<Distcnt;ii++)
                {
                    std::getline (*ifile , line);
                    data = rtc::devide (line);
                    captable.push_back(*(new std::vector<double>()));
                    write_table(Width             ,
                                data.getSpace()   ,
                                data.getCtot()    ,
                                data.getCc()      ,
                                data.getCarea()   ,
                                data.getCfrg()    ,
                                &captable[ii]      );
                
                }
            }
            write_output(ofile,met,captable);
        }
    }
    return;
}


void rtc::write_table(double width               , 
                      double space               , 
                      double Ctot                ,
                      double Cc                  ,
                      double Carea               ,
                      double Cfrg                ,
                      std::vector<double>* captable)
{
        captable->push_back(width);
        captable->push_back(space);
        captable->push_back(Ctot);
        captable->push_back(Cc);
        captable->push_back(Carea);
        captable->push_back(Cfrg);
}





void rtc::write_output(std::ofstream* ofile,int met , std::vector<std::vector<double>> captable)
{
    *ofile << "M" << met <<std::endl;

    *ofile << "width(um)  space(um) Ctot(Ff/um)  Cc(Ff/um)    Carea(Ff/um) Cfrg(Ff/um)"<<std::endl;

    for(int kk=0;kk<captable.size();kk++)
    {       
    *ofile<<std::fixed<<std::setprecision(4) << captable[kk][0] << "   "
                                             << captable[kk][1] << "   "
                                             << captable[kk][2] << "   "
                                             << captable[kk][3] << "   "
                                             << captable[kk][4] << "   "
                                             << captable[kk][5] << "   "<<std::endl;
    }   
    *ofile<<std::endl; 
    return;

}


rtc::fline rtc::devide(std::string line)
{
    rtc::fline curline;
    int cnt = 0;
    curline.data.push_back(*(new std::string()));
    for(int jj;jj<line.length();jj++)
    {
        if(line[jj]!=' ')
        {   
            curline.data[cnt].push_back(line[jj]);
        }
        else
        {
            curline.data.push_back(*(new std::string()));
            cnt++;
        }
    
    }

    return curline;
}

//rtc::fline
rtc::fline::fline()
{   
    data = {};
}

bool rtc::fline::isMetOVER()  
{
    if(this->data[0]=="Metal" && this->data[2]=="OVER")
        return true;
    else    
        return false;
};

int  rtc::fline::getOVER() 
{
    return std::stod(this->data[3]);
}

int  rtc::fline::getMetal()
{
    return std::stod(this->data[1]);
}

int  rtc::fline::getDistcnt() 
{
    return std::stod(this->data[2]);
}

double rtc::fline::getWidth()   
{
    return std::stod(this->data[4]);
}

double rtc::fline::getSpace()
{
    return std::stod(this->data[0]);
}

double rtc::fline::getCtot()
{
    return 2*std::stod(this->data[3]);
}


double rtc::fline::getCc()  
{
    return std::stod("0");
}  

double rtc::fline::getCarea()   
{
    return std::stod("0");
}

double rtc::fline::getCfrg()    
{
    return std::stod(this->data[3]);
}


//rtc::fline

