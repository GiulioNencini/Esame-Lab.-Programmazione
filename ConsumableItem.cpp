#include "ConsumableItem.h"

ConsumableItem::ConsumableItem(string name, int amount) : NormItem(std::move(name)), amount(amount) {}

void ConsumableItem::accumulateAmount(int adding) {
    try {
        overflowPrevention(amount, adding);
        amount += adding;
    } catch (std::exception &e) {
        cerr << e.what() << endl;
        amount = std::numeric_limits<int>::max();//la variabile sarà quindi riempita fino all'orlo
    }
}
