#ifndef ITENS_HPP
#define ITENS_HPP

#include <iostream>
#include <string>
#include "screensWeapons.hpp"

using namespace std;

class Itens{
    protected:
        string name;
        double resistance;
        double weight;
    public:
        Itens(string name, double resistance, double weight) : name(name), resistance(resistance), weight(weight){}
    
        const string& getName(){ 
            return name; 
        }
        const double getResistence(){ 
            return resistance; 
        }
        const double getWeight(){ 
            return weight; 
        }

        void deterioration(double deterioration_up) {
            resistance -= deterioration_up;
            if (resistance < 0) resistance = 0;
        }
        
        void toFix(double fix_up) {
            resistance += fix_up;
        }

        bool status(){ 
            return resistance > 0;
        }

};

// ___ Implementação: Amor ___
class Armor : public Itens{
    private:
        double defenseResistense;

    public:
        const double getDefenseResistense(){ 
            return defenseResistense; 
        }
        
        bool status_armor(){ 
            return resistance > 0; 
        }

};

// ___ Implementação: Equipment ___
class Equipment : public Itens{
    protected:
        double range;
        double exdamage;
        double exdefense;
    
    public:
        Equipment(string name="\0", double exdamage=0.0, double exdefense=0.0, double resistance=0.0, double weight=0.0, double range=1)
            : Itens(name, resistance, weight), range(range), exdamage(exdamage), exdefense(exdefense){}

        const string& getName(){ 
            return name; 
        }
        const double getExdamage(){ 
            return exdamage; 
        }
        const double getResistence(){ 
            return resistance; 
        }
        const double getExdefense(){ 
            return resistance; 
        }
};

// ___ Implementação: long_range ___
class LongRange : public Equipment{
    protected:
        int cargo;

    public:
        LongRange(string name, double exdamage, double exdefense, double resistance, double weight, double range, int cargo)
            : Equipment(name, exdamage, exdefense, resistance, weight, range), cargo(cargo) {}

        const double getRange(){ 
            return range; 
        }
        const int getCargo(){ 
            return cargo; 
        }

        void recharge(int cargo){
            this->cargo += cargo;
        }

        void upRange(double range){
            this->range += range;
        }

        virtual double shoot(double distance){
            if(cargo > 0){
                distance -= range;
                if(distance <= 0) return exdamage;
            }
        }
        
};

// ___ Implementação: long_range Waepons ___ 
class Bow : public LongRange{
    public:
        Bow(string name, double exdamage, double exdefense, double resistance, double weight, double range, int cargo)
            : LongRange(name, exdamage, exdefense, resistance, weight, range, cargo){}

        double shoot(double distance){
            if(cargo > 0){
                distance -= range;
                if(distance <= 0) return exdamage;
            }
        }
        void img(){
            bow();
        }
        
};

class Crossbow : public LongRange{
    public:
        Crossbow(string name, double exdamage, double exdefense, double resistance, double weight, double range, int cargo)
            : LongRange(name, exdamage, exdefense, resistance, weight, range, cargo){}

        double shoot(double distance){
            if(cargo > 0){
                distance -= range;
                if(distance <= 0) return exdamage;
            }
        }
        void img(){
            crossbow();
        }
        
};


// ___ Implementação: Short_range Waepons ___ 
//shiels:
class SquareShield : public Equipment{
    public:
        SquareShield(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            qshield();
        }
        
        
};

class Shield : public Equipment{
    public:
        Shield(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            vshield();
        }
        
        
};

//swords:
class LongSword : public Equipment{
    public:
        LongSword(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            sdsword();
        }
        
        
};

class Daggers : public Equipment{
    public:
        Daggers(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            sdaggers();
        }
        
        
};


//axes:
class SimpleAxe : public Equipment{
    public:
        SimpleAxe(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            oneaxe();
        }
        
        
};

class DoubleAxe : public Equipment{
    public:
        DoubleAxe(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            daxe();
        }
        
        
};

//others:
class Hammer : public Equipment{
    public:
        Hammer(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            hammer();
        }
        
        
};

class Lancer : public Equipment{
    public:
        Lancer(string name, double exdamage, double exdefense, double resistance, double weight, double range)
            : Equipment(name, exdamage, exdefense, resistance, weight, range){}
    
        void img(){
            slancer();
        }
        
        
};

#endif