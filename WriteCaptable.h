
#pragma once


#include <vector>
#include <string>

namespace rtc{


    class fstring
    {
    private:

    public:
        string line;
        fstring();
        fstring(string line);
        vector<string>* devide();
        double getDistcnt();
        double getWidth();
        string* getline();

    };

    //ext strings for fstring per word
    class fline
    {
        private:
            vector<string> data;


        public:
            int    getDistcnt() ;
            int    getMetal()   ;  
            double getWidth()   ;
            double getSpace()   ;
            double getCtot()    ;
            double getCc()      ;
            double getCarea()   ;
            double getCfrg()    ;
    };

    void write_captable();
    void write_table(double width , double distcnt , vector<double>* data);
    rtc::write_output(ofstream* ofile, int met , vector<vector<double>> captable);

}
