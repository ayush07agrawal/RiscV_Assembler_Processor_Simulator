#include <bits/stdc++.h>
using namespace std;

// Size of Memory
#define MEM_SIZE 32

// Pipeline Registers ----------------------------------------------------------

class _PC
{
public:
    int TPC;
    bool stalled;
    bool valid;

    _PC()
    {
        this->TPC = 0;
        this->stalled = false;
        this->valid = true;
    }

    void print()
    {
        cout << "PC" << endl;
        cout << "TPC: " << TPC << endl;
        cout << "Stalled: " << stalled << endl;
        cout << "Valid: " << valid << endl;
    }
};

class _IFID
{
public:
    int DPC;
    int NPC;
    string IR;
    bool stalled;
    bool valid;

    _IFID()
    {
        this->DPC = 0;
        this->NPC = 0;
        this->IR = "";
        this->stalled = false;
        this->valid = false;
    }

    void print()
    {
        cout << "IFID" << endl;
        cout << "DPC: " << DPC << endl;
        cout << "NPC: " << NPC << endl;
        cout << "IR: " << IR << endl;
        cout << "Stalled: " << stalled << endl;
        cout << "Valid: " << valid << endl;
    }
};

class _IDEX
{
public:
    int JPC;
    int DPC;
    string FUNC3_30thBit;
    string IMM_Br;
    string IMM_Reg;
    string CW;
    string RS1;
    string RS2;
    string RD;
    bool stalled;
    bool valid;

    _IDEX()
    {
        this->JPC = 0;
        this->DPC = 0;
        this->FUNC3_30thBit = "";
        this->IMM_Br = "";
        this->IMM_Reg = "";
        this->CW = "";
        this->RS1 = "";
        this->RS2 = "";
        this->RD = "";
        this->stalled = false;
        this->valid = false;
    }

    void print()
    {
        cout << "IDEX" << endl;
        cout << "JPC: " << JPC << endl;
        cout << "DPC: " << DPC << endl;
        cout << "FUNC3_30thBit: " << FUNC3_30thBit << endl;
        cout << "IMM_Br: " << IMM_Br << endl;
        cout << "IMM_Reg: " << IMM_Reg << endl;
        cout << "CW: " << CW << endl;
        cout << "RS1: " << RS1 << endl;
        cout << "RS2: " << RS2 << endl;
        cout << "RD: " << RD << endl;
        cout << "Stalled: " << stalled << endl;
        cout << "Valid: " << valid << endl;
    }
};

class _EXMO
{
public:
    string CW;
    string RS2;
    string RD;
    string ALU_OUT;
    bool stalled;
    bool valid;

    _EXMO()
    {
        this->CW = "";
        this->RS2 = "";
        this->RD = "";
        this->ALU_OUT = "";
        this->stalled = false;
        this->valid = false;
    }

    void print()
    {
        cout << "EXMO" << endl;
        cout << "CW: " << CW << endl;
        cout << "RS2: " << RS2 << endl;
        cout << "RD: " << RD << endl;
        cout << "ALU_OUT: " << ALU_OUT << endl;
        cout << "Stalled: " << stalled << endl;
        cout << "Valid: " << valid << endl;
    }
};

class _MOWB
{
public:
    string CW;
    string LD_OUT;
    string RD;
    string ALU_OUT;
    bool stalled;
    bool valid;

    _MOWB()
    {
        this->CW = "";
        this->LD_OUT = "";
        this->RD = "";
        this->ALU_OUT = "";
        this->stalled = false;
        this->valid = false;
    }

    void print()
    {
        cout << "MOWB" << endl;
        cout << "CW: " << CW << endl;
        cout << "LD_OUT: " << LD_OUT << endl;
        cout << "RD: " << RD << endl;
        cout << "ALU_OUT: " << ALU_OUT << endl;
        cout << "Stalled: " << stalled << endl;
        cout << "Valid: " << valid << endl;
    }
};

// Supporting classes ----------------------------------------------------------

class Utility
{
public:
    string add(string a, string b);
    int shiftLeft(string s);
    int signExtend(string s);
    string Controller(string OpCode);
    int AluController(string Func3_30thBit, string AluOp);
    string AluUnit(int AluSelect, string RS1, string RS2);
    int safe_stoi(string s);
};

class Registers
{
    vector<string> Register_Val;
    vector<int> Reg_Curr_Writing_Cnt;

public:
    Registers();
    int check_Reg(string s);
    string Read_Reg_Value(string s);
    void Write_Reg_Value(string s, string val);
    void Lock_Reg_Curr_Writing_Cnt(string s);
    void Release_Reg_Curr_Writing_Cnt(string s);
    void Print_Vals();
    int safe_stoi(string s);
};

class DataMemory
{
    vector<string> Memory_Val;

public:
    DataMemory();
    string Read_Mem_Value(string s);
    void Write_Mem_Value(string s, string val);
    void Print_Vals();
    int safe_stoi(string s);
};

// Stages ----------------------------------------------------------------------

class Pipeline : private Utility, private DataMemory, private Registers
{
public:
    void Reg_Write(_MOWB *MOWB, Registers *Regs);
    void Mem_Access(_EXMO *EXMO, _MOWB *MOWB, DataMemory *Memory);
    void Ins_Exe(_IFID *IFID, _IDEX *IDEX, _EXMO *EXMO, _PC *PC);
    void Ins_Decode(_IFID *IFID, _IDEX *IDEX, Registers *Regs);
    void Fetch(_PC *PC, _IFID *IFID, vector<string> &Instructions);
};

int main()
{
// Assuming that we receive all the instructions in this vector of strings
#ifndef ONLINE_JUDGE
    freopen("output.txt", "w", stdout);
#endif
    vector<string> Instructions = {
        "00001111000000000000010100010011",
        "00001101000100000000010110010011",
        "00000000101101010111011000110011",
        "00000000110000000010000000100011",
        "00000000101101010110011000110011",
        "00000000110000000010001000100011",
        "00000000101101010100011000110011",
        "00000000110000000010010000100011",
        "11111111111101100100011000010011",
        "00000000110000000010011000100011",
        "00000000001001100001011000010011",
        "00000000110000000010100000100011",
        "00000000001101100101011000010011",
        "00000000110000000010101000100011",
        "01000000010001100101011000010011",
        "00000000110000000010110000100011"};

    Registers *Regs = new Registers();
    DataMemory *Memory = new DataMemory();
    _PC *PC = new _PC();
    _IFID *IFID = new _IFID();
    _IDEX *IDEX = new _IDEX();
    _EXMO *EXMO = new _EXMO();
    _MOWB *MOWB = new _MOWB();
    Pipeline *pipe1 = new Pipeline();
    bool stop = false;

    int cycleCnt = 1;

    while (!stop)
    {
        pipe1->Reg_Write(MOWB, Regs);
        pipe1->Mem_Access(EXMO, MOWB, Memory);
        pipe1->Ins_Exe(IFID, IDEX, EXMO, PC);
        pipe1->Ins_Decode(IFID, IDEX, Regs);
        pipe1->Fetch(PC, IFID, Instructions);

        if ((PC->TPC / 4) >= Instructions.size())
        {
            PC->valid = false;
        }
        else
            PC->valid = true;

        stop = !(PC->valid || IFID->valid || IDEX->valid || EXMO->valid || MOWB->valid);
        // cout << "Next PC-> " << PC->TPC << endl;
        // cout << PC->valid << " " << IFID->valid << " " << IDEX->valid << " " << EXMO->valid << " " << MOWB->valid << endl;
        // cout << "------------" << endl;

        cycleCnt++;

        cout << "Registers Values:" << endl;
        Regs->Print_Vals();
        cout << endl;
    }

    cout << "Cycle Count = " << cycleCnt << endl;

    // cout << "Registers Values:" << endl;
    // Regs->Print_Vals();
    // cout << endl;
    // cout << "Memory Values:" << endl;
    // Memory->Print_Vals();

    return 0;
}

// Utility ---------------------------------------------------------------------
string Utility::add(string a, string b)
{
    int a_int = safe_stoi(a);
    int b_int = safe_stoi(b);
    int sum = a_int + b_int;
    string sum_str = bitset<32>(sum).to_string();
    return sum_str.substr(sum_str.length() - 32, sum_str.length());
}

int Utility::shiftLeft(string s)
{
    int a_int = safe_stoi(s);
    return (a_int << 1);
}

int Utility::signExtend(string s)
{
    char c = s[0];
    while (s.length() < 32)
    {
        s = c + s;
    }
    int res = safe_stoi(s);
    return res;
}

int Utility::safe_stoi(string s)
{
    try
    {
        int num = stoi(s, nullptr, 2);
        return num;
    }
    catch (const out_of_range &e)
    {
        cerr << "Out of range error in stoi for string: " << s << endl;
        throw;
    }
}

string Utility::Controller(string OpCode)
{
    // AluOp2, AluOp1, AluOp0, RegRead, RegWrite, AluSrc, Branch, Jump, MemRead, MemWrite, Mem2Reg
    // AluSrc == 1 (Reg Value)
    // R Type
    if (OpCode == "0110011")
        return "00011100000";
    // I Type
    else if (OpCode == "0010011")
        return "00111000000";
    // Load Type
    else if (OpCode == "0000011")
        return "01011000101";
    // B Type
    else if (OpCode == "1100011")
        return "01110110000";
    // J Type (Check)
    // else if (OpCode == "1100111")
    else if (OpCode == "1101111")
        // return "10011001000"; JALR
        return "10001001000"; // JAL
    // U Type (Check)
    else if (OpCode == "0110111")
        return "10101000000";
    // S Type
    else if (OpCode == "0100011")
        return "11010000010";
}

int Utility::AluController(string Func3_30thBit, string AluOp)
{
    // 1 - Add, 2 - Sub, 3 - And, 4 - Or, 5 - Xor, 6 - Sll, 7 - Srl, 8 - Sra, 9 - Set Less Than, 10 - Nothing
    if (AluOp == "010" || AluOp == "110")
        return 1; // Load and store
    if (AluOp == "011" || AluOp == "101")
        return 10; // Branch and U Type
    if (AluOp == "100")
    {
        // Jump
        if (Func3_30thBit == "")
            return 10;
        else
            return 1;
    }
    if (AluOp == "000" || AluOp == "001")
    {
        // R Type and I Type
        if (AluOp == "000" && Func3_30thBit == "0001")
            return 2;
        if (Func3_30thBit == "1011")
            return 8;
        if (Func3_30thBit == "0000")
            return 1;
        if (Func3_30thBit == "1110")
            return 3;
        if (Func3_30thBit == "1100")
            return 4;
        if (Func3_30thBit == "1000")
            return 5;
        if (Func3_30thBit == "0010")
            return 6;
        if (Func3_30thBit == "1010")
            return 7;
    }
}

string Utility::AluUnit(int AluSelect, string RS1, string RS2)
{
    int a = ((RS1.length() > 0) ? safe_stoi(RS1) : 0);
    int b = ((RS2.length() > 0) ? safe_stoi(RS2) : 0);
    int res = 0;
    cout << a << " " << b << " " << AluSelect << endl;
    switch (AluSelect)
    {
    case 1:
    {
        res = a + b;
        break;
    }
    case 2:
    {
        res = a - b;
        break;
    }
    case 3:
    {
        res = a & b;
        break;
    }
    case 4:
    {
        res = a | b;
        break;
    }
    case 5:
    {
        res = a ^ b;
        break;
    }
    case 6:
    {
        res = a << b;
        break;
    }
    case 7:
    {
        res = a >> b;
        break;
    }
    case 8:
    { // SRA (check)
        res = a >> b;
        break;
    }
    case 9:
    {
        res = (a < b ? a : 0);
        break;
    }
    case 10:
    {
        res = (a != 0 ? a : b);
        break;
    }
    default:
    {
        cout << __LINE__ << "Invalid AluSelect..." << endl;
        break;
    }
    }
    cout << res << endl;
    string res_str = bitset<32>(res).to_string();
    return res_str.substr(res_str.length() - 32, res_str.length());
}

Registers::Registers()
{
    Register_Val.resize(32, "00000000000000000000000000000000");
    Reg_Curr_Writing_Cnt.resize(32, 0);
}

int Registers::check_Reg(string s)
{
    if (s.length() != 5)
    {
        cout << __LINE__ << "Invalid Register Value..." << endl;
        return -1;
    }
    int regInd = 0;
    int i = 4;
    while (i >= 0)
    {
        regInd += ((s[i] == '1') ? (1 << (4 - i)) : 0);
        i--;
    }
    if (regInd >= 0 && regInd < 32)
        return regInd;
    cout << __LINE__ << "Invalid Register value..." << endl;
    return -1;
}

string Registers::Read_Reg_Value(string s)
{
    int regIndex = check_Reg(s);
    if ((regIndex != -1) && (Reg_Curr_Writing_Cnt[regIndex] == 0))
        return Register_Val[regIndex];
    else
    {
        return "WAIT"; // check
    }
}

void Registers::Write_Reg_Value(string s, string val)
{
    if (val.length() != 32)
    {
        cout << __LINE__ << "Invalid value to write in the Register. Data writing failed..." << endl;
        return;
    }
    int regIndex = check_Reg(s);
    if (regIndex != -1)
    {
        Register_Val[regIndex] = val;
    }
    else
    {
        cout << __LINE__ << " Invalid Register Number. Cannot Write..." << endl;
    }
}

void Registers::Lock_Reg_Curr_Writing_Cnt(string s)
{
    int regIndex = check_Reg(s);
    if (regIndex != -1)
        Reg_Curr_Writing_Cnt[regIndex]++;
}

void Registers::Release_Reg_Curr_Writing_Cnt(string s)
{
    int regIndex = check_Reg(s);
    if (regIndex != -1 && Reg_Curr_Writing_Cnt[regIndex] == 0)
    {
        cout << __LINE__ << "No Instructions is writing to the register. Release Failed..." << endl;
        return;
    }
    if (regIndex != -1)
    {
        Reg_Curr_Writing_Cnt[regIndex]--;
    }
}

void Registers::Print_Vals()
{
    for (int i = 10; i < 13; i++)
    {
        cout << "x" << i << " -> " << safe_stoi(this->Register_Val[i]) << endl;
    }
    cout << endl;
}

int Registers::safe_stoi(string s)
{
    try
    {
        int num = stoi(s, nullptr, 2);
        return num;
    }
    catch (const out_of_range &e)
    {
        cerr << "Out of range error in stoi for string: " << s << endl;
        throw;
    }
}

DataMemory::DataMemory()
{
    Memory_Val.resize(MEM_SIZE, "00000000000000000000000000000000");
}

string DataMemory::Read_Mem_Value(string s)
{
    if (s.length() != 32)
    { // Check
        cout << __LINE__ << "Invalid Memory Data value. Data Fetching Failed..." << endl;
    }
    int regInd = 0;
    int i = 31;
    while (i >= 22)
    {
        regInd += ((s[i] == '1') ? (1 << (31 - i)) : 0);
        i--;
    }
    regInd = regInd / 4;
    if (regInd >= 0 && regInd < MEM_SIZE)
        return Memory_Val[regInd];
    else
        cout << __LINE__ << "Invalid Memory Address value. Data Fetching Failed..." << endl;
    return NULL;
}

void DataMemory::Write_Mem_Value(string s, string val)
{
    if (s.length() != 32)
    {
        cout << __LINE__ << "Invalid Memory Value. Data Fetching Failed..." << endl;
        return;
    }
    int regInd = 0;
    int i = 31;
    while (i >= 22)
    {
        regInd += ((s[i] == '1') ? (1 << (31 - i)) : 0);
        i--;
    }
    regInd = regInd / 4;
    if (regInd >= 0 && regInd < MEM_SIZE)
        Memory_Val[regInd] = val;
    else
        cout << __LINE__ << "Invalid Memory Address Value. Data Writing Failed..." << endl;
    return;
}

void DataMemory::Print_Vals()
{
    for (int i = 0; i < MEM_SIZE; i++)
    {
        cout << "Mem_" << i << "-> " << safe_stoi(this->Memory_Val[i]) << endl;
    }
    cout << endl;
}

int DataMemory::safe_stoi(string s)
{
    try
    {
        int num = stoi(s, nullptr, 2);
        return num;
    }
    catch (const out_of_range &e)
    {
        cerr << "Out of range error in stoi for string: " << s << endl;
        throw;
    }
}

// Pipeline Stages -------------------------------------------------------------

void Pipeline::Reg_Write(_MOWB *MOWB, Registers *Regs)
{
    if (!MOWB->valid)
        return;
    if (MOWB->CW[4] == '1')
    {
        if (MOWB->CW[10] == '1')
        {
            Regs->Write_Reg_Value(MOWB->RD, MOWB->LD_OUT);
        }
        else
        {
            Regs->Write_Reg_Value(MOWB->RD, MOWB->ALU_OUT);
        }
        Regs->Release_Reg_Curr_Writing_Cnt(MOWB->RD);
    }
}

void Pipeline::Mem_Access(_EXMO *EXMO, _MOWB *MOWB, DataMemory *Memory)
{
    if (MOWB->stalled)
    {
        return;
    }
    if (!EXMO->valid)
    {
        MOWB->valid = false;
        return;
    }
    if (EXMO->CW[9] == '1')
    {
        Memory->Write_Mem_Value(EXMO->ALU_OUT, EXMO->RS2);
    }
    if (EXMO->CW[8] == '1')
    {
        MOWB->LD_OUT = Memory->Read_Mem_Value(EXMO->ALU_OUT);
    }
    MOWB->ALU_OUT = EXMO->ALU_OUT;
    MOWB->CW = EXMO->CW;
    MOWB->RD = EXMO->RD;
    EXMO->stalled = false;
    MOWB->valid = true;
}

void Pipeline::Ins_Exe(_IFID *IFID, _IDEX *IDEX, _EXMO *EXMO, _PC *PC)
{
    if (EXMO->stalled)
        return;
    if (!IDEX->valid)
    {
        EXMO->valid = false;
        return;
    }
    int AluSelect = Utility::AluController(IDEX->FUNC3_30thBit, IDEX->CW.substr(0, 3));
    if (IDEX->RS1.length() != 0)
    {
        EXMO->ALU_OUT = Utility::AluUnit(AluSelect, IDEX->RS1, ((IDEX->CW[5] == '0') ? IDEX->IMM_Reg : IDEX->RS2));
    }
    else if (IDEX->CW.substr(0, 3) == "011")
    {
        // EXMO->ALU_OUT = "";
    }
    else if (IDEX->CW.substr(0, 3) == "100")
    {
        string sum_str = bitset<32>(IDEX->DPC + 4).to_string();
        EXMO->ALU_OUT = sum_str.substr(sum_str.length() - 32, sum_str.length());
    }
    else if (IDEX->CW.substr(0, 3) == "101")
    {
        // cout <<  __LINE__ << " " << IDEX->IMM_Reg << endl;
        int val = Utility::safe_stoi(IDEX->IMM_Reg);
        val = val << 12;
        string val_str = bitset<32>(val).to_string();
        EXMO->ALU_OUT = val_str.substr(val_str.length() - 32, val_str.length());
    }
    bool ALUZeroFlag = false;
    if (IDEX->RS1.length() != 0)
        ALUZeroFlag = (IDEX->RS1 == IDEX->RS2);
    EXMO->CW = IDEX->CW;
    EXMO->RS2 = IDEX->RS2;
    EXMO->RD = IDEX->RD;
    if (IDEX->CW[6] == '1' && ALUZeroFlag)
    {
        PC->TPC = Utility::shiftLeft(IDEX->IMM_Br) + IDEX->DPC;
        IDEX->valid = false;
        IFID->valid = false;
        PC->valid = false;
    }
    if (IDEX->CW[7] == '1')
    {
        PC->TPC = IDEX->JPC;
        IDEX->valid = false;
        IFID->valid = false;
        PC->valid = false;
    }
    IDEX->stalled = false;
    EXMO->valid = true;
}

void Pipeline::Ins_Decode(_IFID *IFID, _IDEX *IDEX, Registers *Regs)
{
    if (IDEX->stalled)
        return;
    if (!IFID->valid)
    {
        IDEX->valid = false;
        return;
    }
    IDEX->CW = Utility::Controller(IFID->IR.substr(25, 7));

    if (IDEX->CW.substr(0, 3) == "100")
    {
        // IDEX->JPC = IFID->NPC + Utility::signExtend(IFID->IR.substr(0, 12)); // Jalr
        IDEX->JPC = IFID->NPC + Utility::signExtend(IFID->IR[0] + IFID->IR.substr(12, 8) + IFID->IR[11] + IFID->IR.substr(1, 10) + '0'); // jal
    }
    IDEX->DPC = IFID->DPC;

    string type = IDEX->CW.substr(0, 3);
    if (type == "000")
    {
        // R Type
        IDEX->RD = IFID->IR.substr(20, 5);
        IDEX->FUNC3_30thBit = IFID->IR.substr(17, 3) + IFID->IR[1];
        IDEX->IMM_Reg = "";
        IDEX->RS2 = Regs->Read_Reg_Value(IFID->IR.substr(7, 5));
        IDEX->RS1 = Regs->Read_Reg_Value(IFID->IR.substr(12, 5));
        IDEX->IMM_Br = "";
    }
    else if (type == "001" || type == "010")
    {
        // I Type and Load Type
        IDEX->RD = IFID->IR.substr(20, 5);
        IDEX->FUNC3_30thBit = IFID->IR.substr(17, 3) + '0';
        IDEX->IMM_Reg = IFID->IR.substr(0, 12);
        if (IFID->IR.substr(17, 3) == "101" || IFID->IR.substr(17, 3) == "001")
        {
            if (IFID->IR.substr(17, 3) == "101")
                IDEX->FUNC3_30thBit[3] = IFID->IR[1];
            IDEX->IMM_Reg = IFID->IR.substr(7, 5);
        }
        IDEX->RS2 = "";
        IDEX->RS1 = Regs->Read_Reg_Value(IFID->IR.substr(12, 5));
        IDEX->IMM_Br = "";
    }
    else if (type == "011")
    {
        // Branch Type
        IDEX->RD = "";
        IDEX->FUNC3_30thBit = IFID->IR.substr(17, 3) + '0';
        IDEX->IMM_Reg = "";
        IDEX->RS2 = Regs->Read_Reg_Value(IFID->IR.substr(7, 5));
        IDEX->RS1 = Regs->Read_Reg_Value(IFID->IR.substr(12, 5));
        IDEX->IMM_Br = IFID->IR.substr(0, 1) + IFID->IR.substr(24, 1) + IFID->IR.substr(1, 6) + IFID->IR.substr(20, 4);
    }
    else if (type == "100")
    {
        // Only Jalr
        // IDEX->RD = IFID->IR.substr(20, 5);
        // IDEX->FUNC3_30thBit = IFID->IR.substr(17, 3) + '0';
        // IDEX->IMM_Reg = IFID->IR.substr(0, 12);
        // IDEX->RS2 = "";
        // IDEX->RS1 = Regs->Read_Reg_Value(IFID->IR.substr(12, 5));
        // IDEX->IMM_Br = "";

        IDEX->RD = IFID->IR.substr(20, 5);
        IDEX->FUNC3_30thBit = "";
        IDEX->IMM_Reg = "";
        IDEX->RS2 = "";
        IDEX->RS1 = "";
        IDEX->IMM_Br = "";
    }
    else if (type == "101")
    {
        // U Type
        IDEX->RD = IFID->IR.substr(20, 5);
        IDEX->FUNC3_30thBit = "";
        IDEX->IMM_Reg = IFID->IR.substr(0, 20);
        IDEX->RS2 = "";
        IDEX->RS1 = "";
        IDEX->IMM_Br = "";
    }
    else if (type == "110")
    {
        // Store Type
        IDEX->RD = "";
        IDEX->FUNC3_30thBit = IFID->IR.substr(17, 3) + '0';
        IDEX->IMM_Reg = IFID->IR.substr(0, 7) + IFID->IR.substr(20, 5);
        IDEX->RS2 = Regs->Read_Reg_Value(IFID->IR.substr(7, 5));
        IDEX->RS1 = Regs->Read_Reg_Value(IFID->IR.substr(12, 5));
        IDEX->IMM_Br = "";
    }

    if (IDEX->RS1 == "WAIT" || IDEX->RS2 == "WAIT")
    {
        IFID->stalled = true;
        IDEX->valid = false;
        return;
    }
    if (IDEX->CW[4] == '1')
    {
        Regs->Lock_Reg_Curr_Writing_Cnt(IDEX->RD);
    }
    IDEX->valid = true;
    IFID->stalled = false;
}

void Pipeline::Fetch(_PC *PC, _IFID *IFID, vector<string> &Instructions)
{
    // Here we should have done +4 for NPC but since we are using array for simulation the index will be +1 of the previous index
    if (IFID->stalled)
        return;
    if (!PC->valid)
    {
        IFID->valid = false;
        return;
    }
    IFID->DPC = PC->TPC;
    IFID->NPC = PC->TPC + 4;
    IFID->IR = Instructions[PC->TPC / 4];
    PC->TPC = IFID->NPC;
    IFID->valid = true;
}
