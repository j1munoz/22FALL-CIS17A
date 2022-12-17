#ifndef MONEY_H
#define MONEY_H

template <class T>
class Money {
    protected:
        T money;
    public:
        Money() {money = 500;}
        virtual T getMoney() const = 0;
};

#endif /* MONEY_H */
