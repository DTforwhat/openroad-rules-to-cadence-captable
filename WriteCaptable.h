
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

namespace rtc{

    //ext strings for fstring per word
    class fline
    {
        private:

        public:
            std::vector<std::string> data;
            fline()             ;
            bool   isMetOVER()  ;
            int    getOVER()    ;
            int    getMetal()   ; 
            int    getDistcnt() ;
            double getWidth()   ;
            double getSpace()   ;
            double getCtot()    ;
            double getCc()      ;
            double getCarea()   ;
            double getCfrg()    ;
    };

    void write_captable(std::ifstream* ifile ,std::ofstream* ofile);
    
    void write_table(   double Width                        ,
                        double space                        ,
                        double Ctot                         ,
                        double Cc                           ,
                        double Carea                        ,
                        double Cfrg                         ,
                        std::vector<double>* captable        );

    void write_output(std::ofstream* ofile, int met , std::vector<std::vector<double>> captable);

    fline devide(std::string line);

}
