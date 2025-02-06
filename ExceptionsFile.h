#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_EXCEPTIONSFILE_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_EXCEPTIONSFILE_H

#include <iostream>

class InvalidInputException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Errore: Input non valido!";
    }
};

class NegativeNumberException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Errore: Il numero deve essere positivo!";
    }
};

class OutOfRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Errore: Numero fuori dall'intervallo consentito!";
    }
};

class NotEnoughQuantity : public std::exception{
public:
    const char* what() const noexcept override {
        return "Errore: Il valore inserito supera la quantita' residua!";
    }
};

class OverflowDanger : public std::exception{
public:
    const char* what() const noexcept override {
        return "Errore: Il valore inserito se aggiunto alla quantita' gia' presente causerebbe un overflow della variabile";
    }
};

class FailedRemove : public std::exception{
public:
    const char* what() const noexcept override {
        return "Errore: Rimozione non avvenuta! Riprovare";
    }
};


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_EXCEPTIONSFILE_H
