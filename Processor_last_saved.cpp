#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// IS = Instruction_Set
class Utility
{
private:
    map<char, string> char_to_binary; // changed
public:
    Utility(); // changed
    string to_binary_21(string s);
    string to_binary_20(string s);
    string to_binary_13(string s);
    string to_binary_12(string s);
    string to_binary_5(string s);
    string hex_to_binary(string s, int len); // changed
};

class Func_to_Instruction_Type
{
private:
    map<string, string> Func_to_Instruction;

public:
    Func_to_Instruction_Type();
    string get_IS_Type(string s);
};

class Registers
{
private:
    map<string, string> reg_to_binary;

public:
    Registers();
    string getRegister(string s);
};

class R_Type : private Registers
{
private:
    string OpCode;
    map<string, string> Func3;
    map<string, string> Func7;

public:
    R_Type();
    string get_Binary(string s, string func);
    string getOpCode();
    string getFunc3(string func);
    string getFunc7(string func);
};

class I_Type : private Registers, Utility
{
private:
    string OpCode;
    map<string, string> Func3;

public:
    I_Type();
    string get_Binary(string s, string func);
    string getOpCode();
    string getFunc3(string func);
};

class Load_Type : private Registers, Utility
{
private:
    string OpCode;
    map<string, string> Func3;

public:
    Load_Type();
    string get_Binary(string s, string func);
    string getOpCode();
    string getFunc3(string func);
};

class B_Type : private Registers, Utility
{
private:
    string OpCode;
    map<string, string> Func3;

public:
    B_Type();
    string get_Binary(string s, string func);
    string getOpCode();
    string getFunc3(string func);
};

class J_Type : private Registers, Utility
{
private:
    string OpCode;

public:
    J_Type();
    string get_Binary(string s, string func);
    string getOpCode();
};

class U_Type : private Registers, Utility
{
private:
    string OpCode;

public:
    U_Type();
    string get_Binary(string s, string func);
    string getOpCode();
};

class S_Type : private Registers, Utility
{
private:
    string OpCode;
    map<string, string> Func3;

public:
    S_Type();
    string get_Binary(string s, string func);
    string getFunc3(string func);
    string getOpCode();
};

int main()
{
    ifstream file1("Input.txt");
    ofstream file2("Output.txt");
    if (file2.is_open() == false)
    {
        cout << "Error Opening Output File.\n";
        return 0;
    }

    Func_to_Instruction_Type f_to_IS_Converter;
    R_Type R_Type_obj;
    I_Type I_Type_obj;
    B_Type B_Type_obj;
    J_Type J_Type_obj;
    U_Type U_Type_obj;
    S_Type S_Type_obj;
    Load_Type Load_Type_obj;

    string str;
    while (getline(file1, str))
    {
        if (str.length() == 0)
            continue; // changed
        for (int i = 0; i < str.length(); i++)
            str[i] = tolower(str[i]);
        string func = str.substr(0, str.find_first_of(" "));
        string type = f_to_IS_Converter.get_IS_Type(func);

        if (type == "R_Type")
        {
            cout << R_Type_obj.get_Binary(str, func) << endl;
        }
        else if (type == "I_Type")
        {
            cout << I_Type_obj.get_Binary(str, func) << endl;
        }
        else if (type == "Load_Type")
        {
            cout << Load_Type_obj.get_Binary(str, func) << endl;
        }
        else if (type == "B_Type")
        {
            cout << B_Type_obj.get_Binary(str, func) << endl;
        }
        else if (type == "J_Type")
        {
            cout << J_Type_obj.get_Binary(str, func) << endl;
        }
        else if (type == "U_Type")
        {
            cout << U_Type_obj.get_Binary(str, func) << endl;
        }
        else if (type == "S_Type")
        {
            cout << S_Type_obj.get_Binary(str, func) << endl;
        }
    }
}

// Utility -------------------------------------------------

// changed
Utility::Utility()
{
    char_to_binary = {
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'a', "1010"},
        {'b', "1011"},
        {'c', "1100"},
        {'d', "1101"},
        {'e', "1110"},
        {'f', "1111"},
    };
}

string Utility::to_binary_21(string s)
{
    int imm = stoi(s);
    string binary = bitset<21>(imm).to_string();
    return binary.substr(binary.length() - 21, binary.length());
}

string Utility::to_binary_20(string s)
{
    int imm = stoi(s);
    string binary = bitset<20>(imm).to_string();
    return binary.substr(binary.length() - 20, binary.length());
}

string Utility::to_binary_13(string s)
{
    int imm = stoi(s);
    string binary = bitset<13>(imm).to_string();
    return binary.substr(binary.length() - 13, binary.length());
}

string Utility::to_binary_12(string s)
{
    int imm = stoi(s);
    string binary = bitset<12>(imm).to_string();
    return binary.substr(binary.length() - 12, binary.length());
}

string Utility::to_binary_5(string s)
{
    int imm = stoi(s);
    string binary = bitset<5>(imm).to_string();
    return binary.substr(binary.length() - 5, binary.length());
}

// changed
string Utility::hex_to_binary(string s, int len)
{
    string res = "";
    for (int i = s.length() - 1; i >= 0; i--)
    {
        res = char_to_binary[s[i]] + res;
    }
    while (len > res.length())
    {
        res = '0' + res;
    }
    int i = 0;
    while (len < (res.length() - i))
        i++;
    return res.substr(i);
}

// Func_To_Instruction_Type ----------------------------------

Func_to_Instruction_Type::Func_to_Instruction_Type()
{
    Func_to_Instruction = {
        {"add", "R_Type"},
        {"slt", "R_Type"},
        {"sltu", "R_Type"},
        {"and", "R_Type"},
        {"or", "R_Type"},
        {"xor", "R_Type"},
        {"sll", "R_Type"},
        {"srl", "R_Type"},
        {"sub", "R_Type"},
        {"sra", "R_Type"},
        {"addi", "I_Type"},
        {"andi", "I_Type"},
        {"ori", "I_Type"},
        {"xori", "I_Type"},
        {"slli", "I_Type"},
        {"srli", "I_Type"},
        {"srai", "I_Type"},
        {"lw", "Load_Type"},
        {"lb", "Load_Type"},
        {"lh", "Load_Type"},
        {"ld", "Load_Type"},
        {"lwu", "Load_Type"},
        {"lhu", "Load_Type"},
        {"lbu", "Load_Type"},
        {"beq", "B_Type"},
        {"bne", "B_Type"},
        {"blt", "B_Type"},
        {"bge", "B_Type"},
        {"bltu", "B_Type"},
        {"bgeu", "B_Type"},
        {"jal", "J_Type"},
        {"jalr", "J_Type"},
        {"lui", "U_Type"},
        {"auipc", "U_Type"},
        {"sd", "S_Type"},
        {"sw", "S_Type"},
        {"sh", "S_Type"},
        {"sb", "S_Type"},
    };
}

string Func_to_Instruction_Type::get_IS_Type(string s)
{
    if (Func_to_Instruction.find(s) != Func_to_Instruction.end())
    {
        return Func_to_Instruction[s];
    }
    else
    {
        cout << "Error in obtaining IS" << __LINE__ << endl;
        return NULL;
    }
}

// Registers -----------------------------------------------

Registers::Registers()
{
    reg_to_binary = {
        {"x0", "00000"},
        {"x1", "00001"},
        {"x2", "00010"},
        {"x3", "00011"},
        {"x4", "00100"},
        {"x5", "00101"},
        {"x6", "00110"},
        {"x7", "00111"},
        {"x8", "01000"},
        {"x9", "01001"},
        {"x10", "01010"},
        {"x11", "01011"},
        {"x12", "01100"},
        {"x13", "01101"},
        {"x14", "01110"},
        {"x15", "01111"},
        {"x16", "10000"},
        {"x17", "10001"},
        {"x18", "10010"},
        {"x19", "10011"},
        {"x20", "10100"},
        {"x21", "10101"},
        {"x22", "10110"},
        {"x23", "10111"},
        {"x24", "11000"},
        {"x25", "11001"},
        {"x26", "11010"},
        {"x27", "11011"},
        {"x28", "11100"},
        {"x29", "11101"},
        {"x30", "11110"},
        {"x31", "11111"},
        {"zero", "00000"},
        {"ra", "00001"},
        {"sp", "00010"},
        {"gp", "00011"},
        {"tp", "00100"},
        {"t0", "00101"},
        {"t1", "00110"},
        {"t2", "00111"},
        {"s0", "01000"},
        {"fp", "01000"},
        {"s1", "01001"},
        {"a0", "01010"},
        {"a1", "01011"},
        {"a2", "01100"},
        {"a3", "01101"},
        {"a4", "01110"},
        {"a5", "01111"},
        {"a6", "10000"},
        {"a7", "10001"},
        {"s2", "10010"},
        {"s3", "10011"},
        {"s4", "10100"},
        {"s5", "10101"},
        {"s6", "10110"},
        {"s7", "10111"},
        {"s8", "11000"},
        {"s9", "11001"},
        {"s10", "11010"},
        {"s11", "11011"},
        {"t3", "11100"},
        {"t4", "11101"},
        {"t5", "11110"},
        {"t6", "11111"},
    };
}

string Registers::getRegister(string s)
{
    if (reg_to_binary.find(s) != reg_to_binary.end())
    {
        return reg_to_binary[s];
    }
    else
        return NULL;
}

// R_Type --------------------------------------------------

R_Type::R_Type()
{
    OpCode = "0110011";
    Func3 = {
        {"add", "000"},
        {"sub", "000"},
        {"and", "111"},
        {"or", "110"},
        {"xor", "100"},
        {"sll", "001"},
        {"srl", "101"},
        {"sra", "101"},
    };
    Func7 = {
        {"add", "0000000"},
        {"sub", "0100000"},
        {"and", "0000000"},
        {"or", "0000000"},
        {"xor", "0000000"},
        {"sll", "0000000"},
        {"srl", "0000000"},
        {"sra", "0100000"},
    };
}

string R_Type::getOpCode() { return OpCode; }

string R_Type::getFunc3(string func)
{
    if (Func3.find(func) != Func3.end())
        return Func3[func];
    else
    {
        cout << "Error in obtaining Func3." << __LINE__ << endl;
        return NULL;
    }
}

string R_Type::getFunc7(string func)
{
    if (Func7.find(func) != Func7.end())
        return Func7[func];
    else
    {
        cout << "Error in obtaining Func7." << __LINE__ << endl;
        return NULL;
    }
}

string R_Type::get_Binary(string s, string func)
{
    int i = s.find_first_of(" ");
    string rd = "";
    while (i < s.length() && s[i] == ' ')
        i++;
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rd += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    string rs1 = "";
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rs1 += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    string rs2 = "";
    while (i < s.length())
        rs2 += s[i++];
    rd = Registers::getRegister(rd);
    rs1 = Registers::getRegister(rs1);
    rs2 = Registers::getRegister(rs2);
    string funct3 = getFunc3(func);
    string funct7 = getFunc7(func);
    string OpCode = getOpCode();
    return funct7 + rs2 + rs1 + funct3 + rd + OpCode;
}

// I_Type
I_Type::I_Type()
{
    OpCode = "0010011";
    Func3 = {
        {"addi", "000"},
        {"andi", "111"},
        {"ori", "110"},
        {"xori", "100"},
        {"slli", "001"},
        {"srli", "101"},
        {"srai", "101"},
    };
}

string I_Type::getOpCode() { return OpCode; }

string I_Type::getFunc3(string func)
{
    if (Func3.find(func) != Func3.end())
        return Func3[func];
    else
    {
        cout << "Error in obtaining Func3." << __LINE__ << endl;
        return NULL;
    }
}

string I_Type::get_Binary(string s, string func)
{
    int i = s.find_first_of(" ");
    string rd = "";
    while (i < s.length() && s[i] == ' ')
        i++;
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rd += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    string rs1 = "";
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rs1 += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    rd = Registers::getRegister(rd);
    rs1 = Registers::getRegister(rs1);

    string Imm = "";
    if (func != "slli" && func != "srli" && func != "srai")
    {
        i = s.length();
        while (i >= 0 && s[i] == ' ')
            i--;
        int immE = i;
        while (i >= 0 && s[i] != ' ')
            i--;
        Imm = s.substr(i + 1, immE - i);
        if (Imm.length() > 1 && Imm[1] == 'x')
            Imm = Utility::hex_to_binary(Imm.substr(2), 12);
        else
            Imm = Utility::to_binary_12(Imm);
    }
    else
    {
        i = s.length();
        while (i >= 0 && s[i] == ' ')
            i--;
        int immE = i;
        while (i >= 0 && s[i] != ' ')
            i--;
        Imm = s.substr(i + 1, immE - i);
        if (Imm.length() > 1 && Imm[1] == 'x')
            Imm = Utility::hex_to_binary(Imm.substr(2), 5);
        else
            Imm = Utility::to_binary_5(Imm);
        Imm = "0000000" + Imm;
        if (func == "srai")
            Imm[1] = '1';
    }
    string funct3 = getFunc3(func);
    string OpCode = getOpCode();
    return Imm + rs1 + funct3 + rd + OpCode;
}

// Load_Type
Load_Type::Load_Type()
{
    OpCode = "0000011";
    Func3 = {
        {"lb", "000"},
        {"lh", "001"},
        {"lw", "010"},
        {"lbu", "100"},
        {"lhu", "101"}};
}

string Load_Type::getOpCode() { return OpCode; }

string Load_Type::getFunc3(string func)
{
    if (Func3.find(func) != Func3.end())
        return Func3[func];
    else
    {
        cout << "Error in obtaining Func3." << __LINE__ << endl;
        return NULL;
    }
}

string Load_Type::get_Binary(string s, string func)
{
    int i = s.find_first_of(" ");
    string rd = "";
    while (i < s.length() && s[i] == ' ')
        i++;
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rd += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    string Imm = "";
    while (i < s.length() && s[i] != '(')
        Imm += s[i++];
    if (Imm.length() > 1 && s[1] == 'x')
        Imm = Utility::hex_to_binary(Imm.substr(2), 12);
    else
        Imm = Utility::to_binary_12(Imm);
    i++;
    string rs1 = "";
    while (i < s.length() && !(s[i] == ' ' || s[i] == ',' || s[i] == ')'))
        rs1 += s[i++];

    rd = Registers::getRegister(rd);
    rs1 = Registers::getRegister(rs1);
    string funct3 = getFunc3(func);
    string OpCode = getOpCode();
    return Imm + rs1 + funct3 + rd + OpCode;
}

// B_Type
B_Type::B_Type()
{
    OpCode = "1100011";
    Func3 = {
        {"beq", "000"},
        {"bne", "001"},
        {"blt", "100"},
        {"bge", "101"},
        {"bltu", "110"},
        {"bgeu", "111"},
    };
}

string B_Type::getOpCode() { return OpCode; }

string B_Type::getFunc3(string func)
{
    if (Func3.find(func) != Func3.end())
        return Func3[func];
    else
    {
        cout << "Error in obtaining Func3." << __LINE__ << endl;
        return NULL;
    }
}

string B_Type::get_Binary(string s, string func)
{
    int i = s.find_first_of(" ");
    string rs1 = "";
    while (i < s.length() && s[i] == ' ')
        i++;
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rs1 += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    string rs2 = "";
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rs2 += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    rs1 = Registers::getRegister(rs1);
    rs2 = Registers::getRegister(rs2);
    string Imm = s.substr(i);
    if (Imm.length() > 1 && Imm[1] == 'x')
        Imm = Utility::hex_to_binary(Imm.substr(2), 13);
    else
        Imm = Utility::to_binary_13(Imm);
    string funct3 = getFunc3(func);
    string OpCode = getOpCode();
    return Imm[0] + Imm.substr(2, 6) + rs2 + rs1 + funct3 + Imm.substr(8, 4) + Imm[1] + OpCode;
}

// J_Type
J_Type::J_Type()
{
    OpCode = "1101111";
}

string J_Type::getOpCode() { return OpCode; }

string J_Type::get_Binary(string s, string func)
{
    if (func == "jalr")
    {
        int i = s.find_first_of(" ");
        string rd = "";
        while (i < s.length() && s[i] == ' ')
            i++;
        while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
            rd += s[i++];
        while (i < s.length() && (s[i] == ' ' || s[i] == ','))
            i++;
        string Imm = "";
        while (i < s.length() && s[i] != '(')
            Imm += s[i++];
        if (Imm.length() > 1 && Imm[1] == 'x')
            Imm = Utility::hex_to_binary(Imm.substr(2), 12);
        else
            Imm = Utility::to_binary_12(Imm);
        i++;
        while (i < s.length() && (s[i] == ' ' || s[i] == ','))
            i++;
        string rs1 = "";
        while (i < s.length() && !(s[i] == ' ' || s[i] == ',' || s[i] == ')'))
            rs1 += s[i++];
        rd = Registers::getRegister(rd);
        rs1 = Registers::getRegister(rs1);
        string Func3 = "000";
        OpCode[3] = '0';
        return Imm + rs1 + Func3 + rd + OpCode;
    }
    else
    {
        int i = s.find_first_of(" ");
        string rd = "";
        while (i < s.length() && s[i] == ' ')
            i++;
        while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
            rd += s[i++];
        while (i < s.length() && (s[i] == ' ' || s[i] == ','))
            i++;
        rd = Registers::getRegister(rd);
        string Imm = s.substr(i);
        if (Imm.length() > 1 && Imm[1] == 'x')
            Imm = Utility::hex_to_binary(Imm.substr(2), 21);
        else
            Imm = Utility::to_binary_21(Imm);
        string OpCode = getOpCode();
        return Imm[0] + Imm.substr(10, 10) + Imm[9] + Imm.substr(1, 8) + rd + OpCode;
    }
}

// U_Type
U_Type::U_Type()
{
    OpCode = "0110111";
}

string U_Type::getOpCode() { return OpCode; }

string U_Type::get_Binary(string s, string func)
{
    int i = s.find_first_of(" ");
    string rd = "";
    while (i < s.length() && s[i] == ' ')
        i++;
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rd += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    rd = Registers::getRegister(rd);
    string Imm = s.substr(i);
    if (Imm.length() > 1 && Imm[1] == 'x')
        Imm = Utility::hex_to_binary(Imm.substr(2), 20);
    else
        Imm = Utility::to_binary_20(Imm);

    string OpCode = getOpCode();
    return Imm + rd + OpCode;
}

// S_Type
S_Type::S_Type()
{
    OpCode = "0100011";
    Func3 = {
        {"sd", "011"},
        {"sw", "010"},
        {"sh", "001"},
        {"sb", "000"},
    };
}

string S_Type::getOpCode() { return OpCode; }

string S_Type::getFunc3(string func)
{
    if (Func3.find(func) != Func3.end())
        return Func3[func];
    else
    {
        cout << "Error in obtaining Func3." << __LINE__ << endl;
        return NULL;
    }
}

string S_Type::get_Binary(string s, string func)
{
    int i = s.find_first_of(" ");
    string rs2 = "";
    while (i < s.length() && s[i] == ' ')
        i++;
    while (i < s.length() && !(s[i] == ' ' || s[i] == ','))
        rs2 += s[i++];
    while (i < s.length() && (s[i] == ' ' || s[i] == ','))
        i++;
    string Imm = "";
    while (i < s.length() && s[i] != '(')
        Imm += s[i++];
    if (Imm.length() > 1 && Imm[1] == 'x')
        Imm = Utility::hex_to_binary(Imm.substr(2), 12);
    else
        Imm = Utility::to_binary_12(Imm);
    i++;
    string rs1 = "";
    while (i < s.length() && !(s[i] == ' ' || s[i] == ',' || s[i] == ')'))
        rs1 += s[i++];
    rs2 = Registers::getRegister(rs2);
    rs1 = Registers::getRegister(rs1);
    string funct3 = getFunc3(func);
    string OpCode = getOpCode();
    return Imm.substr(0, 7) + rs2 + rs1 + funct3 + Imm.substr(7, 5) + OpCode;
}