#include "chemistry.h"
#include "../Lib/function.h"
#include "../Lib/functions.h"
#include "../Value/stringvalue.h"
#include "../Value/numbervalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include <cmath>
#include <map>
#include <vector>

namespace{
    struct Element{
        std::string name, russionRead, latinRead, electrons;
        double massa;
        int number, period, group;
        bool metal, mainGroup;
        Element(int number, std::string name, std::string russionRead, std::string latinRead, std::string electrons,
                 double massa, int period, int group, bool metal, bool mainGroup) : number(number), name(name), russionRead(russionRead),
                 latinRead(latinRead), electrons(electrons), massa(massa), period(period), group(group), metal(metal), mainGroup(mainGroup) {}
    };
    const int SizeOfTabel = 72;
    Element elements[SizeOfTabel] = {
        Element(1, "H", "�������", "��", "1s1", 1.00797, 1, 1, false, true),
        Element(2, "He", "�����", "�����", "1s2", 4.0025, 1, 8, false, true),

        Element(3, "Li", "�����", "�����", "2s1", 6.939, 2, 1, true, true),
        Element(4, "Be", "�������", "�������", "2s2", 9.0122, 2, 2, true, true),
        Element(5, "B", "���", "���", "2s22p1", 10.811, 2, 3, false, true),
        Element(6, "C", "�������", "��", "2s22p2", 12.01115, 2, 4, false, true),
        Element(7, "N", "����", "��", "2s22p3", 14.0067, 2, 5, false, true),
        Element(8, "O", "��������", "�", "2s22p4", 15.9994, 2, 6, false, true),
        Element(9, "F", "����", "��", "2s22p5", 18.9984, 2, 7, false, true),
        Element(10, "Ne", "����", "����", "2s22p6", 20.183, 2, 8, false, true),

        Element(11, "Na", "������", "������", "3s1", 22.9898, 3, 1, true, true),
        Element(12, "Mg", "������", "������", "3s2", 24.312, 3, 2, true, true),
        Element(13, "Al", "��������", "��������", "3s23p1", 25.9815, 3, 3, true, true),
        Element(14, "Si", "�������", "��������", "3s23p2", 28.086, 3, 4, false, true),
        Element(15, "P", "������", "��", "3s23p3", 30.9738, 3, 5, false, true),
        Element(16, "S", "����", "��", "3s23p4", 32.064, 3, 6, false, true),
        Element(17, "Cl", "����", "����", "3s23p5", 35.453, 3, 7, false, true),
        Element(18, "Ar", "�����", "�����", "3s23p6", 39.948, 3, 8, false, true),

        Element(19, "K", "�����", "��", "4s1", 39.102, 4, 1, true, true),
        Element(20, "Ca", "�������", "�������", "4s2", 40.08, 4, 2, true, true),
        Element(21, "Sc", "�������", "�������", "3d14s2", 44.956, 4, 3, true, false),
        Element(22, "Ti", "�����", "�����", "3d24s2", 47.9, 4, 4, true, false),
        Element(23, "V", "�������", "�������", "3d34s2", 50.942, 4, 5, true, false),
        Element(24, "Cr", "����", "����", "3d54s1", 51.996, 4, 6, true, false),
        Element(25, "Mn", "��������", "��������", "3d54s2", 54.938, 4, 7, true, false),
        Element(26, "Fe", "������", "�����", "3d64s2", 55.847, 4, 8, true, false),
        Element(27, "Co", "�������", "�������", "3d74s2", 58.9332, 4, 8, true, false),
        Element(28, "Ni", "������", "������", "3d84s2", 58.71, 4, 8, true, false),

        Element(29, "Cu", "����", "������", "3d104s1", 63.546, 4, 1, true, false),
        Element(30, "Zn", "����", "����", "3d104s2", 65.37, 4, 2, true, false),
        Element(31, "Ga", "������", "������", "4s24p1", 69.72, 4, 3, true, true),
        Element(32, "Ge", "��������", "��������", "4s24p2", 72.59, 4, 4, true, true),
        Element(33, "As", "������", "������", "4s24p3", 74.9216, 4, 5, false, true),
        Element(34, "Se", "�����", "�����", "4s24p4", 78.96, 4, 6, false, true),
        Element(35, "Br", "����", "����", "4s24p5", 79.904, 4, 7, false, true),
        Element(36, "Kr", "�������", "�������", "4s24p6", 83.8, 4, 8, false, true),

        Element(37, "Rb", "�������", "�������", "5s1", 85.47, 5, 1, true, true),
        Element(38, "Sr", "��������", "��������", "5s2", 87.62, 5, 2, true, true),
        Element(39, "Y", "������", "������", "4d15s2", 88.905, 5, 3, true, false),
        Element(40, "Zr", "��������", "��������", "4d25s2", 91.22, 5, 4, true, false),
        Element(41, "Nb", "������", "������", "4d45s1", 92.906, 5, 5, true, false),
        Element(42, "Mo", "��������", "��������", "4d55s1", 95.94, 5, 6, true, false),
        Element(43, "Tc", "��������", "��������", "4d55s2", 99, 5, 7, true, false),
        Element(44, "Ru", "�������", "�������", "4d75s1", 101.07, 5, 8, true, false),
        Element(45, "Rh", "�����", "�����", "4d85s1", 102.905, 5, 8, true, false),
        Element(46, "Pd", "��������", "��������", "4d105s0", 106.4, 5, 8, true, false),

        Element(47, "Ag", "�������", "��������", "4d105s1", 107.868, 5, 1, true, false),
        Element(48, "Cd", "������", "������", "4d105s2", 112.4, 5, 2, true, false),
        Element(49, "In", "�����", "�����", "5s25p1", 114.82, 5, 3, true, true),
        Element(50, "Sn", "�����", "�����", "5s25p2", 118.69, 5, 4, true, true),
        Element(51, "Sb", "������", "������", "5s25p3", 121.75, 5, 5, true, true),
        Element(52, "Te", "������", "������", "5s25p4", 127.6, 5, 6, false, true),
        Element(53, "I", "���", "���", "5s25p5", 126.9044, 5, 7, false, true),
        Element(54, "Xe", "������", "������", "5s25p6", 131.3, 5, 8, false, true),

        Element(55, "Cs", "�����", "�����", "6s1", 132.905, 6, 1, true, true),
        Element(56, "Ba", "�����", "�����", "6s2", 137.34, 6, 2, true, true),
        Element(57, "La", "������", "������", "5d16s2", 138.81, 6, 3, true, false),
        /** ���������� **/
        /*new Element(58, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(59, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(60, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(61, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(62, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(63, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(64, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(65, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(66, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(67, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(68, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(69, "B", "���", "���", "2s22p1", 10.811, 2, 3),
        Elemnent(70, "B", "���", "���", "2s22p1", 10.811, 2, 3),*/
        Element(72, "Hf", "������", "������", "4f145d26s2", 178.49, 6, 4, true, false),
        Element(73, "Ta", "������", "������", "4f145d36s2", 180.948, 6, 5, true, false),
        Element(74, "W", "��������", "��������", "4f145d46s2", 183.85, 6, 6, true, false),
        Element(75, "Re", "�����", "�����", "4f145d56s2", 186.2, 6, 7, true, false),
        Element(76, "Os", "�����", "�����", "4f145d66s2", 190.2, 6, 8, true, false),
        Element(77, "Ir", "������", "������", "4f145d76s2", 192.2, 6, 8, true, false),
        Element(78, "Pt", "�������", "�������", "5d96s1", 195.09, 6, 8, true, false),
        Element(79, "Au", "������", "�����", "5d106s1", 196.967, 6, 1, true, false),
        Element(80, "Hg", "�����", "�����������", "5d106s2", 200.59, 6, 2, true, false),
        Element(81, "Tl", "������", "������", "6s26p1", 204.37, 6, 3, true, true),
        Element(82, "Pb", "������", "�������", "6s26p2", 207.19, 6, 4, true, true),
        Element(83, "Bi", "������", "������", "6s26p3", 208.980, 6, 5, true, true),
        Element(84, "Po", "�������", "�������", "6s26p4", 210, 6, 6, true, true),
        Element(85, "At", "�����", "�����", "6s26p5", 210, 6, 7, false, true),
        Element(86, "Rn", "�����", "�����", "6s26p6", 222, 6, 8, false, true),
    };
    std::map<std::string, int> correct(std::string str){
        int pos = 0, index = 0, koeff = 0;
        std::string element;
        std::map<std::string, int> el;
        std::vector<std::string> inBracket;
        bool openParen = false;
        while(pos < str.size() && str[pos] >= '0' && str[pos] <= '9'){
            koeff *= 10;
            koeff += str[pos] - '0';
            ++pos;
        }
        if (!koeff) koeff = 1;
        if (koeff < 0) throw std::logic_error("Minus koefficient");
        el["_"] = koeff;
        while(pos < str.size()){
            if (str[pos] >= '0' && str[pos] <= '9'){
                if (element == "") throw std::logic_error("Empty element");
                index *= 10;
                index += str[pos] - '0';
            }else if (str[pos] >= 'A' && str[pos] <= 'Z'){
                if (element != ""){
                    int finded = -1;
                    for(int i = 0; i < SizeOfTabel && finded == -1; ++i){
                        if (elements[i].name == element) finded = i;
                    }
                    if (finded == -1) throw std::logic_error("Bad element");
                    if (index == 0) index = 1;
                    el[element] += index;
                    if (openParen) inBracket.push_back(element);
                    index = 0;
                    element = "";
                }
                element += str[pos];
            }else if (str[pos] >= 'a' && str[pos] <= 'z'){
                if (element == "") throw std::logic_error("Bad element");
                element += str[pos];
            }else if (str[pos] == '('){
                if (openParen) throw std::logic_error("Two open paren");
                openParen = true;
                if (element != ""){
                    int finded = -1;
                    for(int i = 0; i < SizeOfTabel && finded == -1; ++i){
                        if (elements[i].name == element) finded = i;
                    }
                    if (finded == -1) throw std::logic_error("Bad element");
                    if (index == 0) index = 1;
                    el[element] += index;
                    index = 0;
                    element = "";
                }
            }else if (str[pos] == ')'){
                if (!openParen) throw std::logic_error("Missing open paren");
                int finded = -1;
                for(int i = 0; i < SizeOfTabel && finded == -1; ++i){
                    if (elements[i].name == element) finded = i;
                }
                if (finded == -1) throw std::logic_error("Bad element");
                if (index == 0) index = 1;
                el[element] += index;
                inBracket.push_back(element);
                element = "";
                index = 0;
                ++pos;
                while(pos < str.size() && str[pos] >= '0' && str[pos] <= '9') { index *= 10; index += str[pos] - '0'; ++pos; }
                if (!index) index = 1;
                for(int i = 0; i < inBracket.size(); ++i){
                    el[inBracket[i]] *= index;
                }
                index = 0;
                inBracket.clear();
            }
            else throw std::logic_error("Bad symbol");
            ++pos;
        }
        if (element != ""){
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i){
                if (elements[i].name == element) finded = i;
            }
            if (finded == -1) throw std::logic_error("Bad element");
            if (index == 0) index = 1;
            el[element] += index;
        }
        return el;
    }
    double mr(std::string str){
        std::map<std::string, int> element = correct(str);
        double m = 0;
        for(auto x : element){
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == x.first) finded = i;
            m += elements[finded].massa * x.second;
        }
        return m * element["_"];
    }
    double omega(std::string str, std::string findedString){
        std::map<std::string, int> element = correct(str);
        std::string el = findedString;
        int index = 0;
        for(auto x : element){
            if (x.first == el){
                index = x.second;
                break;
            }
        }
        if (!index) throw std::logic_error(str + " not contain a " + el);
        for(int i = 0; i < SizeOfTabel; ++i){
            if (elements[i].name == el) return index * elements[i].massa / mr(str);
        }
        return -1;
    }

    class Electron : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type() != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((StringValue*)values[0]) -> asString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new NumberValue(elements[finded].number);
        }
    };

    class LatinRead : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type() != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((StringValue*)values[0]) -> asString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new StringValue(elements[finded].latinRead);
        }
    };

    class Mr : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type() != Values::STRING) throw TypeException("String excepted");
            std::string str = ((StringValue*)values[0]) -> asString();
            return new NumberValue(mr(str));
        }
    };

    class Neutron : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type() != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((StringValue*)values[0]) -> asString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new NumberValue(round(elements[finded].massa) - elements[finded].number);
        }
    };

    class Omega : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw ArgumentsMismatchException("Two argument excepted");
            if (values[0] -> type() != Values::STRING) throw TypeException("String excepted in first argument");
            if (values[1] -> type() != Values::STRING) throw TypeException("String excepted in second argument");
            std::string str1 = ((StringValue*)values[0]) -> asString(), str2 = ((StringValue*)values[1]) -> asString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            if (mr(str2) == 0) throw std::logic_error("Bad second argument");
            return new NumberValue(omega(str2, str1));
        }
    };

    class RussionRead : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type() != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((StringValue*)values[0]) -> asString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new StringValue(elements[finded].russionRead);
        }
    };

    class Write : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type() != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str = ((StringValue*)values[0]) -> asString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel; ++i) if (elements[i].russionRead == str) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new StringValue(elements[finded].name);
        }
    };
}

void Chemistry::initFunctions(){
    Functions::set("electron", new Electron());
    Functions::set("latin_read", new LatinRead());
    Functions::set("mr", new Mr());
    Functions::set("neutron", new Neutron());
    Functions::set("omega", new Omega());
    Functions::set("proton", new Electron());
    Functions::set("russian_read", new RussionRead());
    Functions::set("write", new Write());
}
