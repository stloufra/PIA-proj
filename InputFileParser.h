#ifndef INPUTFILEPARSER_H
#define INPUTFILEPARSER_H

class InputFileParser
{
    public:
        InputFileParser();
        virtual ~InputFileParser();

        void readFile(std::string path);
        void parse();
        std::vector<std::vector<int>> getData();

    private:
        std::vector<std::string> dataIn;
        std::vector<std::vector<int>> dataArray;
        
};

#endif // INPUTFILEPARSER_H