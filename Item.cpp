#include "Item.h"
#include <sstream>

Item::Item(std::string n, std::string desc, ItemType t, int v)
    : name(n), description(desc), type(t), value(v) {}

std::string Item::serialize() const {
    std::stringstream ss;
    ss << name << "|" << description << "|" << (int)type << "|" << value;
    return ss.str();
}

Item Item::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string name, desc;
    int type, value;
    
    std::getline(ss, name, '|');
    std::getline(ss, desc, '|');
    ss >> type;
    ss.ignore();
    ss >> value;
    
    return Item(name, desc, (ItemType)type, value);
}