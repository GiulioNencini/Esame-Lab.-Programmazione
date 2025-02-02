//
// Created by Giulio Nencini on 21/01/2025.
//
//Developer::Developer(string name, string surname, unsigned int hourWork, unsigned int euroHour) : Employee(std::move(name),std::move(surname),hourWork,euroHour){}
#include "ConsumableItem.h"

ConsumableItem::ConsumableItem(std::string &name, unsigned int amount) : NormItem(name), amount(amount){}
