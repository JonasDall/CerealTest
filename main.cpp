#include <iostream>
#include <fstream>
#include "libs/cereal/cereal.hpp"
#include "libs/cereal/archives/binary.hpp"

struct Vector{
    int x;
    int y;

    template<class Archive>
    void serialize(Archive & ar)
    {
        ar(x, y);
    }
};

class Data{
private:
    Vector m_data;

public:
    Data() = default;
    Data(int x, int y){
        m_data.x = x;
        m_data.y = y;
    }

    void print(){
        std::cout << m_data.x << ' ' << m_data.y << '\n';
    }

    template<class Archive>
    void serialize(Archive & ar)
    {
        ar(m_data);
    }
};

int main(){
    {
        std::ofstream outf{"file.bin", std::ios::binary};
        if (!outf) return 1;

        Data data(30, 40);

        cereal::BinaryOutputArchive outa(outf);

        outa(data);
    }

    {
        std::ifstream inf{"file.bin", std::ios::binary};
        if (!inf) return 1;

        Data data;

        cereal::BinaryInputArchive ina(inf);

        ina(data);

        data.print();
    }
    return 0;
}