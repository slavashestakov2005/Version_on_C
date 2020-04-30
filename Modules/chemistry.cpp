#include "chemistry.h"
#include "../Lib/function.h"
#include "../Lib/functions.h"
#include "../Lib/string.h"
#include "../Lib/bignumber.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include <cmath>
#include <map>
#include <vector>
namespace{
    struct Elemnent{
        std::string name, russionRead, latinRead, electrons;
        double massa;
        int number, period, group;
        bool metal, mainGroup;
        Elemnent(int number, std::string name, std::string russionRead, std::string latinRead, std::string electrons,
                 double massa, int period, int group, bool metal, bool mainGroup) : number(number), name(name), russionRead(russionRead),
                 latinRead(latinRead), electrons(electrons), massa(massa), period(period), group(group), metal(metal), mainGroup(mainGroup) {}
    };
    const int SizeOfTabel = 54;
    Elemnent elements[SizeOfTabel] = {
        Elemnent(1, "H", "водород", "аш", "1s1", 1.00797, 1, 1, false, true),
        Elemnent(2, "He", "гелий", "гелий", "1s2", 4.0025, 1, 8, false, true),

        Elemnent(3, "Li", "литий", "литий", "2s1", 6.939, 2, 1, true, true),
        Elemnent(4, "Be", "берилий", "берилий", "2s2", 9.0122, 2, 2, true, true),
        Elemnent(5, "B", "бор", "бор", "2s22p1", 10.811, 2, 3, false, true),
        Elemnent(6, "C", "углерод", "цэ", "2s22p2", 12.01115, 2, 4, false, true),
        Elemnent(7, "N", "азот", "эн", "2s22p3", 14.0067, 2, 5, false, true),
        Elemnent(8, "O", "кислород", "о", "2s22p4", 15.9994, 2, 6, false, true),
        Elemnent(9, "F", "фтор", "эф", "2s22p5", 18.9984, 2, 7, false, true),
        Elemnent(10, "Ne", "неон", "неон", "2s22p6", 20.183, 2, 8, false, true),

        Elemnent(11, "Na", "натрий", "натрий", "3s1", 22.9898, 3, 1, true, true),
        Elemnent(12, "Mg", "магний", "магний", "3s2", 24.312, 3, 2, true, true),
        Elemnent(13, "Al", "алюминий", "алюминий", "3s23p1", 25.9815, 3, 3, true, true),
        Elemnent(14, "Si", "кремний", "силициум", "3s23p2", 28.086, 3, 4, false, true),
        Elemnent(15, "P", "фосфор", "пэ", "3s23p3", 30.9738, 3, 5, false, true),
        Elemnent(16, "S", "сера", "эс", "3s23p4", 32.064, 3, 6, false, true),
        Elemnent(17, "Cl", "хлор", "хлор", "3s23p5", 35.453, 3, 7, false, true),
        Elemnent(18, "Ar", "аргон", "аргон", "3s23p6", 39.948, 3, 8, false, true),

        Elemnent(19, "K", "калий", "кэ", "4s1", 39.102, 4, 1, true, true),
        Elemnent(20, "Ca", "кальций", "кальций", "4s2", 40.08, 4, 2, true, true),
        Elemnent(21, "Sc", "скандий", "скандий", "3d14s2", 44.956, 4, 3, true, false),
        Elemnent(22, "Ti", "титан", "титан", "3d24s2", 47.9, 4, 4, true, false),
        Elemnent(23, "V", "ванадий", "ванадий", "3d34s2", 50.942, 4, 5, true, false),
        Elemnent(24, "Cr", "хром", "хром", "3d54s1", 51.996, 4, 6, true, false),
        Elemnent(25, "Mn", "марганец", "марганец", "3d54s2", 54.938, 4, 7, true, false),
        Elemnent(26, "Fe", "железо", "ферум", "3d64s2", 55.847, 4, 8, true, false),
        Elemnent(27, "Co", "кобальт", "кобальт", "3d74s2", 58.9332, 4, 8, true, false),
        Elemnent(28, "Ni", "никель", "никель", "3d84s2", 58.71, 4, 8, true, false),

        Elemnent(29, "Cu", "медь", "купрум", "3d104s1", 63.546, 4, 1, true, false),
        Elemnent(30, "Zn", "цинк", "цинк", "3d104s2", 65.37, 4, 2, true, false),
        Elemnent(31, "Ga", "галлий", "галлий", "4s24p1", 69.72, 4, 3, true, true),
        Elemnent(32, "Ge", "германий", "германий", "4s24p2", 72.59, 4, 4, true, true),
        Elemnent(33, "As", "мышьяк", "мышьяк", "4s24p3", 74.9216, 4, 5, false, true),
        Elemnent(34, "Se", "селен", "селен", "4s24p4", 78.96, 4, 6, false, true),
        Elemnent(35, "Br", "бром", "бром", "4s24p5", 79.904, 4, 7, false, true),
        Elemnent(36, "Kr", "криптон", "криптон", "4s24p6", 83.8, 4, 8, false, true),

        Elemnent(37, "Rb", "рубидий", "рубидий", "5s1", 85.47, 5, 1, true, true),
        Elemnent(38, "Sr", "стронций", "стронций", "5s2", 87.62, 5, 2, true, true),
        Elemnent(39, "Y", "иттрий", "иттрий", "4d15s2", 88.905, 5, 3, true, false),
        Elemnent(40, "Zr", "цирконий", "йирконий", "4d25s2", 91.22, 5, 4, true, false),
        Elemnent(41, "Nb", "ниобий", "ниобий", "4d45s1", 92.906, 5, 5, true, false),
        Elemnent(42, "Mo", "молибден", "молибден", "4d55s1", 95.94, 5, 6, true, false),
        Elemnent(43, "Tc", "технеций", "технеций", "4d55s2", 99, 5, 7, true, false),
        Elemnent(44, "Ru", "рутений", "рутений", "4d75s1", 101.07, 5, 8, true, false),
        Elemnent(45, "Rh", "родий", "родий", "4d85s1", 102.905, 5, 8, true, false),
        Elemnent(46, "Pd", "палладий", "палладий", "4d105s0", 106.4, 5, 8, true, false),

        Elemnent(47, "Ag", "серебро", "аргентум", "4d105s1", 107.868, 5, 1, true, false),
        Elemnent(48, "Cd", "кадмий", "кадмий", "4d105s2", 112.4, 5, 2, true, false),
        Elemnent(49, "In", "индий", "индий", "5s25p1", 114.82, 5, 3, true, true),
        Elemnent(50, "Sn", "олово", "олово", "5s25p2", 118.69, 5, 4, true, true),
        Elemnent(51, "Sb", "сурьма", "сурьма", "5s25p3", 121.75, 5, 5, true, true),
        Elemnent(52, "Te", "теллур", "теллур", "5s25p4", 127.6, 5, 6, false, true),
        Elemnent(53, "I", "иод", "иод", "5s25p5", 126.9044, 5, 7, false, true),
        Elemnent(54, "Xe", "ксенон", "ксенон", "5s25p6", 131.3, 5, 8, false, true),

        /*Elemnent(55, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(56, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(57, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(58, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(59, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(60, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(61, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(62, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(63, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(64, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(65, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(66, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(67, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(68, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(69, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),
        Elemnent(70, "B", "бор", "бор", "2s22p1", 10.811, 2, 3),*/
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
    class Mr : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type != Values::STRING) throw TypeException("String excepted");
            std::string str = ((String*)values[0]) -> getString();
            return new BigNumber(mr(str));
        }
    };
    class Omega : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 2) throw ArgumentsMismatchException("Two argument excepted");
            if (values[0] -> type != Values::STRING) throw TypeException("String excepted in first argument");
            if (values[1] -> type != Values::STRING) throw TypeException("String excepted in second argument");
            std::string str1 = ((String*)values[0]) -> getString(), str2 = ((String*)values[1]) -> getString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            if (mr(str2) == 0) throw std::logic_error("Bad second argument");
            return new BigNumber(omega(str2, str1));
        }
    };
    class Electron : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((String*)values[0]) -> getString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new BigNumber(elements[finded].number);
        }
    };
    class Neutron : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((String*)values[0]) -> getString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new BigNumber(round(elements[finded].massa) - elements[finded].number);
        }
    };
    class RussionRead : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((String*)values[0]) -> getString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new String(elements[finded].russionRead);
        }
    };
    class LatinRead : public Function{
    public:
        Value* execute(std::vector<Value*> values){
            if (values.size() != 1) throw ArgumentsMismatchException("One argument excepted");
            if (values[0] -> type != Values::STRING) throw TypeException("String excepted in first argument");
            std::string str1 = ((String*)values[0]) -> getString();
            int finded = -1;
            for(int i = 0; i < SizeOfTabel && finded == -1; ++i) if (elements[i].name == str1) finded = i;
            if (finded == -1) throw std::logic_error("First argument not element");
            return new String(elements[finded].latinRead);
        }
    };
}
void Chemistry::init(){
    Functions::set("mr", new Mr());
    Functions::set("omega", new Omega());
    Functions::set("electron", new Electron());
    Functions::set("proton", new Electron());
    Functions::set("neutron", new Neutron());
    Functions::set("russian_read", new RussionRead());
    Functions::set("latin_read", new LatinRead());
}
