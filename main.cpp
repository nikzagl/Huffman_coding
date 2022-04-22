#include <iostream>
#include "priority_queue.h"
#include<string>
#include <fstream>
#include<clocale>
void code(std::string input, std::string output, std::string codes_table)
{
    setlocale(LC_ALL, "Russian");
    const int N = 256;
    int freq[N] = { 0 };
    std::ifstream in(input);
    if (!in)
        return ;
    std::string old_text;
    std::string line;
    while (std::getline(in,line))
    {
        old_text += line;
        old_text += '\n';
    }
    old_text.pop_back();
    for (int i = 0; i < old_text.length(); i++)
    {
        freq[(unsigned char)old_text[i]]++;
    }
    node* code_tree = nullptr;
    for (int i = 0;i < N;i++)
    {
        if (freq[i])
        {
            node* new_elem = new node();
            new_elem->letter_code = i;
            new_elem->frequency = freq[i];
            new_elem->bin_code = "";
            code_tree = add_in_priority(code_tree, new_elem);
        }
    }
    code_tree = make_tree_from_list(code_tree);
    std::string* codes = new std::string[256];
    int BIT8 = 8;
    get_code(code_tree, codes);
    std::string binary_code;
    for (int i = 0;i < old_text.length();i++)
    {
        binary_code += codes[(unsigned char)old_text[i]];
    }
    for (int i = 0;i < BIT8;i++)
    {
        binary_code += "0";
    }
    typedef union bit2char {
        char symb;
        struct bit {
            unsigned b1 : 1;
            unsigned b2 : 1;
            unsigned b3 : 1;
            unsigned b4 : 1;
            unsigned b5 : 1;
            unsigned b6 : 1;
            unsigned b7 : 1;
            unsigned b8 : 1;
        }mbit;
    }BIT2CHAR;
    int count = (binary_code.length()-8) / BIT8 + 1;
    BIT2CHAR symb;
    char *res=new char[count];
    for (int i = 0; i < count; ++i)
    {
        symb.mbit.b1 = binary_code[i * BIT8 + 0];
        symb.mbit.b2 = binary_code[i * BIT8 + 1];
        symb.mbit.b3=  binary_code[i * BIT8 + 2];
        symb.mbit.b4 = binary_code[i * BIT8 + 3];
        symb.mbit.b5 = binary_code[i * BIT8 + 4];
        symb.mbit.b6 = binary_code[i * BIT8 + 5];
        symb.mbit.b7 = binary_code[i * BIT8 + 6];
        symb.mbit.b8 = binary_code[i * BIT8 + 7];
        res[i]=symb.symb;
    }
    std::ofstream out;
    std::ofstream codes_file;
    out.open(output,std::ofstream::binary);
    codes_file.open(codes_table,std::ofstream::binary);
    codes_file.put((unsigned char)(8 - binary_code.length() % 8+'0'));
    for (int i = 0;i < 256;i++)
    {
        if (codes[i] != "") {
            codes_file.put('\n');
            codes_file.put((unsigned char) i);
            codes_file.put('\n');
            for (int j = 0; j < codes[i].length(); j++)
                codes_file.put(codes[i][j]);
        }
    }
    codes_file.put('\n');
    out.write(res,count);
    out.close();
    codes_file.close();
}
void decode(std::string input, std::string output, std::string codes_table)
{
    setlocale(LC_ALL, "Russian");
    std::ifstream codes_file(codes_table,std::ifstream::binary);
    std::ofstream out(output,std::ifstream::binary);
    std::string codes[256]={""};
    char temp,letter,elem;
    codes_file.get(temp);
    int null_length=(int)(temp-'0');
    codes_file.get(temp);
    while (true)
    {
        if(codes_file.get(temp))
        letter=temp;
        else break;
        codes_file.get(temp);
        while (true)
        {
           codes_file.get(temp);
           if (temp!='\n')
               codes[(unsigned char)letter]+=temp;
           else break;
           }
        }
    std::ifstream in(input, std::ifstream::binary) ;
    in.seekg(0,in.end);
    long size=in.tellg();
    in.seekg(0,in.beg);
    char * old_text=new char[size];
    in.read(old_text,size);
    std::string code;
    for (int i = 0;i < size;i++) {
        int number = (unsigned char) old_text[i];
        for (int j = 0; j < 8; j++) {
            code += std::to_string(number % 2);
            number /= 2;
        }
    }
    while (code.length() > null_length)
    {
        for (int i = 0;i < 256;i++)
        {
            if (codes[i] != "")
            {
                int current_length = codes[i].length();
                if ((code.substr(0, current_length) == codes[i])&&(code.length()>null_length))
                {

                    code.erase(0, current_length);
                    out.put((unsigned char)i);
                }
            }
        }
    }
   out.close();
}
int main() {
    while (true)
    {
        std::cout<<"Input a command,1 -code,2-decode,0-exit\n";
        int choice;
        std::cin >> choice;
        if (choice != 0)
        {
            std::cout << "Input a input file\n";
            std::string input, output, codes_table;
            std::cin >> input;
            std::cout << "Input an output file\n";
            std::cin >> output;
            std::cout << "Input a codes table file\n";
            std::cin >> codes_table;
            if (choice == 1)
                code(input, output, codes_table);
            else
                decode(input, output, codes_table);
        }
        else
            break;
    }
}